#ifndef FENEDITERMOTO_H
#define FENEDITERMOTO_H

#include <QDialog>
#include "ui_EditerMoto.h"
#include "ClassMoto.h"
#include "ClassVehicule.h"
#include "ClassVehicules.h"

class QTreeWidget;
class VehiculeItem;

class FenEditerMoto : public QDialog, private Ui::FenMoto
{
    Q_OBJECT
    public:
        FenEditerMoto(QTreeWidget *treeWidget, ClassVehicules *liste, QWidget *parent = 0);
        FenEditerMoto(VehiculeItem *item, ClassVehicules *liste, QWidget *parent = 0);

        void accept();

    private:
        QTreeWidget *treeWidget;
        VehiculeItem *currentItem;
        ClassMoto MotoModif;
        ClassVehicules *liste;
};

#endif // FENEDITERMOTO_H
