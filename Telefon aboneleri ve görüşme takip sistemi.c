#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ABONE_SAY 900
#define BOS_KAYIT 0

void abone_sil(FILE *,FILE *);
void menu_goruntule();
int abone_goruntule(FILE *) ;
void dis_hat_gorusme_listele (FILE *, FILE *);
void birim_bazinda_listele(FILE *);
void tip_bazinda_listele (FILE *);
int gun_bazinda_listele(FILE *,FILE *);
void toplam_gorusme_listele(FILE *);
void dis_hat_kontor_ihtiyaci(FILE *);
void kontor_yukle(FILE *);
void dis_hat_kayit_ekle(FILE *,FILE *);
void abone_ekle(FILE *);
void kontor_guncelle(int,int,FILE *);
int sayi_al(int,int);

struct aboneler
{
    char ad_soyad[26];
    char birim_adi[31];
    int abone_tipi;
    int kontor;
};

struct gorusmeler
{
    int arayan_dahili_telefon_no;
    char aranan_dis_hat_telefon_no[11];
    int tarih;
    int baslangic_saati;
    int baslangic_dakikasi;
    int sure;

};
typedef struct aboneler Abone_type;
typedef struct gorusmeler Gorusme_type;

char tip[4][10]= {{"Akademik"},{"Idari"},{"Yonetici"},{"Diger"}};

int main()
{
    FILE *fAboneler;
    FILE *fGorusmeler;

    int secenek;

    if((fAboneler=fopen("aboneler.dat","rb+"))==NULL)
        printf("Aboneler dosyasi acilamadi.");

    else
    {
        if((fGorusmeler=fopen("gorusmeler.txt","a+"))==NULL)
            printf("Gorusmeler dosyasi acilamadi.");

        else
        {
            do
            {
                menu_goruntule();
                secenek = sayi_al(1,12);

                switch (secenek)
                {
                case 1:
                    system("cls");
                    abone_goruntule(fAboneler);
                    break;
                case 2:
                    system("cls");
                    dis_hat_gorusme_listele(fAboneler,fGorusmeler);
                    break;
                case 3:
                    system("cls");
                    birim_bazinda_listele(fAboneler);
                    break;
                case 4:
                    system("cls");
                    tip_bazinda_listele(fAboneler);
                    break;
                case 5:
                    system("cls");
                    gun_bazinda_listele(fGorusmeler,fAboneler);
                    break;
                case 6:
                    system("cls");
                    toplam_gorusme_listele(fGorusmeler);
                    break;
                case 7:
                    system("cls");
                    dis_hat_kontor_ihtiyaci(fAboneler);
                    break;
                case 8:
                    system("cls");
                    kontor_yukle(fAboneler);
                    break;
                case 9:
                    system("cls");
                    dis_hat_kayit_ekle(fAboneler,fGorusmeler);
                    break;
                case 10:
                    system("cls");
                    abone_ekle(fAboneler);
                    break;
                case 11:
                    system("cls");
                    abone_sil(fAboneler,fGorusmeler);
                    break;
                default:
                    break;
                }
            }
            while(secenek!=12);

            fclose(fGorusmeler);
        }
        fclose(fAboneler);
    }

    return 0;
}
int sayi_al(int alt_sinir, int ust_sinir)
{
    int sayi;
    scanf("%d",&sayi);

    while (sayi<alt_sinir || sayi>ust_sinir)
    {
        printf("Hatali veri girisi, veriyi %d ile %d arasinda tekrar giriniz:",alt_sinir,ust_sinir);
        scanf("%d",&sayi);
    }
    return sayi;
}

