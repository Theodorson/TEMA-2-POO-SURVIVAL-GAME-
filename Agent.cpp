#include <iostream>
#include <string.h>
#include "Harta.h"
#include "Agent.h"
#include "Iteme.h"
#include <ctime>
#include <stdlib.h>
#include <stdio.h>
using namespace std;



string Cavaler::Get_Type_Agent()
{
    string type_agent="Cavaler";
    return type_agent;
}

string Viking::Get_Type_Agent()
{
    string type_agent="Viking";
    return type_agent;
}

string Arcas::Get_Type_Agent()
{
    string type_agent="Arcas";
    return type_agent;
}


void Agent::Comori(Iteme *a)
{
    this->iteme_adunate.push_back(a);
    return;
}

void Agent::Stergere_Comori ()
{
    for (int i=0; i<iteme_adunate.size(); i++)
        delete iteme_adunate[i];
    return;
}

void Agent::Afisare_Comori ()
{
    for (int i=0; i<iteme_adunate.size(); i++)
    {
        cout<<iteme_adunate[i]->Get_Nume()<<endl;
    }
    return;
}

void Agent::Set_Pozitie(int x, int y)
{
    this->x=x;
    this->y=y;
    return;
}

void Agent::Set_All(Iteme *a)
{
    this->viata=this->viata+a->Get_viata()+a->Get_scut();
    this->atac=this->atac+a->Get_bonus_dmg();
    return;
}

Cavaler::Cavaler ()
{
    this->nume="Unknow";
    this->atac=20;
    this->viata=100;
    this->tip_agent=1;
    this->x=-1;
    this->y=-1;
    this->tip_miscare=1;
}

Cavaler::~Cavaler ()
{
    this->nume="";
    this->atac=0;
    this->viata=0;
    this->x=-1;
    this->y=-1;
}

Viking::Viking ()
{
    this->nume="Unknow";
    this->atac=10;
    this->viata=115;
    this->tip_agent=2;
    this->x=-1;
    this->y=-1;
    this->tip_miscare=1;
}

Viking::~Viking ()
{
    this->nume="";
    this->atac=0;
    this->viata=0;
    this->x=-1;
    this->y=-1;
}


Arcas::Arcas ()
{
    this->nume="Unknow";
    this->atac=50;
    this->viata=90;
    this->tip_agent=3;
    this->x=-1;
    this->y=-1;
    this->tip_miscare=1;
}

Arcas::~Arcas ()
{
    this->nume="";
    this->atac=0;
    this->viata=0;
    this->x=-1;
    this->y=-1;
}

bool Schimbare_Miscare_Colt_Jos (int lungime, int latime, Harta &B)
{
    if ( latime==B.Get_Latime()-1 && lungime==B.Get_Lungime()-1 )
        return true;
    return false;
}


bool Dreapta (int latime,Harta &B)
{
    if (latime<B.Get_Latime()-1)
        return true;
    return false;
}

bool Stanga (int latime, Harta &B)
{
    if ( latime!=0 )
        return true;
    return false;
}

bool Jos (int lungime,Harta &B)
{
    if (lungime<B.Get_Lungime()-1)
        return true;
    return false;
}

bool Sus (int lungime, Harta &B)
{
    if (lungime!=0)
        return true;
    return false;
}

void Agent::Teleportare (Harta &B)
{
    srand(time(NULL));
    int a=rand()%B.Get_Lungime(),b=rand()%B.Get_Lungime();;
    while (a==this->x && b==this->y)
    {
        a=rand()%B.Get_Lungime();
        b=rand()%B.Get_Latime();
    }
    this->x=a;
    this->y=b;
    B.Actualizare(this->x,this->y,this->tip_agent);
    return;
}


