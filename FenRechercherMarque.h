#ifndef FENRECHERCHERMARQUE_H
#define FENRECHERCHERMARQUE_H

#include <QDialog>
#include "ui_RechercheMarque.h"
#include "ClassVehicules.h"

class FenRechercherMarque : public QDialog, private Ui::FenRechercheMarque
{
    public:
        FenRechercherMarque(ClassVehicules *liste, QWidget *parent = 0);
        void accept();
    private:
        ClassVehicules *liste;
};

#endif // FENRECHERCHERMARQUE_H
