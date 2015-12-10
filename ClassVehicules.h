#ifndef CLASSVEHICULES_H
#define CLASSVEHICULES_H
#include <map>
#include "ClassVehicule.h"
#include "ClassAuto.h"
#include "ClassMoto.h"

class ClassVehicules
{
    private:
        std::map<std::string, ClassVehicule*> _liste;
        std::map<std::string, ClassVehicule*> _searchListe;
        std::map<std::string, ClassVehicule*>::iterator _it;
        std::string _url;
        static unsigned int IDVehicule; // Variable globale pour affecter un ID unique pour chaque véhicule

    public:
        // Constructeurs & Destructeur
        ClassVehicules();
        ~ClassVehicules();

        // Accesseurs
        // Set
        void setListe(std::map<std::string, ClassVehicule*> liste) {_liste = liste;}
        void setIterator(std::map<std::string, ClassVehicule*>::iterator it) {_it = it;}
        static void incrementID() {IDVehicule++;}
        static void setID(unsigned int id) {IDVehicule = id;}

        // Get
        std::map<std::string, ClassVehicule*> getListe() {return _liste;}
        std::map<std::string, ClassVehicule*>::iterator getIterator() {return _it;}
        std::map<std::string, ClassVehicule*> getListeResult() {return _searchListe;}
        static unsigned int getID() {return IDVehicule;}

        // Méthodes
        bool Charger(std::string url);
        bool Sauvegarder(std::string url);
        bool Ajouter(unsigned int id, std::string marque, std::string modele, std::string type, unsigned int nbRoues, unsigned int poids, std::string eCO2, unsigned int prix, std::string typePropulsion, unsigned int nbPortes, unsigned int nbSieges);
        bool Ajouter(unsigned int id, std::string marque, std::string modele, std::string type, unsigned int nbRoues, unsigned int poids, std::string eCO2, unsigned int prix, unsigned int cylindree);
        bool Modifier(ClassAuto base, unsigned int id, std::string marque, std::string modele, std::string type, unsigned int nbRoues, unsigned int poids, std::string eCO2, unsigned int prix, std::string typePropulsion, unsigned int nbPortes, unsigned int nbSieges);
        bool Modifier(ClassMoto base, unsigned int id, std::string marque, std::string modele, std::string type, unsigned int nbRoues, unsigned int poids, std::string eCO2, unsigned int prix, unsigned int cylindree);
        bool Supprimer(unsigned int id, std::string marque, std::string modele, std::string type);
        void RechercherParMarque(std::string marque);
        bool VerifExist(std::string cle, unsigned int nbRoues, unsigned int poids, std::string eCO2, unsigned int prix, std::string typePropulsion, unsigned int nbPortes, unsigned int nbSieges);
        bool VerifExist(std::string cle, unsigned int nbRoues, unsigned int poids, std::string eCO2, unsigned int prix, unsigned int cylindree);

        ClassVehicule* getbyMarqueModele(std::string marque, std::string modele);
        unsigned int getPrixByMarqueModele(std::string marque, std::string modele);

        void Afficher();
        void AfficherResult();
};

#endif // CLASSVEHICULES_H
