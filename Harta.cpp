#include <iostream>
#include <fstream>
#include "Harta.h"
using namespace std;


Harta::~Harta ()
{
    for (int i=0; i<L; i++)
        delete[] Map[i];
    delete[] Map;
    this->L=0;
    this->C=0;
}


istream & operator >> (istream & in, Harta &B)
{
    cout<<"Lungimea si latimea hartii trebuie sa fie de minim 15x15!\n";
    cout<<"Dati lungimea hartii: ";
    in >> B.C;
    while (B.C<15)
    {
    cout<<"Lungime gresita!\n";
    cout<<"Lungimea si latimea hartii trebuie sa fie de minim 15x15!\n";
    cout<<"Dati lungimea hartii: ";
    in >> B.C;
    }
    cout<<"Dati latimea hartii: ";
    in >> B.L;
    while (B.L<15)
    {
    cout<<"Latime gresita!\n";
    cout<<"Lungimea si latimea hartii trebuie sa fie de minim 15x15!\n";
    cout<<"Dati latimea hartii: ";
    in >> B.L;
    }
    B.Map=new int*[B.L];
    for (int i=0; i<B.L; i++)
        B.Map[i]=new int[B.C];
    for (int i=0; i<B.L; i++)
        for (int j=0; j<B.C; j++)
            B.Map[i][j]=0;
    return in;
}



ostream & operator << (ostream & out, Harta &B)
{
    for (int i=0; i<B.L; i++)
    {
        for (int j=0; j<B.C; j++)
            out << B.Map[i][j]<<" ";
        out<<endl;
    }
    return out;
}

void Harta::Initializare(int x)
{
    for (int i=0; i<this->L; i++)
    for (int j=0; j<this->C; j++)
    {
     this->Map[i][j]=x;
    }
    return;
}


