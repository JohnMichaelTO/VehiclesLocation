#include <iostream>
#include <QMessageBox>
#include "FenRechercherLocation.h"

FenRechercherLocation::FenRechercherLocation(ClassLocations *liste, QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);
    this->liste = liste;

    setWindowTitle(tr("Recherche location"));
}

void FenRechercherLocation::accept()
{
    if(rechercheLocationEdit->text().size() == 0) QMessageBox::warning(this, tr("Erreur"), tr("Vous devez remplir tous les champs."));

    liste->RechercherParLocation(rechercheLocationEdit->text().toStdString());

    QDialog::accept();
}
