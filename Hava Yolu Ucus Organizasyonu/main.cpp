#include <iostream>
#include <windows.h>
using namespace std;

#include "ucuslar.cpp"
#include "kuyruk.cpp"

int menu();
int main()
{
    system("color 0A");
    int menusecim,no,koltuk,luks;
    char k_yer[21],v_yer[21],k_zaman[5];

    numara_kuyrugu kuyruk;
    ucus *bir_ucus,*guncelle,*sil,*silindi;

    do
    {
        menusecim=menu();
        switch(menusecim)
        {
        case 1:
        {
            cout<<"Ucus numarasi : ";
            cin>>no;
            if(kuyruk.tarama(no)==NULL)
            {
                cout<<"\nKalkis Yeri: ";
                cin>>k_yer;
                cout<<"\nVaris Yeri : ";
                cin>>v_yer;
                cout<<"\nKalkis Zamani : ";
                cin>>k_zaman;
                cout<<"\nKoltuk Sayisi : ";
                cin>>koltuk;
                luks=0;

                bir_ucus=new ucus(no,k_yer,v_yer,k_zaman,koltuk,luks);
                kuyruk.ekle(bir_ucus);
            }
            else
                cout<< "Boyle bir ucus bulunmaktadir."<<endl;

            break;
        }
        case 2:
        {
            cout<<"Ucus numarasi : ";
            cin>>no;
            if(kuyruk.tarama(no)==NULL)
            {
                cout<<"\nKalkis Yeri: ";
                cin>>k_yer;
                cout<<"\nVaris Yeri : ";
                cin>>v_yer;
                cout<<"\nKalkis Zamani : ";
                cin>>k_zaman;
                koltuk=0;
                cout<<"\nLuks Koltuk Sayisi : ";
                cin>>luks;
                bir_ucus=new ucus(no,k_yer,v_yer,k_zaman,koltuk,luks);
                kuyruk.ekle(bir_ucus);
            }
            else
                cout<<"Boyle bir ucus bulunmaktadir"<<endl;

            break;
        }

        case 3:
        {
            cout<<"Luks koltuk sayisini guncellemek istediginiz ucusun numarasi : ";
            cin>>no;

            guncelle=kuyruk.tarama(no);

            if(guncelle==NULL)
            {
                cout<<"Boyle bir ucus bulunmamaktadir!"<<endl;
                break;
            }
            else
            {
                cout<<"Yeni luks koltuk sayisi : ";
                cin>>luks;
                guncelle->setLuks(luks);
                cout<<"\nBasariyla guncellendi."<<endl;
            }
            break;
        }

        case 4:
        {
            cout<<"Iptal etmek istediginiz ucusun numarasi : ";
            cin>>no;

            sil=kuyruk.tarama(no);
            if(sil==NULL)
            {
                cout<<"Boyle bir ucus bulunmamaktadir!"<<endl;
                break;
            }
            else
            {
                silindi=kuyruk.cikar(no);
                delete silindi;
                cout<<"\nBasariyla silindi."<<endl;
            }
            break;
        }

        case 5:
        {
            cout<<"Bilgilerini goruntulemek istediginiz ucusun numarasini giriniz : ";
            cin>>no;
            if(kuyruk.tarama(no)==NULL)
            {
                cout<<"Boyle bir ucus bulunmamaktadir"<<endl;
            }
            else
            {
                cout<<"Ucus No  Kalkis Yeri  Varis Yeri  Kalkis Vakti  Normal Koltuk  Luks Koltuk""\n"
                <<"-------  -----------  ----------  ------------  ------------  ------------"<<endl;
                bir_ucus=kuyruk.tarama(no);
                kuyruk.yazdir(bir_ucus);
            }
            break;
        }
        case 6:
        {
            cout<<"Ucus No  Kalkis Yeri  Varis Yeri  Kalkis Vakti  Normal Koltuk  Luks Koltuk""\n"
            <<"-------  -----------  ----------  ------------  ------------  ------------"<<endl;
            kuyruk.luks_tarama();
            break;
        }
        }
    }
    while (menusecim!=10);

    return 0;
}
int menu()
{
    int secim;

    cout<<"\n\n\n       ----------------------------------------------------------------""\n"
        <<"                                   MENU  ""\n"
        <<"\n         ------------------------------------------------------------------""\n"
        <<"\n   1 ) Luks koltuk icermeyen yeni bir ucusun eklenmesi""\n"
        <<"   2 ) Luks koltuk iceren yeni bir ucusun eklenmesi""\n"
        <<"   3 ) Bir ucusun luks koltuk sayisinin guncellenmesi""\n"
        <<"   4 ) Bir ucusun iptal edilmesi""\n"
        <<"   5 ) Bir ucusun bilgilerinin goruntulenmesi""\n"
        <<"   6 ) Luks koltuk iceren ucuslarin listelenmesi\n"
        <<"   7 ) Bir yere olan ucuslarin listelenmesi""\n"
        <<"   8 ) Bir yerden kalkan ucuslarin listelenmesi""\n"
        <<"   9 ) Bir yerden bir yere olan ucuslarin listelenmesi""\n"
        <<"  10 ) Cikis"
        <<"  \n Seciminizi giriniz : "<<endl;
    cin>>secim;

    return secim;
}
