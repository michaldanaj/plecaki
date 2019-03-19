#ifndef WCZYTAJ_H
#define WCZYTAJ_H
#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include "Przedmiot.h"
#include "Plecaki.h"

class Wczytaj
{
	public:

    Wczytaj():in(std::cin){};
    Wczytaj(istream& strumien):in(strumien){};
    //Wczytaj(string nazwa_pliku):plik(openFile(nazwa_pliku)),in(plik){};
    ~Wczytaj(){
        if (plik.is_open())
            plik.close();
    };

    //Wczytuje liczbe przypadków testowych
    int ile_przypadkow();

    //Wczytuje liczbe plecaków (dodaje 1 dla puli)
    int ile_plecakow();

    //Wczytuje pojemnooeci plecaków (plus wstawiona jest pojemnooeae dla puli)
    std::vector<int> pojemnosci(int ile_plecakow);

    //Wczytuje liczbe przedmiotów
    int ile_przedmiotow();

    //Wczytuje zadan^1 liczbe przedmiotów
    void przedmioty(int ile_plecakow, int ile_przedmiotow, list<Przedmiot>& lista);

    //Wczytuje przedmioty miejsca do konca pliku
    void przedmioty(int ile_plecakow, list<Przedmiot>& lista);

    //bool dane(const string nazwa_pliku, Plecaki& plec);

    void otworz(string nazwa_pliku){
            plik.open(nazwa_pliku, ios_base::in);
            if (!plik.is_open())
                throw string("Problem z otwarciem pliku ")+nazwa_pliku;
            //in=plik;
    }

    private:
        istream& in;
        ifstream plik;
};

#endif
