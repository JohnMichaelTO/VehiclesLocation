#ifndef FENEDITERLOCATION_H
#define FENEDITERLOCATION_H

#include <QDialog>
#include "ui_EditerLocation.h"
#include "ClassLocation.h"
#include "ClassLocations.h"

class QTreeWidget;
class LocationItem;

class FenEditerLocation : public QDialog, private Ui::FenLocation
{
    Q_OBJECT
    public:
        FenEditerLocation(QTreeWidget *treeWidget, ClassLocations *liste, QWidget *parent = 0);
        FenEditerLocation(LocationItem *item, ClassLocations *liste, QWidget *parent = 0);

        void accept();
    public slots:
        void changerSelectionModele(int index);
        void changerSelectionNom(int index);
        void changerExemplaire(int index);
        void changerDateDebut(QDate dateStart);
        void changerDateFin(QDate dateEnd);
        void changerModele(int);
        void changerAssurance(bool);
        void rechargerPrixEstimer();

    private:
        QTreeWidget *treeWidget;
        LocationItem *currentItem;
        ClassLocation LocationModif;
        ClassLocations *liste;
        ClassEmprunteurs *listeEmprunteurs;
        ClassExemplaires *listeExemplaires;
        std::map<std::string, ClassExemplaire*>::iterator itEx;
        std::map<std::string, ClassExemplaire*> listParcoursExemplaires;
        std::map<std::string, ClassEmprunteur*>::iterator itEm;
        std::map<std::string, ClassEmprunteur*> listParcoursEmprunteurs;
        QDate dateDebut, dateFin;
        unsigned int prix, prixEstime, assurance;
};

#endif // FENEDITERLOCATION_H
