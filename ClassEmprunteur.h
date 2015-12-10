#include "ClassAdresse.h"
#ifndef CLASSEMPRUNTEUR_H_INCLUDED
#define CLASSEMPRUNTEUR_H_INCLUDED

class ClassEmprunteur
{
    private:
        unsigned int _id;
        std::string _nom;
        std::string _prenom;
        ClassAdresse _adresse;
        unsigned int _age;

    public:
        // Constructeurs & Destructeur
        ClassEmprunteur();
        ClassEmprunteur(unsigned int id, std::string nom, std::string prenom, ClassAdresse adresse, unsigned int age);
        ~ClassEmprunteur();

        // Accesseurs
        // Set
        void setID(unsigned int id) {_id = id;}
        void setNom(std::string nom) {_nom = nom;}
        void setPrenom(std::string prenom) {_prenom = prenom;}
        void setAdresse(ClassAdresse adresse) {_adresse = adresse;}
        void setAge(unsigned int age) {_age = age;}

        // Get
        unsigned int getID() {return _id;}
        std::string getNom() {return _nom;}
        std::string getPrenom() {return _prenom;}
        ClassAdresse getAdresse() {return _adresse;}
        unsigned int getAge() {return _age;}

        // Méthodes
        // Saisie d'une adresse
        void setEmprunteur(unsigned int id, std::string nom, std::string prenom, ClassAdresse adresse, unsigned int age);

        void Afficher();

        // std::string ClassEmprunteur::what() const;

    // Surcharges opérateurs
    bool operator ==(const ClassEmprunteur& b) const;
    bool operator !=(const ClassEmprunteur& b) const;

    // Surcharges flux
    friend std::ostream& operator<<(std::ostream &flux, ClassEmprunteur const& adresse);
    friend std::istream& operator>>(std::istream &flux, ClassEmprunteur &adresse);
};

#endif // CLASSEMPRUNTEUR_H_INCLUDED
