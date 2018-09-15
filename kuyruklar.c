#include <stdio.h>

#define KAPASITE 200

struct aday {
    int no;
    char ad_soyad[21];
    int boy;
};

void d_ekle(struct aday *kuyruk, int *on, int *arka, struct aday yeni);//dairesel kuyruga eleman ekleme
struct aday d_cikar(struct aday *kuyruk, int *on, int *arka);//dairesel kuyruktan eleman cikarma
int bos_mu(int on);
int d_eleman_say(int on, int arka);//dairesel kuyruktaki eleman sayisini bulma
void d_listele(struct aday *kuyruk, int on, int arka);//dairesel kuyruktaki elemanlari listeleme

int menu_secim(void);

int main()
{
    struct aday kuyruk[KAPASITE];//kuyrukta tutulacak elemanlar icin 200 elemanli vektor
    int on=-1;//kuyrugun onunu belirtir
    int arka=-1;//kuyrugun arkasini belirtir
    struct aday bir_aday;
    int secenek;

	do {
        secenek=menu_secim(); 
        switch(secenek) {
            case 1:
                printf("Adayin numarasini giriniz:");
                scanf("%d",&bir_aday.no);
                printf("Adayin adini soyadini giriniz:");
                fflush(stdin);
                gets(bir_aday.ad_soyad);
                printf("Adayin boyunu giriniz:");
                scanf("%d",&bir_aday.boy);
                d_ekle(kuyruk,&on,&arka,bir_aday);//aday, bekleme salonundaki kuyrugun sonuna ekleniyor
                break;
            case 2:
                if (!bos_mu(on)) {//bekleme salonu bos degilse...
                    bir_aday=d_cikar(kuyruk,&on,&arka);//siradaki aday sinava cagriliyor
                    printf("Aday No  Ad Soyad              Boy\n");
                    printf("-------  --------------------  ---\n");
                    printf("%-7d  %-20s  %d\n",bir_aday.no,bir_aday.ad_soyad,bir_aday.boy);
                }
                else
                    printf("Bekleme salonu bos\n");
                break;
            case 3:
                if (!bos_mu(on))//bekleme salonu bos degilse...
                    printf("Bekleme salonunda beklyen aday sayisi: %d\n",d_eleman_say(on,arka));//bekleyen aday sayisi yazdiriliyor
                else
                    printf("Bekleme salonu bos\n");
                break;
            case 4:
                if (!bos_mu(on))//bekleme salonu bos degilse...
                    d_listele(kuyruk,on,arka);//bekleyen tum adaylar gelis sirasina gore listeleniyor
                else
                    printf("Bekleme salonu bos\n");
                break;
        }
    } while (secenek!=5);

    return 0;
}

int menu_secim(void){

    int secim;
    printf("\n");
    printf("********************MENU************************************\n");
    printf("            1. Bir adayin bekleme salonuna alinmasi\n");
    printf("            2. Bekleme salonundan siradaki adayin sinava cagrilmasi\n");
    printf("            3. Bekleme salonunda bekleyen aday sayisinin goruntulenmesi\n");
    printf("            4. Bekleme salonunda bekleyen adaylarin bilgilerinin listelenmesi\n");
    printf("            5. Cikis\n");
    printf("\n");
    do {
        printf("\nSeciminizi Giriniz:  ");
        scanf("%d", &secim);

    }while(secim<0 || secim>5);

    return secim;
}

void d_ekle(struct aday *kuyruk, int *on, int *arka, struct aday yeni)
{
    if((*arka+1)%KAPASITE==*on)
        printf("Salon dolu!\n");
    else {
        *arka=(*arka+1)%KAPASITE;
        kuyruk[*arka]=yeni;
        if(*on==-1) *on=0;//ilk eleman ekleniyorsa
    }
}

struct aday d_cikar(struct aday *kuyruk, int *on, int *arka)
{
    struct aday gecici;

    gecici=kuyruk[*on];
    if(*on==*arka) {//son eleman cikariliyorsa
        *on=-1;
        *arka=-1;
    }
    else *on=(*on+1)%KAPASITE;

    return gecici;
}

int bos_mu(int on)
{
    return on==-1;
}

int d_eleman_say(int on, int arka)
{
    if((arka-on)<0)
        return arka-on+KAPASITE+1;
    else
        return arka-on+1;
}

void d_listele(struct aday *kuyruk, int on, int arka)//on ve arka call-by-value ile aktariliyor
{
    printf("Aday No  Ad Soyad              Boy\n");
    printf("-------  --------------------  ---\n");
    while(on!=arka) {
        printf("%-7d  %-20s  %d\n",kuyruk[on].no,kuyruk[on].ad_soyad,kuyruk[on].boy);
        on=(on+1)%KAPASITE;//on 1 oteleniyor ama main'deki on degismiyor
    };
    printf("%-7d  %-20s  %d\n",kuyruk[on].no,kuyruk[on].ad_soyad,kuyruk[on].boy);//son eleman yazdiriliyor
}