void menu_goruntule()
{
    printf("\n1) Abone bilgisinin gosterilmesi.\n");
    printf("2) Abonenin bilgisinin ve ay icerisinde yaptigi dishat gorusmelerinin gosterilmesi.\n");
    printf("3) Bir birimdeki abonelerin bilgilerinin listelenmesi.\n");
    printf("4) Abone tipine gore abone sayilarinin ve yuzdelerinin listelenmesi.\n");
    printf("5) Bir gun icerisinde yapilan gorusmelerin listelenmesi.\n");
    printf("6) Gune gore gorusme sayilarinin ve surelerinin listelenmesi.\n");
    printf("7) Dis hat gorusmesi yapabilmek icin kontor yuklemesi gereken abonelerin listelenmesi.\n");
    printf("8) Bir abonenin kontor yuklemesi.\n");
    printf("9) Dis hat gorusme kaydi eklenmesi.\n");
    printf("10) Yeni bir abone eklenmesi.\n");
    printf("11) Abone silinmesi.\n");
}


int abone_goruntule(FILE *fAboneler)
{
    Abone_type bir_abone;
    int tel_no;
    int kayit_no;

    printf("Bilgilerini istediginiz abonenin dahili telefon numarasini giriniz(100-999): ");
    tel_no=sayi_al(100,999);

    kayit_no=tel_no-99;                                                         //rahat kullanmak amaciyla 1 den baslatýlýyor
    fseek(fAboneler,(kayit_no-1)*sizeof(Abone_type),SEEK_SET);                  //istenen kisim dosyada aranýyor
    fread(&bir_abone,sizeof(Abone_type),1,fAboneler);                           //dosyada bulunuyor

    if(bir_abone.abone_tipi==0)                                                 //kontrol
    {
        printf("Boyle bir abone yok !");
    }
    else
    {
        printf("Tel No Ad Soyad                  Birimi                         Tip        Kontor \n");
        printf("------ ------------------------- ------------------------------ ---------- ---------\n");
        printf("%-6d %-25s %-30s %-10s %-9d\n", tel_no,bir_abone.ad_soyad,bir_abone.birim_adi,tip[bir_abone.abone_tipi-1],bir_abone.kontor);
    }
    rewind(fAboneler);
    return tel_no;
}

void dis_hat_gorusme_listele (FILE *fAboneler, FILE *fGorusmeler)
{
    int abone_no, bulundu=0,gunduz_sure=0,gece_sure = 0;
    int kayit_no;
    Gorusme_type bir_gorusme;
    Abone_type bir_abone;
    abone_no=abone_goruntule(fAboneler);

    kayit_no=abone_no-99;
    fseek(fAboneler,(kayit_no-1)*sizeof(Abone_type),SEEK_SET);
    fread(&bir_abone,sizeof(Abone_type),1,fAboneler);

    if(bir_abone.abone_tipi != BOS_KAYIT)
    {
        printf("\n Bu ay yapilan dis hat gorusmeleri :\n");
        printf("Aranan Tel No Gun No Baslangic Bitis \n");
        printf("------------- ------ --------- -----\n");
        rewind(fGorusmeler);
        int i;

        fscanf(fGorusmeler,"%d %s %d %d %d %d",&bir_gorusme.arayan_dahili_telefon_no,bir_gorusme.aranan_dis_hat_telefon_no,&bir_gorusme.tarih,&bir_gorusme.baslangic_saati,&bir_gorusme.baslangic_dakikasi,&bir_gorusme.sure);

        while (!feof(fGorusmeler))
        {
            fscanf(fGorusmeler,"%d %s%d %d %d %d",&bir_gorusme.arayan_dahili_telefon_no,bir_gorusme.aranan_dis_hat_telefon_no,&bir_gorusme.tarih,&bir_gorusme.baslangic_saati,&bir_gorusme.baslangic_dakikasi,&bir_gorusme.sure);

            if (abone_no==bir_gorusme.arayan_dahili_telefon_no)
            {
                int zaman = bir_gorusme.baslangic_saati*60+bir_gorusme.baslangic_dakikasi;
                int zamanSure = (bir_gorusme.baslangic_saati*60+bir_gorusme.baslangic_dakikasi+bir_gorusme.sure)%1440;

                printf("%-13s %-6d %-2d:%-6d %-2d:%-2d\n",bir_gorusme.aranan_dis_hat_telefon_no,bir_gorusme.tarih,bir_gorusme.baslangic_saati,bir_gorusme.baslangic_dakikasi,zamanSure/60,zamanSure%60);
                bulundu++;
                for(i=1; i<=bir_gorusme.sure; i++)
                {
                    if(zaman<481 || zaman>1200)
                    {
                        gece_sure++;
                    }
                    else
                    {
                        gunduz_sure++;
                    }
                    zaman+=i;
                }
            }
        }

        int kontor = gece_sure*2 + gunduz_sure*3 + bulundu*3;
        printf("\nToplam gorusme sayisi: %d\n",bulundu);
        printf("Toplam gunduz gorusme suresi: %d\n",gunduz_sure);
        printf("Toplam gece gorusme suresi: %d\n",gece_sure);
        printf("Toplam harcadigi kontor: %d\n",kontor);

    }
    else
    {
        printf("Boyle bir kullanici bulunmamaktadir.\n");
    }
    rewind(fAboneler);
    rewind(fGorusmeler);

    return;
}


