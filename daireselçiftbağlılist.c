#include <stdio.h>
#include <stdlib.h>

struct ogrenci
{
    int no;
    float ort;
    struct ogrenci *onceki;
    struct ogrenci *sonraki;
};

void d_cift_sirali_ekle(struct ogrenci *liste_basi_ptr, struct ogrenci *yeni);
void kucukten_buyuge_listele(struct ogrenci *liste_basi_ptr);
void buyukten_kucuge_listele(struct ogrenci *liste_basi_ptr);
struct ogrenci *ara(struct ogrenci *liste_basi_ptr, int aranan_no);
void d_cift_baglidan_dugum_cikar(struct ogrenci *cikarilacak);
void d_cift_baglidan_dugum_sil(struct ogrenci *silinecek);

int main()
{
    struct ogrenci liste_basi;
    struct ogrenci *birOgrenci;
    int no,secim;
    float min_ort;
    int sayac;

    liste_basi.sonraki=&liste_basi;//liste basi dugumune sahip dairesel cift bagli liste ilkleniyor
    liste_basi.onceki=&liste_basi;

    do
    {
        printf("1.Yeni bir ogrenci ekleme\n");
        printf("2.Ogrencileri not ortalamalarina gore kucukten buyuge dogru listeleme\n");
        printf("3.Ogrencileri not ortalamalarina gore buyukten kucuge dogru listeleme\n");
        printf("4.Bir ogrencinin not ortalamasini goruntuleme\n");
        printf("5.Bir ogrencinin not ortalamasini guncelleme\n");
        printf("6.Bir ogrenciyi silme\n");
        printf("7.Ortalamasi dusuk olan ogrencileri silme\n");
        printf("8.Cikis\n");
        printf("Seciminizi giriniz:");
        scanf("%d",&secim);
        switch (secim)
        {
        case 1:
            birOgrenci=malloc(sizeof(struct ogrenci));//yeni ogrenci icin bellekten yer ayriliyor
            printf("Ogrencinin numarasini giriniz:");
            scanf("%d",&birOgrenci->no);
            printf("Ogrencinin not ortalamasini giriniz:");
            scanf("%f",&birOgrenci->ort);
            d_cift_sirali_ekle(&liste_basi,birOgrenci);//yeni ogrenci, not ortalamasina gore listenin uygun yerine eklenir
            printf("Ogrenci eklendi\n");
            break;
        case 2:
            kucukten_buyuge_listele(&liste_basi);
            break;
        case 3:
            buyukten_kucuge_listele(&liste_basi);
            break;
        case 4:
            printf("Ogrencinin numarasini giriniz:");
            scanf("%d",&no);
            birOgrenci=ara(&liste_basi,no);
            if (birOgrenci)//ogrenci listede bulunduysa
                printf("bu ogrencinin ortalamasi: %.2f\n",birOgrenci->ort);
            else
                printf("bu numarali bir ogrenci yok\n");
            break;
        case 5:
            printf("Ogrencinin numarasini giriniz:");
            scanf("%d",&no);
            birOgrenci=ara(&liste_basi,no);
            if (birOgrenci)//ogrenci listede bulunduysa
            {
                printf("bu ogrencinin yeni not ortalamasini giriniz:");
                scanf("%f",&birOgrenci->ort);
                if ((birOgrenci->onceki!=&liste_basi && birOgrenci->ort<birOgrenci->onceki->ort) ||
                   (birOgrenci->sonraki!=&liste_basi && birOgrenci->ort>birOgrenci->sonraki->ort))
                //ogrencinin listedeki konumu degisecekse
                {
                    d_cift_baglidan_dugum_cikar(birOgrenci);//once ogrenciyi listeden cikar (ama yok etme)
                    d_cift_sirali_ekle(&liste_basi,birOgrenci);//sonra ogrenciyi tekrar listenin uygun yerine ekle
                }
                printf("Ogrencinin not ortalamasi guncellendi\n");
            }
            else
                printf("bu numarali bir ogrenci yok\n");
            break;
        case 6:
            printf("Ogrencinin numarasini giriniz:");
            scanf("%d",&no);
            birOgrenci=ara(&liste_basi,no);
            if (birOgrenci)//ogrenci listede bulunduysa
            {
                d_cift_baglidan_dugum_sil(birOgrenci);//ogrenciyi listeden sil, yani listeden cikar ve yok et
                printf("Ogrenci silindi\n");
            }
            else
                printf("bu numarali bir ogrenci yok\n");
            break;
        case 7:
            printf("Silinecek ogrencilerin not ortalamasi icin sinir degerini giriniz:");
            scanf("%f",&min_ort);
            sayac=0;
            while(liste_basi.sonraki!=&liste_basi && liste_basi.sonraki->ort<min_ort)
            {
                d_cift_baglidan_dugum_sil(liste_basi.sonraki);//surekli notu en dusuk olan ogrenciyi sil
                sayac++;
            }
            if (sayac>0)
                printf("%d ogrencinin kaydi silindi\n",sayac);
            else//hic ogrenci silinmediyse
                printf("ortalamasi sinirin altinda olan ogrenci yok\n");
            break;
        }
    }
    while (secim!=8);

    return 0;
}

