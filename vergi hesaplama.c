#include <stdio.h>
#include <stdlib.h>

int main()
{
    int vergisiz_fiyat,motor_hacmi,sira_no=1,sayac_30000=0,sayac_100000=0,sayac_engelli=0,en_buyuk=0,en_buyuk_satis=0,en_buyuk_motor=0;
    int buyuk_anahtar=0,buyuk_vergisiz=0,buyuk_satis=0,buyuk_motor=0;
    float sayac_1600_az=0,sayac_1600_2000=0,sayac_2000_ustu=0,toplam_arac=0,toplam_anahtar_teslim=0;
    float anahtar_teslim,kdv,otv,mtv,toplam_vergisiz_1600=0,toplam_vergisiz_1600_2000=0,toplam_vergisiz_2000=0;
    float en_buyuk_teslim=0,toplam_kdv=0,toplam_otv=0,toplam_mtv;
    char etiket,cevap;
    do
    {
        printf("Aracin vergisiz fiyatini giriniz>\n");
        scanf("%d", &vergisiz_fiyat);
        printf("Aracin motor hacmini giriniz>\n");
        scanf("%d",&motor_hacmi);
        if(motor_hacmi<1601)
        {
            if(vergisiz_fiyat<30000)
                sayac_30000++;
            toplam_vergisiz_1600+=vergisiz_fiyat;
            sayac_1600_az++;
            printf("Alici ortopedik engelli mi?(e-E/h-H)\n");
            fflush(stdin);
            scanf("%c",&etiket);

            if (etiket=='E' || etiket=='e')
            {
                sayac_engelli++;
                otv=0;
                kdv=vergisiz_fiyat*0.18;
                mtv=0;
                anahtar_teslim=vergisiz_fiyat+kdv+otv+375;
            }
            else if (etiket=='H' || etiket=='h')
            {
                if(motor_hacmi<1301)
                {
                    otv=vergisiz_fiyat*0.4;
                    kdv=vergisiz_fiyat*0.4*0.18;
                    mtv=517;
                    anahtar_teslim=vergisiz_fiyat+kdv+otv+(mtv/2)+375;
                }
                else
                {
                    otv=vergisiz_fiyat*0.4;
                    kdv=vergisiz_fiyat*0.4*0.18;
                    mtv=827;
                    anahtar_teslim=vergisiz_fiyat+kdv+otv+(mtv/2)+375;;
                }
            }
        }
        else if(motor_hacmi<=1800)
        {
            toplam_vergisiz_1600_2000+=vergisiz_fiyat;
            sayac_1600_2000++;
            otv=vergisiz_fiyat*0.8;
            kdv=vergisiz_fiyat*0.8*0.18;
            mtv=1457;
            anahtar_teslim=vergisiz_fiyat+otv+kdv+(mtv/2)+375;
        }
        else if(motor_hacmi<=2000)
        {
            toplam_vergisiz_1600_2000+=vergisiz_fiyat;
            sayac_1600_2000++;
            otv=vergisiz_fiyat*0.8;
            kdv=vergisiz_fiyat*0.8*0.18;
            mtv=2295;
            anahtar_teslim=vergisiz_fiyat+kdv+otv+(mtv/2)+375;
        }
        else if(motor_hacmi<=2500)
        {
            toplam_vergisiz_2000+=vergisiz_fiyat;
            sayac_2000_ustu++;
            otv=vergisiz_fiyat*1.3;
            kdv=vergisiz_fiyat*1.3*0.18;
            mtv=3443;
            anahtar_teslim=vergisiz_fiyat+kdv+otv+(mtv/2)+375;
        }
        else if(motor_hacmi<=3000)
        {
            toplam_vergisiz_2000+=vergisiz_fiyat;
            sayac_2000_ustu++;
            otv=vergisiz_fiyat*1.3;
            kdv=vergisiz_fiyat*1.3*0.18;
            mtv=4799;
            anahtar_teslim=vergisiz_fiyat+kdv+otv+(mtv/2)+375;
        }
        else if(motor_hacmi<=3500)
        {
            toplam_vergisiz_2000+=vergisiz_fiyat;
            sayac_2000_ustu++;
            otv=vergisiz_fiyat*1.3;
            kdv=vergisiz_fiyat*1.3*0.18;
            mtv=7308;
            anahtar_teslim=vergisiz_fiyat+kdv+otv+(mtv/2)+375;
        }
        else if(motor_hacmi<=4000)
        {
            toplam_vergisiz_2000+=vergisiz_fiyat;
            sayac_2000_ustu++;
            otv=vergisiz_fiyat*1.3;
            kdv=vergisiz_fiyat*1.3*0.18;
            mtv=11489;
            anahtar_teslim=vergisiz_fiyat+kdv+otv+(mtv/2)+375;
        }
        else
        {
            toplam_vergisiz_2000+=vergisiz_fiyat;
            sayac_2000_ustu++;
            otv=vergisiz_fiyat*1.3;
            kdv=vergisiz_fiyat*1.3*0.18;
            mtv=18803;
            anahtar_teslim=vergisiz_fiyat+kdv+otv+(mtv/2)+375;
        }
        printf("sira no: %d\n",sira_no);
        sira_no++;
        printf("Vergisiz fiyat: %d\n",vergisiz_fiyat);
        printf("KDV: %.2f TL\nOTV: %.2f TL\nMTV: %.2f TL\nPlaka Fiyati: 375 TL\n",kdv,otv,mtv);
        printf("Anahtar teslim fiyati:%.2f\n",anahtar_teslim);

        toplam_kdv+=kdv;
        toplam_otv+=otv;
        toplam_mtv+=mtv/2;

        printf("Satilan baska arac var mi?(e-E/h-H)");
        fflush(stdin);
        scanf("%c",&cevap);
        while(cevap!='e' && cevap !='E' && cevap!='h' && cevap!='H')
        {
            printf("Yanlis bir karakter girdiniz,lutfen tekrar deneyin\n");
            printf("Satilan baska arac var mi?(e-E/h-H)");
            fflush(stdin);
            scanf("%c",&cevap);
        }
        toplam_arac++;
        toplam_anahtar_teslim+=anahtar_teslim;
        if(anahtar_teslim>100000)
            sayac_100000++;
            if(en_buyuk<vergisiz_fiyat)
            {
                en_buyuk=vergisiz_fiyat;
                en_buyuk_satis=sira_no;
                en_buyuk_motor=motor_hacmi;
                en_buyuk_teslim=anahtar_teslim;
            }
            if(buyuk_anahtar<anahtar_teslim)
            {
                buyuk_anahtar=anahtar_teslim;
                buyuk_vergisiz=vergisiz_fiyat;
                buyuk_satis=sira_no;
                buyuk_motor=motor_hacmi;
            }
    }
    while(cevap=='e' || cevap=='E');
    printf("Istatistikler\n");
    printf("1600 alti arac sayisi: %.f yuzdesi: %.2f\n",sayac_1600_az,sayac_1600_az*100/toplam_arac);
    printf("1600-2000 arasi arac sayisi: %.f yuzdesi: %.2f\n",sayac_1600_2000,sayac_1600_2000*100/toplam_arac);
    printf("2000 ustu arac sayisi: %.f yuzdesi: %.2f\n",sayac_2000_ustu,sayac_2000_ustu*100/toplam_arac);
    printf("1600 alti araclarin vergisiz fiyat ortalamasi %.2f TL\n",toplam_vergisiz_1600/sayac_1600_az);
    printf("1600-2000 arasi araclarin vergisiz fiyat ortalamasi %.2f TL\n",toplam_vergisiz_1600_2000/sayac_1600_2000);
    printf("2000 ustu araclarin vergisiz fiyat ortalamasi %.2f TL\n",toplam_vergisiz_2000/sayac_2000_ustu);
    printf("Tum araclarin vergisiz fiyatlarinin toplami:%.2f TL\n",(toplam_vergisiz_1600+toplam_vergisiz_1600_2000+toplam_vergisiz_2000)/toplam_arac);
    printf("Tum araclarin toplam anahtar teslim fiyatlarinin ortalamasi: %.2f TL\n",toplam_anahtar_teslim/toplam_arac);
    printf("Vergisiz fiyati 30000 TL den dusuk ve motor hacmi 1600 cm3 u gecmeyen araclarin sayisi: %d\n",sayac_30000);
    printf("Anahtar teslim satis fiyati 100000 TL den yuksek olan araclarin sayisi %d\n",sayac_100000);
    printf("Ortopedik engelli kisilere satilan araclarin sayisi %d\n",sayac_engelli);
    printf("Vergisiz fiyati en yuksek olan aracin satis sira numarasi: %d\n",en_buyuk);
    printf("Vergisiz fiyati: %d TL\n",en_buyuk_satis);
    printf("Motor hacmi: %d cm3\n",en_buyuk_motor);
    printf("anahtar teslim satis fiyati: %.2f TL\n",en_buyuk_teslim);
    printf("Anahtar teslim fiyati en yuksek olan aracin satis sira numarasi: %d\n",buyuk_satis);
    printf("Vergisiz fiyati: %d TL\n",buyuk_vergisiz);
    printf("motor hacmi: %d cm3\n",buyuk_motor);
    printf("anahtar teslim satis fiyati: %.2f TL\n",buyuk_anahtar);
    printf("Devlete odenen toplam OTV tutari; %.2f TL\n ",toplam_otv);
    printf("Devlete odenen toplam KDV tutari; %.2f TL\n ",toplam_kdv);
    printf("Devlete odenen toplam OTV tutari; %.2f TL\n ",toplam_mtv);
    printf("Devlete odenen toplam Plaka Masrafi; %d TL\n ",toplam_arac*375);

    return 0;

}
