#include <iostream>
#include "ClassAuto.h"

ClassAuto::ClassAuto()
{
}

ClassAuto::ClassAuto(unsigned int id, std::string marque, std::string modele, std::string type, unsigned int nbRoues, unsigned int poids, std::string eCO2, unsigned int prix, std::string typePropulsion, unsigned int nbPortes, unsigned int nbSieges) : ClassVehicule(id, marque, modele, type, nbRoues, poids, eCO2, prix)
{
    _typePropulsion = typePropulsion;
    _nbPortes = nbPortes;
    _nbSieges = nbSieges;
}

ClassAuto::~ClassAuto()
{
}

void ClassAuto::setAuto(unsigned int id, std::string marque, std::string modele, std::string type, unsigned int nbRoues, unsigned int poids, std::string eCO2, unsigned int prix, std::string typePropulsion, unsigned int nbPortes, unsigned int nbSieges)
{
    _id = id;
    _marque = marque;
    _modele = modele;
    _type = type;
    _nbRoues = nbRoues;
    _poids = poids;
    _eCO2 = eCO2;
    _prix = prix;

    _typePropulsion = typePropulsion;
    _nbPortes = nbPortes;
    _nbSieges = nbSieges;
}

void ClassAuto::Afficher()
{
    cout << _id << "|";
    cout << _marque << "|";
    cout << _modele << "|";
    cout << _type << "|";
    cout << _nbRoues << "|";
    cout << _poids << "|";
    cout << _eCO2 << "|";
    cout << _prix << "|";
    cout << _typePropulsion << "|";
    cout << _nbPortes << "|";
    cout << _nbSieges << endl;
}

istream& operator>>(istream& flux, ClassAuto &a)
{
	cout << "saisir la marque" ;
	flux >> a._marque;
	return flux;
}

ostream& operator<<(ostream& flux, const ClassAuto &a)
{
	flux << "le modele de la ClassAuto est :" << a._modele;
	return flux;
}
