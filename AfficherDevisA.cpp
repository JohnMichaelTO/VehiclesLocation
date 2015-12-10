#include <QMessageBox>
#include "AfficherDevisA.h"
#include "LocationItem.h"
#include "ClassLocations.h"
#include "Fonctions.h"
#include <iostream>
#include <QDate>

AfficherDevisA::AfficherDevisA(LocationItem *item, ClassLocations *liste, QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);
    this->liste = liste;

    listeEmprunteurs = liste->getListeEmprunteurs();
    listeExemplaires = liste->getListeExemplaires();

    ClassDate debut, fin;
    debut.setDate(item->getDJ().toInt(), item->getDM().toInt(), item->getDA().toInt());
    fin.setDate(item->getFJ().toInt(), item->getFM().toInt(), item->getFA().toInt());

    ClassEmprunteur* emprunteur;
    ClassExemplaire* exemplaire;
    emprunteur = listeEmprunteurs->getByID(item->getIDEmprunteur().toUInt());
    exemplaire = listeExemplaires->getByID(item->getIDExemplaire().toUInt());

    // Emprunteur
    nomEdit->setText(QString(emprunteur->getNom().c_str()));
    prenomEdit->setText(QString(emprunteur->getPrenom().c_str()));
    ageEdit->setText(QString(IntToString(emprunteur->getAge()).c_str()));
    rueEdit->setText(QString(QString(emprunteur->getAdresse().getNumero().c_str()) + " " + QString(emprunteur->getAdresse().getRue().c_str())));
    CPEdit->setText(QString(emprunteur->getAdresse().getCP().c_str()));
    villeEdit->setText(QString(emprunteur->getAdresse().getVille().c_str()));

    // Location
    dateDEdit->setText(QString(QString(IntToString(debut.getJour()).c_str()) + "/" + QString(IntToString(debut.getMois()).c_str()) + "/" + QString(IntToString(debut.getAnnee()).c_str())));
    dateFEdit->setText(QString(QString(IntToString(fin.getJour()).c_str()) + "/" + QString(IntToString(fin.getMois()).c_str()) + "/" + QString(IntToString(fin.getAnnee()).c_str())));

    QDate dateDebut, dateFin;
    dateDebut.setDate(item->getDA().toInt(), item->getDM().toInt(), item->getDJ().toInt());
    dateFin.setDate(item->getFA().toInt(), item->getFM().toInt(), item->getFJ().toInt());

    int soustract = dateDebut.daysTo(dateFin);
    dureeEdit->setText(IntToString(soustract).c_str());

    assuranceEdit->setText(item->getAssurance());

    // Véhicule
    typeEdit->setText("Moto");
    marqueEdit->setText(item->getMarque());
    modeleEdit->setText(item->getModele());
    couleurEdit->setText(exemplaire->getCouleur().c_str());
    kmEdit->setText(IntToString(exemplaire->getKm()).c_str());
    nbRouesEdit->setText(IntToString(exemplaire->getVehicule()->getNbRoues()).c_str());
    poidsEdit->setText(IntToString(exemplaire->getVehicule()->getPoids()).c_str());
    eCO2Edit->setText(exemplaire->getVehicule()->getECO2().c_str());
    typePropulsionEdit->setText(exemplaire->getVehicule()->getTypePropulsion().c_str());
    nbPortesEdit->setText(IntToString(exemplaire->getVehicule()->getNbPortes()).c_str());
    nbSiegesEdit->setText(IntToString(exemplaire->getVehicule()->getNbSieges()).c_str());
    prixEdit->setText(IntToString(exemplaire->getVehicule()->getPrix()).c_str());

    // Prix total
    prixEstime = exemplaire->getVehicule()->getPrix() * (soustract + 1);

    if(item->getAssurance() == "oui")
    {
        prixEstime += 20;
    }
    prixTotalEdit->setText(IntToString(prixEstime).c_str());

    setWindowTitle(tr("Afficher un devis"));
}
