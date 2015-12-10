#ifndef CLASSEMPRUNTEURS_H_INCLUDED
#define CLASSEMPRUNTEURS_H_INCLUDED
#include <map>
#include "ClassEmprunteur.h"

class ClassEmprunteurs
{
    private:
        std::map<std::string, ClassEmprunteur*> _liste;
        std::map<std::string, ClassEmprunteur*> _searchListe;
        std::map<std::string, ClassEmprunteur*>::iterator _it;
        std::string _url;
        static unsigned int IDEmprunteur; // Variable globale pour affecter un ID unique pour chaque emprunteur

    public:
        // Constructeurs & Destructeur
        ClassEmprunteurs();
        ~ClassEmprunteurs();

        // Accesseurs
        // Set
        void setListe(std::map<std::string, ClassEmprunteur*> liste) {_liste = liste;}
        void setIterator(std::map<std::string, ClassEmprunteur*>::iterator it) {_it = it;}
        static void incrementID() {IDEmprunteur++;}
        static void setID(unsigned int id) {IDEmprunteur = id;}

        // Get
        std::map<std::string, ClassEmprunteur*> getListe() {return _liste;}
        std::map<std::string, ClassEmprunteur*>::iterator getIterator() {return _it;}
        std::map<std::string, ClassEmprunteur*> getListeResult() {return _searchListe;}
        static unsigned int getID() {return IDEmprunteur;}

        // Méthodes
        bool Charger(std::string url);
        bool Sauvegarder(std::string url);
        bool Ajouter(unsigned int id, std::string nom, std::string prenom, ClassAdresse adresse, unsigned int age);
        bool Modifier(ClassEmprunteur base, unsigned int id, std::string nom, std::string prenom, ClassAdresse adresse, unsigned int age);
        bool Supprimer(ClassEmprunteur e);
        void RechercherParNom(std::string nom);
        bool VerifExist(std::string cle, ClassAdresse adresse);

        ClassEmprunteur* getByID(unsigned int id);

        void Afficher();
        void AfficherResult();
};

#endif // CLASSEMPRUNTEURS_H_INCLUDED
