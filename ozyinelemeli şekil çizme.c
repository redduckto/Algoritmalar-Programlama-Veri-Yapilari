#include <stdio.h>
#include <stdlib.h>
// Kullanicinin menuden yapacagi secime gore istenilen sekilleri cizdiren program
void DogruCiz(int uzunluk,int aci,char karakter);// Dogru cizilmesi gerektiginde kullanilacak fonksiyonun prototipi
void ikizkenarUcgenCiz(int yukseklik,char karakter);// ikizkenar ucgen cizimi icin kullanilan fonksiyonun prototipi
void TersIkizkenarUcgenCiz(int yukseklik,char karakter);// Ters ikizkenar ucgen cizimi icin kullanilan fonksiyonun prototipi
void KareCiz(int kenar,char karakter);// Kare ciziminde kullanilan fonksiyonun prototipi
void DikdortgenCiz(int yukseklik,int genislik,char karakter);// Dikdortgen ciziminde kullanilan fonksiyonun prototipi
void EskenarDortgenCiz(int yukseklik,char karakter);//Eskenar dortgen ciziminde kullanilan fonksiyonun prototipi
void ParalelkenarCiz(int yukseklik,int genislik,char karakter);// Paralelkenar ciziminde kullanilan fonksiyonun prototipi

int main()
{
    int secim,kenar,aci,dogru_uz,yukseklik,genislik;// Kullanilan degiskenlerin tanimlanmasi
    char cikis='h',karakter,devam;// Kullanilan degiskenlerin tanimlanmasi
    karakter='x';// Kullanicinin aksini belirtmemesi durumundaki sekil cizimlerinde varsayilan olarak x kullanilacagindan,x karaktere atanmistir
    while(cikis=='H'||cikis=='h'){// Kullanici istemeden programin sonlanmamasi icin kullanilan while dongusu
        do{// Menu yazdiriliyor
            printf("1. Dogru (Duz Cizgi) Cizme\n");
            printf("2. Ikizkenar Ucgen Cizme\n");
            printf("3. Ters Ikizkenar Ucgen Cizme\n");
            printf("4. Kare Cizme\n");
            printf("5. Dikdortgen Cizme\n");
            printf("6. Kum Saati Cizme\n");
            printf("7. Eskenar Dortgen (Baklava Dilimi) Cizme\n");
            printf("8. Paralel Kenar Cizme\n");
            printf("9. Cizim Karakterini Degistirme\n");
            printf("10. Cikis\n"); 
            do{
                printf("\nSeciminizi Giriniz:");
                scanf("%d",&secim);
              }while (secim<1||secim>10);// Kullanici dogru deger girene kadar bekleniyor
            switch (secim){// Kullanicinin menuden sectigi komut aliniyor
                case 1:
                    do{
                        do{
                            printf("Cizilecek Dogrunun Uzunlugunu(min 2,max 22) ve X Ekseniyle Yapacagi Aciyi Giriniz(0,45,90,135)\n");
                            scanf("%d %d",&dogru_uz,&aci);
                          }while((aci!=0&&aci!=45&&aci!=90&&aci!=135)||(dogru_uz>22||dogru_uz<2));// Kullanici dogru deger girene kadar bekleniyor
                        printf("Uzunlugu %d ve X Ekseniyle Acisi %d Olan Dogru:\n",dogru_uz,aci);
                        DogruCiz(dogru_uz,aci,karakter);// Dogru cizen fonksiyon cagriliyor
                        do{
                            printf("\nTekrar Ayni Sekilden Cizmek Istermisiniz?(e/E/h/H)\n");
                            fflush(stdin);
                            devam=getchar();
                          }while(devam!='e' && devam!='E' && devam!='h' && devam!='H');// Kullanici dogru deger girene kadar bekleniyor
                     }while(devam=='e'||devam=='E');// Kullanicinin istegine gore dongu tekrar dondurulur
                break;
                case 2:
                    do{
                        do{
                            printf("Cizilecek Ikizkenar Ucgenin Yuksekligini Giriniz(min 2, max 22)\n");
                            scanf("%d",&yukseklik);
                          }while(yukseklik<2||yukseklik>22);// Kullanici dogru deger girene kadar bekleniyor
                        printf("Yuksekligi %d Olan Ikizkenar Ucgen:\n",yukseklik);
                        ikizkenarUcgenCiz(yukseklik,karakter);// Ikizkenar ucgen cizen fonksiyon cagriliyor
                        do{
                            printf("Tekrar Ayni Sekilden Cizmek Istermisiniz?(e/E/h/H)\n");
                            fflush(stdin);
                            devam=getchar();
                          }while(devam!='e' && devam!='E' && devam!='h' && devam!='H');// Kullanici dogru deger girene kadar bekleniyor
                     }while(devam=='e'||devam=='E');// Kullanicinin istegine gore dongu tekrar dondurulur
                break;
                case 3:
                    do{
                        do{
                            printf("Cizilecek Ters Ikizkenar Ucgenin Yuksekligini Giriniz(min 2, max 22)\n");
                            scanf("%d",&yukseklik);
                          }while(yukseklik<2||yukseklik>22);// Kullanici dogru deger girene kadar bekleniyor
                        printf("Yuksekligi %d Olan Ters Ikizkenar Ucgen:\n",yukseklik);
                        TersIkizkenarUcgenCiz(yukseklik,karakter);// Ters ikizkenar ucgen cizen fonksiyon cagriliyor
                        do{
                            printf("Tekrar Ayni Sekilden Cizmek Istermisiniz?(e/E/h/H)\n");
                            fflush(stdin);
                            devam=getchar();
                          }while(devam!='e' && devam!='E' && devam!='h' && devam!='H');// Kullanici dogru deger girene kadar bekleniyor
                    }while(devam=='e'||devam=='E');// Kullanicinin istegine gore dongu tekrar dondurulur
                break;
                case 4:
                    do{
                        do{
                            printf("Cizilecek Karenin Kenar Uzunlugunu Giriniz(min 2, max 22)\n");
                            scanf("%d",&kenar);
                          }while(kenar<2||kenar>22);
                        printf("Bir Kenarinin Uzunlugu %d Olan Kare:\n",kenar);
                        KareCiz(kenar,karakter);// Kare cizen fonksiyon cagriliyor
                        do{
                            printf("Tekrar Ayni Sekilden Cizmek Istermisiniz?(e/E/h/H)\n");
                            fflush(stdin);
                            devam=getchar();
                          }while(devam!='e' && devam!='E' && devam!='h' && devam!='H');
                      }while(devam=='e'||devam=='E');
                break;
                case 5:
                    do{
                        do{
                            printf("Cizilecek Dikdortgenin Yuksekligini(min 2, max 22) ve Genisligini Giriniz(min 2, max 80)\n");
                            scanf("%d %d",&yukseklik,&genislik);
                          }while(yukseklik<2||yukseklik>22||genislik<2||genislik>80);
                        printf("Yuksekligi %d ve Genisligi %d Olan Dikdortgen:\n",yukseklik,genislik);
                        DikdortgenCiz(yukseklik,genislik,karakter);// Dikdortgen cizen fonksiyon cagriliyor
                        do{
                            printf("Tekrar Ayni Sekilden Cizmek Istermisiniz?(e/E/h/H)\n");
                            fflush(stdin);
                            devam=getchar();
                          }while(devam!='e' && devam!='E' && devam!='h' && devam!='H');
                      }while(devam=='e'||devam=='E');
                break;
                case 6:
                    do{
                        do{
                            printf("Cizilecek Kum Saatinin Yuksekligini Giriniz(min 4, max 22 ve cift sayi)\n");
                            scanf("%d",&yukseklik);
                          }while(yukseklik<4||yukseklik>22||yukseklik%2!=0);// Kullanicinin dogru deger girip girmedigi kontrol ediliyor
                        printf("Yuksekligi %d Olan Kum Saati:\n",yukseklik);
                        TersIkizkenarUcgenCiz(yukseklik/2,karakter);/* Kum saatinin ust kismini cizmek icin tersikizkenar ucgen cizen fonksiyon
                        cagriliyor ve sadece ust kismini cizeceginden yuksekligin yarisi fonksiyona gonderiliyor*/
                        ikizkenarUcgenCiz(yukseklik/2,karakter);/* Kum saatinin alt kismini cizmek icin ikizkenar ucgen cizen fonksiyon
                        cagriliyor ve sadece alt kismini cizeceginden yuksekligin yarisi fonksiyona gonderiliyor*/
                        do{
                            printf("Tekrar Ayni Sekilden Cizmek Istermisiniz?(e/E/h/H)\n");
                            fflush(stdin);
                            devam=getchar();
                          }while(devam!='e' && devam!='E' && devam!='h' && devam!='H');
                      }while(devam=='e'||devam=='E');
                break;
                case 7:
                    do{
                        do{
                            printf("Cizilecek Eskenar Dortgenin (Baklava Dilimi) Yuksekligini Giriniz(min 5, max 21 ve tek sayi)\n");
                            scanf("%d",&yukseklik);
                          }while(yukseklik<5||yukseklik>21||yukseklik%2==0);
                        printf("Yuksekligi %d Olan Eskenar Dortgen:\n",yukseklik);
                        EskenarDortgenCiz(yukseklik,karakter);// Eskenar dortgen cizen fonksiyon cagriliyor
                        do{
                            printf("Tekrar Ayni Sekilden Cizmek Istermisiniz?(e/E/h/H)\n");
                            fflush(stdin);
                            devam=getchar();
                          }while(devam!='e' && devam!='E' && devam!='h' && devam!='H');
                      }while(devam=='e'||devam=='E');
                break;
                case 8:
                    do{
                        do{
                            printf("Cizilecek Paralelkenarin Yuksekligini(min 2, max 22) ve Genisligini Giriniz(min 2, max 58)\n");
                            scanf("%d %d",&yukseklik,&genislik);
                          }while(yukseklik<2||yukseklik>22||genislik<2||genislik>58);
                        printf("Yuksekligi %d ve Genisligi %d Olan Paralelkenar:\n",yukseklik,genislik);
                        ParalelkenarCiz(yukseklik,genislik,karakter);// Paralelkenar cizen fonksiyon cagriliyor
                        do{
                            printf("Tekrar Ayni Sekilden Cizmek Istermisiniz?(e/E/h/H)\n");
                            fflush(stdin);
                            devam=getchar();
                          }while(devam!='e' && devam!='E' && devam!='h' && devam!='H');
                      }while(devam=='e'||devam=='E');
                  break;
                  case 9:
                    do{
                        printf("Sekli Ciziminde Kullanilmak Istenen Karakteri Giriniz(Bosluk Girilemez)\n");
                        fflush(stdin);
                        scanf("%c",&karakter);// Kullanicinin kullanmak istedigi karakter aliniyor
                      }while(karakter==' ');// Boslukla cizim yapilamayacagindan kullanicinin bosluk girmemesi bekleniyor
                  break;
                  case 10:
                     do{
                        printf("Cikmak Istediginize Emin misiniz?(e/E/h/H)\n");
                        fflush(stdin);
                        cikis=getchar();
                     }while(cikis!='e' && cikis!='E' && cikis!='h' && cikis!='H');
                  break;
               }
               printf("\n\n");
    }while(cikis=='H'||cikis=='h');
    }
    return 0;
}
void DogruCiz (int uzunluk,int aci,char karakter)// Dogru cizen,geriye deger dondurmeyen fonksiyonun tanimi
{
    int i,j;// Karakter ve bosluklar icin kullanilan sayaclar
    if (aci==0){
        for(i=uzunluk;i>0;i--)// Belirlenen uzunluk kadar karakterin yazilmasini saglayan for dongusu
            printf("%c",karakter);
    }
    else if (aci==45){
            for(j=uzunluk;j>0;j--){
                for(i=uzunluk;i>0;i--){// Belirlenen uzunluk kadar karakterin yazilmasini saglayan for dongusu
                    uzunluk--;
                    for(i=uzunluk;i>0;i--)// Karakter yazilana kadar kullanilacak boslugun yaziminda kullanilan for dongusu
                        printf("%c",' ');
                    printf("%c",karakter);
                    printf("\n");
                }
            }
    }
          else if (aci==90){
                  for(i=uzunluk;i>0;i--){
                     printf("%c",karakter);
                     printf("\n");
                  }
          }
               else if (aci==135){
                        for(j=1;j<=uzunluk;j++){
                            for(i=j-1;i>0;i--)
                                printf("%c",' ');
                            printf("%c",karakter);
                            printf("\n");
                        }
               }
}
void ikizkenarUcgenCiz(int yukseklik,char karakter)
{
    int satir_no,i;
    for(satir_no=1;satir_no<=yukseklik;satir_no++){
        for(i=yukseklik-satir_no;i>=1;i--)
            printf("%c",' ');
        for(i=1;i<=2*satir_no-1;i++){
            printf("%c",karakter);
        }
        printf("\n");
    }
}
void TersIkizkenarUcgenCiz(int yukseklik,char karakter)
{
    int satir_no,i;
    for(satir_no=1;satir_no<=yukseklik;satir_no++){
        for(i=satir_no-1;i>0;i--)
            printf("%c",' ');
        for(i=1;i<=2*yukseklik-(2*satir_no-1);i++)
            printf("%c",karakter);
        printf("\n");
    }
}
void KareCiz(int kenar,char karakter)
{
    int i,j;
    for(j=kenar;j>0;j--){
        for(i=kenar;i>0;i--)
            printf("%c",karakter);
        printf("\n");
    }
}
void DikdortgenCiz(int yukseklik,int genislik,char karakter)
{
    int i;
    for(i=genislik;i>0;i--)
        printf("%c",karakter);
    printf("\n");
    yukseklik--;
    if(yukseklik>0)
        return DikdortgenCiz(yukseklik,genislik,karakter);
}
void EskenarDortgenCiz(int yukseklik,char karakter)
{
    int i,satir_no;
    ikizkenarUcgenCiz(yukseklik/2+1,karakter);
    for(satir_no=1;satir_no<=yukseklik/2;satir_no++){
        printf(" ");
        for(i=satir_no-1;i>0;i--)
            printf("%c",' ');
        for(i=1;i<=yukseklik-(2*satir_no);i++)
            printf("%c",karakter);
        printf("\n");
    }
}
void ParalelkenarCiz(int yukseklik,int genislik,char karakter)
{
    int i,j;
    for (i=yukseklik;i>0;i--){
        yukseklik--;
        for(j=yukseklik-1;j>=0;j--)
            printf("%c",' ');
        DogruCiz(genislik,0,karakter);
        printf("\n");
    }
}
