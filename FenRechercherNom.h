#ifndef FENRECHERCHERNOM_H
#define FENRECHERCHERNOM_H

#include <QDialog>
#include "ui_RechercheEmprunteur.h"
#include "ClassEmprunteurs.h"

class FenRechercherNom : public QDialog, private Ui::FenRechercherNom
{
    public:
        FenRechercherNom(ClassEmprunteurs *liste, QWidget *parent = 0);
        void accept();
    private:
        ClassEmprunteurs *liste;
};

#endif // FENRECHERCHERNOM_H
