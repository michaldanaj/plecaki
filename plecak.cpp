#include "Plecak.h"




Plecak::pom::pom(Przedmiot *przed, int plecak_doc){
        prz=przed;
        d=przed->d[plecak_doc];
}



//pomocnicza struktura, do przechowywania na i-ej kolejce informacje
//ze wskaznikeme na przedmiot oraz delt¹, jak¹ jest przy przeniesieniu
//przedmiotu z obecnego plecaka do i-tego. Jak ju¿ przedmiot znajdzie
//siê w tym plecaku, mo¿na dodaæ go do kolejek

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

//kompresja plecaka. Jeœli na górze kolejki le¿¹ elementy nie nale¿¹ce
//do danego plecaka, to je usuwa
void Plecak::kompresja(){    
    //kompresja kolejek
   // cout <<"KOMPRESJA plecaka :"<<id<<endl;
    for (int i=0; i<ile_plec; i++){
        if (pqs[i].size()>0){
            //jeœli na kolejce jest element nie nale¿¹cy do tego plecaka
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

//wk³ada przedmiot do tego plecaka, update'uj¹c niezbêdne parametry
//umo¿liwiam w³o¿enie do plecaka o jeden przedmiot ni¿ jest jego pojemnoœæ
//tylko na cele algorytmu. Zaraz po nim musi nast¹piæ wyjêcie z plecaka
void Plecak::wloz(Przedmiot &prz){        
    //umo¿liwiam w³o¿enie do plecaka o jeden przedmiot ni¿ jest jego pojemnoœæ
    //tylko na cele algorytmu. Zaraz po nim musi nast¹piæ wyjêcie z plecaka
    if (ile_prz==poj+1){
        string kom="Próba za³adowania do plecaka, który jest pe³ny";
        throw kom;
    }
    prz.wloz(id);
    ile_prz++;
    //wk³adam do ka¿dej kolejki
    for (int i=0; i < ile_plec; i++)
        pqs[i].push(pom(&prz, i));                    
}    

//wyci¹ga przedmiot z plecaka, pozostawiaj¹c go w "pró¿ni"
//updateuje przynale¿noœæ przedmiotu do plecaka na -1 (pró¿nia)
//i kompresuje kolejki, usuwaj¹c z góry elementy przypisane do innych plecaków
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

//Jako ¿e nie wiadomo, gdzi w kolejkach znajduje siê przedmiot
//mo¿na jedynie zmieniæ jego przypisanie i zmniejszyæ liczbê elemenów
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



