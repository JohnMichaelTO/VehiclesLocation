#include <iostream>
#include <string>
#include "ClassVehicule.h"

using namespace std;

// Constructeur & Destructeur
ClassVehicule::ClassVehicule()
{
}

ClassVehicule::ClassVehicule(unsigned int id, std::string marque, std::string modele, std::string type, unsigned int nbRoues, unsigned int poids, std::string eCO2, unsigned int prix)
{
    _id = id;
    _marque = marque;
    _modele = modele;
    _type = type;
    _nbRoues = nbRoues;
    _poids = poids;
    _eCO2 = eCO2;
    _prix = prix;
}

ClassVehicule::~ClassVehicule()
{
}
