#ifndef CLASSMOTO_H
#define CLASSMOTO_H
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "ClassVehicule.h"

class ClassMoto : public ClassVehicule
{
    private:
        unsigned int _cylindree;

    public:
        // Constructeurs && Destructeur
        ClassMoto();
        ClassMoto(unsigned int id, std::string marque, std::string modele, std::string type, unsigned int nbRoues, unsigned int poids, std::string eCO2, unsigned int prix, unsigned int cylindree);
        virtual ~ClassMoto();

        // Accesseurs & Destructeur
        // Set
        virtual void setCylindree(unsigned int cylindree) {_cylindree = cylindree;}
        virtual void setMoto(unsigned int id, std::string marque, std::string modele, std::string type, unsigned int nbRoues, unsigned int poids, std::string eCO2, unsigned int prix, unsigned int cylindree);

        // Get
        virtual unsigned int getCylindree() {return _cylindree;}

        // Accessibilités classes filles
        virtual void setTypePropulsion(std::string typePropulsion) {}
        virtual void setNbPortes(unsigned int nbPortes) {}
        virtual void setNbSieges(unsigned int nbSieges) {}
        virtual void setAuto(unsigned int id, std::string marque, std::string modele, std::string type, unsigned int nbRoues, unsigned int poids, std::string eCO2, unsigned int prix, std::string typePropulsion, unsigned int nbPortes, unsigned int nbSieges) {}
        virtual std::string getTypePropulsion() {return "";}
        virtual unsigned int getNbPortes() {return 0;}
        virtual unsigned int getNbSieges() {return 0;}

        // Méthodes
        virtual int what() {return 2;}
        virtual void Afficher();

    // Surcharges flux
    friend istream& operator>>(istream&, ClassMoto &m);
    friend ostream& operator<<(ostream&, const ClassMoto &m);
};

#endif // CLASSMOTO_H
