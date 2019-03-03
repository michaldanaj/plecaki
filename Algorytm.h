#ifndef ALGORYTM_H
#define ALGORYTM_H
#include <iostream>
#include <vector>
#include "Plecaki.h"

extern bool debug;
extern void wysw_przedmioty();

class Algorytm{
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
    
    Plecaki *plecaki;
    vector<int> sekw_ruchow;        //aktualna sekwencja testowanych ruchów
    vector<int> sekw_ruchow_max;    //maksymalizuj¹ca sekwencja ruchów
    vector<bool> odwiedzony;        //czy plecka ju¿ by³ wykorzystany w sekwencji
    double ocena_max=0;             //zysk maksymalizuj¹cej sekwencji ruchów
    double ocena_akt=0;             //zysk aktualnej sekwencji testowanych ruchów
        
    Algorytm(Plecaki *plecaki_);
    
    //Wylicza zysk przy prze³o¿eniu przedmiotu z plecak_pocz do plecak_doc
    //Bierze pod uwagê wszystkie mo¿liwe roz³o¿enia w plecakach po wykonaniu
    //tego prze³o¿enia i wybiera optymalne roz³o¿enie.
    double ocena_ruchu(const int plecak_pocz, const int plecak_doc, int ocena_akt);      
    
    //dodaje do plecaków jeden przedmiot z puli. Przedmiot dodawany jest
    //do plecaka, który generuje najwiêkszy zysk. W elemencie klasy
    //bêdzie zapisana najbardziej zyskowna œcie¿ka
    bool dodaj_przedmiot();
};

#endif
