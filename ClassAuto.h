#ifndef CLASSAUTO_H
#define CLASSAUTO_H
#include <string>
#include "ClassVehicule.h"

class ClassAuto : public ClassVehicule
{
    private:
        std::string _typePropulsion;
        unsigned int _nbPortes;
        unsigned int _nbSieges;

    public:
        // Constructeur & Destructeur
        ClassAuto();
        ClassAuto(unsigned int id, std::string marque, std::string modele, std::string type, unsigned int nbRoues, unsigned int poids, std::string eCO2, unsigned int prix, std::string typePropulsion, unsigned int nbPortes, unsigned int nbSieges);
        virtual ~ClassAuto();

        // Accesseurs
        // Set
        virtual void setTypePropulsion(std::string typePropulsion) {_typePropulsion = typePropulsion;}
        virtual void setNbPortes(unsigned int nbPortes) {_nbPortes = nbPortes;}
        virtual void setNbSieges(unsigned int nbSieges) {_nbSieges = nbSieges;}
        virtual void setAuto(unsigned int id, std::string marque, std::string modele, std::string type, unsigned int nbRoues, unsigned int poids, std::string eCO2, unsigned int prix, std::string typePropulsion, unsigned int nbPortes, unsigned int nbSieges);

        // Get
        virtual std::string getTypePropulsion() {return _typePropulsion;}
        virtual unsigned int getNbPortes() {return _nbPortes;}
        virtual unsigned int getNbSieges() {return _nbSieges;}

        // Accessibilités classes filles
        virtual void setCylindree(unsigned int cylindree) {}
        virtual void setMoto(unsigned int id, std::string marque, std::string modele, std::string type, unsigned int nbRoues, unsigned int poids, std::string eCO2, unsigned int prix, unsigned int cylindree) {}
        virtual unsigned int getCylindree() {return 0;}

        // Méthodes
        virtual int what() {return 1;}
        virtual void Afficher();

    // Surcharges flux
    friend istream& operator>>(istream&, ClassAuto &a);
    friend ostream& operator<<(ostream&, const ClassAuto &a);
};

#endif // CLASSAUTO_H
