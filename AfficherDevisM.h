#ifndef AFFICHERDEVISM_H
#define AFFICHERDEVISM_H

#include <QDialog>
#include "ui_AfficherDevisMoto.h"
#include "ClassLocation.h"
#include "ClassLocations.h"

class QTreeWidget;
class LocationItem;

class AfficherDevisM : public QDialog, private Ui::FenDevisMoto
{
    Q_OBJECT
    public:
        AfficherDevisM(LocationItem *item, ClassLocations *liste, QWidget *parent = 0);

    private:
        ClassLocations *liste;
        ClassEmprunteurs *listeEmprunteurs;
        ClassExemplaires *listeExemplaires;
        unsigned int prixEstime;
};

#endif // AFFICHERDEVISM_H
