#include <iostream>
#include <string>
#include "ClassVehicule.h"
#include "ClassExemplaire.h"

using namespace std;

ClassExemplaire::ClassExemplaire()
{
}

ClassExemplaire::ClassExemplaire(unsigned int numero, ClassVehicule *vehicule, unsigned int Km, std::string couleur, bool disponible)
{
    _numero = numero;
    _vehicule = vehicule;
    _Km = Km;
    _couleur = couleur;
    _disponible = disponible;
}

ClassExemplaire::~ClassExemplaire()
{

}

void ClassExemplaire::setExemplaire(unsigned int numero, ClassVehicule *vehicule, unsigned int Km, std::string couleur, bool disponible)
{
    _numero = numero;
    _vehicule = vehicule;
    _Km = Km;
    _couleur = couleur;
    _disponible = disponible;
}
