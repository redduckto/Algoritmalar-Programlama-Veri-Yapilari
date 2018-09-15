#ifndef UCUSLAR_H
#define UCUSLAR_H

class ucus{

private:
    int ucus_no;
    char kalkis_yeri[21];
    char varis_yeri[21];
    char kalkis_zamani[5];
    int normalkoltuksay;
    int lukskoltuksay;

    ucus *sonraki_ucus;
    ucus *k_yere_sonraki;
    ucus *k_yere_onceki;

public:
    ucus(int, char *, char *, char *, int, int);

    int getNo();
    char *getKalkis();
    char *getVaris();
    char *getZaman();
    int getNormal();
    int getLuks();

    ucus *getSonraki();
    ucus *getKygsonra();
    ucus *getKygonce();

    void setSonraki(ucus *);
    void setLuks(int);
    void setKygsonra(ucus *);
    void setKygonce(ucus *);
    void listele();
};


#endif
