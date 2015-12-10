#ifndef FENRECHERCHERKM_H
#define FENRECHERCHERKM_H

#include <QDialog>
#include "ui_RechercheExemplaire.h"
#include "ClassExemplaires.h"

class FenRechercherKm : public QDialog, private Ui::FenRechercherKm
{
    public:
        FenRechercherKm(ClassExemplaires *liste, QWidget *parent = 0);
        void accept();
    private:
        ClassExemplaires *liste;
};

#endif // FENRECHERCHERKM_H
