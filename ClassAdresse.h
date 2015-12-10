#ifndef CLASSADRESSE_H_INCLUDED
#define CLASSADRESSE_H_INCLUDED
#include <string>

class ClassAdresse
{
    private:
        std::string _numero;
        std::string _rue;
        std::string _CP;
        std::string _ville;

    public:
        // Constructeur & Destructeur
        ClassAdresse();
        ~ClassAdresse();

        // Accesseurs
        // Set
        void setNumero(std::string numero) {_numero = numero;}
        void setRue(std::string rue) {_rue = rue;}
        void setCP(std::string CP) {_CP = CP;}
        void setVille(std::string ville) {_ville = ville;}

        // Get
        std::string getNumero() {return _numero;}
        std::string getRue() {return _rue;}
        std::string getCP() {return _CP;}
        std::string getVille() {return _ville;}

        // Méthodes
        // Saisie d'une adresse
        void setAdresse(std::string numero, std::string rue, std::string CP, std::string ville);
        // Affichage d'une adresse
        void showAdresse();

    // Surcharges opérateurs
    bool operator ==(const ClassAdresse& a) const;
    bool operator !=(const ClassAdresse& a) const;

    // Surcharges flux
    friend std::ostream& operator<<(std::ostream &flux, ClassAdresse const& adresse);
    friend std::istream& operator>>(std::istream &flux, ClassAdresse &adresse);
};

//ClassAdresse operator+(ClassAdresse const& a, ClassAdresse const& b);
//ClassAdresse operator-(ClassAdresse const& a, ClassAdresse const& b);

#endif // CLASSADRESSE_H_INCLUDED
