#ifndef CLASSVEHICULE_H_INCLUDED
#define CLASSVEHICULE_H_INCLUDED
#include <string>

using namespace std;

class ClassVehicule
{
    protected:
        unsigned int _id;
        std::string _marque;
        std::string _modele;
        std::string _type;
        unsigned int _nbRoues;
        unsigned int _poids;
        std::string _eCO2; // Emission de CO2
        unsigned int _prix;

    public:
        // Constructeur & Destructeur
        ClassVehicule();
        ClassVehicule(unsigned int id, std::string marque, std::string modele, std::string type, unsigned int nbRoues, unsigned int poids, std::string eCO2, unsigned int prix);
        virtual ~ClassVehicule();

        // Accesseurs
        // Set
        void setID(unsigned int id) {_id = id;}
        void setMarque(std::string marque) {_marque = marque;}
        void setModele(std::string modele) {_modele = modele;}
        void setType(std::string type) {_type = type;}
        void setNbRoues(unsigned int nbRoues) {_nbRoues = nbRoues;}
        void setPoids(unsigned int poids) {_poids = poids;}
        void setECO2(std::string eCO2) {_eCO2 = eCO2;}
        void setPrix(unsigned int prix) {_prix = prix;}
        // void setVehicule(std::string marque, std::string modele, std::string type, unsigned int nbRoues, unsigned int poids, std::string eCO2, unsigned int prix);

        // Get
        unsigned int getID() {return _id;}
        std::string getMarque() {return _marque;}
        std::string getModele() {return _modele;}
        std::string getType() {return _type;}
        unsigned int getNbRoues() {return _nbRoues;}
        unsigned int getPoids() {return _poids;}
        std::string getECO2() {return _eCO2;}
        unsigned int getPrix() {return _prix;}

        // Accessibilités classes filles
        virtual void setTypePropulsion(std::string typePropulsion) = 0;
        virtual void setNbPortes(unsigned int nbPortes) = 0;
        virtual void setNbSieges(unsigned int nbSieges) = 0;
        virtual void setAuto(unsigned int id, std::string marque, std::string modele, std::string type, unsigned int nbRoues, unsigned int poids, std::string eCO2, unsigned int prix, std::string typePropulsion, unsigned int nbPortes, unsigned int nbSieges) = 0;
        virtual std::string getTypePropulsion() = 0;
        virtual unsigned int getNbPortes() = 0;
        virtual unsigned int getNbSieges() = 0;

        virtual void setCylindree(unsigned int cylindree) = 0;
        virtual void setMoto(unsigned int id, std::string marque, std::string modele, std::string type, unsigned int nbRoues, unsigned int poids, std::string eCO2, unsigned int prix, unsigned int cylindree) = 0;
        virtual unsigned int getCylindree() = 0;

        // Méthodes
        virtual int what() = 0;
        virtual void Afficher() = 0;
};

#endif // CLASSVEHICULE_H_INCLUDED
