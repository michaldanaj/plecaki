#ifndef PLECAKI_H
#define PLECAKI_H
#include <iostream>
#include <vector>
#include <list>
#include "Plecak.h"


class Plecaki{

    vector<Plecak> plecaki;

  public:

    //Plecak pula = Plecak(ile_plec, std::numeric_limits<int>::max(), 0);
    const int ile_plec;

    Plecaki(const int ile_plec_);
    Plecaki(vector<int> pojemnosci);

    void nowy_plecak(const int poj_);

    //Wk�ada wszystkie, do tej pory nigdzie nie w�o�one przedmioty
    //do puli
    void wypelnij_pule(list<Przedmiot>& przedmioty);

    //zwraca wska�nik do przemiotu, najlepszego do przeniesienia z plecak_pocz
    //do plecak_doc
    Przedmiot *przed_do_przel(int plecak_pocz, int plecak_doc) const{
            return plecaki[plecak_pocz].przed_do_przel(plecak_doc);
    };

    //wk�ada do plecaka przedmiot.
    void wloz_do_plecaka(Przedmiot *przed, int plecak_doc){
      plecaki[plecak_doc].wloz(*przed);
      };

    //prze�adowuje przedmiot  mi�dzy dwoma plecakami
    //zwraca wska�ni do prze�o��nego przedmiotu (chyba nie potrzebnie)
    Przedmiot* przeloz(int pl1_id, int pl2_id){
            Przedmiot& prz=plecaki[pl1_id].wyjmij(pl2_id);
        plecaki[pl2_id].wloz(prz);
        return &prz;

    };

    //wykonuje sekwencj� ruch�w zapisan� w wektorze
    void wykonaj_sekwencje(vector<int>& sekw);

    //Przywraca przeniesiony wcze�niej przedmiot. Przedmiot mo�e by�
    //w �rodku kolejki, dlatego jedyne co jest robione, to update
    //parametr�w przedmiotu i za�adowanie go do plecaka
    void przywroc_przedmiot(Przedmiot* przed, int plecak_pocz){
            plecaki[przed->akt_plecak].wyjmij(*przed);
        plecaki[plecak_pocz].wloz(*przed);
    };

    //Wyjmuje przedmiot z plecaka. Przedmiot mo�e by�
    //w �rodku kolejki, dlatego jedyne co jest robione, to update
    //parametr�w przedmiotu
    void wyjmij_przedmiot(Przedmiot* przed){
      plecaki[przed->akt_plecak].wyjmij(*przed);
    };

    //zwracam z puli najwi�ksz� delt� przy przeniesieniu do zadanego plecaka
    double zysk_przelozenia(int plecak_pocz, int plecak_doc) const {
        return plecaki[plecak_pocz].zysk_przelozenia(plecak_doc);
    }


    //wylicza zysk z wymiany dw�ch najbardziej op�acalnych element�w
    //mi�dzy plecakami
    double zysk_wymiany(int plecak_pocz, int plecak_doc) const{
          if (plecaki[plecak_pocz].ile_prz==0 || plecaki[plecak_doc].ile_prz==0)
                return 0;
            double z1 = zysk_przelozenia(plecak_pocz, plecak_doc);
            double z2 = zysk_przelozenia(plecak_doc, plecak_pocz);
            return z1+z2;
    };

    //indeks plecaka, kt�ry wygeneruje najwi�kszy zysk przy prze�ozeniu
    //z plecaka plecak_pocz. Bierze pod uwag� tylko plecaki nie wype�nione
    //do ko�ca
//    int plecak_maks_zysk(int plecak_pocz) const;

    //Srawdza, czy przedmiot k�ry ma zosta� przeniesiony z plecakaa plecak_pocz
    //do plecaka plecak_doc, b�dzie mia� w plecak_doc tak ma�� warto��,
    //�e jakie� elementy z puli b�d� mia�y w plecak_docc wy�sz� warto�c od niego
    bool czy_powrot_do_puli(int plecak_pocz, int plecak_doc);

    //Zwraca liczb� plecak�w (wlicza w to pul�)
    int size() const{
          return plecaki.size();
    };

    //Zwraca liczb� przedmiot�w w i-tym plecaku
    int size(int i) const{
      return plecaki[i].ile_prz;
    };

    //pojemnosc i-tego plecaka
    int poj(int i) const{
        if (i>=ile_plec)
            return -1;
        return plecaki[i].poj;
    };

    //czy pe�ny plecak plec
    bool czy_pelny(int plec) const{
            return plecaki[plec].czy_pelny();
    };

    //czy wszystkie plecaki s� pe�ne
    bool czy_pelne() const;

    friend ostream &operator<<( ostream &output,  Plecaki &c );

    void wysw_wielk_kolejek(int plecak){
            cout << "Wielkosc kolejek: ";
            for (int i=0; i<ile_plec; i++)
                cout<<plecaki[plecak].wielk_kolejki(i)<<" ";
            cout<<endl;
    }
};

int plecak_maks_zysk(const Plecaki& plec,int plecak_pocz);

#endif
