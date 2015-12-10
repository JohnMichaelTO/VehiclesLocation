#include <iostream>
#include "ClassVehicule.h"
#include "ClassMoto.h"

ClassMoto::ClassMoto()
{

}

ClassMoto::ClassMoto(unsigned int id, std::string marque, std::string modele, std::string type, unsigned int nbRoues, unsigned int poids, std::string eCO2, unsigned int prix, unsigned int cylindree) : ClassVehicule(id, marque, modele, type, nbRoues, poids, eCO2, prix)
{
    _cylindree = cylindree;
}

ClassMoto::~ClassMoto()
{
}

void ClassMoto::setMoto(unsigned int id, std::string marque, std::string modele, std::string type, unsigned int nbRoues, unsigned int poids, std::string eCO2, unsigned int prix, unsigned int cylindree)
{
    _id = id;
    _marque = marque;
    _modele = modele;
    _type = type;
    _nbRoues = nbRoues;
    _poids = poids;
    _eCO2 = eCO2;
    _prix = prix;

    _cylindree = cylindree;
}

void ClassMoto::Afficher()
{
    cout << _id << "|";
    cout << _marque << "|";
    cout << _modele << "|";
    cout << _type << "|";
    cout << _nbRoues << "|";
    cout << _poids << "|";
    cout << _eCO2 << "|";
    cout << _prix << "|";
    cout << _cylindree << endl;
}

istream& operator>>(istream& flux, ClassMoto &m)
{
	cout << endl << "saisir la marque de la moto" ;
	flux >> m._marque;
	cout << endl <<"saisir le modele" ;
	flux >> m._modele;
	cout << endl <<"saisir la cylindre" ;
	flux >> m._cylindree;
	return flux;
}

ostream& operator<<(ostream& flux, const ClassMoto &m)
{
	flux << "le modele de la moto est :" << m._modele << endl << m._marque << endl << m._cylindree;
	return flux;
}
