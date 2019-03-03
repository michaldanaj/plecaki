#ifndef PLECAK_H
#define PLECAK_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include "Przedmiot.h"

using namespace std;

class Plecak{
    
    //pomocnicza struktura, przechowuj�ca na i-ej kolejce informacje
    //ze wskaznikiem na przedmiot oraz delt�, jak� jest przy przeniesieniu
    //przedmiotu z obecnego plecaka do i-tego. Jak ju� przedmiot znajdzie
    //si� w tym plecaku, mo�na doda� go do kolejek
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
    
    //i-t kolejka odpowiada i-temu plecakowi. Trzyma elementy z akualnego 
    //plecaka posortowane od najwi�kszej delty przy przeniesieniu
    //do i-tego plecaka. Ten sam przedmiot b�d�cy pierwszym w jednej kolejce,
    //mo�e by� w �rodu innej kolejki, przez co usuni�cie elementu ze wszystkich
    //kolejek jest k�opotliwe, w wr�cz niemo�liwe przy tych strukturach.
    //Dlatego przy wyj�ciu przedmiotu z plecaka, sprawdzamy czy nie dokopali�my
    //si� w danej kolejce do przemiot�w kt�rych ju� nie ma w plecaku. Je�li tak,
    //to �ciagamy je z kolejki (funkcja kompresuj).
    vector<priority_queue<pom>> pqs;

    //kompresja plecaka. Je�li na g�rze kolejki le�� elementy nie nale��ce
    //do danego plecaka, to je  z niej usuwa.
    void kompresja();
    
  public:    
    const int id;  //identyfikator plecaka. 
    const int poj; //pojemno�� plecaka, mierzona maksymaln� liczb� przedmiot�w
    const int ile_plec; //ile w sumie jest plecak�w (nie licz�c puli)
    int ile_prz; //ile przemiot�w znajduje si� w plecaku
    
    Plecak(const int id_, const int poj_, const int ile_plec_);

    //Zwraca wska�nik do przedmiotu, kt�ry daje najwy�szy zysk (delta)
    //przy prze�o�eniu przedmiotu z aktualnego plecaka do plecaka plecak_doc
    Przedmiot* przed_do_przel(int plecak_doc);

    //Jaki jest zysk(delta) wynikaj�ca z prze�o�enia najbardziej zyskownego
    //przedmiotu pomi�dzy aktualnym plecakiem a plecakiem plecak_doc
    double zysk_przelozenia(int plecak_doc);
        
    //wk�ada przedmiot do tego plecaka, update'uj�c niezb�dne parametry
    //umo�liwiam w�o�enie do plecaka o jeden przedmiot wi�cej ni� jest jego pojemno��
    //tylko na cele algorytmu. Zaraz po nim musi nast�pi� wyj�cie z plecaka
    //TODO jeszcze si� nad tym zastanowi�, czy w og�le taki mechanizm jest
    //potrzebny. Je�li ju�, do doda� jaki� bufor, do kt�rego wk�adany jest
    //przedmiot zanim zostanie faktycznie w�o�ony do plecaka
    void wloz(Przedmiot &prz);
    
    //wyci�ga przedmiot z plecaka, pozostawiaj�c go w "pr�ni"
    //updateuje przynale�no�� przedmiotu do plecaka na -1 (pr�nia)
    //i kompresuje kolejki
    Przedmiot& wyjmij(int plecak_doc);

    //Jako �e nie wiadomo, gdzie w kolejkach znajduje si� przedmiot
    //mo�na jedynie zmieni� jego przypisanie do plecaka i zmniejszy� liczb� 
    //przedmiotow w plecaku
    Przedmiot& wyjmij(Przedmiot &prz);

    bool czy_pelny();
    
    friend ostream &operator<<( ostream &output, const Plecak &c );
};



#endif
