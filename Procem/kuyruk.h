#ifndef KUYRUK_H_INCLUDED
#define KUYRUK_H_INCLUDED

class numara_kuyrugu {
    private:
    ucus *bas;

    public:
    numara_kuyrugu();

    void ekle(ucus *);
    ucus *cikar(int);
    bool bos_mu();
    void yazdir(ucus *);
    ucus *tarama(int);
    void luks_tarama();
};

#endif
