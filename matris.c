#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#define m 10     //max sütun sayisi
#define n 10     //max satir sayisi
int kontrol(int [][m], char [][m],int,int);
void gizli_resmi_goster(int [][m],int,int);
void sutunlardaki_1_sayisi(int [][m],int,int);
void satirlardaki_1_sayisi(int [][m],int,int);
int main()
{
    static char kare[n][m];             //üzerinde isaretleme yapilacak matris
    int satir, sutun,sutun_yeni, satir_yeni,isaretleme_kodu;
    int matris[n][m];                   //dosyadan alinan verilerle olusturulan matris(gizli resim)
    int sayi1,sayi2;                    //dosyadan alinan matrisin, sirasiyla satir ve sütun sayilari
    int sayac_oyun;                     //veri girisini bitirmek üzere,do-while döngüsünden çikmaya yarayan sayaç
    int i,j;                            //for döngülerinde kullanilmak üzere olusturdugumuz degiskenler
    char ascii_219;
    FILE *cfPtr;                        //dosya çagiran pointer
    ascii_219=219;                      //219 kodlu karakteri, iflerin içinde sorunsuz kullanmak için degiskene atadik

    system("color F0");
    cfPtr = fopen("resim.txt.txt", "r");        //resim.txt.txt dosyasi, okunmak üzere açiliyor
    fscanf(cfPtr ,"%d %d",&sayi1, &sayi2 );     //ilk satirdaki,satir-sütun degerleri aliniyor
    printf("\t\t<<<<<Kare Karalamaca Oyununa Hosgeldiniz>>>>>\n");
    for(i=0; i<n; i++)
        for(j=0; j<m; j++)
            kare[i][j]='O';
            for(i=0; i<sayi1; i++)
        {
            if(i==0)                                    //satirlara numara verilen kisim
            {
                printf("\t\t\t  ");
                for(j=1; j<=sayi2; j++)
                {
                    if(j==10)
                        printf(" %2d",j);
                    else
                        printf("%2d",j);
                }
                printf("\n\n");
            }
            if(i+1==10)                                 //sütunlara numara verilen kisim
                printf("\t\t\t%d",i+1);
            else
                printf("\t\t\t%d ",i+1);
            for(j=0; j<sayi2; j++)                      //bu döngü dosyadan alinan degerleri matris'e atiyor
            {                                           //ve üzerinde oynayacagimiz matrisin güncel halini yazdiriyor
                fscanf(cfPtr, "%d", &matris[i][j]);
                printf("%2c",kare[i][j]);
            }
            satirlardaki_1_sayisi(matris,sayi2,i);
            printf("\n");
        }
    printf("\n");
    sutunlardaki_1_sayisi(matris,sayi1,sayi2);
    system("pause");
    do
    {
        system("cls");
        do
        {
            printf("\n\n\t\t\tSatir numarasini giriniz (1-%d)>>> \n\t\t\t\t\t",sayi1);
            scanf("%d", &satir);
            satir_yeni=satir-1;
        }
        while(satir_yeni>sayi1 || satir_yeni<0);

        do
        {
            printf("\t\t\tSutun numarasini giriniz (1-%d)>>> \n\t\t\t\t\t",sayi2);
            scanf("%d", &sutun);
            sutun_yeni=sutun-1;
        }
        while(sutun_yeni>sayi2 || sutun_yeni<0);
        do
        {
            printf("\t\tIsaretleme kodunu giriniz (1:dolu, 0:bos, 2:belirsiz)>>> \n\t\t\t\t\t");
            scanf("%d", &isaretleme_kodu);
        }
        while(isaretleme_kodu<0 || isaretleme_kodu>2);      //aldigimiz 0,1,2 degerlerinin karsiliginda, belirtilen harfler ataniyor
        if(isaretleme_kodu==1)
            kare[ satir_yeni][sutun_yeni]=ascii_219;
        else if(isaretleme_kodu==0)
            kare[ satir_yeni][sutun_yeni]='O';
        else if(isaretleme_kodu==2)
            kare[ satir_yeni][sutun_yeni]='X';

        for(i=0; i<sayi1; i++)
        {
            if(i==0)                                    //satirlara numara verilen kisim
            {   printf("\t\t\t  ");
                for(j=1; j<=sayi2; j++)
                {
                    if(j==10)
                        printf(" %2d",j);
                    else
                        printf("%2d",j);
                }
                printf("\n\n");
            }
            if(i+1==10)                                 //sütunlara numara verilen kisim
                printf("\t\t\t%d",i+1);
            else
                printf("\t\t\t%d ",i+1);
            for(j=0; j<sayi2; j++)                      //bu döngü dosyadan alinan degerleri matris'e atiyor
            {                                           //ve üzerinde oynayacagimiz matrisin güncel halini yazdiriyor
                fscanf(cfPtr, "%d", &matris[i][j]);
                printf("%2c",kare[i][j]);
            }
            satirlardaki_1_sayisi(matris,sayi2,i);
            printf("\n");
        }
    printf("\n");
    sutunlardaki_1_sayisi(matris,sayi1,sayi2);
    sayac_oyun=kontrol(matris,kare,sayi1,sayi2);
    system("pause");
    }
    while(sayac_oyun!=(sayi1*sayi2));       //bu döngüden çikildiginda gizli resim gösteriliyor ve programdan cikiliyor
    printf("<<Tebrikler gizli resmi buldunuz>>\n");
    gizli_resmi_goster(matris,sayi1,sayi2);
    return 0;
}
int kontrol(int matris[][m], char kare[][m],int sayi1,int sayi2)
{
    int i,j,sayac_oyun=0;
    char ascii_219;
    ascii_219=219;

            for(i=0; i<sayi1; i++)          //bu döngü her veri girisinden sonra üzerinden oynadigimiz
        {                                   //kare matrisi ile, dosyadan aldýðýmýz matris matrisini karsilastiriyor
            for(j=0; j<sayi2; j++)          //eger tüm elemanlar ayni ise sayac_oyun=sayi1*sayi2 esitligi saglaniyor
            {                               //ve do-while dongüsnden cikiliyor
                if(matris[i][j]==1 && kare[i][j]==ascii_219)
                    sayac_oyun++;
                else if(matris[i][j]==0 && kare[i][j]=='O')
                    sayac_oyun++;
                else if(matris[i][j]==0 && kare[i][j]=='X')
                    sayac_oyun++;
                else
                    continue;
            }
        }
return sayac_oyun;
}
void gizli_resmi_goster(int matris[][m],int sayi1,int sayi2)        //oyun bitiminde gizli resmi gösteren fonksiyon
{
    int i,j;
    for(i=0; i<sayi1; i++)
    {
        for(j=0; j<sayi2; j++)
        {
            printf("%d",matris[i][j]);
        }
        printf("\n");
    }
}
void sutunlardaki_1_sayisi(int matris[][m],int sayi1,int sayi2)     //bu fonksiyon her sütundaki 1 sayisini yazdiriyor
{
    int a,b,i,j,tur,tut;
    int sayac;
    int sayac_mtrs[n][m];               //her sutunda kaç tane 1 oldugunu gösteren matris

    for(i=0; i<n; i++)                  //bu döngüde sayac_mtrs'in, elemanlari tekrar yazdirmamasi için,bu matrisi sifirliyoruz
        for(j=0; j<m; j++)
            sayac_mtrs[i][j]=0;
    for(b=0; b<sayi2; b++)              //bu döngünün içinde, sütunlardaki 1 sayisina göre
    {                                   //olusturulan sayac_mtrs'e degerleri ataniyor
        sayac=0;
        for(a=0; a<sayi1; a++)
        {
            if(matris[a][b]==1)
                sayac++;
            if(a==sayi1-1)
                sayac_mtrs[b][a]=sayac;
            else if(matris[a][b]==0)
            {
                if(sayac>0)
                {
                    sayac_mtrs[b][a]=sayac;
                    sayac=0;
                }
            }
        }
    }
    for(i=0; i<sayi2; i++)               //bu döngüde sayac_mtrs elemanlari her satir için
    {                                    //büyükten küçüge siralaniyor
        for(tur=0;tur<sayi1-1;tur++)
        {
            for(j=0; j<sayi1-1; j++)
            {
                if(sayac_mtrs[i][j]<sayac_mtrs[i][j+1])
                {
                    tut=sayac_mtrs[i][j];
                    sayac_mtrs[i][j]=sayac_mtrs[i][j+1];
                    sayac_mtrs[i][j+1]=tut;
                }
            }
        }
    }
    for(i=0; i<sayi2; i++)              //bu döngüde ise olusturulan sayac_mtrs'in transpozesi yazdiriliyor
    {
        printf("\t\t\t");
        printf("  ");
        for(j=0; j<sayi1; j++)
        {
            if(sayac_mtrs[j][i]>0)
                printf("%2d",sayac_mtrs[j][i]);
            else if(sayac_mtrs[j][i]==0)
                printf("  ");
        }
    printf("\n");
    }
}
void satirlardaki_1_sayisi(int matris[][m],int sayi2,int i)         //bu fonksiyon her satirdaki 1 sayisini yazdiriyor
{
    int j,sayac=0;

    printf(" ");
    for(j=0; j<sayi2; j++)
    {
        if(matris[i][j]==1)
            sayac++;
        else if(matris[i][j]==0)
        {
            if(sayac>0)
                printf(" %d",sayac);
            sayac=0;
        }
    }
    if(sayac>0)
        printf(" %d",sayac);
}
