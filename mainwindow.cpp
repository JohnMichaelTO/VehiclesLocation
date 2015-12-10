#include <iostream>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ListeEmprunteurs.h"
#include "FenAide.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    listeDesEmprunteurs = new ListeEmprunteurs();
    listeDesVehicules = new ListeVehicules();
    listeDesExemplaires = new ListeExemplaires(listeDesVehicules->getList());
    listeDesLocations = new ListeLocations(listeDesExemplaires->getList(), listeDesEmprunteurs->getList());

    vue = new QStackedWidget;
    vue->addWidget(listeDesEmprunteurs);
    vue->addWidget(listeDesVehicules);
    vue->addWidget(listeDesExemplaires);
    vue->addWidget(listeDesLocations);
    setCentralWidget(vue);

    // Signals/slots
    connect(ui->actionListe_des_emprunteurs, SIGNAL(triggered()), this, SLOT(AfficheListeEmprunteurs()));
    connect(ui->actionListe_des_v_hicules, SIGNAL(triggered()), this, SLOT(AfficheListeVehicules()));
    connect(ui->actionListe_des_v_hicules_pr_sents, SIGNAL(triggered()), this, SLOT(AfficheListeExemplaires()));
    connect(ui->actionConsultation_des_locations, SIGNAL(triggered()), this, SLOT(AfficheListeLocations()));

    connect(ui->actionModifier_emprunteur, SIGNAL(triggered()), this, SLOT(ModifierEmprunteur()));
    connect(ui->actionNouvel_emprunteur, SIGNAL(triggered()), this, SLOT(AjouterEmprunteur()));
    connect(ui->actionSupprimer_emprunteur, SIGNAL(triggered()), this, SLOT(SupprimerEmprunteur()));

    connect(ui->actionModifier_v_hicule, SIGNAL(triggered()), this, SLOT(ModifierVehicule()));
    connect(ui->actionNouvelle_Moto, SIGNAL(triggered()), this, SLOT(AjouterMoto()));
    connect(ui->actionNouvelle_voiture, SIGNAL(triggered()), this, SLOT(AjouterVoiture()));
    connect(ui->actionSupprimer_v_hicule, SIGNAL(triggered()), this, SLOT(SupprimerVehicule()));

    connect(ui->actionAjouter_un_exemplaire, SIGNAL(triggered()), this, SLOT(AjouterExemplaire()));
    connect(ui->actionModifier_un_exemplaire, SIGNAL(triggered()), this, SLOT(ModifierExemplaire()));
    connect(ui->actionSupprimer_un_exemplaire, SIGNAL(triggered()), this, SLOT(SupprimerExemplaire()));

    connect(ui->actionNouvelle_location, SIGNAL(triggered()), this, SLOT(AjouterLocation()));
    connect(ui->actionEditer_un_devis, SIGNAL(triggered()), this, SLOT(ModifierLocation()));
    connect(ui->actionAnnuler_location, SIGNAL(triggered()), this, SLOT(SupprimerLocation()));
    connect(ui->actionRetour_de_location, SIGNAL(triggered()), this, SLOT(RestituerLocation()));

    connect(ui->actionListe_des_commandes, SIGNAL(triggered()), this, SLOT(AfficherAide()));

    connect(ui->actionAfficher_le_devis, SIGNAL(triggered()), this, SLOT(AfficherDevis()));
    connect(ui->actionAfficher_la_facture, SIGNAL(triggered()), this, SLOT(AfficherFacture()));

    AfficheListeEmprunteurs();
}

MainWindow::~MainWindow()
{
    delete listeDesEmprunteurs;
    delete listeDesVehicules;
    delete listeDesExemplaires;
    delete listeDesLocations;
    delete ui;
}

void MainWindow::AfficheListeEmprunteurs()
{
    vue->setCurrentWidget(listeDesEmprunteurs);

    //Désactivation des actions Vehicule
    cacherVehicule();

    // Activation des actions Emprunteur
    afficherEmprunteur();

    // Désactivation des actions Location
    cacherLocation();

    // Désactivation des Exemplaires
    cacherExemplaire();

    // Signals/slots pour la recherche
    disconnect(ui->actionRechercher, SIGNAL(triggered()), this, SLOT(RechercherParKm()));
    disconnect(ui->actionRechercher, SIGNAL(triggered()), this, SLOT(RechercherParLocation()));
    disconnect(ui->actionRechercher, SIGNAL(triggered()), this, SLOT(RechercherParMarque()));
    connect(ui->actionRechercher, SIGNAL(triggered()), this, SLOT(RechercherParNom()));

    listeDesEmprunteurs->List();
}

void MainWindow::ModifierEmprunteur()
{
    listeDesEmprunteurs->Modif();
}

