#include <iostream>

using namespace std;

#include "ucuslar.h"
#include "kuyruk.h"

numara_kuyrugu::numara_kuyrugu()
{
    bas=NULL;
}

void numara_kuyrugu::ekle(ucus *yeni)
{
    ucus *gecici, *onceki;

    if (bas==NULL || yeni->getNo()<bas->getNo())
    {
        yeni->setSonraki(bas);
        bas=yeni;
    }
    else
    {
        onceki=bas;
        gecici=bas->getSonraki();
        while ((gecici!=NULL) && (gecici->getNo()<yeni->getNo()))
        {
            onceki=gecici;
            gecici=gecici->getSonraki();
        }
        yeni->setSonraki(gecici);
        onceki->setSonraki(yeni);
    }
}

ucus *numara_kuyrugu::cikar(int cik)
{
    ucus *gecici=bas,*onceki;

    if(bas->getSonraki()==NULL)
       bas==NULL;
    else
    {
        while(gecici->getNo()!=cik)
    {
        onceki=gecici;
        gecici=gecici->getSonraki();
    }

    onceki->setSonraki(gecici->getSonraki());
    }

    return gecici;
}

bool numara_kuyrugu::bos_mu()
{
    return  bas==NULL;
}

void numara_kuyrugu::yazdir(ucus *yaz)
{
    char *gecici;
    gecici=yaz->getZaman();

    cout<<yaz->getNo()<<"      "<<yaz->getKalkis()<<"         "<<yaz->getVaris()<<"       "<<gecici[0]<<gecici[1]<<":"<<gecici[2]<<gecici[3]<<"         "
    <<yaz->getNormal()<<"           "<<yaz->getLuks()<<endl;
}

ucus *numara_kuyrugu::tarama(int varmi)
{
    ucus *bir_ucus;
    bir_ucus=bas;
    while(bir_ucus!=NULL)
    {
        if(bir_ucus->getNo()==varmi)
            break;
        bir_ucus=bir_ucus->getSonraki();
    }
    if(bir_ucus==NULL)
        return NULL;
    else
        return bir_ucus;
}

void numara_kuyrugu::luks_tarama()
{
    ucus *bir_ucus=bas;
    char *gecici;

    while(bir_ucus!=NULL)
    {
        if(bir_ucus->getLuks()!=0)
        {
            gecici=bir_ucus->getZaman();
            cout<<bir_ucus->getNo()<<"      "<<bir_ucus->getKalkis()<<"         "<<bir_ucus->getVaris()<<"       "<<gecici[0]<<gecici[1]<<":"<<gecici[2]<<
            gecici[3]<<"         "<<bir_ucus->getNormal()<<"           "<<bir_ucus->getLuks()<<endl;
            cout<<"\n"<<endl;
        }
        bir_ucus=bir_ucus->getSonraki();
    }
}
