#ifndef ALGORYTMZCHL_H
#define ALGORYTMZCHL_H

#include "plecaki.h"
#include "Algorytm.h"

class AlgorytmZCH:public Algorytm
{
    Plecaki* plecaki;   //wskaŸnik do plecaków

	public:
    string nazwa = "AlgorytmZCH";

    AlgorytmZCH(Plecaki *plecaki_);
    vector<int> kolejnosc_plecakow(int plecak_pocz) const;
    void start();

};

#endif
