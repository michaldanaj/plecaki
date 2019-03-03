#ifndef PRZEDMIOT_H
#define PRZEDMIOT_H
#include<string>
#include<vector>
#include<iostream>
#include<limits>

using namespace std;

class Przedmiot{
  public:
    string id;              //identyfikator plecaka
    int akt_plecak;         //aktualny plecak w którym znajduje siê Przedmiot
    double akt_wartosc;     //wartoœæ przedmiotu w aktualnym plecaku
    
    vector <double> w;      //wartoœæ przedmiotu w ka¿dym z plecaków
    vector <double> d;      //delta przedmiotu z aktualnego miejsca do ka¿dego z plecaków
    
    //Tworzy przedmiot i ustawia jego wartoœci tak, jakby by³ w puli
    Przedmiot(const string id_, const vector<double> wartosci);
    
    void wysw();

    //W³o¿enie przedmiotu do i-tego plecakda
    void wloz(int j);
    
    friend ostream &operator<<( ostream &output, const Przedmiot &p );    
};


#endif
