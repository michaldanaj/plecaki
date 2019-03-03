#ifndef ALGORYTMBF_H
#define ALGORYTMBF_H

#include <vector>
#include "Przedmiot.h"
#include "Plecaki.h"

class AlgorytmBF
{
    double** wartosci; //tablica z warto�ciami przedmiotow w plecaku
    int** odwiedzony;  //tablica z informacj�, kt�ry przedmiot 
                                        //w kt�rym plecaku
    Plecaki* plecaki;   //wska�nik do plecak�w
    
    const int ile_plec;
    const int ile_prz;
    
    vector<Przedmiot> przedmioty;
    
  public:
      
    AlgorytmBF(Plecaki *plecaki_, const list<Przedmiot>& przedm);
    ~AlgorytmBF();
    
    
    //TODO: na razie algorytm zak�ada, �e wszystkie przedmioty s� w puli na sart
    void start();
};

#endif
