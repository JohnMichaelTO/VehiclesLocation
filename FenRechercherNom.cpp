#include <iostream>
#include <QMessageBox>
#include "FenRechercherNom.h"


FenRechercherNom::FenRechercherNom(ClassEmprunteurs *liste, QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);
    this->liste = liste;

    setWindowTitle(tr("Recherche emprunteur par nom"));
}

void FenRechercherNom::accept()
{
    if(rechercherParNomEdit->text().size() == 0) QMessageBox::warning(this, tr("Erreur"), tr("Vous devez remplir tous les champs."));

    liste->RechercherParNom(rechercherParNomEdit->text().toStdString());

    QDialog::accept();
}