void MainWindow::AjouterEmprunteur()
{
    listeDesEmprunteurs->Ajout();
}

void MainWindow::SupprimerEmprunteur()
{
    listeDesEmprunteurs->Suppr();
}

void MainWindow::AfficheListeVehicules()
{
    vue->setCurrentWidget(listeDesVehicules);

    // Activation des actions Vehicule
    afficherVehicule();

    // Désactivation des actions Emprunteur
    cacherEmprunteur();

    // Désactivation des actions Location
    cacherLocation();

    // Désactivation des Exemplaires
    cacherExemplaire();

    // Signals/slots pour la recherche
    disconnect(ui->actionRechercher, SIGNAL(triggered()), this, SLOT(RechercherParNom()));
    disconnect(ui->actionRechercher, SIGNAL(triggered()), this, SLOT(RechercherParKm()));
    disconnect(ui->actionRechercher, SIGNAL(triggered()), this, SLOT(RechercherParLocation()));
    connect(ui->actionRechercher, SIGNAL(triggered()), this, SLOT(RechercherParMarque()));

    listeDesVehicules->List();
}

void MainWindow::ModifierVehicule()
{
    listeDesVehicules->Modif();
}

void MainWindow::AjouterVoiture()
{
    listeDesVehicules->AjoutVoiture();
}

void MainWindow::AjouterMoto()
{
    listeDesVehicules->AjoutMoto();
}

void MainWindow::SupprimerVehicule()
{
    listeDesVehicules->Suppr();
}

void MainWindow::AfficheListeExemplaires()
{
    vue->setCurrentWidget(listeDesExemplaires);

    // Désactivation des actions Vehicule
    cacherVehicule();

    // Désactivation des actions Emprunteur
    cacherEmprunteur();

    // Désactivation des actions Location
    cacherLocation();

    // Activation des Exemplaires
    afficherExemplaire();

    // Signals/slots pour la recherche
    disconnect(ui->actionRechercher, SIGNAL(triggered()), this, SLOT(RechercherParNom()));
    disconnect(ui->actionRechercher, SIGNAL(triggered()), this, SLOT(RechercherParMarque()));
    disconnect(ui->actionRechercher, SIGNAL(triggered()), this, SLOT(RechercherParLocation()));
    connect(ui->actionRechercher, SIGNAL(triggered()), this, SLOT(RechercherParKm()));

    listeDesExemplaires->List();
}

void MainWindow::AfficheListeLocations()
{
    vue->setCurrentWidget(listeDesLocations);

    // Désactivation des actions Vehicule
    cacherVehicule();

    // Désactivation des actions Emprunteur
    cacherEmprunteur();

    // Désactivation des Exemplaires
    cacherExemplaire();

    // Activation des actions Location
    afficherLocation();

    // Signals/slots pour la recherche
    disconnect(ui->actionRechercher, SIGNAL(triggered()), this, SLOT(RechercherParNom()));
    disconnect(ui->actionRechercher, SIGNAL(triggered()), this, SLOT(RechercherParMarque()));
    disconnect(ui->actionRechercher, SIGNAL(triggered()), this, SLOT(RechercherParKm()));
    connect(ui->actionRechercher, SIGNAL(triggered()), this, SLOT(RechercherParLocation()));

    listeDesLocations->List();
}

void MainWindow::AjouterLocation()
{
    listeDesLocations->Ajout();
}

void MainWindow::ModifierLocation()
{
    listeDesLocations->Modif();
}

void MainWindow::SupprimerLocation()
{
    listeDesLocations->Suppr();
}

void MainWindow::AjouterExemplaire()
{
    listeDesExemplaires->Ajout();
}

void MainWindow::ModifierExemplaire()
{
    listeDesExemplaires->Modif();
}

void MainWindow::SupprimerExemplaire()
{
    listeDesExemplaires->Suppr();
}

void MainWindow::RechercherParNom()
{
    listeDesEmprunteurs->RechercherNom();
}

void MainWindow::RechercherParMarque()
{
    listeDesVehicules->RechercherMarque();
}

void MainWindow::RechercherParKm()
{
    listeDesExemplaires->RechercherKm();
}

void MainWindow::RechercherParLocation()
{
    listeDesLocations->RechercherLocation();
}

void MainWindow::AfficherDevis()
{
    listeDesLocations->AfficherDevis();
}

void MainWindow::AfficherFacture()
{
    listeDesLocations->AfficherFacture();
}

void MainWindow::AfficherAide()
{
    FenAide dialog(this);
    dialog.exec();
}

void MainWindow::RestituerLocation()
{
    listeDesLocations->RestituerLocation();
}

