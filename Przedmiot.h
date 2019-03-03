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
    int akt_plecak;         //aktualny plecak w kt�rym znajduje si� Przedmiot
    double akt_wartosc;        //warto�� przedmiotu w aktualnym plecaku
   // double max_d;          //maksymalna delta spo�r�d wszystkich plecak�w
    //int max_d_dokad;    //do kt�rego plecaka kieruje maksymalna delta
    
    vector <double> w;      //warto�� przedmiotu w ka�dym z plecak�w
    vector <double> d;  //delta przedmiotu z aktualnego miejsca do ka�dego z plecak�w
    
    //Przedmiot(){;}
    Przedmiot(const string id_, const vector<double> wartosci);
    void wysw();
//    friend int operator<(const Przedmiot& left, const Przedmiot& right);
  //  friend int operator>(const Przedmiot& left,
    //           const Przedmiot& right);
    //do jakiego plecaka przenie�� ten element
    void wloz(int j);
    friend ostream &operator<<( ostream &output, const Przedmiot &p );    
};


#endif
