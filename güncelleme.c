#include <stdio.h>
#include <stdlib.h>
#define BOS_KAYIT_NO 0
struct ucus
{
    int ucus_numarasi;
    
    char varis_yeri[21];
    int kalkis_saat;
    int kalkis_dk;
    int kapasite;
    int bos_koltuk_say;
    float baslangic_bilet_fiyati;
};
typedef struct ucus ucus_type;

int menu_secimi();
void ucus_ekle(FILE *);
void ucus_sil(FILE *);
void kalkis_zamani_degistir(FILE *);
void bilet_satis(FILE *);
int main()
{
    int secim; 
    FILE *dosya1;
    FILE *dosya2;
    if((dosya1=fopen("ucus.dat","rb+"))==NULL)
    {
        printf("Ucus bilgilerine ait dosya acilamadi\n");
        return 0;
    }
    int secenek;
    do
    {
        secim=menu_secimi();
        switch (secim)
        {
        case 1:
            ucus_ekle(dosya1);
            break;
        case 2:
            ucus_sil(dosya1);
            break;
        case 3:
            kalkis_zamani_degistir(dosya1);
            break;
        case 4:
            bilet_satis(dosya1);
        case 5:
            return 0;
            break;
        }
    }
    while (secim>5 && secim<1);
    fclose(dosya1);
    return 0;
}
int menu_secimi()
{
    int secim;

    printf("   ___________________________________________________________________________\n");
    printf("                        GUNCELLEME MENUSU \n");
    printf("   ___________________________________________________________________________\n\n");
    printf("1) Yeni Bir Ucusun Eklenmesi\n");
    printf("2) Bir Ucusun Silinmesi\n");
    printf("3) Bir Ucusun Kalkis Zamaninin Degistirmesi\n");
    printf("4) Bir Ucusa Ait Bilet Satimi\n");
    printf("5) Cikis\n");
    do
    {
        printf("\nSeciminizi Giriniz:\n");
        scanf("%d", &secim);
        if (secim<=0 || secim>5)
            printf("Hatali giris yaptiniz! Lutfen 1 ile 4 arasinda bir deger giriniz.\n\a");
    }
    while(secim<1 || secim>5);

    return secim;
}
void ucus_ekle(FILE *dosya1)
{
    ucus_type bir_ucus;
    int ucus_no;

    printf("Eklemek istediginiz yeni ucusun numarasini giriniz\n");
    scanf("%d",&ucus_no);


    fseek(dosya1,(ucus_no-1)*sizeof(ucus_type),SEEK_SET);
    fread(&bir_ucus,sizeof(ucus_type),1,dosya1);
    if(bir_ucus.ucus_numarasi==0)
    {
        bir_ucus.ucus_numarasi=ucus_no;
        printf("Ucusun kalkis noktasini giriniz\n");
        scanf("%s",bir_ucus.kalkis_yeri);
        printf("Ucusun varis noktasini giriniz\n");
        scanf("%s",bir_ucus.varis_yeri);
        printf("kaklis saati");
        scanf("%d",&bir_ucus.kalkis_saat);
        printf("kaklis dakika");
        scanf("%d",&bir_ucus.kalkis_dk);
        printf("Ucagin kapasitesini giriniz.\n");
        scanf("%d",&bir_ucus.kapasite);
        printf("bilet fiyati\n");
        scanf("%f",&bir_ucus.baslangic_bilet_fiyati);

        bir_ucus.bos_koltuk_say=bir_ucus.kapasite;
        fseek(dosya1,(ucus_no-1)*sizeof(ucus_type),SEEK_SET);
        fwrite(&bir_ucus,sizeof(ucus_type),1,dosya1);
        printf("Ekleme islemi basari ile gerceklestirildi.\n");
    }
    else
        printf("Girilen ucus numarasina ait ucus bulunmaktadir\n");

    return;

}
void ucus_sil(FILE *dosya1)
{
    FILE *dosya2;
    FILE *gecici;

    gecici=fopen("gecici.txt","w+");
    dosya2=fopen("bilet.txt","r+");

    int ucus_dosya;
    float fiyat_dosya;
    double tc_dosya;

    ucus_type bir_ucus;
    int ucus_no;
    printf("Silmek istediginiz ucusun numarasini giriniz\n");
    scanf("%d",&ucus_no);

    fseek(dosya1,(ucus_no-1)*sizeof(ucus_type),SEEK_SET);
    fread(&bir_ucus,sizeof(ucus_type),1,dosya1);
    if(bir_ucus.ucus_numarasi==BOS_KAYIT_NO)
        printf("Boyle bir ucus bulunmamaktadir.\n");
    else
    {
        bir_ucus.ucus_numarasi=0;
        fseek(dosya1,(ucus_no-1)*sizeof(ucus_type),SEEK_SET);
        fwrite(&bir_ucus,sizeof(ucus_type),1,dosya1);

        fscanf(dosya2,"%d %lf %f",&ucus_dosya,&tc_dosya,&fiyat_dosya);

        while(!feof(dosya2))
        {
            if(ucus_dosya!=ucus_no)
            {
                fprintf(gecici,"%d %lf %f\n",ucus_dosya,tc_dosya,fiyat_dosya);
            }
            fscanf(dosya2,"%d %lf %f",&ucus_dosya,&tc_dosya,&fiyat_dosya);
        }



        printf("Silme islemi basariyla gerceklestirilmistir.\n");
    }

    fclose(dosya2);
    fclose(gecici);

    remove("bilet.txt");
    rename("gecici.txt","bilet.txt");
    return;
}
void kalkis_zamani_degistir(FILE *dosya1)
{
    ucus_type bir_ucus;
    int guncel_saat,guncel_dk;
    int ucus_no;
    printf("Zamanini degistirmek istediginiz ucus numarasini girin.\n");
    scanf("%d",&ucus_no);
    fseek(dosya1,(ucus_no-1)*sizeof(ucus_type),SEEK_SET);
    fread(&bir_ucus,sizeof(ucus_type),1,dosya1);
    if(ucus_no==0)
    {
        printf("Boyle bir ucus bulunmamaktadir.\n");
    }
    else
    {
        printf("Yeni kalkis saatini giriniz.\n");
        scanf("%d",&guncel_saat);
        printf("Yeni kalkis dakikasini giriniz.\n");
        scanf("%d",&guncel_dk);
        bir_ucus.kalkis_saat=guncel_saat;
        bir_ucus.kalkis_dk=guncel_dk;
        fseek(dosya1,(ucus_no-1)*sizeof(ucus_type),SEEK_SET);
        fwrite(&bir_ucus,sizeof(ucus_type),1,dosya1);
        printf("Saat guncelleme islemi basari ile gerceklestirilmistir.\n");
    }
    return;
}

