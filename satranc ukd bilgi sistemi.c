#include <stdio.h>
#include <stdlib.h>
struct sporcular
{
    int lisans_no;
    int tc_no;
    char ad_soyad[30];
    int plaka;
    int ukd;
};
struct turnuva
{
    int turnuva_no;
    char turnuva_ad[40];
    char tarih[10];
    char sehir[15];
};
struct maclar
{
    int tur_no;
    int beyaz_lisans;
    int siyah_lisans;
    int sonuc;
    float beyaz_ukd;
    float siyah_ukd;
};
void menu();
void oyuncu_listeleme(FILE*);
void biten_turnuva(FILE *,FILE *,FILE *,FILE *,FILE *);
void oyuncu_bilgileri_ve_maclar(FILE *,FILE *,FILE *,FILE *);
void bir_ildeki_oyuncular(FILE *);
void top10_ukd(FILE *);
void illere_gore_oyuncu_sayisi(FILE *);
void bir_turnuvanin_bilgileri(FILE *,FILE *,FILE *);
void siyah_beyaz_karsilastirma(FILE *);
void yeni_oyuncu_ekleme(FILE *);
void oyuncu_il_guncelleme(FILE *);
int main()
{
    int secim;
    FILE *ptr_sporcu;
    FILE *ptr_turnuva;
    FILE *ptr_turnuva_genel;
    FILE *ptr_tum_maclar;
    FILE *ptr_turnuva_maclar;
    do
    {
        menu();
        printf("lutfen seciminizi giriniz\n");
        scanf("%d",&secim);

        if((ptr_sporcu=fopen("sporcular.dat","wb+"))==NULL)
            printf("file couldn't be open");

        if((ptr_turnuva=fopen("turnuva.dat","wb+"))==NULL)
            printf("file couldn't be open");

        if((ptr_tum_maclar=fopen("tum_maclar.txt","wb+"))==NULL)
            printf("file couldn't be open");

        if((ptr_turnuva_genel=fopen("turnuva_genel.txt","wb+"))==NULL)
            printf("file couldn't be open");

        if((ptr_turnuva_maclar=fopen("turnuva_maclar.txt","wb+"))==NULL)
            printf("file couldn't be open");

        switch(secim)
        {
        case 1:
            biten_turnuva(ptr_turnuva_genel,ptr_turnuva_maclar,ptr_tum_maclar,ptr_turnuva,ptr_sporcu);
            fclose(ptr_turnuva_genel);
            fclose(ptr_turnuva_maclar);
            fclose(ptr_turnuva);
            fclose(ptr_tum_maclar);
            fclose(ptr_sporcu);
            break;
        case 2:
            oyuncu_listeleme(ptr_sporcu);
            fclose(ptr_sporcu);
            break;
        case 3:
            oyuncu_bilgileri_ve_maclar(ptr_sporcu,ptr_tum_maclar,ptr_turnuva_maclar,ptr_turnuva);
            fclose(ptr_sporcu);
            fclose(ptr_tum_maclar);
            fclose(ptr_turnuva);
            fclose(ptr_turnuva_maclar);
            break;
        case 4:
            bir_ildeki_oyuncular(ptr_sporcu);
            fclose(ptr_sporcu);
            break;
        case 5:
            top10_ukd(ptr_sporcu);
            fclose(ptr_sporcu);
            break;
        case 6:
            illere_gore_oyuncu_sayisi(ptr_sporcu);
            fclose(ptr_sporcu);
            break;
        case 7:
            bir_turnuvanin_bilgileri(ptr_turnuva_genel,ptr_turnuva,ptr_sporcu);
            fclose(ptr_turnuva_genel);
            fclose(ptr_turnuva);
            fclose(ptr_sporcu);
            break;
        case 8:
            siyah_beyaz_karsilastirma(ptr_turnuva_genel);
            fclose(ptr_turnuva_genel);
            break;
        case 9:
            yeni_oyuncu_ekleme(ptr_sporcu);
            fclose(ptr_sporcu);
            break;
        case 10:
            oyuncu_il_guncelleme(ptr_sporcu);
            fclose(ptr_sporcu);
            break;
        case 11:
            exit(0);
        }
    }
    while(secim>0 || secim<11);
    return 0;
}
void menu()
{
    printf("1) Biten bir turnuvaya iliþkin bilgilerin sisteme aktarýlmasý\n");
    printf("2) Bir oyuncunun bilgilerinin listelenmesi\n");
    printf("3) Bir oyuncunun bilgilerinin ve katýldýðý turnuvalarda oynadýðý maçlarýn listelenmesi\n");
    printf("4) Bir ildeki tüm oyuncularýn listelenmesi\n");
    printf("5) UKD puaný en yüksek 10 oyuncunun listelenmesi\n");
    printf("6) Ýllerdeki oyuncu sayýlarýnýn listelenmesi\n");
    printf("7) Bir turnuvanýn bilgilerinin ve turnuvada oynanan maçlarýn listelenmesi\n");
    printf("8) Tüm maçlardaki beyaz-siyah karþýlaþtýrmasý\n");
    printf("9) Yeni bir oyuncunun eklenmesi\n");
    printf("10) Bir oyuncunun ilinin güncellenmesi\n");
}
void biten_turnuva(FILE *ptr_turnuva_genel,FILE *ptr_turnuva_maclar,FILE *ptr_tum_maclar,FILE *ptr_turnuva,FILE *ptr_sporcu)
{
    int i=0,sayac_lisans=0,sayac=0,gosterici=0,j;
    struct turnuva Tdat;
    struct turnuva Tdat2;
    struct maclar dosya_maclar;
    struct sporcular dosya_sporcu;
    int lisans_no[100];
    float ukd_ort;
    do
    {
        i=0;
        fseek(ptr_turnuva_genel,gosterici,SEEK_SET);
        fgets(Tdat.turnuva_ad,40,ptr_turnuva_genel);
        fgets(Tdat.sehir,15,ptr_turnuva_genel);
        fgets(Tdat.tarih,10,ptr_turnuva_genel);
        fscanf(ptr_turnuva_genel,"%f\n",&ukd_ort);
        do
        {
            do
            {
                gosterici=ftell(ptr_turnuva_genel);
                fscanf(ptr_turnuva_genel,"%d\n",&lisans_no[i]);
                i++;

            }
            while((char)lisans_no[i]<'A' || (char)lisans_no[i]>'z' || !feof(ptr_turnuva_genel));
        }
        while((lisans_no[i]>65 && lisans_no[i]<122 )|| !feof(ptr_turnuva_genel));
        sayac=0;
        do
        {

            fseek(ptr_turnuva,sizeof(Tdat2),SEEK_SET);
            fread(&Tdat2,sizeof(Tdat2),1,ptr_turnuva);
            sayac++;

        }
        while(!feof(ptr_turnuva));
        Tdat.turnuva_no=sayac+1;
        sayac_lisans=0;
        do
        {
            fread(&dosya_maclar,sizeof(dosya_maclar),1,ptr_turnuva_maclar);
            for(j=0;j<i;j++)
            {
                if(lisans_no[j]==dosya_maclar.beyaz_lisans || lisans_no[j]==dosya_maclar.siyah_lisans)
                sayac_lisans++;
            }

            if(sayac_lisans==2)
            {
                fprintf(ptr_tum_maclar,"%d\n",Tdat.turnuva_no);
                fwrite(&dosya_maclar,sizeof(dosya_maclar),1,ptr_tum_maclar);
            }

        }
        while(!feof(ptr_turnuva_maclar));
         do
        {
            fseek(ptr_sporcu,sizeof(dosya_sporcu),SEEK_SET);
            fread(&dosya_sporcu,sizeof(dosya_sporcu),1,ptr_sporcu);

            if(dosya_sporcu.ukd==0)
                dosya_sporcu.ukd=ukd_ort;
            if(dosya_sporcu.lisans_no==dosya_maclar.siyah_lisans)
                dosya_sporcu.ukd=dosya_sporcu.ukd+(int)dosya_maclar.siyah_ukd;
            if(dosya_sporcu.lisans_no==dosya_maclar.beyaz_lisans)
                dosya_sporcu.ukd=dosya_sporcu.ukd+(int)dosya_maclar.beyaz_lisans;
            if(dosya_sporcu.ukd<1000)
                dosya_sporcu.ukd=0;

        }
        while(!feof(ptr_sporcu));
        fwrite(&dosya_sporcu,sizeof(dosya_sporcu),1,ptr_sporcu);

    }
    while(!feof(ptr_turnuva_genel));

}
void oyuncu_listeleme(FILE *ptr_sporcu)
{
    struct sporcular dosya_sporcu;
    int tcKimlik_no;
    int sayac=0;
    do
    {
        do
        {
            printf("goruntlemek istediginiz oyuncunun tc kimlik numarasini giriniz\n");
            scanf("%d",&tcKimlik_no);

            fseek(ptr_sporcu,sizeof(dosya_sporcu),SEEK_SET);
            fread(&dosya_sporcu,sizeof(dosya_sporcu),1,ptr_sporcu);
            if(dosya_sporcu.tc_no==tcKimlik_no)
            {
                printf("Lisans No  TC Kimlik No   Ad Soyad   Ýli     UKD Puani ");
                printf("%d    %d    %s   %d   %d",dosya_sporcu.lisans_no,dosya_sporcu.tc_no,dosya_sporcu.ad_soyad,dosya_sporcu.plaka,dosya_sporcu.ukd);
                sayac=1;
            }
        }
        while(!feof(ptr_sporcu));
        if(sayac==0)
        {
            printf("aradiginiz tc numarasina sahip kisi bulunamadi\n");
            printf("tekrar");
        }

    }
    while(sayac==0);
}
void oyuncu_bilgileri_ve_maclar(FILE *ptr_sporcu,FILE *ptr_tum_maclar,FILE *ptr_turnuva_maclar,FILE *ptr_turnuva)
{
    struct sporcular dosya_sporcu , dosya_sporcu_rakip;
    struct maclar dosya_maclar;
    struct turnuva dosya_turnuva;
    int oyuncu_lisans_no;
    int maclar_turnuva_no;
    float sonuc_puan;

    printf("oyuncunun lisans numarasini giriniz:\n");
    scanf("%d",&oyuncu_lisans_no);
    do
    {
        fseek(ptr_sporcu,sizeof(dosya_sporcu),SEEK_SET);
        fread(&dosya_sporcu,sizeof(dosya_sporcu),1,ptr_sporcu);
        if(dosya_sporcu.lisans_no==oyuncu_lisans_no)
        {
            printf("Lisans No  TC Kimlik No   Ad Soyad   Ýli     UKD Puani ");
            printf("%d    %d    %s   %d   %d",dosya_sporcu.lisans_no,dosya_sporcu.tc_no,dosya_sporcu.ad_soyad,dosya_sporcu.plaka,dosya_sporcu.ukd);

        }

    }
    while(!feof(ptr_sporcu));

    do
    {
        fscanf(ptr_tum_maclar,"%d\n",&maclar_turnuva_no);
        fread(&dosya_maclar,sizeof(dosya_maclar),1,ptr_tum_maclar);
        if(dosya_maclar.siyah_lisans==oyuncu_lisans_no)
        {
            if(dosya_maclar.sonuc==1)
                sonuc_puan=1;
            if(dosya_maclar.sonuc==2)
                sonuc_puan=0;
            if(dosya_maclar.sonuc==0)
                sonuc_puan=0,5;
            do
            {
                fseek(ptr_turnuva,sizeof(dosya_turnuva),SEEK_SET);
                fread(&dosya_turnuva,sizeof(dosya_turnuva),1,ptr_turnuva);
                if(dosya_turnuva.turnuva_no==maclar_turnuva_no)
                {

                    printf("Katıldığı Turnuvalar ve Oynadığı Maçlar:\n");
                    printf("Turnuva Adı, Tarihi ve Şehri: %s    %s    %s\n",dosya_turnuva.turnuva_ad,dosya_turnuva.tarih,dosya_turnuva.sehir);

                    do
                    {
                        fseek(ptr_sporcu,sizeof(dosya_sporcu_rakip),SEEK_SET);
                        fread(&dosya_sporcu_rakip,sizeof(dosya_sporcu_rakip),1,ptr_sporcu);

                        if(dosya_sporcu_rakip.lisans_no==dosya_maclar.beyaz_lisans)
                        {
                            printf("Tur No Rakip Ad Soyad Rakip UKD Maç Puanı UKD Değişimi");
                            printf("%d    %s      %d     %f   %f \n",dosya_maclar.tur_no,dosya_sporcu_rakip.ad_soyad,dosya_sporcu_rakip.ukd,sonuc_puan,dosya_maclar.beyaz_ukd);
                        }

                    }
                    while(!feof(ptr_sporcu));
                }
            }
            while(!feof(ptr_turnuva));

        }
        else if(dosya_maclar.beyaz_lisans==oyuncu_lisans_no)
        {
            if(dosya_maclar.sonuc==1)
                sonuc_puan=0;
            if(dosya_maclar.sonuc==2)
                sonuc_puan=1;
            if(dosya_maclar.sonuc==0)
                sonuc_puan=0,5;
            do
            {
                fseek(ptr_turnuva,sizeof(dosya_turnuva),SEEK_SET);
                fread(&dosya_turnuva,sizeof(dosya_turnuva),1,ptr_turnuva);
                if(dosya_turnuva.turnuva_no==maclar_turnuva_no)
                {

                    printf("Katıldığı Turnuvalar ve Oynadığı Maçlar:\n");
                    printf("Turnuva Adı, Tarihi ve Şehri: %s    %s    %s\n",dosya_turnuva.turnuva_ad,dosya_turnuva.tarih,dosya_turnuva.sehir);

                    do
                    {
                        fseek(ptr_sporcu,sizeof(dosya_sporcu),SEEK_SET);
                        fread(&dosya_sporcu_rakip,sizeof(dosya_sporcu),1,ptr_sporcu);

                        if(dosya_sporcu_rakip.lisans_no==dosya_maclar.siyah_lisans)
                        {
                            printf("Tur No Rakip Ad Soyad Rakip UKD Maç Puanı UKD Değişimi");
                            printf("%d    %s      %d     %f   %f \n",dosya_maclar.tur_no,dosya_sporcu_rakip.ad_soyad,dosya_sporcu_rakip.ukd,sonuc_puan,dosya_maclar.siyah_ukd);
                        }

                    }
                    while(!feof(ptr_sporcu));
                }
            }
            while(!feof(ptr_turnuva));

        }
    }
    while(!feof(ptr_tum_maclar));

}
void bir_ildeki_oyuncular(FILE *ptr_sporcu)
{
    struct sporcular dosya_sporcu[100],gecici_dosya;
    int il_plaka,index=0,i,j;
    printf("goruntulemek istediginiz ilin plaka kodunu giriniz:\n");
    scanf("%d",&il_plaka);
    do
    {
        fseek(ptr_sporcu,sizeof(dosya_sporcu),SEEK_SET);
        fread(&dosya_sporcu[index],sizeof(dosya_sporcu),1,ptr_sporcu);
        if(dosya_sporcu[index].plaka==il_plaka)
        {
            index++;
        }

    }
    while(!feof(ptr_sporcu));
    for(j=0; j<index; j++)
    {
        for(i=0; i<index-1; i++)
        {
            if(dosya_sporcu[i].lisans_no>dosya_sporcu[i+1].lisans_no)
            {
                gecici_dosya=dosya_sporcu[i];
                dosya_sporcu[i]=dosya_sporcu[i+1];
                dosya_sporcu[i+1]=gecici_dosya;
            }
        }
    }
    printf("lisans no....tc kimlik no....ad soyad........ili....ukd puani\n");

    for(i=0; i<index; i++)
    {
        printf("%d     %d      %s      %d      %d\n",dosya_sporcu[i].lisans_no,dosya_sporcu[i].tc_no,dosya_sporcu[i].ad_soyad,dosya_sporcu[i].plaka,dosya_sporcu[i].ukd);
    }

}
void top10_ukd(FILE *ptr_sporcu)
{
    struct sporcular dosya_sporcu[100],gecici_dosya;
    int index=0,i,j;

    do
    {
        fseek(ptr_sporcu,sizeof(dosya_sporcu),SEEK_SET);
        fread(&dosya_sporcu[index],sizeof(dosya_sporcu),1,ptr_sporcu);


        index++;

    }
    while(!feof(ptr_sporcu));
    for(j=0; j<index; j++)
    {
        for(i=0; i<index-1; i++)
        {
            if(dosya_sporcu[index].ukd<dosya_sporcu[index+1].ukd)
            {
                gecici_dosya=dosya_sporcu[index];
                dosya_sporcu[index]=dosya_sporcu[index+1];
                dosya_sporcu[index+1]=gecici_dosya;
            }
        }

    }
    index=9;
    while(dosya_sporcu[index].ukd==dosya_sporcu[index+1].ukd)
    {
        index++;
    }
    printf("lisans no....tc kimlik no....ad soyad........ili....ukd puani\n");
    for(i=0; i<index; i++)
    {
        printf("%d     %d     %s      %d     %d\n",dosya_sporcu[i].lisans_no,dosya_sporcu[i].tc_no,dosya_sporcu[i].ad_soyad,dosya_sporcu[i].plaka,dosya_sporcu[i].ukd);
    }
}
void illere_gore_oyuncu_sayisi(FILE *ptr_sporcu)
{
    struct sporcular dosya_sporcu[100];
    int index=0,i,j;
    int plaka_no[80]= {0},gecici_plaka,plaka_index[80]= {0};

    do
    {
        fseek(ptr_sporcu,sizeof(dosya_sporcu),SEEK_SET);
        fread(&dosya_sporcu[index],sizeof(dosya_sporcu),1,ptr_sporcu);

        plaka_no[dosya_sporcu[index].plaka]++;
        index++;

    }
    while(!feof(ptr_sporcu));
    for(j=0; j<79; j++)
    {
        for(i=0; i<80; i++)
        {
            if(plaka_no[i]<plaka_no[i+1])
            {
                gecici_plaka=plaka_no[i];
                plaka_no[i]=plaka_no[i+1];
                plaka_no[i+1]=gecici_plaka;
                plaka_index[j]=i+1;

            }
        }

    }
    printf("il plaka kodu......oyuncu sayisi\n");
    i=0;
    do
    {
        printf("%d ------  %d\n",plaka_index[i],plaka_no[i]);
        i++;
    }
    while(plaka_no[i]==0);
}
void bir_turnuvanin_bilgileri(FILE *ptr_turnuva_genel,FILE *ptr_turnuva,FILE *ptr_sporcu)
{
    struct turnuva dosya_turnuva;
    struct sporcular dosya_sporcu;
    struct maclar dosya_turnuva_maclar;
    int dosyaTurnuva_no,anahtar;

    printf("goruntulemek istediginiz turnuvanin numarasini giriniz:\n");
    scanf("%d",&anahtar);

    do
    {
        fscanf(ptr_turnuva_genel,"%d\n",&dosyaTurnuva_no);
        fread(&dosya_turnuva_maclar,sizeof(dosya_turnuva_maclar),1,ptr_turnuva_genel);
        if(anahtar==dosyaTurnuva_no)
        {
            fseek(ptr_turnuva,sizeof(dosya_turnuva),SEEK_SET);
            fread(&dosya_turnuva,sizeof(dosya_turnuva),1,ptr_turnuva);
            if(dosyaTurnuva_no==dosya_turnuva.turnuva_no)
            {
                printf("turnuva no...turnuva adi..........tarih.....sehir\n");
                printf("%d----%s----%s---%s\n",dosya_turnuva.turnuva_no,dosya_turnuva.turnuva_ad,dosya_turnuva.tarih,dosya_turnuva.sehir);
            }
            printf("    beyaz oynayanlar  --- siyah oynayanlar    \n");

            do
            {
                fseek(ptr_sporcu,sizeof(dosya_sporcu),SEEK_SET);
                fread(&dosya_sporcu,sizeof(dosya_sporcu),1,ptr_sporcu);
                if(dosya_turnuva_maclar.beyaz_lisans==dosya_sporcu.lisans_no)
                {
                    printf("%d    %s   %d   %d",dosya_turnuva_maclar.tur_no,dosya_sporcu.ad_soyad,dosya_sporcu.ukd,dosya_turnuva_maclar.sonuc);
                }
                else  if(dosya_turnuva_maclar.siyah_lisans==dosya_sporcu.lisans_no)
                {
                    printf("%d    %s   %d  \n",dosya_turnuva_maclar.sonuc,dosya_sporcu.ad_soyad,dosya_sporcu.ukd);
                }
            }
            while(!feof(ptr_sporcu));
        }

    }
    while(!feof(ptr_turnuva_genel));
}
void siyah_beyaz_karsilastirma(FILE *ptr_turnuva_genel)
{
    struct maclar dosya_maclar;
    int dosyaTurnuva_no;
    float ukd_degisim_beyaz=0,ukd_degisim_siyah=0,beyaz_puan=0,siyah_puan=0;
    do
    {

        fscanf(ptr_turnuva_genel,"%d\n",&dosyaTurnuva_no);
        fread(&dosya_maclar,sizeof(dosya_maclar),1,ptr_turnuva_genel);
        if(dosya_maclar.sonuc==1)
        {
            beyaz_puan=1+beyaz_puan;
        }
        else if(dosya_maclar.sonuc==2)
        {
            siyah_puan=1+siyah_puan;
        }
        else
        {
            siyah_puan=0.5+siyah_puan;
            beyaz_puan=0.5+beyaz_puan;
        }
        ukd_degisim_beyaz=dosya_maclar.beyaz_ukd+ukd_degisim_beyaz;
        ukd_degisim_siyah=dosya_maclar.siyah_ukd+ukd_degisim_siyah;
    }
    while(!feof(ptr_turnuva_genel));
    printf("\t\t\tbeyaz oynayanlar----siyah oynayanlar\n");
    printf("toplam mac puani   : %f         %f\n",beyaz_puan,siyah_puan);
    printf("toplam ukd degisim : %f         %f\n",ukd_degisim_beyaz,ukd_degisim_siyah);

}
void yeni_oyuncu_ekleme(FILE *ptr_sporcu)
{
    struct sporcular dosya_sporcu;
    int anahtar,sayac,oyuncu_plaka;
    long int oyuncu_tcKimlik;
    do
    {
        sayac=0;
        printf("eklemek istediginiz oyuncunun lisans numarasini giriniz:\n");
        scanf("%d",&anahtar);

        fseek(ptr_sporcu,sizeof(dosya_sporcu),SEEK_SET);
        fread(&dosya_sporcu,sizeof(dosya_sporcu),1,ptr_sporcu);
        if(anahtar==dosya_sporcu.lisans_no)
        {
            printf("bu lisans numaarsina sahip oyuncu bulunmakta tekrar");
            sayac=1;
        }
    }
    while(sayac==1);
    printf("oyuncunun tc kimlik numarasini giriniz:\n");
    scanf("%ld",&oyuncu_tcKimlik);
    printf("oyuncunun adini ve soyadini giriniz: \n");
    gets(dosya_sporcu.ad_soyad);
    printf("oyuncunun sehir plaka kodunu giriniz :\n");
    scanf("%d",&oyuncu_plaka);
    dosya_sporcu.lisans_no=anahtar;
    dosya_sporcu.tc_no=oyuncu_tcKimlik;
    dosya_sporcu.plaka=oyuncu_plaka;
    dosya_sporcu.ukd=0;
    fseek(ptr_sporcu,sizeof(dosya_sporcu),SEEK_SET);
    fwrite(&dosya_sporcu,sizeof(dosya_sporcu),1,ptr_sporcu);
}
void oyuncu_il_guncelleme(FILE *ptr_sporcu)
{
    struct sporcular dosya_sporcu;
    int oyuncu_lisans,oyuncu_plaka;
    do
    {
        printf("sehir numarasini guncellemek istediginiz oyuncunun lisans numarasini giriniz:\n");
        scanf("%d",&oyuncu_lisans);

        fseek(ptr_sporcu,sizeof(dosya_sporcu),SEEK_SET);
        fread(&dosya_sporcu,sizeof(dosya_sporcu),1,ptr_sporcu);
        if(oyuncu_lisans==dosya_sporcu.lisans_no)
        {
            printf("yeni sehir numarasini giriniz: \n");
            scanf("%d",&oyuncu_plaka);
            dosya_sporcu.plaka=oyuncu_plaka;
            fwrite(&dosya_sporcu,sizeof(dosya_sporcu),1,ptr_sporcu);
        }
    }
    while(!feof(ptr_sporcu));
}


