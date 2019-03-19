#include "Wczytaj.h"

using namespace std;



int Wczytaj::ile_przypadkow(){
    int ile;
    in >> ile;
    return ile;
}

int Wczytaj::ile_plecakow(){
    int ile;
    in>>ile;
    return ile+1;
}

vector<int> Wczytaj::pojemnosci(int ile_plecakow){
    vector<int> pojemnosci;

    //pierwszy to pula, pojemno¶æ o nieskoñczono¶c
    pojemnosci.push_back(1e9);
    for (int i=1; i<ile_plecakow; i++){
        int poj;
        in >> poj;
        pojemnosci.push_back(poj);
    }
    return pojemnosci;
}

int Wczytaj::ile_przedmiotow(){
   int ile;
   in >> ile;
   return ile;
}

void Wczytaj::przedmioty(int ile_plecakow, int ile_przedmiotow, list<Przedmiot>& lista){
    //odczytujê kolejne elementy
    while (ile_przedmiotow--){
        string id;
        in >> id;

        vector<double> wart(ile_plecakow);
        //pierwszy to pula
        wart[0]=0;

        for (int i=1; i<ile_plecakow; i++)
            in >> wart[i];

        lista.push_back(Przedmiot(id, wart));
    }
}


void Wczytaj::przedmioty(int ile_plecakow, list<Przedmiot>& lista){
    //odczytujê kolejne elementy
    while (!in.eof()){
        string id;
        in >> id;

        vector<double> wart(ile_plecakow);

        //pierwszy to pula
        wart[0]=0;

        for (int i=1; i<ile_plecakow; i++)
            in>>wart[i];

        lista.push_back(Przedmiot(id, wart));
    }
}
