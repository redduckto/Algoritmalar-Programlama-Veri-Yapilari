#include <stdio.h>
#include <stdlib.h>

struct aday {
    int no;
    char ad_soyad[21];
    int boy;
    struct aday *sonraki;
};

void sirali_ekle(struct aday **bas, struct aday *yeni);//oncelik kuyruguna sirali ekleme
int bos_mu(struct aday *bas);
void listele(struct aday *bas);//oncelik kuyrugundaki elemanlari listeleme
struct aday *bastan_cikar(struct aday **bas);//oncelik kuyrugundan eleman cikarma

int menu_secim(void);

int main()
{
    struct aday *ilk=NULL;//baslangicta oncelik kuyrugu bos
    struct aday *bir_aday;
    int secenek;

	do {
        secenek=menu_secim();
        switch(secenek) {
            case 1:
                bir_aday=malloc(sizeof(struct aday));//yeni gelen aday icin bellekte yer ayriliyor, yani yeni bir dugum yaratiliyor
                printf("Adayin numarasini giriniz:");
                scanf("%d",&bir_aday->no);
                printf("Adayin adini soyadini giriniz:");
                fflush(stdin);
                gets(bir_aday->ad_soyad);
                printf("Adayin boyunu giriniz:");
                scanf("%d",&bir_aday->boy);
                sirali_ekle(&ilk,bir_aday);//aday, bekleme salonundaki kuyruga boy sirasina gore ekleniyor
                break;
            case 2:
                if (!bos_mu(ilk)) {//bekleme salonu bos degilse...
                    bir_aday=bastan_cikar(&ilk);//kuyrugun en onundeki aday kuyruktan cikarilarak sinava cagriliyor
                    printf("Aday No  Ad Soyad              Boy\n");
                    printf("-------  --------------------  ---\n");
                    printf("%-7d  %-20s  %d\n",bir_aday->no,bir_aday->ad_soyad,bir_aday->boy);
                    free(bir_aday);//sinavi biten adayi temsil eden dugum yok ediliyor, yani kullanilan bellek alani bosaltiliyor
                }
                else
                    printf("Bekleme salonu bos\n");
                break;
            case 3:
                if (!bos_mu(ilk))//bekleme salonu bos degilse...
                    listele(ilk);//bekleyen tum adaylar boy sirasina gore listeleniyor
                else
                    printf("Bekleme salonu bos\n");
                break;
        }
    } while (secenek!=4);

    return 0;
}

int menu_secim(void){

    int secim;
    printf("\n");
    printf("********************MENU************************************\n");
    printf("            1. Bir adayin bekleme salonuna alinmasi\n");
    printf("            2. Bekleme salonundan siradaki adayin sinava cagrilmasi\n");
    printf("            3. Bekleme salonunda bekleyen adaylarin bilgilerinin listelenmesi\n");
    printf("            4. Cikis\n");
    printf("\n");
    do {
        printf("\nSeciminizi Giriniz:  ");
        scanf("%d", &secim);

    }while(secim<0 || secim>4);

    return secim;

}

void sirali_ekle(struct aday **bas, struct aday *yeni)
{
    struct aday *gecici, *onceki;

    if (*bas==NULL) {//kuyruk bossa
        yeni->sonraki=NULL;
        *bas=yeni;
    } else
        if (yeni->boy>(*bas)->boy) {//en basa eklenecekse
            yeni->sonraki=*bas;
            *bas=yeni;
        } else {//araya ya da sona eklenecekse
            onceki=*bas;
            gecici=(*bas)->sonraki;
            while ((gecici!=NULL) && (gecici->boy>yeni->boy)) {//eklenecek uygun yer araniyor
                onceki=gecici;
                gecici=gecici->sonraki;
            }
            yeni->sonraki=gecici;//gecici NULL ise en sona, degilse onceki dugumu ile gecici dugumu arasina ekleniyor
            onceki->sonraki=yeni;
        }
}

int bos_mu(struct aday *bas)
{
    return bas==NULL;
}

void listele(struct aday *bas)//kuyrugun ilk dugumunun adresi call-by-value ile aktariliyor
{
    printf("Aday No  Ad Soyad              Boy\n");
    printf("-------  --------------------  ---\n");

    while(bas!=NULL) {
        printf("%-7d  %-20s  %d\n",bas->no,bas->ad_soyad,bas->boy);
        bas=bas->sonraki;//bas 1 oteleniyor ama main'deki ilk degismiyor
    }
}

struct aday *bastan_cikar(struct aday **bas)
{
    struct aday *cikarilan;

    cikarilan=*bas;
    *bas=(*bas)->sonraki;

    return cikarilan;
}
