#include "AlgorytmBF.h"


AlgorytmBF::AlgorytmBF(Plecaki *plecaki_, const list<Przedmiot>& przedm):
        ile_plec(plecaki_->size()), ile_prz(plecaki_->size(0))
{
    plecaki = plecaki_;
    
    w_ktorym = vector<int>(ile_prz); //w którym plecaku znajduje siê przedmiot
                                     //przy starcie w zerowym
                                     
    ile_przed = vector<int>(ile_plec); //ile przedmiotow jest w plecaku
    ile_przed[0]=ile_prz;  //wszystko w puli

    for (auto &el:przedm){
        przedmioty.push_back(el);
    }
    
    //tworzê tabelê z wartoœciami
    wartosci = new double*[ile_prz];
    for (int i=0; i < ile_prz; i++)
        wartosci[i] = new double[ile_plec];
                
    //Wype³niam wartoœciami, poza pul¹
    for (int i=0; i < ile_prz; i++)
        for (int j=1; j < ile_plec; j++)
            wartosci[i][j] = przedmioty[i].w[j];
    //Wype³niam wartoœciami w puli
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
    
    //dla ka¿dego plecaka
    //umieszczamy w nim i-ty przedmiot i wywo³ujemy przeszukiwanie
    //dla kolejnego kroku
    for (int j=1; j < ile_plec; j++)
        if (ile_przed[j] < plecaki->poj(j))
            for (int i=0; i < ile_prz; i++) {
                //jeœli jest w puli
                if (w_ktorym[i] == 0){
                    //wk³ada do plecaka
                    przeloz(i, 0, j);                      
                    //wywo³uje dalsze przeszukiwanie
                    licz();
                    //przek³ada do puli
                    przeloz(i, j, 0);
                }
            }                
}

//TODO: na razie algorytm zak³ada, ¿e wszystkie przedmioty s¹ w puli na sart
void AlgorytmBF::start(){

    ocena_akt = 0;
    ocena_max = 0;
    
    //czy oby na pewno wszystkie przedmioty s¹ w puli
    for (int i=1; i < ile_plec; i++)
        if (plecaki->size(i) > 0)
            throw string("Przy starcie algorytmu plecaki musza byc puste!");

    licz();
}