// Affiche les actions emprunteur
void MainWindow::afficherEmprunteur()
{
    ui->actionModifier_emprunteur->setDisabled(false);
    ui->actionNouvel_emprunteur->setDisabled(false);
    ui->actionSupprimer_emprunteur->setDisabled(false);

    ui->actionModifier_emprunteur->setVisible(true);
    ui->actionNouvel_emprunteur->setVisible(true);
    ui->actionSupprimer_emprunteur->setVisible(true);
}

// Cache les actions emprunteur
void MainWindow::cacherEmprunteur()
{
    ui->actionModifier_emprunteur->setDisabled(true);
    ui->actionNouvel_emprunteur->setDisabled(true);
    ui->actionSupprimer_emprunteur->setDisabled(true);

    ui->actionModifier_emprunteur->setVisible(false);
    ui->actionNouvel_emprunteur->setVisible(false);
    ui->actionSupprimer_emprunteur->setVisible(false);
}

// Affiche les actions véhicule
void MainWindow::afficherVehicule()
{
    ui->actionModifier_v_hicule->setDisabled(false);
    ui->actionNouvelle_Moto->setDisabled(false);
    ui->actionNouvelle_voiture->setDisabled(false);
    ui->actionSupprimer_v_hicule->setDisabled(false);

    ui->actionModifier_v_hicule->setVisible(true);
    ui->actionNouvelle_Moto->setVisible(true);
    ui->actionNouvelle_voiture->setVisible(true);
    ui->actionSupprimer_v_hicule->setVisible(true);;
}

// Cache les actions véhicule
void MainWindow::cacherVehicule()
{
    ui->actionModifier_v_hicule->setVisible(false);
    ui->actionNouvelle_Moto->setVisible(false);
    ui->actionNouvelle_voiture->setVisible(false);
    ui->actionSupprimer_v_hicule->setVisible(false);

    ui->actionModifier_v_hicule->setDisabled(true);
    ui->actionNouvelle_Moto->setDisabled(true);
    ui->actionNouvelle_voiture->setDisabled(true);
    ui->actionSupprimer_v_hicule->setDisabled(true);
}

// Affiche les actions location
void MainWindow::afficherLocation()
{
    ui->actionNouvelle_location->setDisabled(false);
    ui->actionAnnuler_location->setDisabled(false);
    ui->actionEditer_un_devis->setDisabled(false);
    ui->actionRetour_de_location->setDisabled(false);
    ui->actionAfficher_le_devis->setDisabled(false);
    ui->actionAfficher_la_facture->setDisabled(false);

    ui->actionNouvelle_location->setVisible(true);
    ui->actionAnnuler_location->setVisible(true);
    ui->actionEditer_un_devis->setVisible(true);
    ui->actionRetour_de_location->setVisible(true);
    ui->actionAfficher_le_devis->setVisible(true);
    ui->actionAfficher_la_facture->setVisible(true);
}

// Cache les actions location
void MainWindow::cacherLocation()
{
    ui->actionNouvelle_location->setDisabled(true);
    ui->actionAnnuler_location->setDisabled(true);
    ui->actionEditer_un_devis->setDisabled(true);
    ui->actionRetour_de_location->setDisabled(true);
    ui->actionAfficher_le_devis->setDisabled(true);
    ui->actionAfficher_la_facture->setDisabled(true);

    ui->actionNouvelle_location->setVisible(false);
    ui->actionAnnuler_location->setVisible(false);
    ui->actionEditer_un_devis->setVisible(false);
    ui->actionRetour_de_location->setVisible(false);
    ui->actionAfficher_le_devis->setVisible(false);
    ui->actionAfficher_la_facture->setVisible(false);
}

// Affiche les actions exemplaire
void MainWindow::afficherExemplaire()
{
    ui->actionAjouter_un_exemplaire->setDisabled(false);
    ui->actionSupprimer_un_exemplaire->setDisabled(false);
    ui->actionModifier_un_exemplaire->setDisabled(false);

    ui->actionAjouter_un_exemplaire->setVisible(true);
    ui->actionSupprimer_un_exemplaire->setVisible(true);
    ui->actionModifier_un_exemplaire->setVisible(true);
}

// Cache les actions exemplaire
void MainWindow::cacherExemplaire()
{
    ui->actionAjouter_un_exemplaire->setDisabled(true);
    ui->actionSupprimer_un_exemplaire->setDisabled(true);
    ui->actionModifier_un_exemplaire->setDisabled(true);

    ui->actionAjouter_un_exemplaire->setVisible(false);
    ui->actionSupprimer_un_exemplaire->setVisible(false);
    ui->actionModifier_un_exemplaire->setVisible(false);
}
