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

    //kompresja plecaka. Je�li na g�rze kolejki le�� elementy nie nale��ce
    //do danego plecaka, to je usuwa
    void kompresja();
    
  public:
      
    //pomocnicza struktura, do przechowywania na i-ej kolejce informacje
    //ze wskaznikeme na przedmiot oraz delt�, jak� jest przy przeniesieniu
    //przedmiotu z obecnego plecaka do i-tego. Jak ju� przedmiot znajdzie
    //si� w tym plecaku, mo�na doda� go do kolejek
    
    const int id;  //identyfikator plecaka. 
    const int poj; //pojemno�� plecaka, mierzona maksymaln� liczb� przedmiot�w
    const int ile_plec; //ile w sumie jest plecak�w (nie licz�c puli)
    int ile_prz; //ile przemiot�w znajduje si� w plecaku
    
    Plecak(const int id_, const int poj_, const int ile_plec_);

    Przedmiot* przed_do_przel(int plecak_doc);

    //Jaki jest zysk(delta) wynikaj�ca z prze�o�enia przedmiotu z plecaka
    //w kt�rym si� znajduje do plecaka doceloweog
    double zysk_przelozenia(int plecak_doc);
    
    //Zwraca warto�� przedmiotu w plecaku plec
    /*double wartosc_w_plec(int plec){
        return 
    }*/
    
    //wk�ada przedmiot do tego plecaka, update'uj�c niezb�dne parametry
    //umo�liwiam w�o�enie do plecaka o jeden przedmiot wi�cej ni� jest jego pojemno��
    //tylko na cele algorytmu. Zaraz po nim musi nast�pi� wyj�cie z plecaka
    void wloz(Przedmiot &prz);
    
    //wyci�ga przedmiot z plecaka, pozostawiaj�c go w "pr�ni"
    //updateuje przynale�no�� przedmiotu do plecaka na -1 (pr�nia)
    //i kompresuje kolejki, usuwaj�c z g�ry elementy przypisane do innych plecak�w
    Przedmiot& wyjmij(int plecak_doc);

    //Jako �e nie wiadomo, gdzi w kolejkach znajduje si� przedmiot
    //mo�na jedynie zmieni� jego przypisanie i zmniejszy� liczb� elemen�w
    //w plecaku
    Przedmiot& wyjmij(Przedmiot &prz);

    bool czy_pelny();

    friend ostream &operator<<( ostream &output, const Plecak &c );
};



#endif
