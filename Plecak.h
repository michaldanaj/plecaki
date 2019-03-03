#ifndef PLECAK_H
#define PLECAK_H

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <limits>
#include <queue>
#include <list>
#include "Przedmiot.h"

using namespace std;

class Plecak{
    struct pom{
        Przedmiot* prz;
        double d;
        
        pom(Przedmiot *przed, int plecak_doc);
        
        friend int operator<(const pom& left, const pom& right){
                return left.d<right.d;
        }
        friend ostream &operator<<( ostream &output, const Plecak::pom &c ) {
                return output << "przedmiot o id="<<c.prz->id<<" ma delte="<<c.d;
        }         
    };
    
    vector<priority_queue<pom>> pqs;

    //kompresja plecaka. Jeœli na górze kolejki le¿¹ elementy nie nale¿¹ce
    //do danego plecaka, to je usuwa
    void kompresja();
    
  public:
      
    //pomocnicza struktura, do przechowywania na i-ej kolejce informacje
    //ze wskaznikeme na przedmiot oraz delt¹, jak¹ jest przy przeniesieniu
    //przedmiotu z obecnego plecaka do i-tego. Jak ju¿ przedmiot znajdzie
    //siê w tym plecaku, mo¿na dodaæ go do kolejek
    
    const int id;  //identyfikator plecaka. 
    const int poj; //pojemnoœæ plecaka, mierzona maksymaln¹ liczb¹ przedmiotów
    const int ile_plec; //ile w sumie jest plecaków (nie licz¹c puli)
    int ile_prz; //ile przemiotów znajduje siê w plecaku
    
    Plecak(const int id_, const int poj_, const int ile_plec_);

    Przedmiot* przed_do_przel(int plecak_doc);

    //Jaki jest zysk(delta) wynikaj¹ca z prze³o¿enia przedmiotu z plecaka
    //w którym siê znajduje do plecaka doceloweog
    double zysk_przelozenia(int plecak_doc);
    
    //Zwraca wartoœæ przedmiotu w plecaku plec
    /*double wartosc_w_plec(int plec){
        return 
    }*/
    
    //wk³ada przedmiot do tego plecaka, update'uj¹c niezbêdne parametry
    //umo¿liwiam w³o¿enie do plecaka o jeden przedmiot wiêcej ni¿ jest jego pojemnoœæ
    //tylko na cele algorytmu. Zaraz po nim musi nast¹piæ wyjêcie z plecaka
    void wloz(Przedmiot &prz);
    
    //wyci¹ga przedmiot z plecaka, pozostawiaj¹c go w "pró¿ni"
    //updateuje przynale¿noœæ przedmiotu do plecaka na -1 (pró¿nia)
    //i kompresuje kolejki, usuwaj¹c z góry elementy przypisane do innych plecaków
    Przedmiot& wyjmij(int plecak_doc);

    //Jako ¿e nie wiadomo, gdzi w kolejkach znajduje siê przedmiot
    //mo¿na jedynie zmieniæ jego przypisanie i zmniejszyæ liczbê elemenów
    //w plecaku
    Przedmiot& wyjmij(Przedmiot &prz);

    bool czy_pelny();

    friend ostream &operator<<( ostream &output, const Plecak &c );
};



#endif
