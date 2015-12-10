#include <QtGui>
#include <iostream>
#include <string>
#include <vector>
#include "Fonctions.h"
#include "ClassVehicule.h"
#include "ClassVehicules.h"
#include "ClassExemplaire.h"
#include "ClassExemplaires.h"
#include "ExemplaireItem.h"
#include "ListeExemplaires.h"
#include "FenEditerExemplaire.h"
#include "FenRechercherKm.h"

ListeExemplaires::ListeExemplaires(ClassVehicules *listeV)
{
    listeVehicules = listeV;
    ListeDataExemplaires = new ClassExemplaires(listeV);
    ListeDataExemplaires->Charger("data/exemplaires.txt");

    listeLabels = new QStringList();
    *listeLabels << tr("Numéro") << tr("Marque") << tr("Modèle") << tr("Kilométrage") << tr("Couleur") << tr("Disponible");

    liste = new QTreeWidget();
    liste->setHeaderLabels(*listeLabels);
    liste->setSortingEnabled(true);
    setCentralWidget(liste);

    refreshModele(ListeDataExemplaires->getListe());
}

void ListeExemplaires::closeEvent(QCloseEvent *event)
{
    event->accept();
}

void ListeExemplaires::refreshModele(std::map<std::string, ClassExemplaire*> listeExemplaires)
{
    liste->clear();
    liste->setHeaderLabels(*listeLabels);

    //On ajoute une ligne d'éléments
    std::map<std::string, ClassExemplaire*>::iterator _it;

    for(_it = listeExemplaires.begin(); _it != listeExemplaires.end(); _it++)
    {
        QString numero = IntToString(_it->second->getNumero()).c_str();
        QString marque = _it->second->getVehicule()->getMarque().c_str();
        QString modele = _it->second->getVehicule()->getModele().c_str();
        QString km = IntToString(_it->second->getKm()).c_str();
        QString couleur = _it->second->getCouleur().c_str();
        QString disponible;

        if(_it->second->getDisponibilite()) disponible = "oui";
        else disponible = "non";

        ExemplaireItem *item = new ExemplaireItem(liste);
        item->setNumero(numero);
        item->setMarque(marque);
        item->setModele(modele);
        item->setKm(km);
        item->setCouleur(couleur);
        item->setDisponible(disponible);
    }
}

void ListeExemplaires::Ajout()
{
    FenEditerExemplaire dialog(liste, ListeDataExemplaires, this);
    dialog.exec();
    refreshModele(ListeDataExemplaires->getListe());
}

void ListeExemplaires::Modif()
{
    ExemplaireItem *item = static_cast<ExemplaireItem *>(liste->currentItem());
    if(item)
    {
        FenEditerExemplaire dialog(item, ListeDataExemplaires, this);
        dialog.exec();
        refreshModele(ListeDataExemplaires->getListe());
    }
}

void ListeExemplaires::Suppr()
{
    if(liste->currentItem() != NULL)
    {
        ExemplaireItem *item = static_cast<ExemplaireItem *>(liste->currentItem());

        ClassExemplaire e;
        ClassVehicule *vehicule;
        vehicule = listeVehicules->getbyMarqueModele(item->getMarque().toStdString(), item->getModele().toStdString());

        e.setExemplaire(item->getNumero().toUInt(), vehicule, item->getKm().toUInt(), item->getCouleur().toStdString(), StringToBool(item->getDisponibilite().toStdString()));

        ListeDataExemplaires->Supprimer(e);
        ListeDataExemplaires->Sauvegarder("data/exemplaires.txt");

        refreshModele(ListeDataExemplaires->getListe());
    }

    delete liste->currentItem();
}

void ListeExemplaires::List()
{
    refreshModele(ListeDataExemplaires->getListe());
}

void ListeExemplaires::RechercherKm()
{
    FenRechercherKm dialog(ListeDataExemplaires, this);
    dialog.exec();
    refreshModele(ListeDataExemplaires->getListeResult());
}
