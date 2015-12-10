#include <QtGui>
#include <iostream>
#include <string>
#include <vector>
#include "Fonctions.h"
#include "ClassDate.h"
#include "ClassExemplaire.h"
#include "ClassExemplaires.h"
#include "ClassLocation.h"
#include "ClassLocations.h"
#include "LocationItem.h"
#include "ListeLocations.h"
#include "FenEditerLocation.h"
#include "FenRechercherLocation.h"
#include "AfficherDevisA.h"
#include "AfficherDevisM.h"
#include "FenEditerRestitution.h"
#include "AfficherFactureA.h"
#include "AfficherFactureM.h"

ListeLocations::ListeLocations(ClassExemplaires *listEx, ClassEmprunteurs *listEm)
{
    listExemplaires = listEx;
    listEmprunteurs = listEm;

    ListeDataLocations = new ClassLocations(listEx, listEm);
    ListeDataLocations->Charger("data/locations.txt");

    listeLabels = new QStringList();
    *listeLabels << tr("ID Location") << tr("ID Exemplaire") << tr("Marque") << tr("Modèle") << tr("Jour D") << tr("Mois D") << tr("Année D") << tr("Jour F") << tr("Mois F") << tr("Année F") << tr("Jour R") << tr("Mois R") << tr("Année R") << tr("Date début") << tr("Date fin") << tr("Date retour") << tr("Assurance") << tr("ID Emprunteur") << tr("Nom") << tr("Prénom") << tr("Niveau Carburant") << tr("Etat Véhicule");

    liste = new QTreeWidget();
    liste->setHeaderLabels(*listeLabels);
    liste->setSortingEnabled(true);
    liste->setColumnHidden(1, true);
    liste->setColumnHidden(4, true);
    liste->setColumnHidden(5, true);
    liste->setColumnHidden(6, true);
    liste->setColumnHidden(7, true);
    liste->setColumnHidden(8, true);
    liste->setColumnHidden(9, true);
    liste->setColumnHidden(10, true);
    liste->setColumnHidden(11, true);
    liste->setColumnHidden(12, true);
    liste->setColumnHidden(17, true);
    setCentralWidget(liste);

    refreshModele(ListeDataLocations->getListe());
}

void ListeLocations::closeEvent(QCloseEvent *event)
{
    event->accept();
}

void ListeLocations::refreshModele(std::map<std::string, ClassLocation*> listeLocations)
{
    liste->clear();
    liste->setHeaderLabels(*listeLabels);

    //On ajoute une ligne d'éléments
    std::map<std::string, ClassLocation*>::iterator _it;

    for(_it = listeLocations.begin(); _it != listeLocations.end(); _it++)
    {
        QString id = IntToString(_it->second->getID()).c_str();
        QString idExemplaire = IntToString(_it->second->getExemplaire()->getNumero()).c_str();
        QString marque = _it->second->getExemplaire()->getVehicule()->getMarque().c_str();
        QString modele = _it->second->getExemplaire()->getVehicule()->getModele().c_str();
        QString DJ = IntToString(_it->second->getDateD().getJour()).c_str();
        QString DM = IntToString(_it->second->getDateD().getMois()).c_str();
        QString DA = IntToString(_it->second->getDateD().getAnnee()).c_str();
        QString FJ = IntToString(_it->second->getDateF().getJour()).c_str();
        QString FM = IntToString(_it->second->getDateF().getMois()).c_str();
        QString FA = IntToString(_it->second->getDateF().getAnnee()).c_str();
        QString RJ = IntToString(_it->second->getDateR().getJour()).c_str();
        QString RM = IntToString(_it->second->getDateR().getMois()).c_str();
        QString RA = IntToString(_it->second->getDateR().getAnnee()).c_str();
        QString assurance;
        if(_it->second->getAssurance()) assurance = "oui";
        else assurance = "non";
        QString idEmprunteur = IntToString(_it->second->getEmprunteur()->getID()).c_str();
        QString nom = _it->second->getEmprunteur()->getNom().c_str();
        QString prenom = _it->second->getEmprunteur()->getPrenom().c_str();
        QString niveauCarburant = IntToString(_it->second->getNiveauCarburant()).c_str();
        QString etatVehicule;
        if(_it->second->getEtatVehicule()) etatVehicule = "Bon état";
        else etatVehicule = "Mauvais état";

        LocationItem *item = new LocationItem(liste);
        item->setID(id);
        item->setIDExemplaire(idExemplaire);
        item->setMarque(marque);
        item->setModele(modele);
        item->setDJ(DJ);
        item->setDM(DM);
        item->setDA(DA);
        item->setFJ(FJ);
        item->setFM(FM);
        item->setFA(FA);
        item->setRJ(RJ);
        item->setRM(RM);
        item->setRA(RA);
        item->setDateDebut(DJ + "/" + DM + "/" + DA);
        item->setDateFin(FJ + "/" + FM + "/" + FA);
        item->setDateRetour(RJ + "/" + RM + "/" + RA);
        item->setAssurance(assurance);
        item->setIDEmprunteur(idEmprunteur);
        item->setNom(nom);
        item->setPrenom(prenom);
        item->setNiveauCarburant(niveauCarburant);
        item->setEtatVehicule(etatVehicule);
    }
}

