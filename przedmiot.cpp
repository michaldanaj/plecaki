#include "Przedmiot.h"

Przedmiot::Przedmiot(const string id_, const vector<double> wartosci){
        id = id_;
        
        akt_plecak=0; //Pula
        akt_wartosc=0; //Warto�� w puli
        
        //ustawiam warto�ci
        w=wartosci;
        //w.insert(w.begin(), 0); //dodana warto�� w puli
        
        //usawiam delt�
        d=w;
        //przeniesienie do samego siebie nie powinno by� mo�liwe, dlatego
        //ustawiam dla tkeij opcji najmniejsz� mo�liw� warto��
        //d[0]= std::numeric_limits<double>::lowest();
        
        //auto el = max_element(d.begin(), d.end());
        //max_d = *el;
        //max_d_dokad = el - d.begin();
    }
    //Przedmiot(int i_):i(i_){;}
    
    
    void Przedmiot::wysw(){
        for (auto &el:w)
            cout<<el<<" ";
        cout<<endl;
        for (auto &el:d)
            cout<<el<<" ";         
        cout<<endl;
    }
       
    //do jakiego plecaka przenie�� ten element
    void Przedmiot::wloz(int j){        
        akt_plecak=j; //Pula
        akt_wartosc=w[j];
        
        for (int i=0; i<w.size(); i++)
            d[i]=w[i]-akt_wartosc;            
        d[akt_plecak] = std::numeric_limits<double>::lowest();
                    
        //auto el = max_element(d.begin(), d.end());
        //max_d = *el;
        //max_d_dokad = el - d.begin();        
    }

//int operator<(const Przedmiot& left, const Przedmiot& right){return left.max_d<right.max_d;}
 
 /*              
friend int operator>(const Przedmiot& left,
               const Przedmiot& right){return left.max_d>right.max_d;}
*/
ostream &operator<<( ostream &output, const Przedmiot &p ) {
        return output << "Przedmiot o id="<<p.id<<" w plecaku="<<p.akt_plecak;//<<
            //" ma wartosc="<<p.akt_wartosc<<" max_delta="<<p.max_d
            //<<" do:"<<p.max_d_dokad<<endl;    
    }    
    
    
