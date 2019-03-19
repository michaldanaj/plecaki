#include "Przedmiot.h"

Przedmiot::Przedmiot(const string id_, const vector<double> wartosci){
    id = id_;

    akt_plecak=0; //Pula
    akt_wartosc=0; //Wartoœæ w puli

    w=wartosci;
    //przeniesienie z puli do plecaka daje deltê równ¹ wartoœci tego
    //przedmiotu w plecaku
    d=w;
}

void Przedmiot::wysw() const{
    for (auto &el:w)
        cout<<el<<" ";
    cout<<endl;
    for (auto &el:d)
        cout<<el<<" ";
    cout<<endl;
}

void Przedmiot::update(int j){
    akt_plecak=j;
    akt_wartosc=w[j];

    for (unsigned int i=0; i<w.size(); i++)
        d[i]=w[i]-akt_wartosc;
    d[akt_plecak] = std::numeric_limits<double>::lowest();
}

ostream &operator<<( ostream &output, const Przedmiot &p ) {
        return output << "Przedmiot o id="<<p.id<<" w plecaku="<<p.akt_plecak;//<<
            //" ma wartosc="<<p.akt_wartosc<<" max_delta="<<p.max_d
            //<<" do:"<<p.max_d_dokad<<endl;
    }


