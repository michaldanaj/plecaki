#include "AlgorytmBF.h"


AlgorytmBF::AlgorytmBF(Plecaki *plecaki_, const list<Przedmiot>& przedm):
        ile_plec(plecaki_->size()), ile_prz(plecaki_->size(0))
{
    plecaki = plecaki_;
    
    for (auto &el:przedm)
        przedmioty.push_back(el);
    
    //tworzê tabelê z wartoœciami
    wartosci = new double*[ile_prz];
    for (int i=0; i < ile_prz; i++)
        wartosci[i] = new double[ile_plec];
        
    //tworzê tabelê czy odwiedzony
    odwiedzony = new int*[ile_prz];
    for (int i=0; i < ile_prz; i++)
        odwiedzony[i] = new int[ile_plec];
        
    //Wype³niam wartoœciami, poza pul¹
    for (int i=0; i < ile_prz; i++)
        for (int j=1; j < ile_plec; j++)
            wartosci[i][j] = przedmioty[i].w[j];
    //Wype³niam wartoœciami w puli
    for (int i=0; i < ile_prz; i++)
        wartosci[i][0] = 0;
        
    //Wype³niam wartoœciami, poza pul¹
    for (int i=0; i < ile_prz; i++)
        for (int j=1; j < ile_plec; j++)
            odwiedzony[i][j] = 0;            
    //Wype³niam wartoœciami w puli
    for (int i=0; i < ile_prz; i++)
        odwiedzony[i][0] = 1;
    
}

AlgorytmBF::~AlgorytmBF(){
    
    for (int i=0; i < ile_prz; i++)
        delete wartosci[i];
    delete wartosci;

    for (int i=0; i < ile_prz; i++)
        delete odwiedzony[i];
    delete odwiedzony;
    
}


//TODO: na razie algorytm zak³ada, ¿e wszystkie przedmioty s¹ w puli na sart
void AlgorytmBF::start(){
    
    //czy oby na pewno wszystkie przedmioty s¹ w puli
    for (int i=1; i < ile_plec; i++)
        if (plecaki->size(i) > 0)
            throw string("Przy starcie algorytmu plecaki musza byc puste!");

};


