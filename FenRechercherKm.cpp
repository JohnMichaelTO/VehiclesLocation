#include <iostream>
#include <QMessageBox>
#include "FenRechercherKm.h"

FenRechercherKm::FenRechercherKm(ClassExemplaires *liste, QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);
    this->liste = liste;

    setWindowTitle(tr("Recherche par kilométrage"));
}

void FenRechercherKm::accept()
{
    if(rechercheParKmEdit->text().size() == 0) QMessageBox::warning(this, tr("Erreur"), tr("Vous devez remplir tous les champs."));

    liste->RechercherParKm(rechercheParKmEdit->text().toStdString());

    QDialog::accept();
}
