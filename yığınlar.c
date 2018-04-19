#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define MAX 20

void push(int *yigin, int *tepe, int yeni);
int pop(int *yigin, int *tepe);
int tepe_eleman(int *yigin, int tepe);
int bos_mu(int tepe);
int oncelik_bul(char karakter);
void ortaek_sonek_donustur(char *ortaek, char *sonek);
int hesapla(char *sonek);

int main()
{
    char ortaek[MAX], sonek[MAX];

    printf("Ortaek ifadeyi giriniz: ");
    scanf("%s",ortaek);

    ortaek_sonek_donustur(ortaek,sonek);

    printf("Girilen ortaek ifadenin sonek ifadeye cevrilmis hali: %s\n",sonek);

    printf("Girilen ifadenin sonucu: %d\n",hesapla(sonek));

    return 0;
}

void push(int *yigin, int *tepe, int yeni)
{
    //hem donusturme hem hesaplamada ayni push fonksiyonu (tamsayi ekleyen) kullaniliyor
    //donusturme isleminde yigina ekleme yapilirken karakterin ascii kodu eklenmektedir
    if(*tepe==MAX-1)
        printf("yigin dolu!\n");
    else
    {
        *tepe=*tepe+1;
        yigin[*tepe]=yeni;
    }

    return;
}

int pop(int *yigin, int *tepe)
{
    //hem donusturme hem hesaplamada ayni pop fonksiyonu (tamsayi donduren) kullaniliyor
    //donusturme isleminde yigindan cikarilan sayi karaktere cevrilerek kullanilmaktadir.
    int gecici;

    gecici=yigin[*tepe];
    *tepe=*tepe-1;

    return gecici;
}

int tepe_eleman(int *yigin, int tepe)//tepedeki elemani dondur ama yigindan cikarma
{
    return yigin[tepe];
}

int bos_mu(int tepe)
{
    return tepe==-1;//yigin bossa dogru(1) bos degilse yanlis(0) dondur
}

int oncelik_bul(char karakter)
{
    int oncelik=3;// */+- disindaki tum karakterler icin

    switch (karakter)
    {
        case '*': case '/': oncelik=2; break;
        case '+': case '-': oncelik=1; break;
    }

    return oncelik;
}

void ortaek_sonek_donustur(char *ortaek, char *sonek)
{
    int yigin[MAX];//yiginda karakterlerin ascii kodu saklanacak...
    int tepe=-1;
    int i,j=0;

    push(yigin,&tepe,ortaek[0]);//ilk karakter direk yigina ekleniyor
    for(i=1;ortaek[i]!='\0';i++)//ortaek ifadenin sonuna kadar...
    {
        //yigin bos degilse ve tepedeki elemanin onceligi eldekinin onceligine esit
        //ya da daha buyuk ise onu yigindan cikar ve sonek ifadenin sonuna ekle
        while(!bos_mu(tepe) && oncelik_bul(tepe_eleman(yigin,tepe))>=oncelik_bul(ortaek[i]))
        {
            sonek[j]=pop(yigin,&tepe);
            j++;
        }
        push(yigin,&tepe,ortaek[i]);//eldekini yigina ekle
    }

    //yiginda kalanlari sonek ifadeye ekle
    while(!bos_mu(tepe))
    {
        sonek[j]=pop(yigin,&tepe);
        j++;
    }

    sonek[j]='\0';//sonek ifade, string haline getiriliyor

    return;
}

int hesapla(char *sonek)
{
    int yigin[MAX];
    int tepe=-1;
    int i,sayi,operand1,operand2;

    for(i=0;sonek[i]!='\0';++i)
    {
        if(isdigit(sonek[i]))//karakter, rakam ise...
        {
            sayi=sonek[i]-48;//sayiya donustur(0-9 arasi rakamlarin ascii kodlari 48-57 arasinda
            push(yigin,&tepe,sayi);//ve yigina ekle
        }
        else
            if(isalpha(sonek[i]))//karakter, harf ise...
            {
                printf("%c nin degerini giriniz(tamsayi): ",sonek[i]);
                scanf("%d",&sayi);//kullanicidan degiskenin degerini al
                push(yigin,&tepe,sayi);//ve yigina ekle
            }
            else//karakter, bir islem operatoru ise...
            {
                operand2=pop(yigin,&tepe);//ikinci operandi yigindan cikar
                operand1=pop(yigin,&tepe);//ilk operandi yigindan cikar

                switch(sonek[i])//islemi yap ve sonucunu yigina ekle
                {
                    case '*': push(yigin,&tepe,operand1*operand2); break;
                    case '/': push(yigin,&tepe,operand1/operand2); break;//tam bolme yapiliyor!
                    case '+': push(yigin,&tepe,operand1+operand2); break;
                    case '-': push(yigin,&tepe,operand1-operand2); break;
                }
            }
     }

    return pop(yigin,&tepe);//yiginda kalan son eleman sonek ifadenin sonucudur
}
