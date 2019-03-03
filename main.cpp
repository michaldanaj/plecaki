#include <iostream>
#include <fstream>
#include <list>
#include "Algorytm.h"
#include "AlgorytmBF.h"
using namespace std;

const string nazwa="plec9.txt";
bool debug=false;

//vector<Przedmiot> przedmioty;
list<Przedmiot> przedmioty;
int ile_plecakow;

void wysw_przedmioty(){
    int zysk = 0;
    for (int i = 0; i<ile_plecakow; i++){
        cout << "Zawartosc plecaka " << i <<":"<<endl;
        for (auto &el:przedmioty)
            if (el.akt_plecak==i){
                cout << "  ID: " << el.id << " Wartosc: " << el.w[i]<<endl;
                zysk+=el.akt_wartosc;
            }
    }
    cout << "wartosc przedmiotow w takiej konfiguracji wynosi "<<zysk;
}

int odczytaj_ile_plecakow(const string nazwa_pliku){
    ifstream plik(nazwa_pliku);
    if (!plik.is_open())
        return -1;
        
    int ile;
    plik>>ile;
    
    plik.close();
    
    //dodajê jeden, bo technicznie jest o jeden wiêcej plecak
    //i jest nim pula
    return ile+1;
}

bool odczytaj_dane(const string nazwa_pliku, Plecaki& plec){
    ifstream plik(nazwa_pliku);
    if (!plik.is_open())
        return false;
    int temp;
    plik>>temp;

    //dodajê pulê
    plec.nowy_plecak(1e9);
    //odczytujê pojemnoœci plecaków
    for (int i=1; i<ile_plecakow; i++){
        int poj;
        plik>>poj;
        plec.nowy_plecak(poj);
    }
    
    //odczytujê kolejne elementy
    while (!plik.eof()){        
        string id;
        plik>>id;
        
        vector<double> wart(ile_plecakow);
        for (int i=1; i<ile_plecakow; i++)
            plik>>wart[i];
        przedmioty.push_back(Przedmiot(id, wart));
    }
    plik.close();
}

void wczytaj_dane(Plecaki &plecaki){    
    
    odczytaj_dane(nazwa, plecaki);
    
    //wrzucam wszystkie przedmioty do puli
    plecaki.wypelnij_pule(przedmioty);
        
}

void gen_wydajnosc(){
    ofstream plik("wydaj1.txt");
    plik<<3<<endl;
    //plik<<1000000<<" "<<1000000<<endl;
    plik<<1000<<" "<<1000000<<" "<<1000000<<endl;
    for (int i=0; i<60000; i++){
        for (int j=0; j<3; j++){
            plik << rand() <<" ";
        }
        plik << endl;
    }
    plik.close(); 
}

int main(int argc, char** argv) {
    //gen_wydajnosc();
    //ile_plecakow=3;
    ile_plecakow=odczytaj_ile_plecakow(nazwa);
    Plecaki plecaki(ile_plecakow);
    wczytaj_dane(plecaki);

    if (debug){    
        for (auto &el:przedmioty)
            cout<<&(el)<<" ";
            
        cout<<endl;
        cout<<plecaki;
    }
    try{        
        AlgorytmBF     alg(&plecaki, przedmioty);
        //Algorytm     alg(&plecaki);
        alg.start();
        
        wysw_przedmioty();
    }
    catch(string kom){
        cout << "ERROR: " << kom <<endl;
    }
    
 	return 0;
}






