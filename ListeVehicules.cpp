#include <QtGui>
#include <iostream>
#include <string>
#include <vector>
#include "Fonctions.h"
#include "ClassVehicule.h"
#include "ClassVehicules.h"
#include "ClassAuto.h"
#include "ClassMoto.h"
#include "VehiculeItem.h"
#include "ListeVehicules.h"
#include "FenEditerMoto.h"
#include "FenEditerAuto.h"

ListeVehicules::ListeVehicules()
{
    ListeDataVehicules.Charger("data/vehicules.txt");

    listeLabels = new QStringList();
    *listeLabels << tr("ID") << tr("Marque") << tr("Modèle") << tr("Type") << tr("NB Roues") << tr("Poids") << tr("eCO2") << tr("Prix") << tr("Carburant") << tr("NB Portes") << tr("NB Sièges") << tr("Cylindrée");

    liste = new QTreeWidget();
    liste->setHeaderLabels(*listeLabels);
    liste->setSortingEnabled(true);
    setCentralWidget(liste);

    refreshModele(ListeDataVehicules.getListe());
}

void ListeVehicules::closeEvent(QCloseEvent *event)
{
    event->accept();
}

void ListeVehicules::refreshModele(std::map<std::string, ClassVehicule*> listeVehicules)
{
    liste->clear();
    liste->setHeaderLabels(*listeLabels);

    //On ajoute une ligne d'éléments
    std::map<std::string, ClassVehicule*>::iterator _it;

    for(_it = listeVehicules.begin(); _it != listeVehicules.end(); _it++)
    {
        QString id = IntToString(_it->second->getID()).c_str();
        QString marque = _it->second->getMarque().c_str();
        QString modele = _it->second->getModele().c_str();
        QString type = _it->second->getType().c_str();
        QString nbRoues = IntToString(_it->second->getNbRoues()).c_str();
        QString poids = IntToString(_it->second->getPoids()).c_str();
        QString eCO2 = _it->second->getECO2().c_str();
        QString prix = IntToString(_it->second->getPrix()).c_str();

        VehiculeItem *item = new VehiculeItem(liste);
        item->setID(id);
        item->setMarque(marque);
        item->setModele(modele);
        item->setType(type);
        item->setNbRoues(nbRoues);
        item->setPoids(poids);
        item->setECO2(eCO2);
        item->setPrix(prix);

        if(_it->second->what() == 1) // Voiture
        {
            QString typePropulsion = _it->second->getTypePropulsion().c_str();
            QString nbPortes = IntToString(_it->second->getNbPortes()).c_str();
            QString nbSieges = IntToString(_it->second->getNbSieges()).c_str();

            item->setTypePropulsion(typePropulsion);
            item->setNbPortes(nbPortes);
            item->setNbSieges(nbSieges);

            item->setCylindree("-");
        }
        else
        {
            QString cylindree = IntToString(_it->second->getCylindree()).c_str();
            item->setCylindree(cylindree);

            item->setTypePropulsion("-");
            item->setNbPortes("-");
            item->setNbSieges("-");
        }
    }
}

void ListeVehicules::AjoutVoiture()
{
    FenEditerAuto dialog(liste, &ListeDataVehicules, this);
    dialog.exec();
    refreshModele(ListeDataVehicules.getListe());
}

void ListeVehicules::AjoutMoto()
{
    FenEditerMoto dialog(liste, &ListeDataVehicules, this);
    dialog.exec();
    refreshModele(ListeDataVehicules.getListe());
}

void ListeVehicules::Modif()
{
    VehiculeItem *item = static_cast<VehiculeItem *>(liste->currentItem());
    if(item)
    {
        if(item->getType() != "Moto")
        {
            FenEditerAuto dialog(item, &ListeDataVehicules, this);
            dialog.exec();
        }
        else
        {
            FenEditerMoto dialog(item, &ListeDataVehicules, this);
            dialog.exec();
        }
        refreshModele(ListeDataVehicules.getListe());
    }
}

void ListeVehicules::Suppr()
{
    if(liste->currentItem() != NULL)
    {
        VehiculeItem *item = static_cast<VehiculeItem *>(liste->currentItem());

        ListeDataVehicules.Supprimer(item->getID().toUInt(), item->getMarque().toStdString(), item->getModele().toStdString(), item->getType().toStdString());
        ListeDataVehicules.Sauvegarder("data/vehicules.txt");

        refreshModele(ListeDataVehicules.getListe());
    }

    delete liste->currentItem();
}

void ListeVehicules::List()
{
    refreshModele(ListeDataVehicules.getListe());
}

void ListeVehicules::RechercherMarque()
{
    FenRechercherMarque dialog(&ListeDataVehicules, this);
    dialog.exec();
    refreshModele(ListeDataVehicules.getListeResult());
}
