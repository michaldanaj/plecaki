#include "AlgorytmMD.h"

AlgorytmMD::AlgorytmMD(Plecaki *plecaki_){

    plecaki=plecaki_;

    //czy oby na pewno wszystkie przedmioty s¹ w puli
    for (int i=1; i < plecaki->size(); i++){

        if (plecaki->size(i) > 0)
            throw string("Przy starcie algorytmu plecaki musza byc puste!");
    }

    odwiedzony = vector<bool>(plecaki->size(), false);
}

void AlgorytmMD::start(){

         //czy oby na pewno wszystkie przedmioty s¹ w puli
        for (int i=1; i < plecaki->size(); i++)
            if (plecaki->size(i) > 0)
                throw string("Przy starcie algorytmu plecaki musza byc puste!");

        int i=0;
        bool czy_pelne=false;

        //while(i < plecaki->size(0) && !czy_pelne){
        while(plecaki->size(0)>0 && !czy_pelne){
            if (debug)
                cout <<"\n\n*************    Wkladam przedmiot "<< i+1 <<"*************\n\n";
            czy_pelne = dodaj_przedmiot();
            i++;
        }
  //          cout<<"po wykonaniu ruchu"<<endl;
//            cout<<plecaki;

        //wysw_przedmioty();
}

double AlgorytmMD::ocena_ruchu(const int plecak_pocz, const int plecak_doc, int ocena_akt){
    odwiedzony[plecak_doc]=true;
    //dodajê do sekwencji ruchów
    sekw_ruchow.push_back(plecak_pocz);
    sekw_ruchow.push_back(plecak_doc);

    //jeœli plecak nie jest pe³ny, to dodajê i próbujê wymieniæ z pul¹
    //i koñczê ocenê
    if (!plecaki->czy_pelny(plecak_doc)){
        double zysk;

        if (debug){
            cout<< " Proba przeniesienia z plecaka "<<plecak_pocz<<" do "<<plecak_doc<<endl;
        }
        //cout<<*plecaki;

        //pobieram adres przemiotu, ¿eby póŸniej go wróciæ
        zysk = plecaki->zysk_przelozenia(plecak_pocz, plecak_doc);
        ocena_akt += zysk;
        if (debug){
            cout << "    Zysk czastkowy: "<<zysk<<endl;
            cout << "    Ocena koncowka: "<<ocena_akt<<endl;
        }

        if (ocena_max < ocena_akt){
            ocena_max = ocena_akt;
            sekw_ruchow_max = sekw_ruchow;
        }

    }
    //jeœli plecak nie jest pe³ny, to zag³êbiam siê
    else{
        //Zysk ywnikaj¹cy z prze³o¿enia przedmiotu
        double zysk = plecaki->zysk_przelozenia(plecak_pocz, plecak_doc);
        ocena_akt+=zysk;
        if (debug){
            cout<< " Proba przeniesienia z plecaka "<<plecak_pocz<<" do "<<plecak_doc;
            cout << ". Plecak pelny!" << endl;
            cout << "    Zysk czastkowy: "<<zysk<<endl;
        }

        //bêdê próbowa³ wstawiaæ do wszystkich mo¿liwych nieodwiedzonych plecaków
        for (int i=1; i < plecaki->ile_plec; i++){
            if (!odwiedzony[i]){

                //Zysk wynikaj¹cy z kolejnych ruchów, koñcz¹cych sekwencjê
                ocena_ruchu(plecak_doc, i, ocena_akt);

                //prze³adowywania trzeba robiæ od koñca, ¿eby
                //zrobiæ miejsce w plecaku

                //wk³adam do starego docelowanego przedmiot
                //wk³adam od nowego docelowego przemiot
            }
        }
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
bool AlgorytmMD::dodaj_przedmiot(){
    odwiedzony[0]=true;
    ocena_max=0;

    bool czy_pelne=true;
    //Sprawdzam, czy wszystkie plecaki s¹ ju¿ pe³ne. Jak tak, to koniec
    for (int pl_doc=1; pl_doc < plecaki->ile_plec; pl_doc++)
        czy_pelne &= plecaki->czy_pelny(pl_doc);

    if (czy_pelne)
        return true;

    for (int pl_doc=1; pl_doc < plecaki->ile_plec; pl_doc++){
        if (debug)
            cout << "\n- Ocena wlozenia nowego przedmiotu do plecaka "<<pl_doc << endl;
        ocena_ruchu(0, pl_doc, 0);
        if (debug)
            cout << "- Maksymalny zysk przy probie wlozenia przedmiotu wynoski poki co "<<
                    ocena_max << endl;
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