void birim_bazinda_listele(FILE *fAboneler)
{
    int i;
    char birim_adi[31];
    Abone_type bir_abone;

    printf("Bilgilerini istediginiz birimi giriniz: ");
    fflush(stdin);
    gets(birim_adi);

    printf("\nTel No Ad Soyad                  Birimi                         Tip        Kontor \n");
    printf("------ ------------------------- ------------------------------ ---------- ---------\n");
    for(i=1; i<MAX_ABONE_SAY; i++)
    {
        fseek(fAboneler,(i-1)*sizeof(Abone_type),SEEK_SET);
        fread(&bir_abone,sizeof(Abone_type),1,fAboneler);


        if(strcmp(bir_abone.birim_adi,birim_adi)==0 && bir_abone.abone_tipi!=0)
        {
            printf("%-6d %-25s %-30s %-10s %-9d\n", i+99,bir_abone.ad_soyad,bir_abone.birim_adi,tip[bir_abone.abone_tipi-1],bir_abone.kontor);
        }
    }
    return;
}

void tip_bazinda_listele (FILE *fAboneler)
{
    Abone_type bir_abone;
    int i;
    int akademikSay=0,IdariSay=0,digerSay=0,YoneticiSay=0,bosSay=0;

    for (i=0; i<MAX_ABONE_SAY; i++)
    {
        fseek(fAboneler,i*sizeof(Abone_type),SEEK_SET);
        fread(&bir_abone,sizeof(Abone_type),1,fAboneler);

        switch (bir_abone.abone_tipi)
        {
        case 1:
            akademikSay++;
            break;
        case 2:
            IdariSay++;
            break;
        case 3:
            YoneticiSay++;
            break;
        case 4:
            digerSay++;
            break;
        default:
            bosSay++;
            break;
        }

    }

    printf("\nAbone Tipi Abone Sayisi Yuzde\n");
    printf("---------- ----------- -----\n");
    printf("Akademik   %-11d %.2f\n",akademikSay,(float)akademikSay*100/MAX_ABONE_SAY);
    printf("Idari      %-11d %-5.2f\n",IdariSay,(float)IdariSay*100/MAX_ABONE_SAY);
    printf("Diger      %-11d %-5.2f\n",digerSay,(float)digerSay*100/MAX_ABONE_SAY);
    printf("Yonetici   %-11d %-5.2f\n",YoneticiSay,(float)YoneticiSay*100/MAX_ABONE_SAY);
    printf("-----------------------------\n");

    printf("Bos        %-11d %-5.2f\n",bosSay,(float)bosSay*100/MAX_ABONE_SAY);


    rewind(fAboneler);
    return;
}

