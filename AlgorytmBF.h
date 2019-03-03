#ifndef ALGORYTMBF_H
#define ALGORYTMBF_H

#include <vector>
#include "Przedmiot.h"
#include "Plecaki.h"

class AlgorytmBF
{
    double** wartosci; //tablica z wartoœciami przedmiotow w plecaku
    int** odwiedzony;  //tablica z informacj¹, który przedmiot 
                                        //w którym plecaku
    Plecaki* plecaki;   //wskaŸnik do plecaków
    
    const int ile_plec;
    const int ile_prz;
    
    vector<Przedmiot> przedmioty;
    
  public:
      
    AlgorytmBF(Plecaki *plecaki_, const list<Przedmiot>& przedm);
    ~AlgorytmBF();
    
    
    //TODO: na razie algorytm zak³ada, ¿e wszystkie przedmioty s¹ w puli na sart
    void start();
};

#endif
