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

    //Wk³ada wszystkie, do tej pory nigdzie nie w³o¿one przedmioty
    //do puli
    void wypelnij_pule(list<Przedmiot>& przedmioty);

    //zwraca wskaŸnik do przemiotu, najlepszego do przeniesienia z plecak_pocz
    //do plecak_doc
    Przedmiot *przed_do_przel(int plecak_pocz, int plecak_doc) const{
            return plecaki[plecak_pocz].przed_do_przel(plecak_doc);
    };

    //wk³ada do plecaka przedmiot.
    void wloz_do_plecaka(Przedmiot *przed, int plecak_doc){
      plecaki[plecak_doc].wloz(*przed);
      };

    //prze³adowuje przedmiot  miêdzy dwoma plecakami
    //zwraca wskaŸni do prze³o¿ónego przedmiotu (chyba nie potrzebnie)
    Przedmiot* przeloz(int pl1_id, int pl2_id){
            Przedmiot& prz=plecaki[pl1_id].wyjmij(pl2_id);
        plecaki[pl2_id].wloz(prz);
        return &prz;

    };

    //wykonuje sekwencjê ruchów zapisan¹ w wektorze
    void wykonaj_sekwencje(vector<int>& sekw);

    //Przywraca przeniesiony wczeœniej przedmiot. Przedmiot mo¿e byæ
    //w œrodku kolejki, dlatego jedyne co jest robione, to update
    //parametrów przedmiotu i za³adowanie go do plecaka
    void przywroc_przedmiot(Przedmiot* przed, int plecak_pocz){
            plecaki[przed->akt_plecak].wyjmij(*przed);
        plecaki[plecak_pocz].wloz(*przed);
    };

    //Wyjmuje przedmiot z plecaka. Przedmiot mo¿e byæ
    //w œrodku kolejki, dlatego jedyne co jest robione, to update
    //parametrów przedmiotu
    void wyjmij_przedmiot(Przedmiot* przed){
      plecaki[przed->akt_plecak].wyjmij(*przed);
    };

    //zwracam z puli najwiêksz¹ deltê przy przeniesieniu do zadanego plecaka
    double zysk_przelozenia(int plecak_pocz, int plecak_doc) const {
        return plecaki[plecak_pocz].zysk_przelozenia(plecak_doc);
    }


    //wylicza zysk z wymiany dwóch najbardziej op³acalnych elementów
    //miêdzy plecakami
    double zysk_wymiany(int plecak_pocz, int plecak_doc) const{
          if (plecaki[plecak_pocz].ile_prz==0 || plecaki[plecak_doc].ile_prz==0)
                return 0;
            double z1 = zysk_przelozenia(plecak_pocz, plecak_doc);
            double z2 = zysk_przelozenia(plecak_doc, plecak_pocz);
            return z1+z2;
    };

    //indeks plecaka, który wygeneruje najwiêkszy zysk przy prze³ozeniu
    //z plecaka plecak_pocz. Bierze pod uwagê tylko plecaki nie wype³nione
    //do koñca
//    int plecak_maks_zysk(int plecak_pocz) const;

    //Srawdza, czy przedmiot kóry ma zostaæ przeniesiony z plecakaa plecak_pocz
    //do plecaka plecak_doc, bêdzie mia³ w plecak_doc tak ma³¹ wartoœæ,
    //¿e jakieœ elementy z puli bêd¹ mia³y w plecak_docc wy¿sz¹ wartoœc od niego
    bool czy_powrot_do_puli(int plecak_pocz, int plecak_doc);

    //Zwraca liczbê plecaków (wlicza w to pulê)
    int size() const{
          return plecaki.size();
    };

    //Zwraca liczbê przedmiotów w i-tym plecaku
    int size(int i) const{
      return plecaki[i].ile_prz;
    };

    //pojemnosc i-tego plecaka
    int poj(int i) const{
        if (i>=ile_plec)
            return -1;
        return plecaki[i].poj;
    };

    //czy pe³ny plecak plec
    bool czy_pelny(int plec) const{
            return plecaki[plec].czy_pelny();
    };

    //czy wszystkie plecaki s¹ pe³ne
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
