#ifndef VEHICULEITEM_H
#define VEHICULEITEM_H

#include <QObject>
#include <QTreeWidgetItem>

class VehiculeItem : public QObject, public QTreeWidgetItem
{
    public:
        VehiculeItem(QTreeWidget *treeWidget);
        void setID(const QString &ID);
        void setMarque(const QString &marque);
        void setModele(const QString &modele);
        void setType(const QString &type);
        void setNbRoues(const QString &nbRoues);
        void setPoids(const QString &poids);
        void setECO2(const QString &eCO2);
        void setPrix(const QString &prix);

        void setTypePropulsion(const QString &typePropulsion);
        void setNbPortes(const QString &nbPortes);
        void setNbSieges(const QString &nbSieges);

        void setCylindree(const QString &cylindree);

        QString getID() const {return text(0);}
        QString getMarque() const {return text(1);}
        QString getModele() const {return text(2);}
        QString getType() const {return text(3);}
        QString getNbRoues() const {return text(4);}
        QString getPoids() const {return text(5);}
        QString getECO2() const {return text(6);}
        QString getPrix() const {return text(7);}

        QString getTypePropulsion() const {return text(8);}
        QString getNbPortes() const {return text(9);}
        QString getNbSieges() const {return text(10);}

        QString getCylindree() const {return text(11);}

    signals:

    public slots:
        void Supprimer();
};

#endif // VEHICULEITEM_H
