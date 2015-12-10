#ifndef CLASSEXEMPLAIRE_H
#define CLASSEXEMPLAIRE_H
#include <string>
#include "ClassVehicule.h"

class ClassExemplaire
{
    private :
        unsigned int _numero;
        ClassVehicule *_vehicule;
        unsigned int _Km;
        std::string _couleur;
        bool _disponible;

    public:
        // Constructeurs & Destructeur
        ClassExemplaire();
        ClassExemplaire(unsigned int numero, ClassVehicule *vehicule, unsigned int Km, std::string couleur, bool disponible);
        ~ClassExemplaire();

        // Accesseurs
        // Set
        void setNumero(unsigned int numero) {_numero = numero;}
        void setVehicule(ClassVehicule* vehicule) {_vehicule = vehicule;}
        void setKm(unsigned int Km) {_Km = Km;}
        void setCouleur(std::string couleur) {_couleur = couleur;}
        void setDisponible(bool disponible) {_disponible = disponible;}
        void setExemplaire(unsigned int numero, ClassVehicule *vehicule, unsigned int Km, std::string couleur, bool disponible);

        // Get
        unsigned int getNumero() {return _numero;}
        ClassVehicule* getVehicule() {return _vehicule;}
        unsigned int getKm() {return _Km;}
        std::string getCouleur() {return _couleur;}
        bool getDisponibilite() {return _disponible;}

        // Méthodes

    // Surcharges opérateurs
    bool operator ==(const ClassExemplaire& b) const;
    bool operator !=(const ClassExemplaire& b) const;
};

#endif // CLASSEXEMPLAIRE_H