int gun_bazinda_listele(FILE *fGorusmeler,FILE *fAboneler)
{
    Gorusme_type bir_gorusme;
    Abone_type bir_abone;
    int gun_nosu;

    printf("Bilgilerini istediginiz gunun nosunu giriniz(1,31): ");
    gun_nosu=sayi_al(1,31);
    rewind(fGorusmeler);

    printf("\nArayan Tel No Arayan Ad Soyad           Aranan Tel No Baslangic Sure \n");
    printf("------------  ------------------------- ------------- --------- ----\n");

    fscanf(fGorusmeler,"%d %s%d %d %d %d",&bir_gorusme.arayan_dahili_telefon_no,bir_gorusme.aranan_dis_hat_telefon_no,&bir_gorusme.tarih,&bir_gorusme.baslangic_saati,&bir_gorusme.baslangic_dakikasi,&bir_gorusme.sure);

    while (!feof(fGorusmeler))
    {
        fscanf(fGorusmeler,"%d %s%d %d %d %d",&bir_gorusme.arayan_dahili_telefon_no,bir_gorusme.aranan_dis_hat_telefon_no,&bir_gorusme.tarih,&bir_gorusme.baslangic_saati,&bir_gorusme.baslangic_dakikasi,&bir_gorusme.sure);
        if (gun_nosu==bir_gorusme.tarih)
        {
            int kayit_no = bir_gorusme.arayan_dahili_telefon_no-99;
            rewind(fAboneler);
            fseek(fAboneler,(kayit_no-1)*sizeof(Abone_type),SEEK_SET);
            fread(&bir_abone,sizeof(Abone_type),1,fAboneler);
            printf("%-12d %-25s %-13s %-2d:%-6d %-4d\n",bir_gorusme.arayan_dahili_telefon_no,bir_abone.ad_soyad,bir_gorusme.aranan_dis_hat_telefon_no,bir_gorusme.baslangic_saati,bir_gorusme.baslangic_dakikasi,bir_gorusme.sure);

        }

    }

    return gun_nosu;
}

void toplam_gorusme_listele(FILE *fGorusmeler)
{
    Gorusme_type bir_gorusme;
    int gun[32][2],i,topGor=0,topSure=0;
    for(i=1; i<32; i++)
    {
        gun[i][0]=0;
        gun[i][1]=0;
    }

    printf("\nGun Top Gor Sayisi Top Gor Suresi(dk) Ortalama Gor Suresi(dk)\n");
    printf("---- -------------- ----------------- -----------------------\n");
    rewind(fGorusmeler);
    do
    {
        fscanf(fGorusmeler,"%d %s%d %d %d %d",&bir_gorusme.arayan_dahili_telefon_no,bir_gorusme.aranan_dis_hat_telefon_no,&bir_gorusme.tarih,&bir_gorusme.baslangic_saati,&bir_gorusme.baslangic_dakikasi,&bir_gorusme.sure);
        gun[bir_gorusme.tarih][0]++;
        gun[bir_gorusme.tarih][1]+= bir_gorusme.sure;


    }
    while(!feof(fGorusmeler));

    for(i=1; i<32; i++)
    {
        if(gun[i][0]!=0)
        {
            printf("%-4d %-14d %-18d %-23.2f\n",i,gun[i][0],gun[i][1],(float)gun[i][1]/gun[i][0]);
        }
        topGor+=gun[i][0];
        topSure+=gun[i][1];
    }
    printf("--------------------------------------------------------------------------\n");
    printf("Aylik toplam gorusme sayisi: %d\n",topGor);
    printf("Aylik toplam gorusme suresi: %d\n",topSure);


}

