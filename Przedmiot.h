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
    int akt_plecak;         //aktualny plecak w kt�rym znajduje si� Przedmiot
    double akt_wartosc;     //warto�� przedmiotu w aktualnym plecaku
    
    vector <double> w;      //warto�� przedmiotu w ka�dym z plecak�w
    vector <double> d;      //delta przedmiotu z aktualnego miejsca do ka�dego z plecak�w
    
    //Tworzy przedmiot i ustawia jego warto�ci tak, jakby by� w puli
    Przedmiot(const string id_, const vector<double> wartosci);
    
    void wysw();

    //Updateuje parametry przedmiou po w�o�eniu go do i-tego plecakda
    void update(int j);
    
    friend ostream &operator<<( ostream &output, const Przedmiot &p );    
};


#endif
