#include <iostream>

using namespace std;

#include "ucuslar.h"

ucus::ucus(int arg_no, char arg_kalkis[], char arg_varis[], char arg_zaman[], int arg_normal, int arg_luks)
{
    int i;

    sonraki_ucus=NULL;
    ucus_no=arg_no;

    for(i=0;i<21;i++)
    {
        kalkis_yeri[i]=arg_kalkis[i];
        varis_yeri[i]=arg_varis[i];
    }
    for(i=0;i<5;i++)
    {
        kalkis_zamani[i]=arg_zaman[i];
    }

    normalkoltuksay=arg_normal;
    lukskoltuksay=arg_luks;

}

int ucus::getNo()
{

    return ucus_no;
}

char *ucus::getKalkis()
{
    return kalkis_yeri;
}

char *ucus::getVaris()
{
    return varis_yeri;
}

char *ucus::getZaman()
{
    return kalkis_zamani;
}

int ucus::getNormal()
{
    return normalkoltuksay;
}

int ucus::getLuks()
{
    return lukskoltuksay;
}

ucus *ucus::getSonraki()
{
    return sonraki_ucus;
}

void ucus::setSonraki(ucus *arg_sonraki)
{
    sonraki_ucus=arg_sonraki;
}

void ucus::setLuks(int yeni_luks)
{
    lukskoltuksay=yeni_luks;
}
ucus *ucus::getKygsonra()
{
    return k_yere_sonraki;
}
ucus *ucus::getKygonce()
{
    return k_yere_onceki;
}
void ucus::setKygonce(ucus *arg_kygonce)
{
    k_yere_onceki=arg_kygonce;
}
void ucus::setKygsonra(ucus *arg_kygsonra)
{
    k_yere_sonraki=arg_kygsonra;
}
