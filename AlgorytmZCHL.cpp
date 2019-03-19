#include <vector>
#include <algorithm>
#include "AlgorytmZCHL.h"


AlgorytmZCH::AlgorytmZCH(Plecaki *plecaki_){
    plecaki = plecaki_;
}


vector<int> AlgorytmZCH::kolejnosc_plecakow(int plecak_pocz) const{
    vector<int> v(plecaki->size());
    for (int i=0; i<plecaki->size(); i++){
        v[i]=plecaki->zysk_przelozenia(plecak_pocz, i);
    }
    sort(v.begin(), v.end(), std::greater<double>());
    return v;
}


void AlgorytmZCH::start(){

    //tyle przedmiotów wk³adam, na ile starczy plecaków lub przedmiotów
    while (plecaki->czy_pelne()==false && plecaki->size(0)>0)
        plecaki->przeloz(0, plecak_maks_zysk(*plecaki, 0));
}



