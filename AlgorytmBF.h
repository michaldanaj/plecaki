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

    double** wartosci; //tablica z wartoœciami przedmiotow w plecaku
    Plecaki* plecaki;   //wskaŸnik do plecaków

    vector<int> w_ktorym; //w którym plecaku znajduje siê przedmiot
    vector<int> ile_przed; //ile przedmiotow jes w plecaku

    vector<Przedmiot*> przedmioty;

    vector<int> kombinacja_max;   //kombinacja przedmiotów maksymalizuj¹ca wynik
    double ocena_akt=0; //aktualna wartoœæ przedmiotów w plecakach
    double ocena_max=0; //maksymalna wartoœæ przedmiotów w plecakach

    void licz();
    void licz2(int i, int ile_wlozonych, int glebokosc);
    void przeloz(int i, int plecak_akt, int plecak_doc);
    void wypelnij_plecaki();

  public:

    string nazwa = "AlgorytmBF";

    AlgorytmBF(Plecaki *plecaki_, list<Przedmiot>& przedm);
    ~AlgorytmBF();


    //TODO: na razie algorytm zak³ada, ¿e wszystkie przedmioty s¹ w puli na sart
    void start();

};

#endif
