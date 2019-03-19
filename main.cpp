#include <iostream>
#include <list>
#include <chrono>
#include "Algorytm.h"
#include "AlgorytmMD.h"
#include "AlgorytmBF.h"
#include "AlgorytmZCHL.h"
#include <fstream>
#include "Wczytaj.h"

using namespace std;

string nazwa;
bool debug=false;
bool wiele_przypadkow=false;
bool wyswietl_plecaki=false;
bool z_kodu=false; //czy odpalenie z kodu

//list<Przedmiot> przedmioty;
list<Przedmiot> przedmioty;

enum class alg_enum{ MD, BF, ZCH};

double policz_zysk(){
    int zysk = 0;
    for (auto &el:przedmioty)
        zysk += el.akt_wartosc;
    return zysk;
}

void wysw_przedmioty(){
    int zysk = 0;
    for (int i = 0; i<przedmioty.begin()->ile_plecakow(); i++){
        cout << "Zawartosc plecaka " << i <<":"<<endl;
        for (auto &el:przedmioty)
            if (el.akt_plecak==i){
                cout << "  ID: " << el.id << " Wartosc: " << el.w[i]<<endl;
                zysk+=el.akt_wartosc;
            }
    }
    cout << "wartosc przedmiotow w takiej konfiguracji wynosi "<<zysk;
}

void reset(Plecaki& plecaki, list<Przedmiot> &przedmioty){
    for (int i=1; i < plecaki.ile_plec; i++)
        while (plecaki.size(i)>0)
            plecaki.przeloz(i, 0);

    for (auto &el:przedmioty)
            el.update(0);
}

void gen_wydajnosc(){
    ofstream plik("wydaj1.txt");
    plik<<3<<endl;
    //plik<<1000000<<" "<<1000000<<endl;
    plik<<1000<<" "<<1000000<<" "<<1000000<<endl;
    for (int i=0; i<40000; i++){
        for (int j=0; j<3; j++){
            plik << rand() <<" ";
        }
        plik << endl;
    }
    plik.close();
}


void odpal_algorytm(list<Przedmiot>& przedmioty, Plecaki& plecaki , Algorytm& alg){

        auto start = std::chrono::high_resolution_clock::now();

        alg.start();

        cout << "Zysk wynosi: " << policz_zysk() <<endl;
        if (wyswietl_plecaki)
            wysw_przedmioty();
        auto finish = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = finish - start;
        std::cout << "\nElapsed time: " << elapsed.count() << " s\n";

}

void wys_wektor(vector<int> v){
    for (auto &el:v)
        cout << el <<" ";
}

void help(){
    cout << "Wywo�anie: plecak.exe <parametry> plik_in plik_out\n\n";
    cout << "Przyk�adowe wywo�anie: \n"
            "plecaki.exe -a=BF -w plec1.txt plec1_BF.txt\n\n";
    cout << "Parametry:\n";
    cout << "-h help\n";
    cout << "-d tryb debug\n";
    cout << "-w wy�wietla na konsol� wynikowe roz�o�enie przedmiot�w\n";
    cout << "-a=[nazwa algorytmu]\n\n";
    cout << "Algorytmy:\n"
            "MD - Micha� Danaj ;) Algorytm domy�lny\n"
            "BF - Brute Force. Wszystkie mo�liwo�ci roz�o�enia przedmiot�w\n"
            "ZCH - Zach�anny\n\n";
    cout << "Struktura danych wej�ciowych:\n";
    cout << /*"Dane wej�ciowe mog� by� dostarczone w dw�ch formatach. Jako "
            "jeden przypadek, oraz wiele przypadk�w (w za�o�eniu testowych)."
            "Dane mog� by� dostarczone na standarowe wej�cie lub odczytane z "
            "pliku. Plik powinien mie� nast�puj�cy format:\n"
            "1. Jeden przypadek\n"*/
            "   - pierwszy wiersz: liczba plecak�w\n"
            "   - drugi wiersz: pojemno�ci kolejnych plecak�w oddzielone spacj�\n"
            "   - kolejne wiersze to opis przedmiot�w. Opis jednego przedmiotu w jednym\n"
            "     wierszu. Pierwsza kolumna to identyfikator przedmiotu. W kolejnych \n"
            "     kolumnach s� warto�ci przedmiotu w ka�dym z plecak�w oddzielone spacj�.\n\n"
            /*"2. Wiele przypadek\n"
            "   - pierwszy wiersz: liczba przypadk�w. Kolejne wiersze zawieraj� opis\n"
            "     poszczeg�lnych przypadk�w:\n"
            "   - pierwszy wiersz: liczba plecak�w\n"
            "   - drugi wiersz: pojemno�ci kolejnych plecak�w oddzielone spacj�\n"
            "   - trzeci wiersz: liczba przedmiot�w do wczytania\n"
            "   - kolejne wiersze: warto�ci przedmiot�w w ka�dym z plecak�w "
            "oddzielone sapcj�"*/
            ;
    cout << "Struktura danych wyj�ciowych:\n"
            "  - pierwszy wiersz: Warto�� plecak�w\n"
            "  - drugi wiersz: nag��wek\n"
            "  - kolejne wiersze to kolejne przedmioty. W kolejnych kolumnach\n"
            "    odzielonych spacj� znajduj� si�:\n"
            "    * identyfikator pzedmiotu\n"
            "    * nr plecaka do kt�rego nale�y. 0 oznacza, �e nie ma go w plecaku\n"
            "    * warto�� przedmiotu w tym plecaku\n\n\n";
}