void bilet_satis(FILE *dosya1)
{
    FILE *dosya2;
    float bos_koltuk_oran;
    int a;
    ucus_type bir_ucus;
    dosya2=fopen("bilet.txt","a+");
    double kimlik_no;
    int ucus_no,bilet_fiyat;
    int alinacak_bilet;
    printf("Bilet almak istediginiz ucus numarasini giriniz.\n");
    scanf("%d",&ucus_no);
    fseek(dosya1,(ucus_no-1)*sizeof(ucus_type),SEEK_SET);
    fread(&bir_ucus,sizeof(ucus_type),1,dosya1);

    if(bir_ucus.ucus_numarasi==0)
    {
        printf("Boyle bir ucus bulunmamaktadir.\n");
    }
    else
    {
        printf("Kimlik numaranizi giriniz.\n");
        scanf("%lf",&kimlik_no);
        printf("Kac tane bilet alinacaktir.\n");
        scanf("%d",&alinacak_bilet);
        if(alinacak_bilet>bir_ucus.bos_koltuk_say)
            printf("Bu ucusta istediginiz bilet sayisi kadar yer bulunmamaktadir");
        else
        {
            printf("Bilet fiyati:\n");
            for(a=0;a<alinacak_bilet;a++)
            {
                bos_koltuk_oran=(bir_ucus.bos_koltuk_say/bir_ucus.kapasite)*100;
                fseek(dosya1,(ucus_no-1)*sizeof(ucus_type),SEEK_SET);
                fread(&bir_ucus,sizeof(ucus_type),1,dosya1);
                bir_ucus.bos_koltuk_say=bir_ucus.bos_koltuk_say-1;
            if(bos_koltuk_oran>0 && bos_koltuk_oran<=10)
                bilet_fiyat=bir_ucus.baslangic_bilet_fiyati*1.9;
                else if (bos_koltuk_oran>10 && bos_koltuk_oran<=20)
                        bilet_fiyat=bir_ucus.baslangic_bilet_fiyati*1.8;
                        else if (bos_koltuk_oran>20 && bos_koltuk_oran<=30)
                                bilet_fiyat=bir_ucus.baslangic_bilet_fiyati*1.7;
                                else if(bos_koltuk_oran>30 && bos_koltuk_oran<=40)
                                        bilet_fiyat=bir_ucus.baslangic_bilet_fiyati*1.6;
                                        else if (bos_koltuk_oran>40 && bos_koltuk_oran<=50)
                                                bilet_fiyat=bir_ucus.baslangic_bilet_fiyati*1.5;
                                                else if(bos_koltuk_oran>50 && bos_koltuk_oran<=60)
                                                        bilet_fiyat=bir_ucus.baslangic_bilet_fiyati*1.4;
                                                        else if(bos_koltuk_oran>60 && bos_koltuk_oran<=70)
                                                                bilet_fiyat=bir_ucus.baslangic_bilet_fiyati*1.3;
                                                                else if(bos_koltuk_oran>70 && bos_koltuk_oran<=80)
                                                                        bilet_fiyat=bir_ucus.baslangic_bilet_fiyati*1.2;
                                                                        else if(bos_koltuk_oran>80 && bos_koltuk_oran<=90)
                                                                                bilet_fiyat=bir_ucus.baslangic_bilet_fiyati*1.1;
                                                                                else if(bos_koltuk_oran>90 && bos_koltuk_oran<=100)
                                                                                        bilet_fiyat=bir_ucus.baslangic_bilet_fiyati;
        printf("%.2f TL \n",bilet_fiyat);
                                    }
        }
        fprintf(dosya2,"%d %lf %.2f",ucus_no,kimlik_no,bilet_fiyat);
        fseek(dosya1,(ucus_no-1)*sizeof(ucus_type),SEEK_SET);
        fwrite(&bir_ucus,sizeof(ucus_type),1,dosya1);

    }
    fclose(dosya2);
    return;
}