void ListeLocations::Ajout()
{
    FenEditerLocation dialog(liste, ListeDataLocations, this);
    dialog.exec();
    refreshModele(ListeDataLocations->getListe());
}

void ListeLocations::Modif()
{
    LocationItem *item = static_cast<LocationItem *>(liste->currentItem());
    if(item)
    {
        FenEditerLocation dialog(item, ListeDataLocations, this);
        dialog.exec();
        refreshModele(ListeDataLocations->getListe());
    }
}

void ListeLocations::Suppr()
{
    if(liste->currentItem() != NULL)
    {
        LocationItem *item = static_cast<LocationItem *>(liste->currentItem());

        ClassLocation e;
        ClassExemplaire *exemplaire;
        ClassEmprunteur *emprunteur;
        ClassDate debut, fin, retour;

        emprunteur = listEmprunteurs->getByID(item->getIDEmprunteur().toUInt());
        exemplaire = listExemplaires->getByID(item->getIDExemplaire().toUInt());

        debut.setDate(item->getDJ().toUInt(), item->getDM().toUInt(), item->getDA().toUInt());
        fin.setDate(item->getFJ().toUInt(), item->getFM().toUInt(), item->getFA().toUInt());
        retour.setDate(item->getRJ().toUInt(), item->getRM().toUInt(), item->getRA().toUInt());

        e.setLocation(item->getID().toUInt(), debut, fin, retour, emprunteur, exemplaire, StringToBool(item->getAssurance().toStdString()), item->getNiveauCarburant().toUInt(), StringToBool(item->getEtatVehicule().toStdString()));

        ListeDataLocations->Supprimer(e);
        ListeDataLocations->Sauvegarder("data/locations.txt");

        refreshModele(ListeDataLocations->getListe());
    }

    delete liste->currentItem();
}

void ListeLocations::List()
{
    refreshModele(ListeDataLocations->getListe());
}

void ListeLocations::RechercherLocation()
{
    FenRechercherLocation dialog(ListeDataLocations, this);
    dialog.exec();
    refreshModele(ListeDataLocations->getListeResult());
}

void ListeLocations::AfficherDevis()
{
    LocationItem *item = static_cast<LocationItem *>(liste->currentItem());
    if(item)
    {
        ClassExemplaire *exemplaire;
        exemplaire = listExemplaires->getByID(item->getIDExemplaire().toUInt());

        if(exemplaire->getVehicule()->what() == 1)
        {
            AfficherDevisA dialog(item, ListeDataLocations, this);
            dialog.exec();
        }
        else
        {
            AfficherDevisM dialog(item, ListeDataLocations, this);
            dialog.exec();
        }
        refreshModele(ListeDataLocations->getListe());
    }
}

void ListeLocations::RestituerLocation()
{
    LocationItem *item = static_cast<LocationItem *>(liste->currentItem());
    if(item)
    {
        FenEditerRestitution dialog(item, ListeDataLocations, this);
        dialog.exec();
        refreshModele(ListeDataLocations->getListe());
    }
}

void ListeLocations::AfficherFacture()
{
    LocationItem *item = static_cast<LocationItem *>(liste->currentItem());
    if(item)
    {
        ClassExemplaire *exemplaire;
        exemplaire = listExemplaires->getByID(item->getIDExemplaire().toUInt());

        if(exemplaire->getVehicule()->what() == 1)
        {
            AfficherFactureA dialog(item, ListeDataLocations, this);
            dialog.exec();
        }
        else
        {
            AfficherFactureM dialog(item, ListeDataLocations, this);
            dialog.exec();
        }
        refreshModele(ListeDataLocations->getListe());
    }
}
