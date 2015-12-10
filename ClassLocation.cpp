#include "ClassLocation.h"

using namespace std;

ClassLocation::ClassLocation()
{
}

ClassLocation::ClassLocation(unsigned int id, ClassDate dateD, ClassDate dateF, ClassDate dateR, ClassEmprunteur *emprunteur, ClassExemplaire *exemplaire, bool assurance, unsigned int niveauCarburant, bool etatVehicule)
{
    _id = id;
    _dateD = dateD;
    _dateF = dateF;
    _dateR = dateR;
    _emprunteur = emprunteur;
    _exemplaire = exemplaire;
    _assurance = assurance;
    _niveauCarburant = niveauCarburant;
    _etatVehicule = etatVehicule;
}

ClassLocation::~ClassLocation()
{
}

void ClassLocation::setLocation(unsigned int id, ClassDate dateD, ClassDate dateF, ClassDate dateR, ClassEmprunteur *emprunteur, ClassExemplaire *exemplaire, bool assurance, unsigned int niveauCarburant, bool etatVehicule)
{
    _id = id;
    _dateD = dateD;
    _dateF = dateF;
    _dateR = dateR;
    _emprunteur = emprunteur;
    _exemplaire = exemplaire;
    _assurance = assurance;
    _niveauCarburant = niveauCarburant;
    _etatVehicule = etatVehicule;
}

unsigned int ClassLocation::getPrix()
{
    if(_assurance)return (_prix + 20);
    return _prix;
}