void d_cift_sirali_ekle(struct ogrenci *liste_basi_ptr, struct ogrenci *yeni)
{
    struct ogrenci *gecici;

    gecici=liste_basi_ptr->sonraki;
    while (gecici!=liste_basi_ptr && gecici->ort<yeni->ort)
        gecici=gecici->sonraki;

    yeni->sonraki=gecici;
    yeni->onceki=gecici->onceki;
    gecici->onceki->sonraki=yeni;
    gecici->onceki=yeni;
}

void kucukten_buyuge_listele(struct ogrenci *liste_basi_ptr)
{
    struct ogrenci *gecici;

    printf("Ogr No Not Ortalamasi\n");
    printf("------ --------------\n");

    gecici=liste_basi_ptr->sonraki;
    while (gecici!=liste_basi_ptr)
    {
        printf("%-6d %.2f\n",gecici->no,gecici->ort);
        gecici=gecici->sonraki;
    }
}

void buyukten_kucuge_listele(struct ogrenci *liste_basi_ptr)
{
    struct ogrenci *gecici;

    printf("Ogr No Not Ortalamasi\n");
    printf("------ --------------\n");

    gecici=liste_basi_ptr->onceki;
    while (gecici!=liste_basi_ptr)
    {
        printf("%-6d %.2f\n",gecici->no,gecici->ort);
        gecici=gecici->onceki;
    }
}

struct ogrenci *ara(struct ogrenci *liste_basi_ptr, int aranan_no)//ogrenci listede bulunursa isaretcisi dondurulur, bulunamazsa NULL dondurulur
{
    struct ogrenci *gecici;

    gecici=liste_basi_ptr->sonraki;
    while (gecici!=liste_basi_ptr)//dikkat:liste not ortalamasina gore sirali, burada numaraya gore arama yapiliyor
    {
        if (gecici->no==aranan_no) return gecici;
        gecici=gecici->sonraki;
    }

    return NULL;
}

void d_cift_baglidan_dugum_cikar(struct ogrenci *cikarilacak)//adresi verilen dugumu listeden cikarir ama yok etmez
{
    cikarilacak->onceki->sonraki=cikarilacak->sonraki;
    cikarilacak->sonraki->onceki=cikarilacak->onceki;
}

void d_cift_baglidan_dugum_sil(struct ogrenci *silinecek)//adresi verilen dugumu listeden siler, yani hem listeden cikarir hem yok eder
{
    d_cift_baglidan_dugum_cikar(silinecek);//once dugumu listeden cikar
    free(silinecek);//sonra dugumu yok et
}
