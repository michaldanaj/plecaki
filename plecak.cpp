#include "Plecak.h"




Plecak::pom::pom(Przedmiot *przed, int plecak_doc){
        prz=przed;
        d=przed->d[plecak_doc];
}



//pomocnicza struktura, do przechowywania na i-ej kolejce informacje
//ze wskaznikeme na przedmiot oraz delt�, jak� jest przy przeniesieniu
//przedmiotu z obecnego plecaka do i-tego. Jak ju� przedmiot znajdzie
//si� w tym plecaku, mo�na doda� go do kolejek

Plecak::Plecak(const int id_, const int poj_, const int ile_plec_):id(id_), 
        poj(poj_), ile_plec(ile_plec_){
    
    for (int i=0; i<ile_plec; i++){
        priority_queue<pom> kolej;
        pqs.push_back(kolej);
    }
    ile_prz=0;
}

double Plecak::zysk_przelozenia(int plecak_doc){
    return pqs[plecak_doc].top().d;
}

Przedmiot* Plecak::przed_do_przel(int plecak_doc){
    return pqs[plecak_doc].top().prz;
}

//kompresja plecaka. Je�li na g�rze kolejki le�� elementy nie nale��ce
//do danego plecaka, to je usuwa
void Plecak::kompresja(){    
    //kompresja kolejek
   // cout <<"KOMPRESJA plecaka :"<<id<<endl;
    for (int i=0; i<ile_plec; i++){
        if (pqs[i].size()>0){
            //je�li na kolejce jest element nie nale��cy do tego plecaka
            //to go wyrzucam
           // cout<< "PRZED id plecaka: "<<id<< " element: "<<pqs[i].top().prz->id << " w ktorym plecaku: "<<pqs[i].top().prz->akt_plecak;
            //cout<<" w sumie elementow "<<pqs[i].size()<<endl;
            while (pqs[i].size()>0 && pqs[i].top().prz -> akt_plecak != id)
                pqs[i].pop();          
            //cout<< "PO id plecaka: "<<id<< " element: "<<pqs[i].top().prz->id << " w ktorym plecaku: "<<pqs[i].top().prz->akt_plecak ;   
            //cout<<" w sumie elementow "<<pqs[i].size()<<endl;
        }
    }
}

//wk�ada przedmiot do tego plecaka, update'uj�c niezb�dne parametry
//umo�liwiam w�o�enie do plecaka o jeden przedmiot ni� jest jego pojemno��
//tylko na cele algorytmu. Zaraz po nim musi nast�pi� wyj�cie z plecaka
void Plecak::wloz(Przedmiot &prz){        
    //umo�liwiam w�o�enie do plecaka o jeden przedmiot ni� jest jego pojemno��
    //tylko na cele algorytmu. Zaraz po nim musi nast�pi� wyj�cie z plecaka
    if (ile_prz==poj+1){
        string kom="Pr�ba za�adowania do plecaka, kt�ry jest pe�ny";
        throw kom;
    }
    prz.wloz(id);
    ile_prz++;
    //wk�adam do ka�dej kolejki
    for (int i=0; i < ile_plec; i++)
        pqs[i].push(pom(&prz, i));                    
}    

//wyci�ga przedmiot z plecaka, pozostawiaj�c go w "pr�ni"
//updateuje przynale�no�� przedmiotu do plecaka na -1 (pr�nia)
//i kompresuje kolejki, usuwaj�c z g�ry elementy przypisane do innych plecak�w
Przedmiot& Plecak::wyjmij(int plecak_doc){
    if (ile_prz==0)
        throw(string("Nie mozna wyladowac z plecaka, brak przemiotow"));
    pom elem=pqs[plecak_doc].top();
    pqs[plecak_doc].pop();
    elem.prz->akt_plecak=-1;
    
    ile_prz--;
    
    kompresja();
    return *elem.prz;
}

//Jako �e nie wiadomo, gdzi w kolejkach znajduje si� przedmiot
//mo�na jedynie zmieni� jego przypisanie i zmniejszy� liczb� elemen�w
//w plecaku
Przedmiot& Plecak::wyjmij(Przedmiot &prz){
    if (ile_prz==0)
        throw(string("Nie mozna wyladowac z plecaka, brak przemiotow"));
    prz.akt_plecak=-1;
    
    ile_prz--;
    
    kompresja();
    return prz;
}

bool Plecak::czy_pelny(){
    if (ile_prz<poj)
        return false;
    return true;
}
       
ostream &operator<<( ostream &output, const Plecak &c ) {
    output << "PLECAK o id="<<c.id<<" ma "<<c.ile_prz<<" przemiotow (limit: ";
    output << c.poj <<")"<<endl;
    if (c.ile_prz>0) {
        for (int i=0; i<c.ile_plec; i++){
            output <<"  Top PQ do plecaka "<<i<<" "<<c.pqs[i].top()<<endl;
        }
    }
    //output << endl;
    return output ;    
} 



