#include <iostream>
#include "ClassDate.h"

using namespace std;

// Constructeur & Destructeur
ClassDate::ClassDate() : _jour(1), _mois(1), _annee(1970)
{
}

ClassDate::~ClassDate()
{
}

// Méthodes
// Saisie d'une date
void ClassDate::setDate(int jj, int mm, int aa)
{
    _jour = jj;
    _mois = mm;
    _annee = aa;
}

// Affichage d'une date
void ClassDate::showDate()
{
    cout << _jour << "/" << _mois << "/" << _annee;
}

ClassDate& ClassDate::operator=(const  ClassDate &a)
{
    _jour = a._jour;
    _mois = a._mois;
    _annee = a._annee;
}

// Surcharge des opérateurs
bool ClassDate::operator ==(const ClassDate& b) const
{
    return (_jour == b._jour && _mois == b._mois && _annee == b._annee);
}

ostream& operator<< (ostream &flux, ClassDate const& date)
{
    flux << date._jour << "/" << date._mois << "/" << date._annee;
    return flux;
}

istream& operator>> (istream &flux, ClassDate &date)
{
    cout << "Jour : ";
    flux >> date._jour;
    cout << "Mois : ";
    flux >> date._mois;
    cout << "Annee : ";
    flux >> date._annee;
    return flux;
}
