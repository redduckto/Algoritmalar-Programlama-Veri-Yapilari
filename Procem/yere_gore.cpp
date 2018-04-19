#include <iostream>

using namespace std;

#include "ucuslar.h"
#include "yere_gore.h"

yer_kuyrugu::yer_kuyrugu()
{
    bas=NULL;
}
void yer_kuyrugu::ekle(ucus *yeni)
{
    yer_kuyrugu onceki,gecici;
    if(bas==NULL)
    {
        bas=yeni;
        yeni->setKygsonra()=yeni;
        yeni->setKygonce()=yeni;
    }
}


