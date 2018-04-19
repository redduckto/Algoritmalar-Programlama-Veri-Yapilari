#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct PersonelVerisi{
    int per_no;
    char ad_soyad[26];
    char giris_tarihi[9];
    char unvani[16];
    float ucret_katsayisi;
    int toplam_sure;
};

int main()
{
   struct PersonelVerisi personel={0,"","","",0.0,0};
   int i,k=0;
   int orta,aranan;
   int en_alt=0,en_ust=100;
   int per_no;

   FILE *fdosya;

   fdosya=fopen("personel_yedek.dat","rb+");

   printf("Gormek istediginiz personelin numarasini giriniz:\n");
   scanf("%d",&aranan);
   while(en_alt<=en_ust){
       orta=(en_alt+en_ust)/2;
       if(aranan==orta){
           per_no=aranan;
           en_alt=en_ust+1;
       }
       else if(aranan<orta){
           en_ust=orta-1;
       }
       else{
           en_alt=orta+1;
       }
   }
   for(i=0;i<100;i++){
      fseek(fdosya,i*sizeof(struct PersonelVerisi),SEEK_SET);
      fread(&personel,sizeof(struct PersonelVerisi),1,fdosya);
      if(personel.per_no==per_no){
          printf("%d%-15s%-12s%-10s%-7.2f\n",personel.per_no,personel.ad_soyad,
                        personel.giris_tarihi,personel.unvani,personel.ucret_katsayisi);
                        k--;
      }
      k++;
   }
   if(k==100){
       printf("Bulunamadi.\n");
   }
   fclose(fdosya);

   return 0;
}
