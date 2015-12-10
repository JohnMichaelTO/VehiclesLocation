#include <iostream>
#include <QMessageBox>
#include "FenEditerAuto.h"
#include "VehiculeItem.h"
#include "ClassAuto.h"
#include "ClassVehicule.h"
#include "ClassVehicules.h"
#include "Fonctions.h"

FenEditerAuto::FenEditerAuto(QTreeWidget *treeWidget, ClassVehicules *liste, QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);

    this->treeWidget = treeWidget;
    this->liste = liste;
    currentItem = 0;

    setWindowTitle(tr("Ajouter une voiture"));
}

FenEditerAuto::FenEditerAuto(VehiculeItem *item, ClassVehicules *liste, QWidget *parent) :
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
    typePropulsionEdit->setText(item->getTypePropulsion());
    nbPortesEdit->setCurrentIndex(nbPortesEdit->findText(item->getNbPortes()));
    nbSiegesEdit->setCurrentIndex(nbSiegesEdit->findText(item->getNbSieges()));

    treeWidget = item->treeWidget();
    currentItem = item;

    // Conservation des données de départ
    AutoModif.setID(item->getID().toUInt());
    AutoModif.setMarque(item->getMarque().toStdString());
    AutoModif.setModele(item->getModele().toStdString());
    AutoModif.setType(item->getType().toStdString());
    AutoModif.setNbRoues(item->getNbRoues().toUInt());
    AutoModif.setPoids(item->getPoids().toUInt());
    AutoModif.setECO2(item->getECO2().toStdString());
    AutoModif.setPrix(item->getPrix().toUInt());
    AutoModif.setTypePropulsion(item->getTypePropulsion().toStdString());
    AutoModif.setNbPortes(item->getNbPortes().toUInt());
    AutoModif.setNbSieges(item->getNbSieges().toUInt());

    setWindowTitle(tr("Modifier une voiture"));
}

void FenEditerAuto::accept()
{
    if(marqueEdit->text().size() == 0 || modeleEdit->text().size() == 0 || typeEdit->text().size() == 0 || poidsEdit->text().size() == 0 || eCO2Edit->text().size() == 0 || prixEdit->text().size() == 0 || typePropulsionEdit->text().size() == 0)
    {
        QMessageBox::warning(this, tr("Erreur"), tr("Vous devez remplir tous les champs."));
    }
    else if(typeEdit->text() == "Moto")
    {
        QMessageBox::warning(this, tr("Erreur"), tr("Pour créer une moto, faites 'Nouvelle moto'"));
    }
    else
    {
        // Ajouter
        if(!currentItem)
        {
            currentItem = new VehiculeItem(treeWidget);

            if(liste->Ajouter(ClassVehicules::getID(), marqueEdit->text().toStdString(), modeleEdit->text().toStdString(), typeEdit->text().toStdString(), nbRouesEdit->currentText().toUInt(), poidsEdit->text().toUInt(), eCO2Edit->text().toStdString(), prixEdit->text().toUInt(), typePropulsionEdit->text().toStdString(), nbPortesEdit->currentText().toUInt(), nbSiegesEdit->currentText().toUInt()))
            {
                QString message("L'ajout de la voiture " + marqueEdit->text() + " " + modeleEdit->text() + " a été effectué avec succès.");
                QMessageBox::information(this, tr("Ajout effectué avec succès"), tr(message.toStdString().c_str()));

                liste->Sauvegarder("data/vehicules.txt");
            }
            else
            {
                QMessageBox::warning(this, tr("Erreur dans l'ajout"), tr("L'ajout de la voiture n'a pu être effectué correctement."));
                return;
            }
        }
        else
        {
            if(liste->Modifier(AutoModif, IDEdit->text().toUInt(), marqueEdit->text().toStdString(), modeleEdit->text().toStdString(), typeEdit->text().toStdString(), nbRouesEdit->currentText().toUInt(), poidsEdit->text().toUInt(), eCO2Edit->text().toStdString(), prixEdit->text().toUInt(), typePropulsionEdit->text().toStdString(), nbPortesEdit->currentText().toUInt(), nbSiegesEdit->currentText().toUInt()))
            {
                QString message("La modification de la voiture " + marqueEdit->text() + " " + modeleEdit->text() + " a été effectuée avec succès.");
                QMessageBox::information(this, tr("Modification effectuée avec succès"), tr(message.toStdString().c_str()));
            }
            else
            {
                QMessageBox::warning(this, tr("Erreur dans la modification"), tr("La modification de la voiture n'a pu être effectuée correctement."));
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
        currentItem->setTypePropulsion(typePropulsionEdit->text());
        currentItem->setNbPortes(nbPortesEdit->currentText());
        currentItem->setNbSieges(nbSiegesEdit->currentText());

        QDialog::accept();
    }
}
