#include "AlgorytmBF.h"


AlgorytmBF::AlgorytmBF(Plecaki *plecaki_, const list<Przedmiot>& przedm):
        ile_plec(plecaki_->size()), ile_prz(plecaki_->size(0))
{
    plecaki = plecaki_;
    
    w_ktorym = vector<int>(ile_prz); //w kt�rym plecaku znajduje si� przedmiot
                                     //przy starcie w zerowym
                                     
    ile_przed = vector<int>(ile_plec); //ile przedmiotow jest w plecaku
    ile_przed[0]=ile_prz;  //wszystko w puli

    for (auto &el:przedm){
        przedmioty.push_back(el);
    }
    
    //tworz� tabel� z warto�ciami
    wartosci = new double*[ile_prz];
    for (int i=0; i < ile_prz; i++)
        wartosci[i] = new double[ile_plec];
                
    //Wype�niam warto�ciami, poza pul�
    for (int i=0; i < ile_prz; i++)
        for (int j=1; j < ile_plec; j++)
            wartosci[i][j] = przedmioty[i].w[j];
    //Wype�niam warto�ciami w puli
    for (int i=0; i < ile_prz; i++)
        wartosci[i][0] = 0;
        
    
}

AlgorytmBF::~AlgorytmBF(){
    
    for (int i=0; i < ile_prz; i++)
        delete wartosci[i];
    delete wartosci;
   
}
void AlgorytmBF::przeloz(int i, int plecak_akt, int plecak_doc){
    w_ktorym[i] = plecak_doc;
    ile_przed[plecak_akt]--;
    ile_przed[plecak_doc]++;
    ocena_akt = -wartosci[i][plecak_akt]+wartosci[i][plecak_doc];
    if (ocena_akt > ocena_max){
        ocena_max = ocena_akt;
        kombinacja_max = w_ktorym;
    }
}

void AlgorytmBF::licz(){
    
    //dla ka�dego plecaka
    //umieszczamy w nim i-ty przedmiot i wywo�ujemy przeszukiwanie
    //dla kolejnego kroku
    for (int j=1; j < ile_plec; j++)
        if (ile_przed[j] < plecaki->poj(j))
            for (int i=0; i < ile_prz; i++) {
                //je�li jest w puli
                if (w_ktorym[i] == 0){
                    //wk�ada do plecaka
                    przeloz(i, 0, j);                      
                    //wywo�uje dalsze przeszukiwanie
                    licz();
                    //przek�ada do puli
                    przeloz(i, j, 0);
                }
            }                
}

//TODO: na razie algorytm zak�ada, �e wszystkie przedmioty s� w puli na sart
void AlgorytmBF::start(){

    ocena_akt = 0;
    ocena_max = 0;
    
    //czy oby na pewno wszystkie przedmioty s� w puli
    for (int i=1; i < ile_plec; i++)
        if (plecaki->size(i) > 0)
            throw string("Przy starcie algorytmu plecaki musza byc puste!");

    licz();
}



