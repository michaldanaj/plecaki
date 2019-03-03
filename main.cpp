#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <limits>
#include <queue>
#include <list>
#include <cstdlib>
#include "Przedmiot.h"
#include "Plecak.h"
#include "Plecaki.h"
using namespace std;

const string nazwa="plec1.txt";
int debug=false;

//vector<Przedmiot> przedmioty;
list<Przedmiot> przedmioty;
int ile_plecakow;


void wysw_przedmioty(){
    for (int i = 0; i<ile_plecakow; i++){
        cout << "Zawartosc plecaka " << i <<endl;
        for (auto &el:przedmioty)
            if (el.akt_plecak==i){
                cout << "  ID: " << el.id << " Wartosc: " << el.w[i]<<endl;
            }
    }
}


class Algorytm{
    public:
    struct elem_sekw{
        Przedmiot* prz;
        int plecak_pocz;
        int plecak_doc;
        
        elem_sekw(Przedmiot* prz_, int plecak_pocz_, int plecak_doc_){
            prz=prz_;
            plecak_pocz=plecak_pocz_;
            plecak_doc=plecak_doc_;
        }
        
    };
    
    Plecaki *plecaki;
    //vector<elem_sekw> sekw_ruchow;
    //vector<elem_sekw> sekw_ruchow_max;
    vector<int> sekw_ruchow;
    vector<int> sekw_ruchow_max;
    vector<bool> odwiedzony;
    double ocena_max=0;
    double ocena_akt=0;
        
    Algorytm(Plecaki *plecaki_){
        plecaki=plecaki_;
        odwiedzony = vector<bool>(plecaki->ile_plec,false);
    }

    double ocena_ruchu(const int plecak_pocz, const int plecak_doc, int ocena_akt){
        odwiedzony[plecak_doc]=true;
        //dodajê do sekwencji ruchów
        sekw_ruchow.push_back(plecak_pocz);
        sekw_ruchow.push_back(plecak_doc);
        
        //jeœli plecak nie jest pe³ny, to dodajê i próbujê wymieniæ z pul¹
        //i koñczê ocenê
        if (plecaki->czy_pelny(plecak_doc)==false){
            double zysk;            
            
            if (debug){
                cout<< " Proba przeniesienia z plecaka "<<plecak_pocz<<" do "<<plecak_doc<<endl;
            }
            //cout<<*plecaki;

            //pobieram adres przemiotu, ¿eby póŸniej go wróciæ
           // Przedmiot* przed=plecaki->przed_do_przel(plecak_pocz, plecak_doc);
            //zysk = plecaki->przeloz(plecak_pocz, plecak_doc);
            zysk = plecaki->zysk_przelozenia(plecak_pocz, plecak_doc);
            ocena_akt += zysk;
            if (debug){
                cout << "    Zysk czastkowy: "<<zysk<<endl;
                cout << "    Ocena koncowka: "<<ocena_akt<<endl;
            }
        
            Przedmiot* prz = plecaki->przeloz(plecak_pocz, plecak_doc);
                                    
            //sprawdzam, czy op³aca siê z docelowego plecaka wymieniæ siê z pul¹ 
            //o ile Ÿród³owym plecakiem nie jest pula, bo wtedy nie ma to sensu
            zysk = plecaki->zysk_wymiany(plecak_doc,0);
            if (plecak_pocz != 0 && zysk>0){    
                    ocena_akt =+ zysk;                
                    //z plecaka do puli       
                    sekw_ruchow.push_back(plecak_doc);                                  
                    sekw_ruchow.push_back(0);                
                    //z puli od plecaka
                    sekw_ruchow.push_back(0);       
                    sekw_ruchow.push_back(plecak_doc);
            
                    if (ocena_max<ocena_akt){
                        ocena_max=ocena_akt;
                        sekw_ruchow_max=sekw_ruchow;
                    }
                    sekw_ruchow.pop_back();
                    sekw_ruchow.pop_back();
                    sekw_ruchow.pop_back();
                    sekw_ruchow.pop_back();
            }
            else{
                //koniec ruchów. Oceniam czy jest to najlepsza sekwencja
                if (ocena_max<ocena_akt){
                    ocena_max=ocena_akt;
                    sekw_ruchow_max=sekw_ruchow;
                }
            }
            //z powrotem wracam przerzucony element
            //plecaki->przywroc_przedmiot(przed, plecak_pocz);
            plecaki->przywroc_przedmiot(prz, plecak_pocz);
        }
        //jeœli plecak jest pe³ny, to zag³êbiam siê 
        else{
            //Zysk ywnikaj¹cy z prze³o¿enia przedmiotu
            double zysk = plecaki->zysk_przelozenia(plecak_pocz, plecak_doc);
            ocena_akt+=zysk;
            if (debug){
                cout<< " Proba przeniesienia z plecaka "<<plecak_pocz<<" do "<<plecak_doc;
                cout << ". Plecak pelny!" << endl;
                cout << "    Zysk czastkowy: "<<zysk<<endl;
            }
//            cout << "    Ocena koncowka: "<<ocena_akt<<endl;
            
            Przedmiot* prz = plecaki->przeloz(plecak_pocz, plecak_doc);
            //bêdê próbowa³ wstawiaæ do wszystkich mo¿liwych nieodwiedzonych plecaków
            for (int i=1; i < plecaki->ile_plec; i++){
                if (!odwiedzony[i]){
                    
                    //Zysk wynikaj¹cy z kolejnych ruchów, koñcz¹cych sekwencjê
                    ocena_akt=ocena_ruchu(plecak_doc, i, ocena_akt);
                    
                    //prze³adowywania trzeba robiæ od koñca, ¿eby
                    //zrobiæ miejsce w plecaku
                    
                    //wk³adam do starego docelowanego przedmiot
                    //wk³adam od nowego docelowego przemiot
                }
            }
            plecaki->przywroc_przedmiot(prz, plecak_pocz);
        }
        

        //odznaczam jako nieodwiedzony
        odwiedzony[plecak_doc]=false;
        sekw_ruchow.pop_back();
        sekw_ruchow.pop_back();
        return ocena_akt;
    }
        
