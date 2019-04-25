#ifndef JOC_H_INCLUDED
#define JOC_H_INCLUDED
#include <vector>
using namespace std;

class Agent;
class Harta;
class Iteme;

class Joc
{
 private:
     int nr_agenti;
     int nr_iteme;
     vector <Agent*> agenti; /// Vectorul care va retine agentii
     vector <Iteme*> iteme; /// Vectorul care va retine itemele
     static int nr_runde;
 public:
    Joc (): nr_agenti(0), nr_iteme(0) {} /// Constructor cu lista de initializare
    void Start_Game(Harta &A); /// Functia care incepe jocul, apelata in main.
    friend void Impartire_Agenti (Harta &A, vector<Agent*>& , int); /// Functia care imparte agentii random pe harta
    friend void Impartire_Iteme (Harta &A, vector<Iteme*>&, int); /// Functia care imparte itemele, daca mai este loc pe harta, random.
    friend void Miscare_Lupta_Agenti (Harta&A, vector<Agent*> &, vector<Iteme*>&, int); /// Functia care misca agentii pe rand, si in cazul in care acestia se intalnesc doar unul va iesi invingator

};







#endif // JOC_H_INCLUDED
