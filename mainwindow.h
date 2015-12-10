#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include "ListeEmprunteurs.h"
#include "ListeVehicules.h"
#include "ListeExemplaires.h"
#include "ListeLocations.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void afficherEmprunteur();
    void cacherEmprunteur();
    void afficherVehicule();
    void cacherVehicule();
    void afficherLocation();
    void cacherLocation();
    void afficherExemplaire();
    void cacherExemplaire();

    ~MainWindow();

public slots:
    void AfficheListeEmprunteurs();
    void ModifierEmprunteur();
    void AjouterEmprunteur();
    void SupprimerEmprunteur();

    void AfficheListeVehicules();
    void ModifierVehicule();
    void AjouterVoiture();
    void AjouterMoto();
    void SupprimerVehicule();

    void AfficheListeExemplaires();
    void AjouterExemplaire();
    void ModifierExemplaire();
    void SupprimerExemplaire();

    void AfficheListeLocations();
    void AjouterLocation();
    void ModifierLocation();
    void SupprimerLocation();
    void RestituerLocation();

    void RechercherParNom();
    void RechercherParMarque();
    void RechercherParKm();
    void RechercherParLocation();

    void AfficherDevis();
    void AfficherFacture();

    void AfficherAide();

private:
    Ui::MainWindow *ui;
    ListeEmprunteurs *listeDesEmprunteurs;
    ListeVehicules *listeDesVehicules;
    ListeExemplaires *listeDesExemplaires;
    ListeLocations *listeDesLocations;
    QStackedWidget *vue;
};
#endif // MAINWINDOW_H
