#ifndef CLASSLOCATIONS_H
#define CLASSLOCATIONS_H

#include <map>
#include "ClassEmprunteur.h"
#include "ClassEmprunteurs.h"
#include "ClassExemplaires.h"
#include "ClassExemplaire.h"
#include "ClassLocation.h"

class ClassLocations
{
    private:
        std::map<std::string, ClassLocation*> _liste;
        std::map<std::string, ClassLocation*> _searchListe;
        std::map<std::string, ClassLocation*>::iterator _it;
        std::string _url;
        ClassExemplaires *_listExemplaires;
        ClassEmprunteurs *_listEmprunteurs;
        static unsigned int IDLocation;

    public:
        ClassLocations(ClassExemplaires *listEx, ClassEmprunteurs *listEm);
        ~ClassLocations();

        // Accesseurs
        // Set
        void setListe(std::map<std::string, ClassLocation*> liste) {_liste = liste;}
        void setIterator(std::map<std::string, ClassLocation*>::iterator it) {_it = it;}
        static void incrementID() {IDLocation++;}
        static void setID(unsigned int id) {IDLocation = id;}

        // Get
        std::map<std::string, ClassLocation*> getListe() {return _liste;}
        std::map<std::string, ClassLocation*>::iterator getIterator() {return _it;}
        std::map<std::string, ClassLocation*> getListeResult() {return _searchListe;}
        ClassExemplaires* getListeExemplaires() {return _listExemplaires;}
        ClassEmprunteurs* getListeEmprunteurs() {return _listEmprunteurs;}
        static unsigned int getID() {return IDLocation;}

        // Méthodes
        bool Charger(std::string url);
        bool Sauvegarder(std::string url);
        bool Ajouter(unsigned int id, ClassDate dateD, ClassDate dateF, ClassDate dateR, ClassEmprunteur *emprunteur, ClassExemplaire *exemplaire, bool assurance, unsigned int niveauCarburant, bool etatVehicule);
        bool Modifier(ClassLocation e, unsigned int id, ClassDate dateD, ClassDate dateF, ClassDate dateR, ClassEmprunteur *emprunteur, ClassExemplaire *exemplaire, bool assurance, unsigned int niveauCarburant, bool etatVehicule);
        bool Supprimer(ClassLocation e);
        void RechercherParLocation(std::string nom);
        bool VerifExist(std::string cle, ClassDate dateD, ClassDate dateF, ClassDate dateR, ClassEmprunteur *emprunteur, ClassExemplaire *exemplaire, bool assurance, unsigned int niveauCarburant, bool etatVehicule);
};
#endif // CLASSLOCATIONS_H
