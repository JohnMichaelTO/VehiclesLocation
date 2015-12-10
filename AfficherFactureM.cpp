#include <QMessageBox>
#include "AfficherFactureM.h"
#include "LocationItem.h"
#include "ClassLocations.h"
#include "Fonctions.h"
#include <iostream>
#include <QDate>

AfficherFactureM::AfficherFactureM(LocationItem *item, ClassLocations *liste, QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);
    this->liste = liste;

    listeEmprunteurs = liste->getListeEmprunteurs();
    listeExemplaires = liste->getListeExemplaires();

    ClassDate debut, fin, retour;
    debut.setDate(item->getDJ().toInt(), item->getDM().toInt(), item->getDA().toInt());
    fin.setDate(item->getFJ().toInt(), item->getFM().toInt(), item->getFA().toInt());
    retour.setDate(item->getRJ().toInt(), item->getRM().toInt(), item->getRA().toInt());

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
    cylindreeEdit->setText(IntToString(exemplaire->getVehicule()->getCylindree()).c_str());
    prixEdit->setText(IntToString(exemplaire->getVehicule()->getPrix()).c_str());

    // Restitution
    QDate dateRetour;
    dateRetour.setDate(item->getRA().toInt(), item->getRM().toInt(), item->getRJ().toInt());
    dateREdit->setText(QString(QString(IntToString(retour.getJour()).c_str()) + "/" + QString(IntToString(retour.getMois()).c_str()) + "/" + QString(IntToString(retour.getAnnee()).c_str())));

    niveauCarburantEdit->setText(item->getNiveauCarburant() + " %");
    etatVehiculeEdit->setText(item->getEtatVehicule());

    // Prix
    unsigned int sousTotalPrix = exemplaire->getVehicule()->getPrix() * (soustract + 1);
    sousTotalEdit->setText(IntToString(sousTotalPrix).c_str());

    unsigned int JoursRetard = dateFin.daysTo(dateRetour);
    double retardPenalite = JoursRetard * 0.05 * sousTotalPrix;
    retardNB->setText(QString(IntToString(JoursRetard).c_str()) + "j");
    retardEdit->setText(DoubleToString(retardPenalite).c_str());

    double Carburant = (100.0 - item->getNiveauCarburant().toUInt()) * 0.45;
    if(Carburant != 0.0)
    {
        prixCarburant->setText("Carburant :");
        prixCarburantEdit->setText(DoubleToString(Carburant).c_str());
    }
    else
    {
        prixCarburant->setText("");
        prixCarburantEdit->setText("");
    }

    reductionAssurance->setText("");
    reductionAssuranceEdit->setText("");
    double etat;
    if(StringToBool(item->getEtatVehicule().toStdString()))
    {
        etat = 0.0;
        prixEtat->setText("");
        prixEtatEdit->setText("");
    }
    else
    {
        etat = 0.30 * sousTotalPrix;
        prixEtat->setText("Etat du véhicule :");
        prixEtatEdit->setText(DoubleToString(etat).c_str());
        if(item->getAssurance() == "oui")
        {
            reductionAssurance->setText("Assurance :");
            reductionAssuranceEdit->setText("-" + QString(DoubleToString(etat).c_str()));
            etat = 0.0;
        }
    }
    prixAssurance->setText("");
    prixAssuranceEdit->setText("");
    double assurancePrix = 0.0;
    if(item->getAssurance() == "oui")
    {
        prixAssurance->setText("Frais assurance :");
        prixAssuranceEdit->setText("20");
        assurancePrix = 20.0;
    }

    reduction->setText("");
    reductionEdit->setText("");
    reductionPourcent->setText("");
    unsigned int div = exemplaire->getKm() / 50000;
    double reductionKMS = 0.10 * div * sousTotalPrix;
    if(reductionKMS != 0.0)
    {
        reduction->setText("Réduction kms :");
        reductionPourcent->setText("-" + QString(IntToString(div).c_str()) + "0 %");
        reductionEdit->setText(DoubleToString(reductionKMS).c_str());
    }

    double prixTotalCalcul = sousTotalPrix + retardPenalite + Carburant + etat + assurancePrix - reductionKMS;
    prixTotalEdit->setText(DoubleToString(prixTotalCalcul).c_str());

    setWindowTitle(tr("Afficher une facture"));
}
