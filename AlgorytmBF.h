#ifndef ALGORYTMBF_H
#define ALGORYTMBF_H

#include <vector>
#include "Przedmiot.h"
#include "Plecaki.h"
#include "Algorytm.h"

extern bool debug;

class AlgorytmBF:public Algorytm
{
    const int ile_plec;
    const int ile_prz;
    int poj_plecakow = -1;
    int ile_pozostalo = 0;

    double** wartosci; //tablica z warto�ciami przedmiotow w plecaku
    Plecaki* plecaki;   //wska�nik do plecak�w

    vector<int> w_ktorym; //w kt�rym plecaku znajduje si� przedmiot
    vector<int> ile_przed; //ile przedmiotow jes w plecaku

    vector<Przedmiot*> przedmioty;

    vector<int> kombinacja_max;   //kombinacja przedmiot�w maksymalizuj�ca wynik
    double ocena_akt=0; //aktualna warto�� przedmiot�w w plecakach
    double ocena_max=0; //maksymalna warto�� przedmiot�w w plecakach

    void licz();
    void licz2(int i, int ile_wlozonych, int glebokosc);
    void przeloz(int i, int plecak_akt, int plecak_doc);
    void wypelnij_plecaki();

  public:

    string nazwa = "AlgorytmBF";

    AlgorytmBF(Plecaki *plecaki_, list<Przedmiot>& przedm);
    ~AlgorytmBF();


    //TODO: na razie algorytm zak�ada, �e wszystkie przedmioty s� w puli na sart
    void start();

};

#endif
