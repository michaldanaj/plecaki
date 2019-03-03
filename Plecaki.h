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
    
    void nowy_plecak(const int poj_);
    
    void wypelnij_pule(list<Przedmiot>& przedmioty);
    
    //prze�adowuje przedmiot  mi�dzy dwoma plecakami
    //zwraca koszt operacji
    Przedmiot* przeloz(int pl1_id, int pl2_id);
    
    //Przywraca przeniesiony wcze�niej przedmiot. Przedmiot mo�e by�
    //w �rodku kolejki, dlatego jedyne co jest robione, to update
    //parametr�w przedmiotu i za�adowanie go do plecaka    
    void przywroc_przedmiot(Przedmiot* przed, int plecak_pocz);
    
    //Zwraca liczb� plecak�w (wlicza w to pul�)
    int size() const;
    
    //Zwraca liczb� przedmiot�w w i-tym plecaku
    int size(int i);
    
    //pojemnosc i-tego plecaka
    int poj(int i);
    
    friend ostream &operator<<( ostream &output, const Plecaki &c );
    
    //zwracam z puli najwi�ksz� delt� przy przeniesieniu do zadanego plecaka
    double zysk_przelozenia(int plecak_pocz, int plecak_doc);
    
    //wylicza zysk z wymiany dw�ch najbardziej op�acalnych element�w
    //mi�dzy plecakami
    double zysk_wymiany(int plecak_pocz, int plecak_doc);
    
    //zwraca wska�nik do przemiotu, najlepszego do przeniesienia z plecak_pocz
    //do plecak_doc
    Przedmiot *przed_do_przel(int plecak_pocz, int plecak_doc);
    
    bool czy_pelny(int plec);
    
    void wykonaj_sekwencje(vector<int>& sekw);
    
    //Srawdza, czy przedmiot k�ry ma zosta� przeniesiony z plecakaa plecak_pocz
    //do plecaka plecak_doc, b�dzie mia� w plecak_doc tak ma�� warto��,
    //�e jakie� elementy z puli b�d� mia�y w plecak_docc wy�sz� warto�c od niego
    bool czy_powrot_do_puli(int plecak_pocz, int plecak_doc);
    
};


#endif
