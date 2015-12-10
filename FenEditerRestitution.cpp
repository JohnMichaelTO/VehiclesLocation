#include <QMessageBox>
#include "FenEditerRestitution.h"
#include "LocationItem.h"
#include "ClassLocations.h"
#include "Fonctions.h"
#include <iostream>

FenEditerRestitution::FenEditerRestitution(LocationItem *item, ClassLocations *liste, QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);
    this->liste = liste;

    listeEmprunteurs = liste->getListeEmprunteurs();
    listeExemplaires = liste->getListeExemplaires();

    // Remplissage des champs du formulaire
    idEdit->setText(item->getID());
    dateDebut.setDate(item->getDA().toInt(), item->getDM().toInt(), item->getDJ().toInt());
    dateFin.setDate(item->getFA().toInt(), item->getFM().toInt(), item->getFJ().toInt());
    dateRetour.setDate(item->getRA().toInt(), item->getRM().toInt(), item->getRJ().toInt());
    dateREdit->setDate(dateRetour);

    connect(dateREdit, SIGNAL(dateChanged(QDate)), this, SLOT(changerDateRetour(QDate)));

    niveauCarburantEdit->setCurrentIndex(niveauCarburantEdit->findText(item->getNiveauCarburant()));
    etatVehiculeEdit->setCurrentIndex(etatVehiculeEdit->findText(item->getEtatVehicule()));

    currentItem = item;

    // Conservation des données de départ
    ClassDate debut, fin, retour;
    debut.setDate(item->getDJ().toInt(), item->getDM().toInt(), item->getDA().toInt());
    fin.setDate(item->getFJ().toInt(), item->getFM().toInt(), item->getFA().toInt());
    retour.setDate(item->getRJ().toInt(), item->getRM().toInt(), item->getRA().toInt());

    ClassEmprunteur* emprunteur;
    ClassExemplaire* exemplaire;
    emprunteur = listeEmprunteurs->getByID(item->getIDEmprunteur().toUInt());
    exemplaire = listeExemplaires->getByID(item->getIDExemplaire().toUInt());

    LocationModif.setID(item->getID().toUInt());
    LocationModif.setDateD(debut);
    LocationModif.setDateF(fin);
    LocationModif.setDateR(retour);
    LocationModif.setEmprunteur(emprunteur);
    LocationModif.setExemplaire(exemplaire);
    LocationModif.setAssurance(StringToBool(item->getAssurance().toStdString()));
    LocationModif.setNiveauCarburant(item->getNiveauCarburant().toUInt());
    LocationModif.setEtatVehicule(StringToBool(item->getEtatVehicule().toStdString()));

    setWindowTitle(tr("Retour de location"));
}

void FenEditerRestitution::accept()
{
    if(niveauCarburantEdit->currentIndex() == -1 || etatVehiculeEdit->currentIndex() == -1)
    {
        QMessageBox::warning(this, tr("Erreur"), tr("Vous devez remplir tous les champs."));
    }
    else
    {
        ClassEmprunteur* emprunteur;
        ClassExemplaire* exemplaire;
        emprunteur = listeEmprunteurs->getByID(LocationModif.getEmprunteur()->getID());
        exemplaire = listeExemplaires->getByID(LocationModif.getExemplaire()->getNumero());

        ClassDate debut, fin, retour;
        debut.setDate(dateDebut.day(), dateDebut.month(), dateDebut.year());
        fin.setDate(dateFin.day(), dateFin.month(), dateFin.year());
        retour.setDate(dateRetour.day(), dateRetour.month(), dateRetour.year());


        if(liste->Modifier(LocationModif, idEdit->text().toUInt(), debut, fin, retour, emprunteur, exemplaire, LocationModif.getAssurance(), niveauCarburantEdit->currentText().toUInt(), StringToBool(etatVehiculeEdit->currentText().toStdString())))
        {
            QString message("La restitution de la location n°" + idEdit->text() + " a été effectuée avec succès.");
            QMessageBox::information(this, tr("Restitution effectuée avec succès"), tr(message.toStdString().c_str()));
        }
        else
        {
            QMessageBox::warning(this, tr("Erreur dans la restitution"), tr("La restitution de la location n'a pu être effectuée correctement."));
            return;
        }
        // Modifier

        currentItem->setRJ(QString(IntToString(retour.getJour()).c_str()));
        currentItem->setRM(QString(IntToString(retour.getMois()).c_str()));
        currentItem->setRA(QString(IntToString(retour.getAnnee()).c_str()));

        currentItem->setNiveauCarburant(niveauCarburantEdit->currentText());
        currentItem->setEtatVehicule(etatVehiculeEdit->currentText());

        QDialog::accept();
    }
}

void FenEditerRestitution::changerDateRetour(QDate dateRestitution)
{
    dateRetour = dateRestitution;
}
