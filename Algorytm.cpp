#include "Algorytm.h"
    
Algorytm::Algorytm(Plecaki *plecaki_){
    
    plecaki=plecaki_;
        
    //czy oby na pewno wszystkie przedmioty s¹ w puli
    for (int i=1; i < plecaki->size(); i++){
        cout << "poj " << i <<": "<<plecaki->poj(i)<< endl;
        if (plecaki->size(i) > 0)
            throw string("Przy starcie algorytmu plecaki musza byc puste!");
    }
    
    odwiedzony = vector<bool>(plecaki->size(), false);
}

void Algorytm::start(){
 
         //czy oby na pewno wszystkie przedmioty s¹ w puli
        for (int i=1; i < plecaki->size(); i++)
            if (plecaki->size(i) > 0)
                throw string("Przy starcie algorytmu plecaki musza byc puste!");
                       
        int i=0;
        bool czy_pelne=false;
        
        while(i < plecaki->size(0) && !czy_pelne){
            if (debug)
                cout <<"*************    Wkladam przedmiot "<< i+1 <<"*************\n\n";                        
            czy_pelne = dodaj_przedmiot();
            i++;
        }
  //          cout<<"po wykonaniu ruchu"<<endl;
//            cout<<plecaki;
            
        //wysw_przedmioty();
}

double Algorytm::ocena_ruchu(const int plecak_pocz, const int plecak_doc, int ocena_akt){
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
bool Algorytm::dodaj_przedmiot(){
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


