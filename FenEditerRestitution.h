#ifndef FENEDITERRESTITUTION_H
#define FENEDITERRESTITUTION_H

#include <QDialog>
#include "ui_FenRestituer.h"
#include "ClassLocation.h"
#include "ClassLocations.h"

class QTreeWidget;
class LocationItem;

class FenEditerRestitution : public QDialog, private Ui::FenRestituer
{
    Q_OBJECT
    public:
        FenEditerRestitution(LocationItem *item, ClassLocations *liste, QWidget *parent = 0);

        void accept();
    public slots:
        void changerDateRetour(QDate dateRestitution);

    private:
        LocationItem *currentItem;
        ClassLocation LocationModif;
        ClassLocations *liste;
        ClassEmprunteurs *listeEmprunteurs;
        ClassExemplaires *listeExemplaires;
        QDate dateDebut, dateFin, dateRetour;
};

#endif // FENEDITERRESTITUTION_H
