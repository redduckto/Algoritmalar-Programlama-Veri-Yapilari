
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct PersonelVerisi{
    int per_no;
    char ad_soyad[26];
    char giris_tarihi[9];
    char unvani[16];
    float ucret_katsayisi;
    int toplam_sure;
};

void unvanArama(FILE *);
void yillaraGoreListele(FILE *);
void gecGelenleriListele(FILE *);
void mesaiListele(FILE *,FILE *);

int main()
{
   struct PersonelVerisi personel={0,"","","",0.0,0};
   char cikis='h';
   int secim,aranan,calistigi_saat,calistigi_dk,saat_ucreti=10;
   float ucret;
   int gun_no,girilen_saat,girilen_dk,cikis_saat,cikis_dk,personel_no;


   FILE *fdosya;
   FILE *fdosya2;

   fdosya=fopen("personel.dat","rb+");
   fdosya2=fopen("mesai.txt","r");

   do{
      printf("\n    Sorgulama Programi\n\n");

        printf("1)Bir personelin bilgilerinin listelenmesi\n");
        printf("2)Bir personelin bilgilerinin ve o ay icin mesai kayitlarinin listelenmesi\n");
        printf("3)Belirli bir unvana sahip personelin listelenmesi\n");
        printf("4)Ise alinan personel sayilarinin yillara gore dagiliminin listelenmesi\n");
        printf("5)Mesaiye gec gelen personelin listelenmesi\n");
        printf("6)Belirli bir gunun mesai kayitlarinin listelenmesi\n");
        printf("7)Cikis\n");
        printf("Seciminizi giriniz:\n");
        fflush(stdin);
        scanf("%d",&secim);

            switch(secim){
                case 1:
                aranan=-1;
                while(aranan<0||aranan>100){
                    printf("\nBilgilerini gormek istediginiz personelin numarasini giriniz\n");
                    scanf("%d",&aranan);
                    if(aranan<0||aranan>100)
                        printf("Hatali giris yaptiniz.Personel numarasi 1-100 arasinda olmalidir.\n");
                }
                fseek(fdosya,(aranan-1)*sizeof(struct PersonelVerisi),SEEK_SET);
                fread(&personel,sizeof(struct PersonelVerisi),1,fdosya);
                if(personel.per_no==-1)
                    printf("Personel bulunamadi.\n");
                    else{
                        printf("%-10s%-13s%-15s%-10s%-7s\n","Per_no","Ad Soyad","Ise Gir Tar","Unvani","Ucr Katsayisi");
                        printf("%-10d%-13s%-15s%-10s%-7.2f\n",personel.per_no,personel.ad_soyad,
                        personel.giris_tarihi,personel.unvani,personel.ucret_katsayisi);
                    }
                break;
                case 2:
                aranan=-1;
                 while(aranan<0||aranan>100){
                    printf("\nBilgilerini ve o ay icindeki mesai kayitlarini gormek istediginiz personelin numarasini giriniz\n");
                    scanf("%d",&aranan);
                    if(aranan<0||aranan>100)
                        printf("Hatali giris yaptiniz.Personel numarasi 1-100 arasinda olmalidir.\n");
                }
                fseek(fdosya,(aranan-1)*sizeof(struct PersonelVerisi),SEEK_SET);
                fread(&personel,sizeof(struct PersonelVerisi),1,fdosya);
                if(personel.per_no==-1)
                    printf("Personel bulunamadi.\n");
                    else{
                        calistigi_saat=personel.toplam_sure/60;
                        calistigi_dk=personel.toplam_sure%60;
                        ucret=saat_ucreti*personel.toplam_sure*personel.ucret_katsayisi/60;
                        printf("%-10s%-13s%-15s%-10s\n","Per_no","Ad Soyad","Sure","Ucret");
                        printf("%-10d%-13s%d sa %d dk %10.2f\n",personel.per_no,personel.ad_soyad,calistigi_saat,calistigi_dk,ucret);
                    }
                fscanf(fdosya2,"%d%d%d%d%d%d",&personel_no,&gun_no,&girilen_saat,&girilen_dk,&cikis_saat,&cikis_dk);
                printf("\nMesai Kayitlari:\n");
                printf("%-10s%-13s%-15s\n","Gun no","Giris Saati","Cikis Saati");
                while(!feof(fdosya2)){
                    if(personel_no==aranan){
                        printf("%-10d   %.2d:%-7.2d   %.2d:%-5.2d\n",gun_no,girilen_saat,girilen_dk,cikis_saat,cikis_dk);
                    }
                    fscanf(fdosya2,"%d%d%d%d%d%d",&personel_no,&gun_no,&girilen_saat,&girilen_dk,&cikis_saat,&cikis_dk);
                }
                personel_no=0;
                rewind(fdosya2);

                break;
                case 3:
                unvanArama(fdosya);
                break;
                case 4:
                yillaraGoreListele(fdosya);

                break;
                case 5:
                    gecGelenleriListele(fdosya2);
                    rewind(fdosya2);

                break;
                case 6:
                    mesaiListele(fdosya,fdosya2);
                    rewind(fdosya2);

                break;
                case 7:
                do{
                    printf("Cikmak istediginize emin misiniz(e/E/h/H)?:\n");
                    fflush(stdin);
                    cikis=getchar();
               }while (cikis != 'e' && cikis != 'E' && cikis!='h' && cikis!='H');
            }
    }while(cikis=='H'||cikis=='h');
    fclose(fdosya);
    fclose(fdosya2);

    return 0;
}