void zapisz_przedmioty(ostream& out){
    out << "Zysk: " << policz_zysk() << endl;
    out << "ID\tplecak_nr\twartosc_w_plecaku" << endl;
    for (auto& przedm:przedmioty){
        out << przedm.id << "\t"<<przedm.akt_plecak << "\t" <<
            przedm.akt_wartosc << endl;
    }
}

int main(int argc, char** argv) {
    //gen_wydajnosc();

    string plik_in_nazwa="plec9.txt";
    string plik_out_nazwa="out.txt";
    string wybr_alg = "MD";

    setlocale(LC_ALL,"");

    //Odczytuj� parametry wywo�ania
    /*if (argc>1 && argc<3){
            cout << "Za ma�a liczba parametr�w!\n";
            help();
            return 1;
    }
    else */
    if (argc==1){
        cout << "Niepoprawne wywo�anie!"<<endl;
        help();
        return 1;
    }
    else if (argc==2 && string(argv[1]) == "-k")
        cout << "Z kodu!!!\n";
    else if (argc==2 && string(argv[1]) != "-k"){
        cout << "Niepoprawne wywo�anie!"<<endl;
        help();
        return 1;
    }
    else if (argc>2){
        int i=1;
        for (; i<argc-2; i++){
            if (string(argv[i]) == "-h")
                help();
            else if (string(argv[i]) == "-d")
                debug = true;
            else if (string(argv[i]) == "-w")
                wyswietl_plecaki = true;
            else if (string(argv[i]).substr(0,3) == "-a="){
                wybr_alg = string(argv[i]).substr(3, string(argv[i]).length());
                if (wybr_alg == "MD" || wybr_alg == "BF" || wybr_alg == "ZCH")
                    cout << "Wybrany algorytm to --"+wybr_alg <<"--"<< endl;
                else {
                    cout << "Niepoprawny algorytm "+wybr_alg <<"!"<< endl;
                    cout << "Mo�liwe warto�ci to: MD, BF, lub ZCH"<<endl;
                    return 1;
                }
            }
            else {
                cout << "Niepoprawne wywo�anie!"<<endl;
                help();
                return 1;
            }
        }
        plik_in_nazwa = string(argv[i++]);
        plik_out_nazwa = string(argv[i++]);
        if (plik_in_nazwa.substr(0,1)=="-" || plik_out_nazwa.substr(0,1)=="-"){
            cout << "Brak b�d� niepoprawna nazwa pliku!" << endl;
            return 1;
        }
    }

    ifstream plik{plik_in_nazwa};
    if (!plik){
        cout << string("Problem z odczytem z pliku ") + plik_in_nazwa;
        return 1;
    }

    try{
        Wczytaj czytaj(plik);

        int ile_przypadkow = 1;
        //g��wna p�tla
        if (wiele_przypadkow)
            ile_przypadkow=czytaj.ile_przypadkow();

        while(ile_przypadkow){

            //ile plecak�w w pliku. W algorytmach b�dzie o jeden wi�cej, bo pula
            int ile_plec = czytaj.ile_plecakow();

            Plecaki plecaki(czytaj.pojemnosci(ile_plec));

            if (wiele_przypadkow){
                int ile_prz=czytaj.ile_przedmiotow();
                czytaj.przedmioty(ile_plec, ile_prz, przedmioty);
            }
            else
                czytaj.przedmioty(ile_plec, przedmioty);

            plecaki.wypelnij_pule(przedmioty);

            if (debug){
                for (auto &el:przedmioty)
                    cout<<&(el)<<" ";

                cout<<endl;
                cout<<plecaki;
            }

            if (wybr_alg == "MD"){
                cout << "Uruchamiam algorytm MD\n";
                AlgorytmMD algMD(&plecaki);
                odpal_algorytm(przedmioty, plecaki, algMD);
            }
            else if (wybr_alg == "BF"){
                cout << "Uruchamiam algorytm BF\n";
                AlgorytmBF algBF(&plecaki, przedmioty);
                odpal_algorytm(przedmioty, plecaki, algBF);
            }
            else if (wybr_alg == "ZCH"){
                cout << "Uruchamiam algorytm ZCH\n";
                AlgorytmZCH algZCH(&plecaki);
                odpal_algorytm(przedmioty, plecaki, algZCH);
            }

            //zapisuj� dane do pliku
            if (plik_out_nazwa.length() > 0){
                ofstream out_f (plik_out_nazwa);
                if (!out_f)
                    throw string("Problem z zapisem do pliku "+plik_out_nazwa);
                zapisz_przedmioty(out_f);
                out_f.close();
            }
            else
                zapisz_przedmioty(cout);

            reset(plecaki, przedmioty);
            ile_przypadkow--;
        }
    }catch(string s)
    {
        plik.close();
        cout << s;
    }

    plik.close();
}


