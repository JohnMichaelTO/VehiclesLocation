#ifndef DATE_H_INCLUDED
#define DATE_H_INCLUDED
#include <fstream>
#include <sstream>

class ClassDate
{
    private:
        unsigned int _jour;
        unsigned int _mois;
        unsigned int _annee;

    public:
        // Constructeur & Destructeur
        ClassDate();
        ~ClassDate();

        // Accesseurs
        // Set
        void setJour(unsigned int jour) {_jour = jour;}
        void setMois(unsigned int mois) {_mois = mois;}
        void setAnnee(unsigned int annee) {_annee = annee;}

        // Get
        unsigned int getJour() {return _jour;}
        unsigned int getMois() {return _mois;}
        unsigned int getAnnee() {return _annee;}

        // Méthodes
        // Saisie d'une date
        void setDate(int jj, int mm, int aa);
        // Affichage d'une date
        void showDate();

    // Surcharges opérateurs
    ClassDate& operator+=(const ClassDate &a);
    ClassDate& operator-=(const ClassDate &a);
    ClassDate& operator=(const  ClassDate &a);
    bool operator ==(const ClassDate& b) const;
    bool operator !=(const ClassDate& b) const;

    // Surcharges flux
    friend std::ostream& operator<<(std::ostream &flux, ClassDate const& date);
    friend std::istream& operator>>(std::istream &flux, ClassDate &date);
};

//ClassDate operator+(ClassDate const& a, ClassDate const& b);
//ClassDate operator-(ClassDate const& a, ClassDate const& b);

#endif // DATE_H_INCLUDED
