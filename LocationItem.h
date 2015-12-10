#ifndef LOCATIONITEM_H
#define LOCATIONITEM_H

#include <QObject>
#include <QTreeWidgetItem>

class LocationItem : public QObject, public QTreeWidgetItem
{
    Q_OBJECT
    public:
        LocationItem(QTreeWidget *treeWidget);
        void setID(const QString &id);
        void setIDExemplaire(const QString &idExemplaire);
        void setMarque(const QString &marque);
        void setModele(const QString &modele);
        void setDJ(const QString &DJ);
        void setDM(const QString &DM);
        void setDA(const QString &DA);
        void setFJ(const QString &FJ);
        void setFM(const QString &FM);
        void setFA(const QString &FA);
        void setRJ(const QString &RJ);
        void setRM(const QString &RM);
        void setRA(const QString &RA);
        void setDateDebut(const QString &dateDebut);
        void setDateFin(const QString &dateFin);
        void setDateRetour(const QString &dateRetour);
        void setAssurance(const QString &assurance);
        void setIDEmprunteur(const QString &idEmprunteur);
        void setNom(const QString &nom);
        void setPrenom(const QString &prenom);
        void setNiveauCarburant(const QString &niveauCarburant);
        void setEtatVehicule(const QString &etatVehicule);

        QString getID() const {return text(0);}
        QString getIDExemplaire() const {return text(1);}
        QString getMarque() const {return text(2);}
        QString getModele() const {return text(3);}
        QString getDJ() const {return text(4);}
        QString getDM() const {return text(5);}
        QString getDA() const {return text(6);}
        QString getFJ() const {return text(7);}
        QString getFM() const {return text(8);}
        QString getFA() const {return text(9);}
        QString getRJ() const {return text(10);}
        QString getRM() const {return text(11);}
        QString getRA() const {return text(12);}
        QString getDateDebut() const {return text(13);}
        QString getDateFin() const {return text(14);}
        QString getDateRetour() const {return text(15);}
        QString getAssurance() const {return text(16);}
        QString getIDEmprunteur() const {return text(17);}
        QString getNom() const {return text(18);}
        QString getPrenom() const {return text(19);}
        QString getNiveauCarburant() const {return text(20);}
        QString getEtatVehicule() const {return text(21);}

    signals:

    public slots:
        void Supprimer();
};

#endif // LOCATIONITEM_H
