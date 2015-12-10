#ifndef FENRECHERCHERLOCATION_H
#define FENRECHERCHERLOCATION_H

#include <QDialog>
#include "ui_RechercherLocation.h"
#include "ClassLocations.h"

class FenRechercherLocation : public QDialog, private Ui::FenRechercherLocation
{
    public:
        FenRechercherLocation(ClassLocations *liste, QWidget *parent = 0);
        void accept();
    private:
        ClassLocations *liste;
};

#endif // FENRECHERCHERLOCATION_H
