#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct ucus
{
    int ucus_numarasi;
    char kalkis_yeri[21];
    char varis_yeri[21];
    int kalkis_saat;
    int kalkis_dk;
    int kapasite;
    int bos_koltuk_say;
    float baslangic_bilet_fiyati;
};
typedef struct ucus ucus_type;


int menu_secimi();
void ucus_bilgisi(FILE*);
void ucus_ve_bilet_bilgisi(FILE*);
void bir_yerdeki_ucuslar(FILE*);
void koltuk_yarisi_bos(FILE*);
void tek_yolcu_bilet(FILE*);
int main()
{

    int secim;
    FILE *dosya1;
    int bilet_say=0;
    int toplam_biet_fiyat=0;
    if((dosya1=fopen("ucus.dat","rb+"))==NULL)
    {
        printf("Ucus bilgilerine ait dosya acilamadi\n");
        return 0;
    }
    do
    {
        secim=menu_secimi();
        switch (secim)
        {
        case 1:
            ucus_bilgisi(dosya1);
            break;
        case 2:
            ucus_ve_bilet_bilgisi(dosya1);
            break;
        case 3:
            bir_yerdeki_ucuslar(dosya1);
            break;
        case 4:
            koltuk_yarisi_bos(dosya1);
            break;
        case 5:
            tek_yolcu_bilet(dosya1);
            break;
        case 6:
            return 0;
        }
    }
    while (secim>6 && secim<1);
    fclose(dosya1);

    return 0;
}
int menu_secimi(void)
{
    int secim;

    printf("   ___________________________________________________________________________\n");
    printf("                        SORGULAMA MENUSU\n");
    printf("   ___________________________________________________________________________\n\n");
    printf("1) Ucus Bilgilerinin Goruntulenmesi\n");
    printf("2) Ucus Bilgilerinin ve O Ucusa Ait Satilan Biletlerin Listelenmesi\n");
    printf("3) Bir Yerden Kalkan Ucus Bilgilerinin Goruntulenmesi\n");
    printf("4) Koltuk Dolulugu Yaridan Az Olan Ucuslarin Goruntulenmesi\n");
    printf("5) Bir Yolcunun Biletlerinin Goruntulenmesi\n");
    printf("6) Cikis\n");
    do
    {
        printf("\nSeciminizi Giriniz:");
        scanf("%d", &secim);
        if (secim<=0 || secim>6)
            printf("Hatali giris yaptiniz! Lutfen 1 ile 4 arasinda bir deger giriniz.\n\a");
    }
    while(secim<1 || secim>7);

    return secim;
}
void ucus_bilgisi(FILE *dosya)
{
    float yuzde;

    ucus_type bir_ucus;

    int aranacak_numara;
    printf("Ucus bilgilerini sorgulamak istediginiz ucus kodunu giriniz\n");
    scanf("%d",&aranacak_numara);

    fseek(dosya,(aranacak_numara-1)*sizeof(ucus_type),SEEK_SET);
    fread(&bir_ucus,sizeof(ucus_type),1,dosya);

    yuzde=bir_ucus.kapasite-bir_ucus.bos_koltuk_say;
    yuzde=(yuzde/bir_ucus.kapasite)*100;

    if(bir_ucus.ucus_numarasi==0)
        printf("Ucus bulunamadi\n");
    else
    {
        printf("______________________________________________________________________________\n");
        printf("Ucus No  Kalkis Yeri  Varis Yeri  Zamani  Kapasite  Bos Koltuk  Doluluk(yuzde)\n");
        printf("______________________________________________________________________________\n");
        printf("%-7d  %-11s  %-10s  %.2d:%-1.2d   %-8d  %-10d  %-14.2f \n",bir_ucus.ucus_numarasi,bir_ucus.kalkis_yeri,bir_ucus.varis_yeri,bir_ucus.kalkis_saat,bir_ucus.kalkis_dk,bir_ucus.kapasite,bir_ucus.bos_koltuk_say,yuzde);
    }
    return ;
}

void ucus_ve_bilet_bilgisi(FILE *dosya1)
{

    FILE *dosya2;

    dosya2=fopen("bilet.txt","r");
    int i=0;
    float yuzde;

    ucus_type bir_ucus;


    int aranacak_numara;
    printf("Ucus ve bilet bilgilerini kontrol etmek istediginiz ucus numarasini girin.\n");
    scanf("%d",&aranacak_numara);

    fseek(dosya1,(aranacak_numara-1)*sizeof(ucus_type),SEEK_SET);
    fread(&bir_ucus,sizeof(ucus_type),1,dosya1);

    yuzde=bir_ucus.kapasite-bir_ucus.bos_koltuk_say;
    yuzde=(yuzde/bir_ucus.kapasite)*100;

    printf("______________________________________________________________________________\n");
    printf("Ucus No  Kalkis Yeri  Varis Yeri  Zamani  Kapasite  Bos Koltuk  Doluluk(yuzde)\n");
    printf("______________________________________________________________________________\n");
    printf("%-7d  %-11s  %-10s  %.2d:%-1.2d   %-8d  %-10d  %-14.2f \n",bir_ucus.ucus_numarasi,bir_ucus.kalkis_yeri,bir_ucus.varis_yeri,bir_ucus.kalkis_saat,bir_ucus.kalkis_dk,bir_ucus.kapasite,bir_ucus.bos_koltuk_say,yuzde);

    printf("\n\n\n");
    printf("UcusNo TC Kimlik No Bilet Fiyati\n");
    printf("__________________________________\n");
    int ucus_numara;
    double kimlik_no;
    float bilet_fiyat;

    fscanf(dosya2,"%d %lf %f",&ucus_numara,&kimlik_no,&bilet_fiyat);

    while(!feof(dosya2))
    {

        if(aranacak_numara==ucus_numara)
        {
            printf("%-6d %-4.0f %-11.2f\n",ucus_numara,kimlik_no,bilet_fiyat);
            fscanf(dosya2,"%d %lf %f",&ucus_numara,&kimlik_no,&bilet_fiyat);
        }
    }

    fclose(dosya2);
    return ;
}

