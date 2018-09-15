#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BOS_KAYIT_KODU -1

struct PersonelVerisi{
    int per_no;
    char ad_soyad[26];
    char giris_tarihi[9];
    char unvani[16];
    float ucret_katsayisi;
    int toplam_sure;
};

void PersonelEkle(FILE *);
void PersonelGuncelle(FILE *);
void MesaiEkle(FILE *);
void PersonelSil(FILE *);
void YedekAl(FILE *);

int main()
{
   struct PersonelVerisi personel={0,"","","",0.0,0};
   char cikis='h';
   int secim,aranan;

   FILE *fdosya;

   fdosya=fopen("personel.dat","rb+");

   do{
      printf("\n    Guncelleme Programi\n\n");

        printf("1)Yeni Bir Personelin Eklenmesi\n");
        printf("2)Bir Personelin Bilgilerinin Guncellenmesi\n");
        printf("3)Belirli Bir Gunun Mesai Kayitlarinin Eklenmesi\n");
        printf("4)Bir Personelin Kaydinin Silinmesi\n");
        printf("5)Personel Dosyasinin Yedeginin Alinmasi\n");
        printf("6)Cikis\n");
        printf("Seciminizi giriniz:\n");
        scanf("%d",&secim);

            switch(secim){
                case 1:
                   PersonelEkle(fdosya);

                break;
                case 2:
                    PersonelGuncelle(fdosya);

                break;
                case 3:
                    MesaiEkle(fdosya);

                break;
                case 4:
                    PersonelSil(fdosya);

                break;
                case 5:
                    YedekAl(fdosya);

                break;
                case 6:
                do{
                    printf("Cikmak istediginize emin misiniz(e/E/h/H)?:\n");
                    fflush(stdin);
                    cikis=getchar();
               }while (cikis != 'e' && cikis != 'E' && cikis!='h' && cikis!='H');
            }
    }while(cikis=='H'||cikis=='h');
    fclose(fdosya);

    return 0;
}
void PersonelEkle(FILE *fdosya)
{
    struct PersonelVerisi personel={0,"","","",0.0,0};
    int yeni_per_no;

    do{
        printf("Eklemek istediginiz yeni personelin numarasini giriniz.\n");
        scanf("%d",&yeni_per_no);
        if((yeni_per_no<0)||(yeni_per_no>100)){
            printf("Hatali giris yaptiniz personel numarasi 1 ile 100 arasinda olmalidir!\n");
        }
    }while((yeni_per_no<0)||(yeni_per_no>100));

    fseek(fdosya,(yeni_per_no-1)*sizeof(struct PersonelVerisi),SEEK_SET);
    fread(&personel,sizeof(struct PersonelVerisi),1,fdosya);
    if(personel.per_no==BOS_KAYIT_KODU){
        personel.per_no=yeni_per_no;
        printf("Personelin adini soyadini giriniz:\n");
        fflush(stdin);
        gets(personel.ad_soyad);
        printf("Personelin giris tarihini arada hic bir karakter ve bosluk olmadan ggaayyyy olacak sekilde giriniz:\n");
        fflush(stdin);
        gets(personel.giris_tarihi);
        printf("Personelin unvanini giriniz:\n");
        fflush(stdin);
        gets(personel.unvani);
        printf("Personelin ucret katsayisini giriniz:\n");
        scanf("%f",&personel.ucret_katsayisi);
        personel.toplam_sure=0;

        fseek(fdosya,(yeni_per_no-1)*sizeof(struct PersonelVerisi),SEEK_SET);
        fwrite(&personel,sizeof(struct PersonelVerisi),1,fdosya);
        printf("Ekleme islemi basariyla gerceklestirilmistir.\n");
    }else
        printf("Girdiginiz kod numarasina sahip personel bulunmaktadir.\n");
    return;
}
void PersonelGuncelle(FILE *fdosya)
{
    struct PersonelVerisi personel={0,"","","",0.0,0};
    int personel_no;

    do{
        printf("Guncelleme yapmak istediginiz personelin numarasini giriniz:\n");
        scanf("%d",&personel_no);
        if((personel_no<0)||(personel_no>100)){
            printf("Hatali giris yaptiniz personel numarasi 1 ile 100 arasinda olmalidir!\n");
        }
    }while((personel_no<0)||(personel_no>100));

    fseek(fdosya,(personel_no-1)*sizeof(struct PersonelVerisi),SEEK_SET);
    fread(&personel,sizeof(struct PersonelVerisi),1,fdosya);
    if(personel.per_no==BOS_KAYIT_KODU)
        printf("Girdiginiz personel numarasina ait personel bulunmamaktadir.\n");
    else{
        printf("Personelin yeni unvanini giriniz:\n");
        fflush(stdin);
        scanf("%s",personel.unvani);
        printf("Personelin yeni maas katsayisini giriniz:\n");
        scanf("%f",&personel.ucret_katsayisi);
        fseek(fdosya,(personel_no-1)*sizeof(struct PersonelVerisi),SEEK_SET);
        fwrite(&personel,sizeof(struct PersonelVerisi),1,fdosya);
        printf("Guncelleme islemi basariyla tamamlanmistir.\n");
    }
    return;
}
void MesaiEkle(FILE *fdosya){

    struct PersonelVerisi personel={0,"","","",0.0,0};
    int personel_no,personel_no_mesai,gun_no,girilen_saat,girilen_dk,cikis_saat,cikis_dk;
    char devam;
    FILE *fdosya2;

    fdosya2=fopen("mesai.txt","a+");
    printf("Mesai kaydini eklemek istediginiz gunun numarasini giriniz:\n");
    scanf("%d",&gun_no);

    do{
        do{
            printf("Ekleme yapmak istediginiz personelin numarasini giriniz:\n");
            scanf("%d",&personel_no);
            if((personel_no<0)||(personel_no>100)){
                printf("Hatali giris yaptiniz personel numarasi 1 ile 100 arasinda olmalidir!\n");
            }
        }while((personel_no<0)||(personel_no>100));
        fseek(fdosya,(personel_no-1)*sizeof(struct PersonelVerisi),SEEK_SET);
        fread(&personel,sizeof(struct PersonelVerisi),1,fdosya);
        if(personel.per_no==BOS_KAYIT_KODU)
            printf("Girdiginiz personel numarasina ait personel bulunmamaktadir.\n");
        else{
            fseek(fdosya,(personel_no-1)*sizeof(struct PersonelVerisi),SEEK_SET);
            fread(&personel,sizeof(struct PersonelVerisi),1,fdosya);
            printf("personelin ise giris zamanini arada bosluk birakarak sa dk olarak giriniz:\n");
            scanf("%d%d",&girilen_saat,&girilen_dk);
            printf("personelin isten cikis zamanini arada bosluk birakarak sa dk olarak giriniz:\n");
            scanf("%d%d",&cikis_saat,&cikis_dk);
            fprintf(fdosya2,"%d %d %d %d %d %d\n",personel_no,gun_no,girilen_saat,girilen_dk,cikis_saat,cikis_dk);
            personel.toplam_sure=(cikis_saat-girilen_saat)*60+(cikis_dk-girilen_dk)+personel.toplam_sure;
            fseek(fdosya,(personel_no-1)*sizeof(struct PersonelVerisi),SEEK_SET);
            fwrite(&personel,sizeof(struct PersonelVerisi),1,fdosya);
        }
        do{
            printf("Ekleme islemine devam etmek istiyormusunuz?(E/e/H/h)\n");
            fflush(stdin);
            scanf("%c",&devam);
        }while (devam != 'e' && devam != 'E' && devam!='h' && devam!='H');
    }while((devam=='e')||(devam=='E'));
    fclose(fdosya2);
    return;

}
void PersonelSil(FILE *fdosya)
{
    struct PersonelVerisi personel={0,"","","",0.0,0};
    int personel_no,personel_no_mesai,gun_no,girilen_saat,girilen_dk,cikis_saat,cikis_dk;
    FILE *geciciDosya;
    FILE *fdosya2;

    fdosya2=fopen("mesai.txt","r");
    geciciDosya=fopen("gecici.txt","w");

    do{
        printf("Silmek istediginiz personelin numarasini giriniz:\n");
        scanf("%d",&personel_no);
        if((personel_no<0)||(personel_no>100)){
            printf("Hatali giris yaptiniz personel numarasi 1 ile 100 arasinda olmalidir!\n");
        }
    }while((personel_no<0)||(personel_no>100));

    fseek(fdosya,(personel_no-1)*sizeof(struct PersonelVerisi),SEEK_SET);
    fread(&personel,sizeof(struct PersonelVerisi),1,fdosya);
    if(personel.per_no==BOS_KAYIT_KODU)
        printf("Girdiginiz personel numarasina ait personel bulunmamaktadir.\n");
    else{
        personel.per_no=BOS_KAYIT_KODU;
        fseek(fdosya,(personel_no-1)*sizeof(struct PersonelVerisi),SEEK_SET);
        fwrite(&personel,sizeof(struct PersonelVerisi),1,fdosya);

        fscanf(fdosya2,"%d%d%d%d%d%d",&personel_no_mesai,&gun_no,&girilen_saat,&girilen_dk,&cikis_saat,&cikis_dk);
        while(!feof(fdosya2)){
            if(personel_no!=personel_no_mesai)
                fprintf(geciciDosya,"%d %d %d %d %d %d\n",personel_no_mesai,gun_no,girilen_saat,girilen_dk,cikis_saat,cikis_dk);
            fscanf(fdosya2,"%d%d%d%d%d%d",&personel_no_mesai,&gun_no,&girilen_saat,&girilen_dk,&cikis_saat,&cikis_dk);
        }
        fclose(geciciDosya);
        fclose(fdosya2);
        remove("mesai.txt");
        rename("gecici.txt","mesai.txt");
        printf("Personelin kaydi basariyla silinmistir.\n");
    }
    return;
}
void YedekAl(FILE *fdosya)
{
    struct PersonelVerisi personel={0,"","","",0.0,0};
    int i=0,k=0;
    FILE *yedekDosya;

    yedekDosya=fopen("personel_yedek.dat","wb");

    while(i<100){
        fseek(fdosya,i*sizeof(struct PersonelVerisi),SEEK_SET);
        fread(&personel,sizeof(struct PersonelVerisi),1,fdosya);
        if(personel.per_no==BOS_KAYIT_KODU)
            i++;
        else{
            fseek(yedekDosya,k*sizeof(struct PersonelVerisi),SEEK_SET);
            fwrite(&personel,sizeof(struct PersonelVerisi),1,yedekDosya);
            i++;
            k++;
        }
    }
    fclose(yedekDosya);
    printf("personel.dat dosyasinin yedegi basariyla alinmistir.\n");
    return;
}