void dis_hat_kontor_ihtiyaci(FILE *fAboneler)
{
    Abone_type bir_abone;
    int i;
    printf("Tel No Ad Soyad                  Birimi                         Tip        Kontor \n");
    printf("------ ------------------------- ------------------------------ ---------- ---------\n");
    for (i=0; i<MAX_ABONE_SAY; i++)
    {
        fseek(fAboneler,i*sizeof(Abone_type),SEEK_SET);
        fread(&bir_abone,sizeof(Abone_type),1,fAboneler);

        if(bir_abone.kontor<-100)
        {
            printf("%-6d %-25s %-30s %-10s %-9d\n", i+100,bir_abone.ad_soyad,bir_abone.birim_adi,tip[bir_abone.abone_tipi-1],bir_abone.kontor);
        }
    }
}

void kontor_yukle(FILE *fAboneler)
{
    Abone_type bir_abone;
    int tel_no;

    printf("Bilgilerini istediginiz abonenin dahili telefon numarasini giriniz(100-999): ");
    tel_no=sayi_al(100,999);

    fseek(fAboneler,(tel_no-100)*sizeof(Abone_type),SEEK_SET);
    fread(&bir_abone,sizeof(Abone_type),1,fAboneler);

    if(bir_abone.abone_tipi!=0)
    {
        int kontor;
        printf("\nYuklemek istediginiz kontor miktarini giriniz.\n");
        kontor=sayi_al(1,10000);
        kontor_guncelle(tel_no,kontor,fAboneler);

        fseek(fAboneler,(tel_no-100)*sizeof(Abone_type),SEEK_SET);
        fread(&bir_abone,sizeof(Abone_type),1,fAboneler);

        printf("Tel No Ad Soyad                  Birimi                         Tip        Kontor \n");
        printf("------ ------------------------- ------------------------------ ---------- ---------\n");
        printf("%-6d %-25s %-30s %-10s %-9d\n", tel_no,bir_abone.ad_soyad,bir_abone.birim_adi,tip[bir_abone.abone_tipi-1],bir_abone.kontor);
    }
    else
    {
        printf("Boyle bir kullanici bulunmamaktadir.\n");
    }
}

void dis_hat_kayit_ekle(FILE *fAboneler,FILE *fGorusmeler)
{
    int tel_no;
    Abone_type bir_abone;
    printf("Arayan abonenin dahili telefon numarasini giriniz(100-999): ");
    tel_no=sayi_al(100,999);
    fseek(fAboneler,(tel_no-100)*sizeof(Abone_type),SEEK_SET);
    fread(&bir_abone,sizeof(Abone_type),1,fAboneler);
    if(bir_abone.abone_tipi!=0)
    {
        if(bir_abone.kontor>=-100)
        {
            printf("\nAranan abonenin telefon numarasini giriniz: ");
            char aranan[31];
            fflush(stdin);
            gets(aranan);
            printf("\nArama tatihini giriniz(1-31): ");
            int tarih=sayi_al(1,31);
            printf("\nArama saatini giriniz(0-24): ");
            int saat=sayi_al(0,24);
            printf("\nArama dakikasini giriniz(0-59): ");
            int dakika=sayi_al(0,59);
            printf("\nArama suresini giriniz(1-1000): ");
            int sure=sayi_al(1,1000);

            fprintf(fGorusmeler,"%d %s %d %d %d %d\n",tel_no,aranan,tarih,saat,dakika,sure);
            int kontor = 3;
            int i;
            int zaman = saat*60+dakika;
            for(i=1; i<=sure; i++)
            {
                if(zaman<481 || zaman>1200)
                {
                    kontor+=2;
                }
                else
                    kontor+=3;
                zaman+=i;
            }

            kontor_guncelle(tel_no,-kontor,fAboneler);
        }
        else
        {
            printf("\nKullanicinin kontoru yetersizdir.\n");
        }
    }
    else
    {
        printf("\nBoyle bir kullanici bulunmamaktadir.\n");
    }
    fclose(fGorusmeler);
    if((fGorusmeler=fopen("gorusmeler.txt","a+"))==NULL)
        printf("Gorusmeler dosyasi acilamadi.");
}

