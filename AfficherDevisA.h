#ifndef AFFICHERDEVISA_H
#define AFFICHERDEVISA_H

#include <QDialog>
#include "ui_AfficherDevisAuto.h"
#include "ClassLocation.h"
#include "ClassLocations.h"

class QTreeWidget;
class LocationItem;

class AfficherDevisA : public QDialog, private Ui::FenDevisAuto
{
    Q_OBJECT
    public:
        AfficherDevisA(LocationItem *item, ClassLocations *liste, QWidget *parent = 0);

    private:
        ClassLocations *liste;
        ClassEmprunteurs *listeEmprunteurs;
        ClassExemplaires *listeExemplaires;
        unsigned int prixEstime;
};

#endif // AFFICHERDEVISA_H
