#include <iostream>
#include <fstream>
#include "Joc.h"
#include "Harta.h"
#include "Agent.h"
#include "Iteme.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <ctime>
#include <vector>
using namespace std;

int Joc::nr_runde=0;

void Impartire_Agenti (Harta &A, vector <Agent*> &agenti, int numar)
{
    int x,y,random;
    srand(time(NULL));
    x=rand()%A.Get_Lungime();
    y=rand()%A.Get_Latime();
    ifstream f("NUME.txt");
    string nume;
    while (numar>0)
    {
        if (A.Verificare(x,y)==1)
        {
            f>>nume;
            random=rand()%3;
            A.Actualizare(x,y,random+1);
            switch (random+1)
            {
            case 1:
            {
                Agent *PT=new Cavaler ();
                PT->Set_Nume(nume);
                PT->Set_Pozitie(x,y);
                agenti.push_back(PT);
                break;
            }
            case 2:
            {
                Agent *PT=new Viking ();
                PT->Set_Nume(nume);
                PT->Set_Pozitie(x,y);
                agenti.push_back(PT);
                break;
            }
            case 3:
            {
                Agent *PT=new Arcas ();
                PT->Set_Nume(nume);
                PT->Set_Pozitie(x,y);
                agenti.push_back(PT);
                break;
            }
            }
            numar--;
        }
        x=rand()%A.Get_Lungime();
        y=rand()%A.Get_Latime();
    }
    f.close();
    return;
}

void Impartire_Iteme (Harta &A, vector<Iteme*> &iteme, int nr_iteme)
{
    int x,y,random;
    srand((int)time(0));
    x=rand()%A.Get_Lungime();
    y=rand()%A.Get_Latime();
    while (nr_iteme>0)
    {
        if (A.Verificare(x,y)==1)
        {
            random=rand()%13;
            if (random==0 || random==1 || random==2 || random==3)
                random=random+4;
            A.Actualizare(x,y,random);
            switch (random)
            {
            case 4:
            {
                Iteme *PT=new Excalibur ();
                PT->Set_Pozitie(x,y);
                iteme.push_back(PT);
                break;
            }
            case 5:
            {
                Iteme *PT=new The_Shark_Sword ();
                PT->Set_Pozitie(x,y);
                iteme.push_back(PT);
                break;
            }
            case 6:
            {
                Iteme *PT=new Thor_Hammer ();
                PT->Set_Pozitie(x,y);
                iteme.push_back(PT);
                break;
            }
            case 7:
            {
                Iteme *PT=new AK_47 ();
                PT->Set_Pozitie(x,y);
                iteme.push_back(PT);
                break;
            }
            case 8:
            {
                Iteme *PT=new Coiful_Regelui();
                PT->Set_Pozitie(x,y);
                iteme.push_back(PT);
                break;
            }
            case 9:
            {
                Iteme *PT=new Armura_Zeului_Razboiului ();
                PT->Set_Pozitie(x,y);
                iteme.push_back(PT);
                break;
            }
            case 10:
            {
                Iteme *PT=new Tunica_celesta ();
                PT->Set_Pozitie(x,y);
                iteme.push_back(PT);
                break;
            }
            case 11:
            {
                Iteme *PT=new Scutul_Spartan ();
                PT->Set_Pozitie(x,y);
                iteme.push_back(PT);
                break;
            }
            case 12:
            {
                Iteme *PT=new Elixirul_Nemuririi ();
                PT->Set_Pozitie(x,y);
                iteme.push_back(PT);
                break;
            }
            }
            nr_iteme--;
        }
        x=rand()%A.Get_Lungime();
        y=rand()%A.Get_Latime();
    }
    return;
}