void abone_ekle(FILE *fAboneler)
{
    Abone_type bir_abone;
    int tel_no;

    printf("\nEklemek istediginiz abonenin dahili telefon numarasini giriniz(100-999): ");
    tel_no=sayi_al(100,999);

    fseek(fAboneler,(tel_no-100)*sizeof(Abone_type),SEEK_SET);
    fread(&bir_abone,sizeof(Abone_type),1,fAboneler);

    if(bir_abone.abone_tipi==0)
    {

        printf("\nAbonenin adini ve soyadini giriniz.");
        fflush(stdin);
        gets(bir_abone.ad_soyad);
        printf("\nAbonenin birimini giriniz.");
        fflush(stdin);
        gets(bir_abone.birim_adi);

        printf("\nAbonenin tipini giriniz(1,4).");
        bir_abone.abone_tipi = sayi_al(1,4);
        printf("\nAbonenin kontor miktarini giriniz(0,1000).");
        bir_abone.kontor = sayi_al(0,1000);


        fseek(fAboneler,(tel_no-100)*sizeof(Abone_type),SEEK_SET);
        fwrite(&bir_abone,sizeof(Abone_type),1,fAboneler);


    }
    else
    {
        printf("O numaraya kayitli bir abone bulunmaktadir.\n");
    }

}

void kontor_guncelle(int tel_no,int kontor,FILE *fAboneler)
{
    Abone_type bir_abone;
    fseek(fAboneler,(tel_no-100)*sizeof(Abone_type),SEEK_SET);
    fread(&bir_abone,sizeof(Abone_type),1,fAboneler);

    bir_abone.kontor += kontor;

    fseek(fAboneler,(tel_no-100)*sizeof(Abone_type),SEEK_SET);
    fwrite(&bir_abone,sizeof(Abone_type),1,fAboneler);
}


void abone_sil(FILE *fAboneler,FILE *fGorusmeler)
{
    Abone_type bir_abone;
    int tel_no;

    printf("\nBilgilerini istediginiz abonenin dahili telefon numarasini giriniz(100-999): ");
    tel_no=sayi_al(100,999);

    Gorusme_type bir_gorusme;
    fseek(fAboneler,(tel_no-100)*sizeof(Abone_type),SEEK_SET);
    fread(&bir_abone,sizeof(Abone_type),1,fAboneler);

    if(bir_abone.abone_tipi!=0)
    {
        bir_abone.abone_tipi=0;
        fseek(fAboneler,(tel_no-100)*sizeof(Abone_type),SEEK_SET);
        fwrite(&bir_abone,sizeof(Abone_type),1,fAboneler);
        FILE *fGecici;

        fGecici = fopen("gecici.txt","w");

        do
        {
            fscanf(fGorusmeler,"%d %s%d %d %d %d",&bir_gorusme.arayan_dahili_telefon_no,bir_gorusme.aranan_dis_hat_telefon_no,&bir_gorusme.tarih,&bir_gorusme.baslangic_saati,&bir_gorusme.baslangic_dakikasi,&bir_gorusme.sure);
            if(bir_gorusme.arayan_dahili_telefon_no!=tel_no)
            {
                fprintf(fGecici,"%d %s %d %d %d %d\n",bir_gorusme.arayan_dahili_telefon_no,bir_gorusme.aranan_dis_hat_telefon_no,bir_gorusme.tarih,bir_gorusme.baslangic_saati,bir_gorusme.baslangic_dakikasi,bir_gorusme.sure);
            }
        }
        while(!feof(fGorusmeler));

        fclose(fGecici);
        fclose(fGorusmeler);
        remove("gorusmeler.txt");
        rename("gecici.txt","gorusmeler.txt");

        printf("\nAbone silinmistir.");

    }
    else
    {
        printf("Boyle bir abone bulunmamaktadir.\n");
    }
}



















