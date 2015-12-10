#include <QMessageBox>
#include "FenEditerExemplaire.h"
#include "ExemplaireItem.h"
#include "ClassExemplaires.h"
#include "Fonctions.h"
#include <iostream>

FenEditerExemplaire::FenEditerExemplaire(QTreeWidget *treeWidget, ClassExemplaires *liste, QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);

    this->treeWidget = treeWidget;
    this->liste = liste;
    currentItem = 0;

    listeV = liste->getListeVehicules();
    listParcours = listeV->getListe();

    // Liste les marques
    for(it = listParcours.begin(); it != listParcours.end(); it++)
    {
        marqueEdit->addItem(QString(it->second->getMarque().c_str()));
    }

    connect(marqueEdit, SIGNAL(currentIndexChanged(int)), this, SLOT(changerSelection(int)));

    changerSelection(0);

    setWindowTitle(tr("Ajouter un exemplaire de véhicule"));
}

FenEditerExemplaire::FenEditerExemplaire(ExemplaireItem *item, ClassExemplaires *liste, QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);
    this->liste = liste;

    listeV = liste->getListeVehicules();
    listParcours = listeV->getListe();

    // Remplissage des champs du formulaire
    numeroEdit->setText(item->getNumero());

    // Liste les marques
    for(it = listParcours.begin(); it != listParcours.end(); it++)
    {
        marqueEdit->addItem(QString(it->second->getMarque().c_str()));
    }

    listeV->RechercherParMarque(marqueEdit->currentText().toStdString());
    listParcours = listeV->getListeResult();

    modeleEdit->clear();

    // Liste les modèles
    for(it = listParcours.begin(); it != listParcours.end(); it++)
    {
        modeleEdit->addItem(QString(it->second->getModele().c_str()));
    }

    connect(marqueEdit, SIGNAL(currentIndexChanged(int)), this, SLOT(changerSelection(int)));

    marqueEdit->setCurrentIndex(marqueEdit->findText(item->getMarque()));
    modeleEdit->setCurrentIndex(modeleEdit->findText(item->getModele()));
    kmEdit->setText(item->getKm());
    couleurEdit->setCurrentIndex(couleurEdit->findText(item->getCouleur()));
    disponibleEdit->setCurrentIndex(disponibleEdit->findText(item->getDisponibilite()));

    treeWidget = item->treeWidget();
    currentItem = item;

    // Conservation des données de départ
    exemplaireModif.setNumero(item->getNumero().toUInt());
    ClassVehicule *e;
    e = liste->getListeVehicules()->getbyMarqueModele(item->getMarque().toStdString(), item->getModele().toStdString());
    exemplaireModif.setVehicule(e);
    exemplaireModif.setKm(item->getKm().toUInt());
    exemplaireModif.setCouleur(item->getCouleur().toStdString());
    exemplaireModif.setDisponible(StringToBool(item->getDisponibilite().toStdString()));

    setWindowTitle(tr("Modifier un exemplaire de véhicule"));
}

void FenEditerExemplaire::accept()
{
    if(kmEdit->text().size() == 0)
    {
        QMessageBox::warning(this, tr("Erreur"), tr("Vous devez remplir tous les champs."));
    }
    else
    {
        ClassVehicule *e;
        e = liste->getListeVehicules()->getbyMarqueModele(marqueEdit->currentText().toStdString(), modeleEdit->currentText().toStdString());

        // Ajouter
        if(!currentItem)
        {
            currentItem = new ExemplaireItem(treeWidget);

            if(liste->Ajouter(ClassExemplaires::getID(), e, kmEdit->text().toUInt(), couleurEdit->currentText().toStdString(), StringToBool(disponibleEdit->currentText().toStdString())))
            {
                QString message("L'ajout de l'exemplaire " + marqueEdit->currentText() + " " + modeleEdit->currentText() + " a été effectué avec succès.");
                QMessageBox::information(this, tr("Ajout effectué avec succès"), tr(message.toStdString().c_str()));

                liste->Sauvegarder("data/exemplaires.txt");
            }
            else
            {
                QMessageBox::warning(this, tr("Erreur dans l'ajout"), tr("L'ajout de l'exemplaire n'a pu être effectué correctement."));
                return;
            }
        }
        else
        {
            if(liste->Modifier(exemplaireModif, numeroEdit->text().toUInt(), e, kmEdit->text().toUInt(), couleurEdit->currentText().toStdString(), StringToBool(disponibleEdit->currentText().toStdString())))
            {
                QString message("La modification de l'exemplaire " + marqueEdit->currentText() + " " + modeleEdit->currentText() + " a été effectuée avec succès.");
                QMessageBox::information(this, tr("Modification effectuée avec succès"), tr(message.toStdString().c_str()));
            }
            else
            {
                QMessageBox::warning(this, tr("Erreur dans la modification"), tr("La modification de l'exemplaire n'a pu être effectuée correctement."));
                return;
            }
        }
        // Modifier
        currentItem->setMarque(marqueEdit->currentText());
        currentItem->setModele(modeleEdit->currentText());
        currentItem->setKm(kmEdit->text());
        currentItem->setCouleur(couleurEdit->currentText());
        currentItem->setDisponible(disponibleEdit->currentText());

        QDialog::accept();
    }
}

void FenEditerExemplaire::changerSelection(int index)
{
    listeV = liste->getListeVehicules();
    marqueEdit->setCurrentIndex(index);
    listeV->RechercherParMarque(marqueEdit->currentText().toStdString());
    listParcours = listeV->getListeResult();

    modeleEdit->clear();
    // Liste les modèles
    for(it = listParcours.begin(); it != listParcours.end(); it++)
    {
        modeleEdit->addItem(QString(it->second->getModele().c_str()));
    }
}
