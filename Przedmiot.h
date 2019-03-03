#ifndef PRZEDMIOT_H
#define PRZEDMIOT_H
#include<string>
#include<vector>
#include<iostream>
#include<limits>

using namespace std;

class Przedmiot{
  public:
    string id;
    int akt_plecak;         //aktualny plecak w którym znajduje siê Przedmiot
    double akt_wartosc;        //wartoœæ przedmiotu w aktualnym plecaku
   // double max_d;          //maksymalna delta spoœród wszystkich plecaków
    //int max_d_dokad;    //do którego plecaka kieruje maksymalna delta
    
    vector <double> w;      //wartoœæ przedmiotu w ka¿dym z plecaków
    vector <double> d;  //delta przedmiotu z aktualnego miejsca do ka¿dego z plecaków
    
    //Przedmiot(){;}
    Przedmiot(const string id_, const vector<double> wartosci);
    void wysw();
//    friend int operator<(const Przedmiot& left, const Przedmiot& right);
  //  friend int operator>(const Przedmiot& left,
    //           const Przedmiot& right);
    //do jakiego plecaka przenieœæ ten element
    void wloz(int j);
    friend ostream &operator<<( ostream &output, const Przedmiot &p );    
};


#endif
