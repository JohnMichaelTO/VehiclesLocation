#ifndef AFFICHERFACTUREA_H
#define AFFICHERFACTUREA_H

#include <QDialog>
#include "ui_AfficherFactureAuto.h"
#include "ClassLocation.h"
#include "ClassLocations.h"

class QTreeWidget;
class LocationItem;

class AfficherFactureA : public QDialog, private Ui::FenFactureAuto
{
    Q_OBJECT
    public:
        AfficherFactureA(LocationItem *item, ClassLocations *liste, QWidget *parent = 0);

    private:
        ClassLocations *liste;
        ClassEmprunteurs *listeEmprunteurs;
        ClassExemplaires *listeExemplaires;
};

#endif // AFFICHERFACTUREA_H
