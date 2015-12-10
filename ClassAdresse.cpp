#include <iostream>
#include <string>
#include "ClassAdresse.h"

using namespace std;

// Constructeur & Destructeur
ClassAdresse::ClassAdresse() : _numero("30-32"), _rue("Avenue de la Republique"), _CP("94800"), _ville("Villejuif")
{
}

ClassAdresse::~ClassAdresse()
{
}

// Méthodes
// Saisie d'une adresse
void ClassAdresse::setAdresse(std::string numero, std::string rue, std::string CP, std::string ville)
{
    _numero = numero;
    _rue = rue;
    _CP = CP;
    _ville = ville;
}

// Affichage d'une adresse
void ClassAdresse::showAdresse()
{
    cout << _numero << " " << _rue << "\n" << _CP << " " << _ville;
}

// Surcharge des opérateurs
bool ClassAdresse::operator ==(const ClassAdresse& a) const
{
    return (_numero == a._numero && _rue == a._rue && _CP == a._CP && _ville == a._ville);
}

bool ClassAdresse::operator !=(const ClassAdresse& a) const
{
    return (_numero != a._numero || _rue != a._rue || _CP != a._CP || _ville != a._ville);
}

// Surcharge des flux
ostream& operator<< (ostream &flux, ClassAdresse const& adresse)
{
    flux << adresse._numero << "|" << adresse._rue << "|" << adresse._CP << "|" << adresse._ville;
    return flux;
}

istream& operator>> (istream &flux, ClassAdresse &adresse)
{
    cout << "Numero : ";
    // flux >> adresse._numero;
    getline(flux, adresse._numero);
    cout << "Nom de rue : ";
    //flux >> adresse._rue;
    getline(flux, adresse._rue);
    cout << "Code Postal : ";
    // flux >> adresse._CP;
    getline(flux, adresse._CP);
    cout << "Ville : ";
    //flux >> adresse._ville;
    getline(flux, adresse._ville);
    return flux;
}
