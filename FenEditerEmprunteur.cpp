#include <QMessageBox>
#include "FenEditerEmprunteur.h"
#include "EmprunteurItem.h"
#include "ClassAdresse.h"
#include "ClassEmprunteurs.h"
#include "Fonctions.h"
#include <iostream>

FenEditerEmprunteur::FenEditerEmprunteur(QTreeWidget *treeWidget, ClassEmprunteurs *liste, QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);

    this->treeWidget = treeWidget;
    this->liste = liste;
    currentItem = 0;

    setWindowTitle(tr("Ajouter un emprunteur"));
}

FenEditerEmprunteur::FenEditerEmprunteur(EmprunteurItem *item, ClassEmprunteurs *liste, QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);
    this->liste = liste;

    // Remplissage des champs du formulaire
    IDEdit->setText(item->getID());
    nomEdit->setText(item->getNom());
    prenomEdit->setText(item->getPrenom());
    ageEdit->setValue(item->getAge().toInt());
    numeroEdit->setText(item->getNumero());
    rueEdit->setText(item->getRue());
    CPEdit->setText(item->getCP());
    villeEdit->setText(item->getVille());

    treeWidget = item->treeWidget();
    currentItem = item;

    // Conservation des données de départ
    ClassAdresse adresse;
    adresse.setNumero(item->getNumero().toStdString());
    adresse.setRue(item->getRue().toStdString());
    adresse.setCP(item->getCP().toStdString());
    adresse.setVille(item->getVille().toStdString());

    emprunteurModif.setID(item->getID().toUInt());
    emprunteurModif.setNom(item->getNom().toStdString());
    emprunteurModif.setPrenom(item->getPrenom().toStdString());
    emprunteurModif.setAge(item->getAge().toUInt());
    emprunteurModif.setAdresse(adresse);

    setWindowTitle(tr("Modifier un emprunteur"));
}

void FenEditerEmprunteur::accept()
{
    if(nomEdit->text().size() == 0 || prenomEdit->text().size() == 0 || numeroEdit->text().size() == 0 || rueEdit->text().size() == 0 || CPEdit->text().size() == 0 || villeEdit->text().size() == 0)
    {
        QMessageBox::warning(this, tr("Erreur"), tr("Vous devez remplir tous les champs."));
    }
    else
    {
        ClassAdresse adresse;
        adresse.setAdresse(numeroEdit->text().toStdString(), rueEdit->text().toStdString(), CPEdit->text().toStdString(), villeEdit->text().toStdString());

        // Ajouter
        if(!currentItem)
        {
            currentItem = new EmprunteurItem(treeWidget);

            if(liste->Ajouter(ClassEmprunteurs::getID(), nomEdit->text().toStdString(), prenomEdit->text().toStdString(), adresse, ageEdit->text().toUInt()))
            {
                QString message("L'ajout de l'emprunteur " + nomEdit->text() + " " + prenomEdit->text() + " a été effectué avec succès.");
                QMessageBox::information(this, tr("Ajout effectué avec succès"), tr(message.toStdString().c_str()));

                liste->Sauvegarder("data/emprunteurs.txt");
            }
            else
            {
                QMessageBox::warning(this, tr("Erreur dans l'ajout"), tr("L'ajout de l'emprunteur n'a pu être effectué correctement."));
                return;
            }
        }
        else
        {
            if(liste->Modifier(emprunteurModif, IDEdit->text().toUInt(), nomEdit->text().toStdString(), prenomEdit->text().toStdString(), adresse, ageEdit->text().toUInt()))
            {
                QString message("La modification de l'emprunteur " + nomEdit->text() + " " + prenomEdit->text() + " a été effectuée avec succès.");
                QMessageBox::information(this, tr("Modification effectuée avec succès"), tr(message.toStdString().c_str()));
            }
            else
            {
                QMessageBox::warning(this, tr("Erreur dans la modification"), tr("La modification de l'emprunteur n'a pu être effectuée correctement."));
                return;
            }
        }
        // Modifier
        currentItem->setID(IDEdit->text());
        currentItem->setNom(nomEdit->text());
        currentItem->setPrenom(prenomEdit->text());
        currentItem->setAge(ageEdit->text());
        currentItem->setNumero(numeroEdit->text());
        currentItem->setRue(rueEdit->text());
        currentItem->setCP(CPEdit->text());
        currentItem->setVille(villeEdit->text());

        QDialog::accept();
    }
}
