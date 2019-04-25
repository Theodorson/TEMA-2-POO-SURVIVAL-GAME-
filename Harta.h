#ifndef HARTA_H_INCLUDED
#define HARTA_H_INCLUDED
using namespace std;

class Harta
{
private:
    int L,C; /// L-nr linii, C-nr coloane
    int **Map; /// Matricea
public:
    Harta (): L(0), C(0), Map(NULL) {} /// Constructor creat cu lista de initializare
    friend istream & operator >> (istream & in, Harta &B); /// incarcare operator >>
    friend ostream & operator << (ostream & out, Harta &B);  /// incarcare operator <<
    void Actualizare (int x, int y, int simbol) {this->Map[x][y]=simbol;}; /// Functie pentru a actualiza un anume element din harta
    int Get_Lungime () const {return this->L;}; /// Getter pentru a returna nr de linii
    int Get_Latime () const {return this->C;}; /// Getter pentru a returna nr de coloane
    bool Verificare (int x, int y) {if(this->Map[x][y]==0) return true; return false;}; /// Functie pentru a verifica daca pozitia x,y este ocupata sau nu
    void Initializare (int); /// Initializare harta cu un anume numar
    ~Harta ();  /// Destructor
};





#endif // HARTA_H_INCLUDED
