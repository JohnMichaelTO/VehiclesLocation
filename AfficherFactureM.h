#ifndef AFFICHERFACTUREM_H
#define AFFICHERFACTUREM_H

#include <QDialog>
#include "ui_AfficherFactureMoto.h"
#include "ClassLocation.h"
#include "ClassLocations.h"

class QTreeWidget;
class LocationItem;

class AfficherFactureM : public QDialog, private Ui::FenFactureMoto
{
    Q_OBJECT
    public:
        AfficherFactureM(LocationItem *item, ClassLocations *liste, QWidget *parent = 0);

    private:
        ClassLocations *liste;
        ClassEmprunteurs *listeEmprunteurs;
        ClassExemplaires *listeExemplaires;
};

#endif // AFFICHERFACTUREM_H