void unvanArama(FILE *fdosya)
{
    char aranan_unvan[16];
    int i,k,uzunluk,j=0;
    struct PersonelVerisi personel={0,"","","",0.0,0};

    printf("Aramak istediginiz unvani giriniz.\n");
    scanf("%s",aranan_unvan);
    uzunluk=strlen(aranan_unvan);

    printf("%-5s%-10s%-21s%-20s%-7s\n","Sira","Per no","Ad Soyad","Ise Giris Tarihi","Ucr Katsayisi");
    for(i=0;i<=100;i++){
        fseek(fdosya,i*sizeof(struct PersonelVerisi),SEEK_SET);
        fread(&personel,sizeof(struct PersonelVerisi),1,fdosya);
        if(personel.per_no!=-1){
            for(k=0;k<16;k++){
                personel.unvani[k]=tolower(personel.unvani[k]);
                aranan_unvan[k]=tolower(aranan_unvan[k]);
            }
        }
        if(strncmp(personel.unvani,aranan_unvan,uzunluk)==0){
            j++;
            printf("%-5d%-10d%-19s%10s%17.2f\n",j,personel.per_no,personel.ad_soyad,personel.giris_tarihi,personel.ucret_katsayisi);
        }
    }
    return;
}
void yillaraGoreListele(FILE *fdosya)
{
    int i,a,j,k;
    int kac_kisi=0,ikibindensonra=0;
    int yil[12]={0};
    float toplam_kisi=0,yuzde=0;
    char karsilastirici[5]={"2000"};
    char gecici_yil[5];
    struct PersonelVerisi personel={0,"","","",0.0,0};
    printf("Ise alinan personel sayilarinin ve yuzdelerinin yillara gore dagiliminin listelenmesi:\n");
    for(i=0;i<=100;i++){
        fseek(fdosya,i*sizeof(struct PersonelVerisi),SEEK_SET);
        fread(&personel,sizeof(struct PersonelVerisi),1,fdosya);
        if(personel.per_no!=-1){
            kac_kisi++;
        }
    }
    for(j=0;j<10;j++){
        for(i=0;i<=100;i++){
            fseek(fdosya,i*sizeof(struct PersonelVerisi),SEEK_SET);
            fread(&personel,sizeof(struct PersonelVerisi),1,fdosya);
            if(personel.per_no!=-1){
                for(a=0;a<5;a++){
                    gecici_yil[a]=personel.giris_tarihi[a+4];
                }
                if(strcmp(gecici_yil,karsilastirici)==0){
                        yil[j]=yil[j]+1;
                }
            }
        }
        karsilastirici[3]=karsilastirici[3]+1;
    }
    for(i=0;i<12;i++){
        ikibindensonra=yil[i]+ikibindensonra;
    }
    toplam_kisi=kac_kisi;
    printf("%d   %d\n\n",kac_kisi,ikibindensonra);
    printf("Yil         Per say    yuzde\n");
    for(i=0;i<12;i++){
        switch(i){
            case 0:
                yuzde=((toplam_kisi-ikibindensonra)/toplam_kisi);
                printf("2000 den once   %d      %.2f\n",kac_kisi-ikibindensonra,yuzde);
                break;
            case 1:
                printf("2000            %d      %.2f\n",yil[i-1],yuzde=(yil[i-1]/toplam_kisi));
                break;
            case 2:
                printf("2001            %d      %.2f\n",yil[i-1],yuzde=(yil[i-1]/toplam_kisi));
                break;
            case 3:
                printf("2002            %d      %.2f\n",yil[i-1],yuzde=(yil[i-1]/toplam_kisi));
                break;
            case 4:
                printf("2003            %d      %.2f\n",yil[i-1],yuzde=(yil[i-1]/toplam_kisi));
                break;
            case 5:
                printf("2004            %d      %.2f\n",yil[i-1],yuzde=(yil[i-1]/toplam_kisi));
                break;
            case 6:
                printf("2005            %d      %.2f\n",yil[i-1],yuzde=(yil[i-1]/toplam_kisi));
                break;
            case 7:
                printf("2006            %d      %.2f\n",yil[i-1],yuzde=(yil[i-1]/toplam_kisi));
                break;
            case 8:
                printf("2007            %d      %.2f\n",yil[i-1],yuzde=(yil[i-1]/toplam_kisi));
                break;
            case 9:
                yuzde=(yil[i-1]/toplam_kisi);
                printf("2008            %d      %.2f\n",yil[i-1],yuzde);
                break;
            case 10:
                printf("2009            %d      %.2f\n",yil[i-1],yuzde=(yil[i-1]/toplam_kisi));
                break;
            case 11:
                printf("2010            %d      %.2f\n",yil[i-1],yuzde=(yil[i-1]/toplam_kisi));
                break;
        }
    }
    printf("\nToplam:         %.f\n",toplam_kisi);
    return;
}
void gecGelenleriListele(FILE *fdosya2)
{
    int personel_no,gun_no,giris_saat,giris_dk,cikis_saat,cikis_dk;
    int i;
    int personel[100]={0};
    printf("Mesaiye gec gelen personeller:\n");

    fscanf(fdosya2,"%d%d%d%d%d%d",&personel_no,&gun_no,&giris_saat,&giris_dk,&cikis_saat,&cikis_dk);
    while(!feof(fdosya2)){
        if(giris_saat>9){
            personel[personel_no]=personel[personel_no]+1;
        }
        if((giris_saat==9)&&(giris_dk>0)){
            personel[personel_no]=personel[personel_no]+1;
        }
        fscanf(fdosya2,"%d%d%d%d%d%d",&personel_no,&gun_no,&giris_saat,&giris_dk,&cikis_saat,&cikis_dk);
    }
    printf("Per No      Kac kez gec gelmis\n");
    for(i=0;i<100;i++){
        if(personel[i]!=0){
            printf("%d           %d\n",i,personel[i]);
        }
    }
    return;
}
void mesaiListele(FILE *fdosya,FILE *fdosya2)
{
    int aranan_gun,calisilan_saat,calisilan_dk,i=0;
    int personel_no,gun_no,giris_saat,giris_dk,cikis_saat,cikis_dk;
    struct PersonelVerisi personel={0,"","","",0.0,0};
    int calisilan_toplam_dk;
    int ortalama_saat,toplam_saat=0;
    float toplam_dk=0,ortalama_dk;

    printf("Mesai kayitlarini gormek istediginiz gunun numarasini giriniz:\n");
    scanf("%d",&aranan_gun);
    fscanf(fdosya2,"%d%d%d%d%d%d",&personel_no,&gun_no,&giris_saat,&giris_dk,&cikis_saat,&cikis_dk);
    printf("%-10s%-20s%-18s%-16s%-7s\n","Per no","Ad Soyad","Giris Saati","Cikis Saati","Sure");
    while(!feof(fdosya2)){
        calisilan_toplam_dk=0;
        if(gun_no==aranan_gun){
            fseek(fdosya,(personel_no-1)*sizeof(struct PersonelVerisi),SEEK_SET);
            fread(&personel,sizeof(struct PersonelVerisi),1,fdosya);
            calisilan_toplam_dk=(cikis_saat-giris_saat)*60+cikis_dk-giris_dk;
            calisilan_saat=calisilan_toplam_dk/60;
            calisilan_dk=calisilan_toplam_dk%60;
            toplam_dk=calisilan_dk+toplam_dk;
            toplam_saat=calisilan_saat+toplam_saat;
            i++;
            printf("%-10d%-20s%.2d:%-10.2d     %.2d:%-10.2d   %d sa %d dk\n",personel_no,personel.ad_soyad,giris_saat,giris_dk,cikis_saat,
                                                            cikis_dk,calisilan_saat,calisilan_dk);
        }
        fscanf(fdosya2,"%d%d%d%d%d%d",&personel_no,&gun_no,&giris_saat,&giris_dk,&cikis_saat,&cikis_dk);
    }
    ortalama_saat=toplam_saat/i;
    ortalama_dk=(toplam_dk/i)+(((toplam_saat-(ortalama_saat*i))*60)/i);
    printf("\nO gun icin calisma surelerinin ortalamasi: %d sa %.2f dk\n",ortalama_saat,ortalama_dk);
    return;
}




