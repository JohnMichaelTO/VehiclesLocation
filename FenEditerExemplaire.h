#ifndef FENEDITEREXEMPLAIRE_H
#define FENEDITEREXEMPLAIRE_H

#include <QDialog>
#include "ui_EditerExemplaire.h"
#include "ClassExemplaire.h"
#include "ClassExemplaires.h"

class QTreeWidget;
class ExemplaireItem;

class FenEditerExemplaire : public QDialog, private Ui::FenExemplaire
{
    Q_OBJECT
    public:
        FenEditerExemplaire(QTreeWidget *treeWidget, ClassExemplaires *liste, QWidget *parent = 0);
        FenEditerExemplaire(ExemplaireItem *item, ClassExemplaires *liste, QWidget *parent = 0);

        void accept();
    public slots:
        void changerSelection(int index);

    private:
        QTreeWidget *treeWidget;
        ExemplaireItem *currentItem;
        ClassExemplaire exemplaireModif;
        ClassExemplaires *liste;
        ClassVehicules *listeV;
        std::map<std::string, ClassVehicule*>::iterator it;
        std::map<std::string, ClassVehicule*> listParcours;
};

#endif // FENEDITEREXEMPLAIRE_H