    //dodaje do plecaków jeden przedmiot z puli. Przedmiot dodawany jest
    //do plecaka, który generuje najwiêkszy zysk. W elemencie klasy
    //bêdzie zapisana najbardziej zyskowna œcie¿ka
    bool dodaj_przedmiot(){
        odwiedzony[0]=true;
        ocena_max=0;
        
        bool czy_pelne=true;
        //Sprawdzam, czy wszystkie plecaki s¹ ju¿ pe³ne. Jak tak, to koniec
        for (int pl_doc=1; pl_doc < plecaki->ile_plec; pl_doc++)
            czy_pelne&=plecaki->czy_pelny(pl_doc);
        if (czy_pelne)
            return true;
        
        for (int pl_doc=1; pl_doc < plecaki->ile_plec; pl_doc++){
            if (debug)
                cout << "\n- Ocena wlozenia nowego przedmiotu do plecaka "<<pl_doc << endl;                               
            ocena_ruchu(0, pl_doc, 0);
            if (debug)
                cout << "- Zysk po przeniesieniu do plecaka "<< pl_doc <<" wynosi "<< ocena_max << endl;                   
        }                
        odwiedzony[0]=false;
        
        if (debug){
            cout<<"maksymalna sekwencja to\n";
            for (auto &el:sekw_ruchow_max)
                cout << el <<" ";
            cout << endl;
            cout<<"Wykonuje sekwencje. Jej zysk to: " << ocena_max<<endl<<endl;
        }
        plecaki->wykonaj_sekwencje(sekw_ruchow_max);
        if (debug)
            wysw_przedmioty();
        return false;
    }
};


int odczytaj_ile_plecakow(const string nazwa_pliku){
    ifstream plik(nazwa_pliku);
    if (!plik.is_open())
        return -1;
        
    int ile;
    plik>>ile;
    
    plik.close();
    
    //dodajê jeden, bo technicznie jest o jeden wiêcej plecak
    //i jest nim pula
    return ile+1;
}

bool odczytaj_dane(const string nazwa_pliku, Plecaki& plec){
    ifstream plik(nazwa_pliku);
    if (!plik.is_open())
        return false;
    int temp;
    plik>>temp;

    //dodajê pulê
    plec.nowy_plecak(1e9);
    //odczytujê pojemnoœci plecaków
    for (int i=1; i<ile_plecakow; i++){
        int poj;
        plik>>poj;
        plec.nowy_plecak(poj);
    }
    
    //odczytujê kolejne elementy
    while (!plik.eof()){        
        string id;
        plik>>id;
        
        vector<double> wart(ile_plecakow);
        for (int i=1; i<ile_plecakow; i++)
            plik>>wart[i];
        przedmioty.push_back(Przedmiot(id, wart));
    }
    plik.close();
}

void init(Plecaki &plecaki){    
    
    odczytaj_dane(nazwa, plecaki);
    
    //wrzucam wszystkie przedmioty do puli
    plecaki.wypelnij_pule(przedmioty);
        
}

void gen_wydajnosc(){
    ofstream plik("wydaj1.txt");
    plik<<3<<endl;
    //plik<<1000000<<" "<<1000000<<endl;
    plik<<1000<<" "<<1000000<<" "<<1000000<<endl;
    for (int i=0; i<60000; i++){
        for (int j=0; j<3; j++){
            plik << rand() <<" ";
        }
        plik << endl;
    }
    plik.close(); 
}

int main(int argc, char** argv) {
    //gen_wydajnosc();
    //ile_plecakow=3;
    ile_plecakow=odczytaj_ile_plecakow(nazwa);
    Plecaki plecaki(ile_plecakow);
    
    init(plecaki);

    if (debug){    
        for (auto &el:przedmioty)
            cout<<&(el)<<" ";
            
        cout<<endl;
        cout<<plecaki;
    }

    Algorytm alg(&plecaki);
    try{
        
        //for (int i=0; i<przedmioty.size(); i++){
            
        int i=0;
        bool czy_pelne=false;
        
        while(i<przedmioty.size() && !czy_pelne){
            if (debug)
                cout <<"*************    Wkladam przedmiot "<< i+1 <<"*************\n\n";                        
            czy_pelne=alg.dodaj_przedmiot();
            i++;
        }
  //          cout<<"po wykonaniu ruchu"<<endl;
//            cout<<plecaki;
            
        //}
        //wysw_przedmioty();
    }
    catch(string kom){
        cout << kom;
    }
    
 	return 0;
}






