#ifndef ALGORYTMMD_H
#define ALGORYTMMD_H
#include <iostream>
#include <vector>
#include "Plecaki.h"
#include "Algorytm.h"

extern bool debug;
extern void wysw_przedmioty();

class AlgorytmMD:public Algorytm
{
    public:
    struct elem_sekw{
        Przedmiot* prz;
        int plecak_pocz;
        int plecak_doc;

        elem_sekw(Przedmiot* prz_, int plecak_pocz_, int plecak_doc_){
            prz=prz_;
            plecak_pocz=plecak_pocz_;
            plecak_doc=plecak_doc_;
        }

    };

    string nazwa = "Algorytm MD";
    Plecaki *plecaki = nullptr;
    vector<int> sekw_ruchow;        //aktualna sekwencja testowanych ruch�w
    vector<int> sekw_ruchow_max;    //maksymalizuj�ca sekwencja ruch�w
    vector<bool> odwiedzony;        //czy plecka ju� by� wykorzystany w sekwencji
    double ocena_max=0;             //zysk maksymalizuj�cej sekwencji ruch�w
    double ocena_akt=0;             //zysk aktualnej sekwencji testowanych ruch�w

    AlgorytmMD(Plecaki *plecaki_);

    //Startuje algorytm. W jego wyniku Plecaki zostan� wype�nione
    //przedmiotami zgodnie z dzia��niem algortymu
    //TODO: na razie algorytm zak�ada, �e wszystkie przedmioty s� w puli na sart
    void start();

    //Wylicza zysk przy prze�o�eniu przedmiotu z plecak_pocz do plecak_doc
    //Bierze pod uwag� wszystkie mo�liwe roz�o�enia w plecakach po wykonaniu
    //tego prze�o�enia i wybiera optymalne roz�o�enie.
    double ocena_ruchu(const int plecak_pocz, const int plecak_doc, int ocena_akt);

    //dodaje do plecak�w jeden przedmiot z puli. Przedmiot dodawany jest
    //do plecaka, kt�ry generuje najwi�kszy zysk. W elemencie klasy
    //b�dzie zapisana najbardziej zyskowna �cie�ka
    bool dodaj_przedmiot();
};

#endif
