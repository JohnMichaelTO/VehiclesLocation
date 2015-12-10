#include <iostream>
#include <string>
#include "ClassAdresse.h"
#include "ClassEmprunteur.h"

using namespace std;

// Constructeur & Destructeur
ClassEmprunteur::ClassEmprunteur()
{
}

ClassEmprunteur::ClassEmprunteur(unsigned int id, std::string nom, std::string prenom, ClassAdresse adresse, unsigned int age)
{
    _id = id;
    _nom = nom;
    _prenom = prenom;
    _adresse = adresse;
    _age = age;
}

ClassEmprunteur::~ClassEmprunteur()
{
}

void ClassEmprunteur::setEmprunteur(unsigned int id, std::string nom, std::string prenom, ClassAdresse adresse, unsigned int age)
{
    _id = id;
    _nom = nom;
    _prenom = prenom;
    _adresse = adresse;
    _age = age;
}

void ClassEmprunteur::Afficher()
{
    cout << _id << "|";
    cout << _nom << "|";
    cout << _prenom << "|";
    cout << _age << "|";
    cout << _adresse << endl;
}
