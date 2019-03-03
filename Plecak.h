#ifndef PLECAK_H
#define PLECAK_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include "Przedmiot.h"

using namespace std;

class Plecak{
    
    //pomocnicza struktura, przechowuj¹ca na i-ej kolejce informacje
    //ze wskaznikiem na przedmiot oraz delt¹, jak¹ jest przy przeniesieniu
    //przedmiotu z obecnego plecaka do i-tego. Jak ju¿ przedmiot znajdzie
    //siê w tym plecaku, mo¿na dodaæ go do kolejek
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
    //plecaka posortowane od najwiêkszej delty przy przeniesieniu
    //do i-tego plecaka. Ten sam przedmiot bêd¹cy pierwszym w jednej kolejce,
    //mo¿e byæ w œrodu innej kolejki, przez co usuniêcie elementu ze wszystkich
    //kolejek jest k³opotliwe, w wrêcz niemo¿liwe przy tych strukturach.
    //Dlatego przy wyjêciu przedmiotu z plecaka, sprawdzamy czy nie dokopaliœmy
    //siê w danej kolejce do przemiotów których ju¿ nie ma w plecaku. Jeœli tak,
    //to œciagamy je z kolejki (funkcja kompresuj).
    vector<priority_queue<pom>> pqs;

    //kompresja plecaka. Jeœli na górze kolejki le¿¹ elementy nie nale¿¹ce
    //do danego plecaka, to je  z niej usuwa.
    void kompresja();
    
  public:    
    const int id;  //identyfikator plecaka. 
    const int poj; //pojemnoœæ plecaka, mierzona maksymaln¹ liczb¹ przedmiotów
    const int ile_plec; //ile w sumie jest plecaków (nie licz¹c puli)
    int ile_prz; //ile przemiotów znajduje siê w plecaku
    
    Plecak(const int id_, const int poj_, const int ile_plec_);

    //Zwraca wskaŸnik do przedmiotu, który daje najwy¿szy zysk (delta)
    //przy prze³o¿eniu przedmiotu z aktualnego plecaka do plecaka plecak_doc
    Przedmiot* przed_do_przel(int plecak_doc);

    //Jaki jest zysk(delta) wynikaj¹ca z prze³o¿enia najbardziej zyskownego
    //przedmiotu pomiêdzy aktualnym plecakiem a plecakiem plecak_doc
    double zysk_przelozenia(int plecak_doc);
        
    //wk³ada przedmiot do tego plecaka, update'uj¹c niezbêdne parametry
    //umo¿liwiam w³o¿enie do plecaka o jeden przedmiot wiêcej ni¿ jest jego pojemnoœæ
    //tylko na cele algorytmu. Zaraz po nim musi nast¹piæ wyjêcie z plecaka
    //TODO jeszcze siê nad tym zastanowiæ, czy w ogóle taki mechanizm jest
    //potrzebny. Jeœli ju¿, do dodaæ jakiœ bufor, do którego wk³adany jest
    //przedmiot zanim zostanie faktycznie w³o¿ony do plecaka
    void wloz(Przedmiot &prz);
    
    //wyci¹ga przedmiot z plecaka, pozostawiaj¹c go w "pró¿ni"
    //updateuje przynale¿noœæ przedmiotu do plecaka na -1 (pró¿nia)
    //i kompresuje kolejki
    Przedmiot& wyjmij(int plecak_doc);

    //Jako ¿e nie wiadomo, gdzie w kolejkach znajduje siê przedmiot
    //mo¿na jedynie zmieniæ jego przypisanie do plecaka i zmniejszyæ liczbê 
    //przedmiotow w plecaku
    Przedmiot& wyjmij(Przedmiot &prz);

    bool czy_pelny();
    
    friend ostream &operator<<( ostream &output, const Plecak &c );
};



#endif
