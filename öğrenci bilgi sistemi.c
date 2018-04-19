#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
int main()
{
    int ogrenci_numarasi, ders_sayisi;
    int okul_top_kredi=0, az_ders_alan=0, altmis_ustu_ogrenci_sayisi=0;
    int otuzbesalti=0, seksenbesustu=0, ucyuzustu=0,  max_ogrencino=0, max_kredi_toplami=0;
    float max_bursmiktari=0, max_donemsonunotu=0;
	int kiz_basarili=0, erkek_basarili=0, kiz_sayisi=0, erkek_sayisi=0, toplam_basarili, toplam_ogrenci;
    float maxburs_bursmiktari=0, maxburs_donemsonunotu=0, top_kiz_not=0, top_erkek_not=0;
    float toplam_burs=0, bursmiktari;
    float kizbasariyuzde=0,  ailebasariliyuzde=0, evbasariliyuzde=0, yurtbasariliyuzde=0;
    int maxburs_ogrencino=0, maxburs_kreditoplami=0;
    int yurtbasarili=0, evbasarili=0, ailebasarili=0, aile=0, ev=0, yurt=0;
    float toplam_not;
    char cinsiyet, ikamet, bos;
    system("color 0c");
    etiket:
    printf("________________________________________________________________________________\n");
    printf("Ogrenci numarasini giriniz(Ogrenci numarasinin son uc hanesini giriniz)\n(islemi bitirmek icin 0 veya negatif bir sayi giriniz)\n");
    scanf("%d%c", &ogrenci_numarasi, &bos);
        while(ogrenci_numarasi>999 ){
            printf("Hatali aralikta veri girisi yaptiniz. tekrar deneyiniz\n");
            goto etiket;
        }
        while(ogrenci_numarasi<1){
            printf("Ilk veri girisini yapmadan programi sonlandiramazsiniz\n");
            goto etiket;
        }


    while (ogrenci_numarasi>0) {
        printf("Cinsiyet giriniz: (E/e, K/k)\n");
        scanf("%c%c", &cinsiyet, &bos);
        while(cinsiyet!='e' && cinsiyet!='E' && cinsiyet!='k' && cinsiyet!='K'){
            printf("Yanlis bir giris yaptiniz lutfen tekrar deneyiniz\n");
			printf("Cinsiyet giriniz: (E/e, K/k)\n");
            scanf("%c%c", &cinsiyet, &bos);
        }
        if(cinsiyet=='e'||cinsiyet=='E')
            erkek_sayisi++;
        else if(cinsiyet=='k'||cinsiyet=='K')
            kiz_sayisi++;
        printf("Ikamet edilen yeri yaziniz: (yurtta ise 'y' aileyleyse  'a' evde ise 'e')\n");
        scanf("%c%c", &ikamet, &bos);
        while(ikamet!= 'a' && ikamet!= 'A' && ikamet!= 'y' && ikamet!= 'Y' && ikamet!='e' && ikamet!='E') {
            printf("Yanlis bir giris yaptiniz lutfen tekrar deneyiniz\n");
			printf("Ikamet edilen yeri yaziniz: (yurtta ise 'y' aileyleyse  'a' evde ise 'e')\n");
            scanf("%c%c", &ikamet, &bos);
        }
        if (ikamet=='a' || ikamet== 'A')
			aile++;
        else if (ikamet=='y' || ikamet== 'Y')
			yurt++;
        else if (ikamet=='e' || ikamet== 'E')
			ev++;

        printf("Alinan ders sayisini giriniz(1-10):\n");
        scanf("%d", &ders_sayisi);
        while (ders_sayisi<1 || ders_sayisi>10){
			printf("Yanlis aralikta bir deger girdiniz\n");
			printf("Alinan ders sayisini giriniz(1-10):\n");
			scanf("%d", &ders_sayisi);
        }
        if(ders_sayisi<=3)
            az_ders_alan++;

        int sayac=0, kredi, ders_notu, agirlikli_ders_notu, adn_toplam=0, kredi_toplam=0 ;
		int altmis_ustu_ders_sayisi = 0;
        float donemsonuortalamasi;
        while(sayac!=ders_sayisi){

            printf("Dersin kredisini giriniz(1-10)\n");
            scanf("%d", &kredi);
            while(kredi<1 || kredi>10) {
				printf("Yanlis aralikta bir deger girdiniz\n");
				printf("Dersin kredisini giriniz(1-10)\n");
				scanf("%d", &kredi);
            }

            printf("Dersin notunu giriniz(0-100)\n");
            scanf("%d", &ders_notu);

            while(ders_notu<0 || ders_notu>100){
                printf("Yanlis bir deger girdiniz lutfen tekrar deneyiniz\n");
				printf("Dersin notunu giriniz(0-100)\n");
                scanf("%d", &ders_notu);
                }
            sayac++;
            agirlikli_ders_notu= kredi * ders_notu;
            adn_toplam=adn_toplam + agirlikli_ders_notu;
            kredi_toplam= kredi_toplam +kredi;

            if(ders_notu>=60)
                altmis_ustu_ders_sayisi++;

        }
		donemsonuortalamasi= adn_toplam*1.0 / kredi_toplam;

		if(altmis_ustu_ders_sayisi == ders_sayisi)
			altmis_ustu_ogrenci_sayisi++;

        printf("Ogrenci numarasi: %d\n", ogrenci_numarasi);
        printf("Ogrencinin o donem aldigi derslerin toplam kredisi: %d\n", kredi_toplam);
        printf("Donem sonu ortalamasi : %.2f\n\n", donemsonuortalamasi);

        if (donemsonuortalamasi<35)
			otuzbesalti++;
        else if(donemsonuortalamasi>85)
			seksenbesustu++;



        if(cinsiyet=='e'|| cinsiyet=='E')
            top_erkek_not=top_erkek_not+ donemsonuortalamasi;
        else if(cinsiyet=='k'||cinsiyet=='K')
            top_kiz_not=top_kiz_not+ donemsonuortalamasi;


            if(ikamet=='a' || ikamet=='A'){
				if (donemsonuortalamasi<60){
					bursmiktari=100;
				}
				else if(donemsonuortalamasi>=60 && donemsonuortalamasi<70){
					bursmiktari= 140 + donemsonuortalamasi* 1.2;
				}
				else if(donemsonuortalamasi>=70 && donemsonuortalamasi<80){
					bursmiktari= 170 + donemsonuortalamasi* 1.3;
				}
				else if(donemsonuortalamasi>=80 && donemsonuortalamasi<90){
					bursmiktari= 190 + donemsonuortalamasi* 1.5;
				}
				else if(donemsonuortalamasi>=90 ){
					bursmiktari= 200 + donemsonuortalamasi* 1.8;
				}
            }
            if(ikamet=='y' || ikamet== 'Y'){
                if (donemsonuortalamasi<60){
					bursmiktari= 130;
                }
                else if(donemsonuortalamasi>=60 && donemsonuortalamasi<70){
					bursmiktari=(140 + donemsonuortalamasi* 1.2) *1.3;
				}
                else if(donemsonuortalamasi>=70 && donemsonuortalamasi<80){
					bursmiktari= (170 + donemsonuortalamasi* 1.3) *1.3;
                }
                else if(donemsonuortalamasi>=80 && donemsonuortalamasi<90){
					bursmiktari= (190 + donemsonuortalamasi* 1.5)* 1.3;
                }
                else if(donemsonuortalamasi>=90 ){
					bursmiktari= (200 + donemsonuortalamasi* 1.8)* 1.3;
                }
            }
            if(ikamet=='e' || ikamet == 'E'){
                if (donemsonuortalamasi<60){
					bursmiktari= 150;
                }
                else if(donemsonuortalamasi>=60 && donemsonuortalamasi<70){
					bursmiktari= (140 + donemsonuortalamasi* 1.2) *1.5;
                }
                else if(donemsonuortalamasi>=70 && donemsonuortalamasi<80){
					bursmiktari= (170 + donemsonuortalamasi* 1.3) *1.5;
                }
                else if(donemsonuortalamasi>=80 && donemsonuortalamasi<90){
					bursmiktari= (190 + donemsonuortalamasi* 1.5)* 1.5;
                }
                else if(donemsonuortalamasi>=90 ){
					bursmiktari= (200 + donemsonuortalamasi* 1.8)* 1.5;
                }
            }
			printf("Alacagi burs %.2f TL\n", bursmiktari);
            if(bursmiktari >300)
                ucyuzustu++;
            if(donemsonuortalamasi>=60){
				printf("Basarili\n");
				if(cinsiyet=='e' ||cinsiyet=='E')
					erkek_basarili++;
				else if(cinsiyet=='k' ||cinsiyet=='K')
					kiz_basarili++;
				if (ikamet=='a' || ikamet== 'A')
					ailebasarili++;
				else if (ikamet=='y' || ikamet== 'Y')
					yurtbasarili++;
				else if (ikamet=='e' || ikamet== 'E')
					evbasarili++;
            }
			else
				printf("Basarisiz\n");

            toplam_burs += bursmiktari;

            if (donemsonuortalamasi > max_donemsonunotu){
				max_donemsonunotu= donemsonuortalamasi;
				max_ogrencino=  ogrenci_numarasi;
				max_kredi_toplami= kredi_toplam;
				max_bursmiktari= bursmiktari;
            }

            if(maxburs_bursmiktari < bursmiktari){
				maxburs_bursmiktari= bursmiktari;
				maxburs_donemsonunotu= donemsonuortalamasi;
				maxburs_kreditoplami= kredi_toplam;
				maxburs_ogrencino= ogrenci_numarasi;
            }

            okul_top_kredi= okul_top_kredi + kredi_toplam;

			printf("________________________________________________________________________________\n");
			printf("Ogrenci numarasini giriniz(Ogrenci numarasinin son uc hanesini giriniz)\n(islemi bitirmek icin 0 veya negatif bir sayi giriniz) ");
			scanf("%d%c", &ogrenci_numarasi, &bos);
			while(ogrenci_numarasi>999 ){
				printf("Hatali aralikta veri girisi yaptiniz. tekrar deneyiniz\n");
				printf("________________________________________________________________________________\n");
				printf("Ogrenci numarasini giriniz(Ogrenci numarasinin son uc hanesini giriniz)\n(islemi bitirmek icin 0 veya negatif bir sayi giriniz)\n");
				scanf("%d%c", &ogrenci_numarasi, &bos);
			}
        }
        toplam_basarili= erkek_basarili+ kiz_basarili;
        toplam_ogrenci= erkek_sayisi+ kiz_sayisi;
        toplam_not= top_erkek_not+ top_kiz_not;
		printf("______________________________ISTATISTIKLER_____________________________________");
        if(kiz_sayisi!=0){
			kizbasariyuzde= (kiz_basarili*1.0 / kiz_sayisi) *100;
			printf("Kizlar icin basari yuzdesi: %.2f\n", kizbasariyuzde );
		}
        else
			printf("Kizlar icin basari yuzdesi: Kiz ogrenci yok \n");
        if (erkek_sayisi!=0)
			printf("Erkekler icin basari yuzdesi: %.2f\n", (erkek_basarili*1.0/erkek_sayisi)*100);
        else
			printf("Erkekler icin basari yuzdesi: Erkek ogrenci yok. \n");
        printf("Okulun geneli icin basari yuzdesi: %.2f\n\n", (toplam_basarili*1.0/toplam_ogrenci) *100);

        if (kiz_sayisi!=0)
		printf("Kizlar icin genel not ortalamasi: %.2f\n", (float)top_kiz_not/kiz_sayisi );
        else
			printf("Kizlar icin genel not ortalamasi: Bolumde kiz ogrenci yok\n");

        if (erkek_sayisi!=0)
			printf("Erkekler icin genel not ortalamasi: %.2f\n", (float)top_erkek_not/erkek_sayisi);
        else
			printf("Erkekler icin genel not ortalamasi: Bolumde erkek ogrenci yok\n");

        printf("Okul geneli icin not ortalamasi: %.2f\n\n",  (float)toplam_not/toplam_ogrenci );
        printf("Ogrencilerin o donem aldigi derslerin kredi ortalamasi: %.2f\n", (float)okul_top_kredi/ toplam_ogrenci );
        printf("Bu donem aldigi ders sayisi 3 ve altinda olan ogrencilerin sayisi: %d\n", az_ders_alan);
        printf("Hicbir ders notunun 60 altinda olmayan ogrenci sayisi:%d\n", altmis_ustu_ogrenci_sayisi);
		printf("Hicbir ders notunun 60 altinda olmayan ogrenci yuzdesi:%.2f\n", altmis_ustu_ogrenci_sayisi*1.0/toplam_ogrenci);
        printf("Bu donemki agirlikli not ortalamasi 35 in altinda olan ogrenci sayisi: %d\n Yuzdesi: %.2f\n", otuzbesalti, (otuzbesalti*1.0/toplam_ogrenci)*100 );
        printf("Bu donemki agirlikli not ortalamasi 85 in ustunde olan ogrenci sayisi: %d\n Yuzdesi: %.2f\n", seksenbesustu, (seksenbesustu*1.0/toplam_ogrenci)*100);
        printf("Sonraki donem alacagi burs miktari 300 den fazla olan ogrenci sayisi: %d\n", ucyuzustu);
        printf("Bu donem okul birincisi olan ogrencinin:\n     Okul numarasi:%d\n     Bu donem aldigi derslerin kredi toplami: %d\n     Agirlikli not ortalamasi: %.2f\n     Sonraki donem alacagi burs miktari:%.2f\n\n", max_ogrencino, max_kredi_toplami, max_donemsonunotu, max_bursmiktari);
        printf("Sonraki donem en cok burs alacak ogrenci:\n     Okul numarasi:%d\n     Bu donem aldigi derslerin kredi toplami: %d\n     Agirlikli not ortalamasi:%.2f\n     Sonraki donem alacagi burs miktari:%.2f\n\n", maxburs_ogrencino, maxburs_kreditoplami, maxburs_donemsonunotu, maxburs_bursmiktari);
        printf("Tum ogrencilere verilecek aylik toplam burs miktari: %.2f\n\n", toplam_burs);

        if(aile!=0)
			ailebasariliyuzde=  (ailebasarili*1.0/aile ) * 100 ;
        if(ev!=0)
			evbasariliyuzde = (evbasarili*1.0/ev) * 100;
        if(yurt!=0)
			yurtbasariliyuzde= (yurtbasarili*1.0/yurt) * 100;
        if(evbasariliyuzde<yurtbasariliyuzde && evbasariliyuzde<ailebasariliyuzde)
            printf("Basarili ogrencilerin yuzdesinin en dusuk oldugu ikamet yeri: \nEvde Kalanlar \n\n");
        else if(yurtbasariliyuzde<evbasariliyuzde && yurtbasariliyuzde< ailebasariliyuzde)
            printf("Basarili ogrencilerin yuzdesinin en dusuk oldugu ikamet yeri: \nYurtta Kalanlar \n\n");
        else if(ailebasariliyuzde<yurtbasariliyuzde&& ailebasariliyuzde< evbasariliyuzde)
            printf("Basarili ogrencilerin yuzdesinin en dusuk oldugu ikamet yeri: \nAilesiyle Kalanlar \n\n ");
        else if(yurtbasariliyuzde<evbasariliyuzde && yurtbasariliyuzde== ailebasariliyuzde)
            printf("Basarili ogrencilerin yuzdesinin en dusuk oldugu ikamet yeri: \nYurtta kalanlar ve Ailesiyle kalanlar esit yuzdede\n\n");
        else if(yurtbasariliyuzde<ailebasariliyuzde&& yurtbasariliyuzde== evbasariliyuzde)
            printf("Basarili ogrencilerin yuzdesinin en dusuk oldugu ikamet yeri: \nYurtta kalanlar ve Evde kalanlar esit yuzdede\n\n ");
        else if(ailebasariliyuzde<yurtbasariliyuzde && ailebasariliyuzde==evbasariliyuzde)
            printf("Basarili ogrencilerin yuzdesinin en dusuk oldugu ikamet yeri: \nAilesiyle kalanlar ve Evde kalanlar esit yuzdede\n\n");
        else if(ailebasariliyuzde==yurtbasariliyuzde && ailebasariliyuzde==evbasariliyuzde)
            printf("Basarili ogrencilerin yuzdesinin en dusuk oldugu ikamet yeri: \nAilesiyle, Evde ve Yurtta kalanlar esit yuzdede\n\n");


        return 0;
}