void Cavaler::Move(Harta &B)
{
    B.Actualizare(this->x,this->y,0);

    if (Schimbare_Miscare_Colt_Jos(this->x,this->y,B))
    {
        Teleportare(B);
        this->tip_miscare=1;
        return;
    }
    if (tip_miscare==1)
    {
        if (Dreapta(this->y,B))
        {
            this->y=this->y+1;
            B.Actualizare(this->x,this->y,this->tip_agent);
            return;
        }
        else
        {
            if (Jos(this->x,B))
            {
                this->x=this->x+1;
                this->tip_miscare=2;
                B.Actualizare(this->x,this->y,this->tip_agent);
                return;
            }
        }
    }
    if (tip_miscare==2)
    {
        if (Stanga(this->y,B))
        {
            this->y=this->y-1;
            B.Actualizare(this->x,this->y,this->tip_agent);
            return;
        }
        else
        {
            if (Jos(this->x,B))
            {
                this->x=this->x+1;
                this->tip_miscare=1;
                B.Actualizare(this->x,this->y,this->tip_agent);
                return;
            }
        }
    }
    /// Agentul de tip Cavaler se va muta pe o coloana in dreapta pana cand va ajunge la coloana finala, dupa se va muta cu o linie mai jos si
    /// va intra pe cea de a doua optiune de a se muta cu o coloana in dreapta pana ajunge la prima coloana, dupa se va repeta acelasi algoritm.
    /// Se va repeta pana cand ajunge in coltul de jos al hartii, dupa se va apela teleportarea.

}


void Viking::Move(Harta &B)
{
    B.Actualizare(this->x,this->y,0);

    if (Schimbare_Miscare_Colt_Jos(this->x,this->y,B))
    {
        Teleportare(B);
        return;
    }
    if (tip_miscare==1)
    {
        if (Jos(this->x, B))
        {
            this->x=this->x+1;
            B.Actualizare(this->x,this->y,this->tip_agent);
            return;
        }
        else
        {
            if (Dreapta(this->y,B))
            {
                this->y=this->y+1;
                this->tip_miscare=2;
                B.Actualizare(this->x,this->y,this->tip_agent);
                return;
            }
        }
    }
    if (tip_miscare==2)
    {
        if (Sus(this->x,B))
        {
            this->x=this->x-1;
            B.Actualizare(this->x,this->y,this->tip_agent);
            return;
        }
        else
        {
            if (Dreapta(this->y,B))
            {
                this->y=this->y+1;
                this->tip_miscare=1;
                B.Actualizare(this->x,this->y,this->tip_agent);
                return;
            }
        }
    }
    /// Agentul de tip viking se va muta cu o linie in jos pana cand va ajunge la linia finala, dupa se va muta cu o coloana mai in dreapta si
    /// va intra pe cea de a doua optiune de a se muta cu o linie in sus pana ajunge la prima linie, dupa se va repeta acelasi algoritm.
    /// Se va repeta pana cand ajunge in coltul de jos al hartii, dupa se va apela teleportarea.
}

void Arcas::Move(Harta &B)
{
    B.Actualizare(this->x,this->y,0);

    if (tip_miscare==1)
    {
        if (Dreapta(this->y,B) && Sus(this->x,B))
        {

            this->y=this->y+1;
            this->x=this->x-1;
            B.Actualizare(this->x,this->y,this->tip_agent);
            return;
        }
        this->tip_miscare=2;
    }

    if (tip_miscare==2)
    {
        if (Dreapta(this->y,B) && Jos(this->x,B))
        {
            this->y=this->y+1;
            this->x=this->x+1;
            B.Actualizare(this->x,this->y,this->tip_agent);
            return;
        }
        Teleportare(B);
        this->tip_miscare=1;
        return;
    }
    /// Agentul de tip arcas se va muta pe o linie mai sus si o coloana mai in dreapta, daca nu se poate se va muta pe o linie mai jos si o coloana in dreapta.
    /// Daca nu se poate muta din optiunile de mai sus, se va teleporta pe harta (random).
    ///
}




