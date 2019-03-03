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
    
    //prze³adowuje przedmiot  miêdzy dwoma plecakami
    //zwraca koszt operacji
    Przedmiot* przeloz(int pl1_id, int pl2_id);
    
    //Przywraca przeniesiony wczeœniej przedmiot. Przedmiot mo¿e byæ
    //w œrodku kolejki, dlatego jedyne co jest robione, to update
    //parametrów przedmiotu i za³adowanie go do plecaka    
    void przywroc_przedmiot(Przedmiot* przed, int plecak_pocz);
    
    //Zwraca liczbê plecaków (wlicza w to pulê)
    int size() const;
    
    //Zwraca liczbê przedmiotów w i-tym plecaku
    int size(int i);
    
    //pojemnosc i-tego plecaka
    int poj(int i);
    
    friend ostream &operator<<( ostream &output, const Plecaki &c );
    
    //zwracam z puli najwiêksz¹ deltê przy przeniesieniu do zadanego plecaka
    double zysk_przelozenia(int plecak_pocz, int plecak_doc);
    
    //wylicza zysk z wymiany dwóch najbardziej op³acalnych elementów
    //miêdzy plecakami
    double zysk_wymiany(int plecak_pocz, int plecak_doc);
    
    //zwraca wskaŸnik do przemiotu, najlepszego do przeniesienia z plecak_pocz
    //do plecak_doc
    Przedmiot *przed_do_przel(int plecak_pocz, int plecak_doc);
    
    bool czy_pelny(int plec);
    
    void wykonaj_sekwencje(vector<int>& sekw);
    
    //Srawdza, czy przedmiot kóry ma zostaæ przeniesiony z plecakaa plecak_pocz
    //do plecaka plecak_doc, bêdzie mia³ w plecak_doc tak ma³¹ wartoœæ,
    //¿e jakieœ elementy z puli bêd¹ mia³y w plecak_docc wy¿sz¹ wartoœc od niego
    bool czy_powrot_do_puli(int plecak_pocz, int plecak_doc);
    
};


#endif