void Miscare_Lupta_Agenti (Harta &A, vector <Agent*>  &agenti, vector <Iteme*> &iteme, int lupta_obligatorie)
{
    vector <Agent*> agenti_morti;
    /// Ma folosesc de acest vector pentru a putea da delete, la agentii morti, deoarece dandu-le erase din vectorul principal
    /// de agenti, ii elimin, dar pointerii ar crea memory leak
    int copie_x, copie_y;
    for (int i=0; i<agenti.size(); i++)
    {
        int ok=0;
        copie_x=agenti[i]->Get_x();
        copie_y=agenti[i]->Get_y();
        agenti[i]->Move(A);

        for (int j=0; j<agenti.size(); j++)
            if ((agenti[i]->Get_x()==agenti[j]->Get_x() && agenti[i]->Get_y()==agenti[j]->Get_y() && i!=j)||(lupta_obligatorie==1 && i!=j))
               {
                cout<<"FIGHT!"<<endl;
                cout<<"Agentul de tip "<<agenti[i]->Get_Type_Agent()<<" "<<agenti[i]->Get_Name()<<" se va lupta cu agentul de tip "<<agenti[j]->Get_Type_Agent()<<" "<<agenti[j]->Get_Name()<<"!"<<endl;
                int atac_a=agenti[i]->Get_Atac();
                int atac_b=agenti[j]->Get_Atac();
                int viata_a=agenti[i]->Get_Viata();
                int viata_b=agenti[j]->Get_Viata();
                while (viata_a>0 && viata_b>0)
                {
                    viata_b=viata_b-atac_a;
                    if (viata_b<=0)
                        break;
                    viata_a=viata_a-atac_b;
                }
                agenti[i]->Set_Viata(viata_a);
                agenti[j]->Set_Viata(viata_b);

                if (agenti[i]->Get_Viata()<=0)
                {
                    cout<<"Agentul de tip "<<agenti[j]->Get_Type_Agent()<<" "<<agenti[j]->Get_Name()<<" l-a infrant pe agentul de tip "<<agenti[j]->Get_Type_Agent()<<" "<<agenti[i]->Get_Name()<<"!"<<endl;
                    agenti_morti.push_back(agenti[i]);
                    agenti[i]->Stergere_Comori();
                    agenti.erase(agenti.begin()+i);
                    A.Actualizare(agenti[j]->Get_x(),agenti[j]->Get_x(),agenti[j]->Get_Type());
                    A.Actualizare(copie_x,copie_y,0);
                    i--;
                }
                if (agenti[j]->Get_Viata()<=0)
                {
                    cout<<"Agentul de tip "<<agenti[i]->Get_Type_Agent()<<" "<<agenti[i]->Get_Name()<<" l-a infrant pe agentul de tip "<<agenti[j]->Get_Type_Agent()<<" "<<agenti[j]->Get_Name()<<"!"<<endl;
                    cout<<"Agentul de tip "<<agenti[i]->Get_Type_Agent()<<" "<<agenti[i]->Get_Name()<<" s-a mutat de pe pozitia "<<copie_x<<","<<copie_y<<" pe pozitia "<<agenti[i]->Get_x()<<","<<agenti[i]->Get_y()<<"."<<endl;
                    agenti_morti.push_back(agenti[j]);
                    agenti[j]->Stergere_Comori();
                    agenti.erase(agenti.begin()+j);
                }
                ok=1;
                break;
            }
        if (ok==0)
        {

            for (int j=0; j<iteme.size(); j++)
                if (agenti[i]->Get_x()==iteme[j]->Get_x() && agenti[i]->Get_y()==iteme[j]->Get_y())
                {
                    cout<<"Agentul de tip "<<agenti[i]->Get_Type_Agent()<<" "<<agenti[i]->Get_Name()<<" a gasit item-ul "<<iteme[j]->Get_Nume()<<"."<<endl;
                    agenti[i]->Set_All(iteme[j]);
                    agenti[i]->Comori(iteme[j]);
                    iteme.erase(iteme.begin()+j);
                    break;
                }
                 cout<<"Agentul de tip "<<agenti[i]->Get_Type_Agent()<<" "<<agenti[i]->Get_Name()<<" s-a mutat de pe pozitia "<<copie_x<<","<<copie_y<<" pe pozitia "<<agenti[i]->Get_x()<<","<<agenti[i]->Get_y()<<"."<<endl;
        }
    }

    for (int i=0; i<agenti_morti.size(); i++)
    {

      delete agenti_morti[i];
    }
    cout<<endl;
    A.Initializare(0);
    for (int i=0; i<agenti.size(); i++)
    {
        A.Actualizare(agenti[i]->Get_x(), agenti[i]->Get_y(), agenti[i]->Get_Type());
    }
    for (int i=0; i<iteme.size(); i++)
    {
        A.Actualizare(iteme[i]->Get_x(), iteme[i]->Get_y(), iteme[i]->Get_Type());
    }
    /// Stiu ca initializarea hartii cu 0 si restabilirea agentilor, itemelor pe harta nu aduce o eficienta, dar daca nu fac acest lucru, harta nu este corect updatata.
    return;
}



