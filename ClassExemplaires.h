#ifndef CLASSEXEMPLAIRES_H
#define CLASSEXEMPLAIRES_H

#include <map>
#include "ClassVehicule.h"
#include "ClassVehicules.h"
#include "ClassExemplaire.h"

class ClassExemplaires
{
    private:
        std::map<std::string, ClassExemplaire*> _liste;
        std::map<std::string, ClassExemplaire*> _searchListe;
        std::map<std::string, ClassExemplaire*>::iterator _it;
        std::string _url;
        ClassVehicules *_listeVehicules;
        static unsigned int ID;

    public:
        // Constructeurs & Destructeur
        ClassExemplaires(ClassVehicules *listeV);
        ~ClassExemplaires();

        // Accesseurs
        // Set
        void setListe(std::map<std::string, ClassExemplaire*> liste) {_liste = liste;}
        void setIterator(std::map<std::string, ClassExemplaire*>::iterator it) {_it = it;}
        static void incrementID() {ID++;}
        static void setID(unsigned int id) {ID = id;}

        // Get
        std::map<std::string, ClassExemplaire*> getListe() const {return _liste;}
        std::map<std::string, ClassExemplaire*>::iterator getIterator() const {return _it;}
        std::map<std::string, ClassExemplaire*> getListeResult() const {return _searchListe;}
        ClassVehicules* getListeVehicules() const {return _listeVehicules;}
        static unsigned int getID() {return ID;}

        // Méthodes
        bool Charger(std::string url);
        bool Sauvegarder(std::string url);
        bool Ajouter(unsigned int numero, ClassVehicule *vehicule, unsigned int Km, std::string couleur, bool disponible);
        bool Modifier(ClassExemplaire base, unsigned int numero, ClassVehicule *vehicule, unsigned int Km, std::string couleur, bool disponible);
        bool Supprimer(ClassExemplaire e);
        void RechercherParKm(std::string Km);
        bool VerifExist(std::string cle);

        ClassExemplaire* getByID(unsigned int id);
        void RechercherParMarqueDisponibilite(std::string marque, bool disponible);
};

#endif // CLASSEXEMPLAIRES_H
