#include "Algorytm.h"
    
Algorytm::Algorytm(Plecaki *plecaki_){
    
    plecaki=plecaki_;
        
    //czy oby na pewno wszystkie przedmioty s� w puli
    for (int i=1; i < plecaki->size(); i++){
        cout << "poj " << i <<": "<<plecaki->poj(i)<< endl;
        if (plecaki->size(i) > 0)
            throw string("Przy starcie algorytmu plecaki musza byc puste!");
    }
    
    odwiedzony = vector<bool>(plecaki->size(), false);
}

void Algorytm::start(){
 
         //czy oby na pewno wszystkie przedmioty s� w puli
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
    //dodaj� do sekwencji ruch�w
    sekw_ruchow.push_back(plecak_pocz);
    sekw_ruchow.push_back(plecak_doc);
    
    //je�li plecak nie jest pe�ny, to dodaj� i pr�buj� wymieni� z pul�
    //i ko�cz� ocen�
    if (plecaki->czy_pelny(plecak_doc)==false){
        double zysk;            
        
        if (debug){
            cout<< " Proba przeniesienia z plecaka "<<plecak_pocz<<" do "<<plecak_doc<<endl;
        }
        //cout<<*plecaki;

        //pobieram adres przemiotu, �eby p�niej go wr�ci�
       // Przedmiot* przed=plecaki->przed_do_przel(plecak_pocz, plecak_doc);
        //zysk = plecaki->przeloz(plecak_pocz, plecak_doc);
        zysk = plecaki->zysk_przelozenia(plecak_pocz, plecak_doc);
        ocena_akt += zysk;
        if (debug){
            cout << "    Zysk czastkowy: "<<zysk<<endl;
            cout << "    Ocena koncowka: "<<ocena_akt<<endl;
        }
    
        Przedmiot* prz = plecaki->przeloz(plecak_pocz, plecak_doc);
                                
        //sprawdzam, czy op�aca si� z docelowego plecaka wymieni� si� z pul� 
        //o ile �r�d�owym plecakiem nie jest pula, bo wtedy nie ma to sensu
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
            //koniec ruch�w. Oceniam czy jest to najlepsza sekwencja
            if (ocena_max<ocena_akt){
                ocena_max=ocena_akt;
                sekw_ruchow_max=sekw_ruchow;
            }
        }
        //z powrotem wracam przerzucony element
        //plecaki->przywroc_przedmiot(przed, plecak_pocz);
        plecaki->przywroc_przedmiot(prz, plecak_pocz);
    }
    //je�li plecak jest pe�ny, to zag��biam si� 
    else{
        //Zysk ywnikaj�cy z prze�o�enia przedmiotu
        double zysk = plecaki->zysk_przelozenia(plecak_pocz, plecak_doc);
        ocena_akt+=zysk;
        if (debug){
            cout<< " Proba przeniesienia z plecaka "<<plecak_pocz<<" do "<<plecak_doc;
            cout << ". Plecak pelny!" << endl;
            cout << "    Zysk czastkowy: "<<zysk<<endl;
        }
//            cout << "    Ocena koncowka: "<<ocena_akt<<endl;
        
        Przedmiot* prz = plecaki->przeloz(plecak_pocz, plecak_doc);
        //b�d� pr�bowa� wstawia� do wszystkich mo�liwych nieodwiedzonych plecak�w
        for (int i=1; i < plecaki->ile_plec; i++){
            if (!odwiedzony[i]){
                
                //Zysk wynikaj�cy z kolejnych ruch�w, ko�cz�cych sekwencj�
                ocena_akt=ocena_ruchu(plecak_doc, i, ocena_akt);
                
                //prze�adowywania trzeba robi� od ko�ca, �eby
                //zrobi� miejsce w plecaku
                
                //wk�adam do starego docelowanego przedmiot
                //wk�adam od nowego docelowego przemiot
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
    
//dodaje do plecak�w jeden przedmiot z puli. Przedmiot dodawany jest
//do plecaka, kt�ry generuje najwi�kszy zysk. W elemencie klasy
//b�dzie zapisana najbardziej zyskowna �cie�ka
bool Algorytm::dodaj_przedmiot(){
    odwiedzony[0]=true;
    ocena_max=0;
    
    bool czy_pelne=true;
    //Sprawdzam, czy wszystkie plecaki s� ju� pe�ne. Jak tak, to koniec
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