void Joc::Start_Game(Harta &A)
{
    cin>>A;
    cout<<"Numarul de agenti trebuie sa fie minim 2 si maxim "<<A.Get_Lungime()*A.Get_Latime()<<" agenti!!!\n";
    cout<<"Dati numarul de agenti: ";
    cin>>this->nr_agenti;
    while (this->nr_agenti<2 || this->nr_agenti>A.Get_Latime()*A.Get_Lungime())
    {
        cout<<"Numarul de agenti trebuie sa fie minim 2 si maxim "<<A.Get_Latime()*A.Get_Lungime()<<" agenti!!!\n";
        cout<<"Dati numarul de agenti: ";
        cin>>this->nr_agenti;
    }
    this->nr_iteme=(A.Get_Lungime()*A.Get_Latime()-this->nr_agenti)/2;
    cout<<"In acest joc se vor afla "<<this->nr_iteme<<" impartite pe harta!"<<endl;
    Impartire_Agenti(A, agenti, nr_agenti);
    if (this->nr_iteme!=0)
        Impartire_Iteme(A, iteme, nr_iteme);
    cout<<A<<endl;
    string decizie;
    int runda_specifica;
    cout<<"Doriti sa vedeti o anumita runda? (da/nu): ";
    cin>>decizie;
    while (decizie!="da" && decizie!="nu")
    {
        cout<<"Raspuns gresit!"<<endl;
        cout<<"Scrieti da sau nu!"<<endl;
        cin>>decizie;
    }
    if (decizie=="da")
    {
        cout<<"Introduceti numarul rundei dorite (>0):  ";
        cin>>runda_specifica;
    }
   int lupta_obligatorie=0; /// Aceasta variabila are rolul de a face agentii sa se razboiasca chiar daca ei nu isi incalca pozitiile
   /// Daca vor ramane doar 2 agenti pe harta, ii voi mai lasa 20 de runde sa continue miscarea, iar daca totusi nu s-au intalnit ii voi obliga sa se lupte
   /// Am ales aceasta varianta pentru ca poate dura cateodata mai mult pana cand se vor gasi
   int  contor=0;
    do
    {
        Joc::nr_runde++;
        if (decizie=="da" && nr_runde==runda_specifica)
        {
            cout<<"RUNDA NUMARUL: "<<nr_runde<<endl;
            Miscare_Lupta_Agenti(A, agenti, iteme, lupta_obligatorie);
            cout<<A<<endl;
            cout<<"SFARSITUL RUNDEI CU NUMARUL: "<<nr_runde<<endl;
            cout<<"Doriti sa vedeti o anumita runda? (da/nu): ";
            cin>>decizie;
            while (decizie!="da" && decizie!="nu")
            {
                cout<<"Raspuns gresit!"<<endl;
                cout<<"Scrieti da sau nu!"<<endl;
                cin>>decizie;
            }
            if (decizie=="da")
            {
                cout<<"Numarul nou introdus trebuie sa fie strict mai mare ca numarul precedent dat!\n";
                cout<<"Introduceti numarul rundei dorite: ";
                cin>>runda_specifica;
            }
        }
        else Miscare_Lupta_Agenti(A, agenti, iteme, lupta_obligatorie);
         cout<<"RUNDA CU NUMARUL: "<<nr_runde<<endl;
         if (agenti.size()==2)
         {
          contor++;
          if (contor==20)
             lupta_obligatorie=1;
         }
           cout<<A<<endl;
    } while (agenti.size()>1);
    if (decizie=="da")
    if (runda_specifica>nr_runde) cout<<"Jocul s-a terminat inainte de runda data!"<<endl;
    cout<<"G A M E  O V E R ! ! !"<<endl;
    cout<<"Jocul s-a terminat in "<<nr_runde<<" runde!"<<endl;
    cout<<agenti[0]->Get_Name()<<" este castigatorul, "<<"cu "<<agenti[0]->Get_Viata()<<" viata, cu "<<agenti[0]->Get_Atac()<<" atac, si este de tipul "<<agenti[0]->Get_Type_Agent()<<"!"<<endl;
    if (agenti[0]->Get_nr_iteme()>0)
    {cout<<"Agentul "<<agenti[0]->Get_Name()<<" a avut urmatoarele iteme asupra lui: "<<endl;
    agenti[0]->Afisare_Comori();}
    else cout<<"Agentul "<<agenti[0]->Get_Name()<<" nu a avut iteme asupra lui."<<endl;
    agenti[0]->Stergere_Comori();
    delete agenti[0];
    return;
}

