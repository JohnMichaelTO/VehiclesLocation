#ifndef CLASSLOCATION_H
#define CLASSLOCATION_H

#include "ClassDate.h"
#include "ClassEmprunteur.h"
#include "ClassExemplaire.h"
#include "ClassVehicule.h"

class ClassLocation
{
    private:
        unsigned int _id;
        ClassDate _dateD, _dateF, _dateR;
        ClassEmprunteur *_emprunteur;
        ClassExemplaire *_exemplaire;
        unsigned int _prix;
        bool _assurance;
        unsigned int _niveauCarburant;
        bool _etatVehicule;

    public:
        ClassLocation();
        ClassLocation(unsigned int id, ClassDate dateD, ClassDate dateF, ClassDate dateR, ClassEmprunteur *emprunteur, ClassExemplaire *exemplaire, bool assurance, unsigned int niveauCarburant, bool etatVehicule);
        ~ClassLocation();

        // Accesseurs
        // Set
        void setID(unsigned int id) {_id = id;}
        void setEmprunteur(ClassEmprunteur* emprunteur){_emprunteur = emprunteur;}
        void setExemplaire(ClassExemplaire *exemplaire){_exemplaire = exemplaire;}
        void setDateD(ClassDate dateD) {_dateD = dateD;}
        void setDateF(ClassDate dateF) {_dateF = dateF;}
        void setDateR(ClassDate dateR) {_dateR = dateR;}
        void ajoutetPrix(unsigned int prix) {_prix = prix;}
        void setLocation(unsigned int id, ClassDate dateD, ClassDate dateF, ClassDate dateR, ClassEmprunteur *emprunteur, ClassExemplaire *exemplaire, bool assurance, unsigned int niveauCarburant, bool etatVehicule);
        void setAssurance(bool present) {_assurance = present;}
        void setNiveauCarburant(unsigned int niveauCarburant) {_niveauCarburant = niveauCarburant;}
        void setEtatVehicule(bool etatVehicule) {_etatVehicule = etatVehicule;}

        // Get
        unsigned int getID() {return _id;}
        ClassEmprunteur* getEmprunteur() {return _emprunteur;}
        ClassExemplaire* getExemplaire() {return _exemplaire;}
        ClassDate getDateD() {return _dateD;}
        ClassDate getDateF() {return _dateF;}
        ClassDate getDateR() {return _dateR;}
        unsigned int getPrix();
        bool getAssurance() {return _assurance;}
        unsigned int getNiveauCarburant() {return _niveauCarburant;}
        bool getEtatVehicule() {return _etatVehicule;}
};

#endif // CLASSLOCATION_H