void tek_yolcu_bilet(FILE *dosya1)
{
    ucus_type bir_ucus;

    FILE *dosya2;

    dosya2=fopen("bilet.txt","r");

    int ucus_numara;
    float bilet_fiyat;
    double kimlik_no;
    double aranacak_kimlik;

    printf("Bilgilerine ulasmak istediginiz yolcunun kimlik numarasini girin\n");
    scanf("%lf",&aranacak_kimlik);
    printf("______________________________________________________________________________\n");
    printf("Ucus No  Kalkis Yeri  Varis Yeri  Zamani  Fiyat\n");
    printf("______________________________________________________________________________\n");
    fscanf (dosya2,"%d %lf %f",&ucus_numara,&kimlik_no,&bilet_fiyat);
    while(!feof(dosya2))
    {
        if(aranacak_kimlik==kimlik_no)
        {
            fseek(dosya1,(ucus_numara-1)*sizeof(ucus_type),SEEK_SET);
            fread(&bir_ucus,sizeof(ucus_type),1,dosya1);
            printf("%d %s %s %.2d%d %.2f\n",ucus_numara,bir_ucus.kalkis_yeri,bir_ucus.varis_yeri,bir_ucus.kalkis_saat,bir_ucus.kalkis_dk,bilet_fiyat);
        }
        fscanf (dosya2,"%d %lf %f",&ucus_numara,&kimlik_no,&bilet_fiyat);
    }

    fclose(dosya2);
    return;
}

void bir_yerdeki_ucuslar(FILE *dosya1)
{
    ucus_type bir_ucus;
    int sonuc,i,j=0;
    float yuzde;
    char aranacak_il[21];
    printf("Hangi ucuslarin kalkis yerlerini ogrenmek istiyorsunuz?\n");
    scanf("%s",aranacak_il);
    printf("______________________________________________________________________________\n");
    printf("Ucus No  Kalkis Yeri  Varis Yeri  Zamani  Kapasite  Bos Koltuk  Doluluk(yuzde)\n");
    printf("______________________________________________________________________________\n");
    fseek(dosya1,0,SEEK_SET);
    for(i=0; i<1000; i++)
    {
        fread(&bir_ucus,sizeof(ucus_type),1,dosya1);
        yuzde=bir_ucus.kapasite-bir_ucus.bos_koltuk_say;
        yuzde=(yuzde/bir_ucus.kapasite)*100;

        sonuc=strcmp(aranacak_il,bir_ucus.kalkis_yeri);
        if(sonuc==0)
        {
            printf("%-7d  %-11s  %-10s  %.2d:%-1.2d   %-8d  %-10d  %-14.2f \n",bir_ucus.ucus_numarasi,bir_ucus.kalkis_yeri,bir_ucus.varis_yeri,bir_ucus.kalkis_saat,bir_ucus.kalkis_dk,bir_ucus.kapasite,bir_ucus.bos_koltuk_say,yuzde);
            j++;
        }
    }

    if(j==0)
        printf("%s sehri baslangic noktasi olarak herhangi bir ucus bulunmamaktadir.",aranacak_il);


    return;
}

void koltuk_yarisi_bos(FILE *dosya1)
{
    ucus_type bir_ucus;
    int i;
    float yuzde;
    fseek(dosya1,0,SEEK_SET);

    for(i=0; i<1000; i++)
    {
        fread(&bir_ucus,sizeof(ucus_type),1,dosya1);
        yuzde=bir_ucus.kapasite-bir_ucus.bos_koltuk_say;
        yuzde=(yuzde/bir_ucus.kapasite)*100;

        if(yuzde<50)
        {
            printf("%-7d  %-11s  %-10s  %.2d:%-1.2d   %-8d  %-10d  %-14.2f \n",bir_ucus.ucus_numarasi,bir_ucus.kalkis_yeri,bir_ucus.varis_yeri,bir_ucus.kalkis_saat,bir_ucus.kalkis_dk,bir_ucus.kapasite,bir_ucus.bos_koltuk_say,yuzde);
        }
    }


    return;
}
