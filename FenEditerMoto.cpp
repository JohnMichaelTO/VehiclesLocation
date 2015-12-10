#include <iostream>
#include <QMessageBox>
#include "FenEditerMoto.h"
#include "VehiculeItem.h"
#include "ClassMoto.h"
#include "ClassVehicule.h"
#include "ClassVehicules.h"
#include "Fonctions.h"

FenEditerMoto::FenEditerMoto(QTreeWidget *treeWidget, ClassVehicules *liste, QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);

    this->treeWidget = treeWidget;
    this->liste = liste;
    currentItem = 0;

    setWindowTitle(tr("Ajouter une moto"));
}

FenEditerMoto::FenEditerMoto(VehiculeItem *item, ClassVehicules *liste, QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);
    this->liste = liste;

    // Remplissage des champs du formulaire
    IDEdit->setText(item->getID());
    marqueEdit->setText(item->getMarque());
    modeleEdit->setText(item->getModele());
    typeEdit->setText(item->getType());
    nbRouesEdit->setCurrentIndex(nbRouesEdit->findText(item->getNbRoues()));
    poidsEdit->setText(item->getPoids());
    eCO2Edit->setText(item->getECO2());
    prixEdit->setText(item->getPrix());
    cylindreeEdit->setText(item->getCylindree());

    treeWidget = item->treeWidget();
    currentItem = item;

    // Conservation des données de départ
    MotoModif.setID(item->getID().toUInt());
    MotoModif.setMarque(item->getMarque().toStdString());
    MotoModif.setModele(item->getModele().toStdString());
    MotoModif.setType(item->getType().toStdString());
    MotoModif.setNbRoues(item->getNbRoues().toUInt());
    MotoModif.setPoids(item->getPoids().toUInt());
    MotoModif.setECO2(item->getECO2().toStdString());
    MotoModif.setPrix(item->getPrix().toUInt());
    MotoModif.setCylindree(item->getCylindree().toUInt());

    setWindowTitle(tr("Modifier une moto"));
}

void FenEditerMoto::accept()
{
    if(marqueEdit->text().size() == 0 || modeleEdit->text().size() == 0 || typeEdit->text().size() == 0 || poidsEdit->text().size() == 0 || eCO2Edit->text().size() == 0 || prixEdit->text().size() == 0 || cylindreeEdit->text().size() == 0)
    {
        QMessageBox::warning(this, tr("Erreur"), tr("Vous devez remplir tous les champs."));
    }
    else
    {
        // Ajouter
        if(!currentItem)
        {
            currentItem = new VehiculeItem(treeWidget);

            if(liste->Ajouter(ClassVehicules::getID(), marqueEdit->text().toStdString(), modeleEdit->text().toStdString(), typeEdit->text().toStdString(), nbRouesEdit->currentText().toUInt(), poidsEdit->text().toUInt(), eCO2Edit->text().toStdString(), prixEdit->text().toUInt(), cylindree->text().toUInt()))
            {
                QString message("L'ajout de la moto " + marqueEdit->text() + " " + modeleEdit->text() + " a été effectué avec succès.");
                QMessageBox::information(this, tr("Ajout effectué avec succès"), tr(message.toStdString().c_str()));

                liste->Sauvegarder("data/vehicules.txt");
            }
            else
            {
                QMessageBox::warning(this, tr("Erreur dans l'ajout"), tr("L'ajout de la moto n'a pu être effectué correctement."));
                return;
            }
        }
        else
        {
            if(liste->Modifier(MotoModif, IDEdit->text().toUInt(), marqueEdit->text().toStdString(), modeleEdit->text().toStdString(), typeEdit->text().toStdString(), nbRouesEdit->currentText().toUInt(), poidsEdit->text().toUInt(), eCO2Edit->text().toStdString(), prixEdit->text().toUInt(), cylindree->text().toUInt()))
            {
                QString message("La modification de la moto " + marqueEdit->text() + " " + modeleEdit->text() + " a été effectuée avec succès.");
                QMessageBox::information(this, tr("Modification effectuée avec succès"), tr(message.toStdString().c_str()));
            }
            else
            {
                QMessageBox::warning(this, tr("Erreur dans la modification"), tr("La modification de la moto n'a pu être effectuée correctement."));
                return;
            }
        }
        // Modifier

        currentItem->setID(IDEdit->text());
        currentItem->setMarque(marqueEdit->text());
        currentItem->setModele(modeleEdit->text());
        currentItem->setType(typeEdit->text());
        currentItem->setNbRoues(nbRouesEdit->currentText());
        currentItem->setPoids(poidsEdit->text());
        currentItem->setECO2(eCO2Edit->text());
        currentItem->setPrix(prixEdit->text());
        currentItem->setCylindree(cylindree->text());

        QDialog::accept();
    }
}
