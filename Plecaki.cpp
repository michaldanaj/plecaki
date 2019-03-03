#include "Plecaki.h"


Plecaki::Plecaki(const int ile_plec_):ile_plec(ile_plec_){;}

void Plecaki::nowy_plecak(const int poj_){
    Plecak plec = Plecak(plecaki.size(), poj_, ile_plec);
    plecaki.push_back(plec);
    //return plec;
}

void Plecaki::wypelnij_pule(list<Przedmiot>& przedmioty){
    for (auto &el:przedmioty)
        plecaki[0].wloz(el);
}

//prze³adowuje przedmiot  miêdzy dwoma plecakami
//zwraca wskaŸnik na prze³o¿ony przedmiot
Przedmiot* Plecaki::przeloz(int pl1_id, int pl2_id){
    //Przedmiot elem=**p.begin();
    //Przedmiot* prz = przed_do_przel(pl1_id, pl2_id);
    Przedmiot& prz=plecaki[pl1_id].wyjmij(pl2_id);
    plecaki[pl2_id].wloz(prz);
    return &prz;
}

//Przywraca przeniesiony wczeœniej przedmiot. Przedmiot mo¿e byæ
//w œrodku kolejki, dlatego jedyne co jest robione, to update
//parametrów przedmiotu i za³adowanie go do plecaka
void Plecaki::przywroc_przedmiot(Przedmiot* przed, int plecak_pocz){
    plecaki[przed->akt_plecak].wyjmij(*przed);
    plecaki[plecak_pocz].wloz(*przed);
}

int Plecaki::size() const{
    return plecaki.size();
}

//pojemnosc i-tego plecaka
int Plecaki::poj(int i){
    if (i>=ile_plec)
        return -1;
    return plecaki[i].poj;
}  
            
ostream &operator<<( ostream &output, const Plecaki &c ) {
    output << "*****    PULA     *****"<<endl;
    output << c.plecaki[0];
    output << "*****    PLECAKI     *****"<<endl;
    for (int i=1; i<c.size(); i++){
        output << c.plecaki[i]<<endl;
    }
    output << endl;
    return output ;    
}    

//zwracam z puli najwiêksz¹ deltê przy przeniesieniu do zadanego plecaka
double Plecaki::zysk_przelozenia(int plecak_pocz, int plecak_doc){
    return plecaki[plecak_pocz].zysk_przelozenia(plecak_doc);
}

//wylicza zysk z wymiany dwóch najbardziej op³acalnych elementów
//miêdzy plecakami
double Plecaki::zysk_wymiany(int plecak_pocz, int plecak_doc){
    if (plecaki[plecak_pocz].ile_prz==0 || plecaki[plecak_doc].ile_prz==0)
        return 0;
    double z1 = zysk_przelozenia(plecak_pocz, plecak_doc);
    double z2 = zysk_przelozenia(plecak_doc, plecak_pocz);
    return z1+z2;
}

//zwraca wskaŸnik do przemiotu, najlepszego do przeniesienia z plecak_pocz
//do plecak_doc
Przedmiot* Plecaki::przed_do_przel(int plecak_pocz, int plecak_doc){
    return plecaki[plecak_pocz].przed_do_przel(plecak_doc);
}        

bool Plecaki::czy_pelny(int plec){
    return plecaki[plec].czy_pelny();
}

void Plecaki::wykonaj_sekwencje(vector<int>& sekw){
    for (int i=0; i<sekw.size(); i+=2){
        przeloz(sekw[i], sekw[i+1]);
    }
}

/*
bool Plecaki::czy_powrot_do_puli(int plecak_pocz, int plecak_doc){
    Przedmiot *przed=przed_do_przel(plecak_pocz, plecak_doc);
    double wart_doc=przed->;
}
*/


