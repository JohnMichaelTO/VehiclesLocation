#include <iostream>
#include <QMessageBox>
#include "FenRechercherMarque.h"

FenRechercherMarque::FenRechercherMarque(ClassVehicules *liste, QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);
    this->liste = liste;

    setWindowTitle(tr("Recherche véhicule par marque"));
}

void FenRechercherMarque::accept()
{
    if(rechercheParMarqueEdit->text().size() == 0) QMessageBox::warning(this, tr("Erreur"), tr("Vous devez remplir tous les champs."));

    liste->RechercherParMarque(rechercheParMarqueEdit->text().toStdString());

    QDialog::accept();
}
