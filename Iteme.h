#ifndef ITEME_H_INCLUDED
#define ITEME_H_INCLUDED
using namespace std;


class Iteme
{
  protected:
      string nume;
      int bonus_dmg; /// Bonus atac
      int viata;
      int scut; /// Am dorit sa diversific putin, scutul este de fapt tot viata, care se va adauga bonus vietii agentului
      int tip_item; /// O variabila pentru a putea pune pe harta numarul corespunzator item-ului
      int x,y; /// Coordonatele item-ului
  public:
   Iteme (): bonus_dmg(0), viata(0), scut(0), x(-1), y(-1) {} /// Constructor cu lista de initializare
   const int Get_bonus_dmg () {return this->bonus_dmg;};
   const int Get_viata () {return this->viata;};
   const int Get_scut () {return this->scut;};
   const int Get_x () {return this->x;};
   const int Get_y () {return this->y;};
   const int Get_Type () {return this->tip_item;};
   const string Get_Nume () {return this->nume;};
   void Set_Pozitie (int a, int b) {this->x=a; this->y=b; return;};
};

/// Din clasa principala Iteme, deriva inca 9 clase, adica 9 iteme, cu diferite statusuri.

class Excalibur: public Iteme
{
  public:
 Excalibur ();
};

class The_Shark_Sword: public Iteme
{
    public:
    The_Shark_Sword ();
};

class Thor_Hammer: public Iteme
{
    public:
    Thor_Hammer ();
};

class AK_47: public Iteme
{
    public:
    AK_47 ();
};

class Coiful_Regelui: public Iteme
{
    public:
    Coiful_Regelui();
};

class Armura_Zeului_Razboiului: public Iteme
{
    public:
    Armura_Zeului_Razboiului ();
};

class Tunica_celesta: public Iteme
{
    public:
    Tunica_celesta ();
};

class Scutul_Spartan: public Iteme
{
    public:
    Scutul_Spartan ();
};

class Elixirul_Nemuririi: public Iteme
{
    public:
    Elixirul_Nemuririi();
};
#endif // ITEME_H_INCLUDED
