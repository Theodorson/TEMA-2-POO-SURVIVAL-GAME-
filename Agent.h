#ifndef AGENT_H_INCLUDED
#define AGENT_H_INCLUDED
#include <string.h>
#include <vector>
using namespace std;

class Harta;
class Iteme;

class Agent
{
protected:
        string nume;
        int atac;
        int viata;
        int x,y; /// x-nr liniei, y-nr coloanei (coordonatele unui agent)
        int tip_agent; /// O variabila pentru a putea pune litera corespunzatoare pe harta, la impartirea agentilor
        int tip_miscare; /// Un variabila pentru a sti tipul de miscare, care se va executa
        vector <Iteme*> iteme_adunate; /// Vector de tip iteme, care are rolul de retine itemele gasite de agent
public:
    virtual string Get_Type_Agent ()=0; /// Functie virtuala pentru a returna tipul agentului (Cavaler, Viking, Arcas)
    virtual ~Agent () {}; /// Destructor virtual
    void Set_All (Iteme *a); /// Functie care primeste ca parametru un pointer de tip Iteme, care va adauga bonusurile oferite de respectivul item
    void  Comori (Iteme *a); /// Functia care adauga in vector itemele gasite (stiu ca denumirea comori poate creea confuzii, dar am dorit sa diversific putin)
    void Stergere_Comori (); /// Functia va da delete itemelor gasite (functie apelata la final)
    void Afisare_Comori ();  /// Functia care va afisa itemele gasite de un respectiv agent
    void Teleportare (Harta &B); /// O functie care va teleporta agentul random pe harta, cand acesta ajunge intr-un anumit punct
    void Set_Pozitie (int x, int y); /// Functie pentru setarea coordonatelor unui agent
    void Set_Nume (const string nume) {this->nume=nume; return;};
    void Set_Viata (int a) {this->viata=a; return;};
    virtual void Move (Harta &B)=0; /// Functia care va muta agentii dupa o anumita regula pe harta (mai jos gasindu-se inca 6 functii care ajuta la miscarea agentului)
    int Get_nr_iteme () const {return this->iteme_adunate.size();};
    int Get_Viata () const {return this->viata;};
    int Get_Atac ()  const {return this->atac;};
    int Get_x () const  {return this->x;};
    int Get_y () const {return this->y;};
    int Get_Type () const {return this->tip_agent;};
    string Get_Name () const {return this->nume;};
    friend bool Dreapta (int, Harta &B); /// Functie care verifica daca pot merge in dreapta
    friend bool Stanga (int ,Harta &B);  /// Functie care verifica daca pot merge n stanga
    friend bool Sus (int, Harta &B);  /// Functie care verifica daca pot merge in sus
    friend bool Jos (int, Harta &B); /// Functie care verifica daca pot merge in jos
    friend bool Schimbare_Miscare_Colt_Jos (Harta &B); /// Functie care verificata daca s-a ajuns in coltul dreapta jos
};
/// Din clasa abstracta Agent, avem 3 derivate: Cavaler, Viking si Arcas
/// Cele 3 tipuri de agenti difera prin atributele lor si prin tipul micarii.

class Cavaler : public Agent
{

public:
    Cavaler  ();
    void Move (Harta &B);
    string Get_Type_Agent();
    ~Cavaler  ();
};

class Viking: public Agent
{
  public:
  Viking ();
  void Move (Harta &B);
  string Get_Type_Agent ();
  ~Viking ();
};

class Arcas: public Agent
{
  public:
  Arcas ();
  void Move (Harta &B);
  string Get_Type_Agent ();
  ~Arcas();
};


#endif // AGENT_H_INCLUDED
