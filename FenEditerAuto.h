#ifndef FENEDITERAUTO_H
#define FENEDITERAUTO_H

#include <QDialog>
#include "ui_EditerVoiture.h"
#include "ClassAuto.h"
#include "ClassVehicule.h"
#include "ClassVehicules.h"

class QTreeWidget;
class VehiculeItem;

class FenEditerAuto : public QDialog, private Ui::FenVoiture
{
    Q_OBJECT
    public:
        FenEditerAuto(QTreeWidget *treeWidget, ClassVehicules *liste, QWidget *parent = 0);
        FenEditerAuto(VehiculeItem *item, ClassVehicules *liste, QWidget *parent = 0);

        void accept();

    private:
        QTreeWidget *treeWidget;
        VehiculeItem *currentItem;
        ClassAuto AutoModif;
        ClassVehicules *liste;
};

#endif // FENEDITERAUTO_H
