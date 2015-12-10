#include <QMessageBox>
#include "FenEditerLocation.h"
#include "LocationItem.h"
#include "ClassLocations.h"
#include "Fonctions.h"
#include <iostream>

FenEditerLocation::FenEditerLocation(QTreeWidget *treeWidget, ClassLocations *liste, QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);

    this->treeWidget = treeWidget;
    this->liste = liste;
    currentItem = 0;

    listeEmprunteurs = liste->getListeEmprunteurs();
    listeExemplaires = liste->getListeExemplaires();

    listParcoursEmprunteurs = listeEmprunteurs->getListe();

    listeExemplaires->RechercherParMarqueDisponibilite("_", 1);
    listParcoursExemplaires = listeExemplaires->getListeResult();

    // Liste les marques dont les véhicules sont disponibles à la location
    for(itEx = listParcoursExemplaires.begin(); itEx != listParcoursExemplaires.end(); itEx++)
    {
        marqueEdit->addItem(QString(itEx->second->getVehicule()->getMarque().c_str()));
    }

    connect(marqueEdit, SIGNAL(currentIndexChanged(int)), this, SLOT(changerSelectionModele(int)));
    connect(modeleEdit, SIGNAL(currentIndexChanged(int)), this, SLOT(changerModele(int)));
    connect(modeleEdit, SIGNAL(currentIndexChanged(int)), this, SLOT(changerExemplaire(int)));
    // Liste le nom des emprunteurs
    for(itEm = listParcoursEmprunteurs.begin(); itEm != listParcoursEmprunteurs.end(); itEm++)
    {
        nomEdit->addItem(QString(itEm->second->getNom().c_str()));
    }

    connect(nomEdit, SIGNAL(currentIndexChanged(int)), this, SLOT(changerSelectionNom(int)));
    connect(dateDEdit, SIGNAL(dateChanged(QDate)), this, SLOT(changerDateDebut(QDate)));
    connect(dateFEdit, SIGNAL(dateChanged(QDate)), this, SLOT(changerDateFin(QDate)));
    connect(assuranceEdit, SIGNAL(clicked()), this, SLOT(rechargerPrixEstimer()));

    changerSelectionModele(0);
    changerSelectionNom(0);

    dateDebut = dateDebut.currentDate();
    dateFin = dateDebut.addDays(7);
    dateDEdit->setDate(dateDebut);
    dateFEdit->setDate(dateFin);

    setWindowTitle(tr("Ajouter une location"));
}

FenEditerLocation::FenEditerLocation(LocationItem *item, ClassLocations *liste, QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);
    this->liste = liste;

    listeEmprunteurs = liste->getListeEmprunteurs();
    listeExemplaires = liste->getListeExemplaires();

    listParcoursExemplaires = listeExemplaires->getListe();
    listParcoursEmprunteurs = listeEmprunteurs->getListe();

    // Remplissage des champs du formulaire
    idEdit->setText(item->getID());
    // Liste les marques
    for(itEx = listParcoursExemplaires.begin(); itEx != listParcoursExemplaires.end(); itEx++)
    {
        marqueEdit->addItem(QString(itEx->second->getVehicule()->getMarque().c_str()));
    }

    connect(marqueEdit, SIGNAL(currentIndexChanged(int)), this, SLOT(changerSelectionModele(int)));
    connect(modeleEdit, SIGNAL(currentIndexChanged(int)), this, SLOT(changerModele(int)));
    connect(modeleEdit, SIGNAL(currentIndexChanged(int)), this, SLOT(changerExemplaire(int)));
    // Liste le nom des emprunteurs
    for(itEm = listParcoursEmprunteurs.begin(); itEm != listParcoursEmprunteurs.end(); itEm++)
    {
        nomEdit->addItem(QString(itEm->second->getNom().c_str()));
    }

    connect(nomEdit, SIGNAL(currentIndexChanged(int)), this, SLOT(changerSelectionNom(int)));
    connect(dateDEdit, SIGNAL(dateChanged(QDate)), this, SLOT(changerDateDebut(QDate)));
    connect(dateFEdit, SIGNAL(dateChanged(QDate)), this, SLOT(changerDateFin(QDate)));

    marqueEdit->setCurrentIndex(marqueEdit->findText(item->getMarque()));
    modeleEdit->setCurrentIndex(modeleEdit->findText(item->getModele()));
    idExemplaireEdit->setCurrentIndex(idExemplaireEdit->findText(item->getIDExemplaire()));

    nomEdit->setCurrentIndex(nomEdit->findText(item->getNom()));
    prenomEdit->setText(item->getPrenom());
    idEmprunteurEdit->setText(item->getIDEmprunteur());

    dateDebut.setDate(item->getDA().toInt(), item->getDM().toInt(), item->getDJ().toInt());
    dateDEdit->setDate(dateDebut);

    dateFin.setDate(item->getFA().toInt(), item->getFM().toInt(), item->getFJ().toInt());
    dateFEdit->setDate(dateFin);

    assuranceEdit->setChecked(StringToBool(item->getAssurance().toStdString()));
    rechargerPrixEstimer();
    connect(assuranceEdit, SIGNAL(clicked()), this, SLOT(rechargerPrixEstimer()));

    treeWidget = item->treeWidget();
    currentItem = item;

    // Conservation des données de départ
    ClassDate debut, fin;
    debut.setDate(item->getDJ().toInt(), item->getDM().toInt(), item->getDA().toInt());
    fin.setDate(item->getFJ().toInt(), item->getFM().toInt(), item->getFA().toInt());

    ClassEmprunteur* emprunteur;
    ClassExemplaire* exemplaire;
    emprunteur = listeEmprunteurs->getByID(item->getIDEmprunteur().toUInt());
    exemplaire = listeExemplaires->getByID(item->getIDExemplaire().toUInt());

    LocationModif.setID(item->getID().toUInt());
    LocationModif.setDateD(debut);
    LocationModif.setDateF(fin);
    LocationModif.setDateR(fin);
    LocationModif.setEmprunteur(emprunteur);
    LocationModif.setExemplaire(exemplaire);
    LocationModif.setAssurance(StringToBool(item->getAssurance().toStdString()));
    LocationModif.setNiveauCarburant(item->getNiveauCarburant().toUInt());
    LocationModif.setEtatVehicule(StringToBool(item->getEtatVehicule().toStdString()));

    setWindowTitle(tr("Modifier une location"));
}

void FenEditerLocation::accept()
{
    if(marqueEdit->currentIndex() == -1 || modeleEdit->currentIndex() == -1 || nomEdit->currentIndex() == -1)
    {
        QMessageBox::warning(this, tr("Erreur"), tr("Vous devez remplir tous les champs."));
    }
    else
    {
        ClassEmprunteur* emprunteur;
        ClassExemplaire* exemplaire;
        emprunteur = listeEmprunteurs->getByID(idEmprunteurEdit->text().toUInt());
        exemplaire = listeExemplaires->getByID(idExemplaireEdit->currentText().toUInt());

        ClassDate debut, fin;
        debut.setDate(dateDebut.day(), dateDebut.month(), dateDebut.year());
        fin.setDate(dateFin.day(), dateFin.month(), dateFin.year());

        // Ajouter
        if(!currentItem)
        {
            currentItem = new LocationItem(treeWidget);

            if(liste->Ajouter(ClassLocations::getID(), debut, fin, fin, emprunteur, exemplaire, assuranceEdit->isChecked(), 100, true))
            {
                QString message("L'ajout de la location " + marqueEdit->currentText() + " " + modeleEdit->currentText() + " a été effectué avec succès.");
                QMessageBox::information(this, tr("Ajout effectué avec succès"), tr(message.toStdString().c_str()));

                liste->Sauvegarder("data/locations.txt");
            }
            else
            {
                QMessageBox::warning(this, tr("Erreur dans l'ajout"), tr("L'ajout de la location n'a pu être effectué correctement."));
                return;
            }
        }
        else
        {
            if(liste->Modifier(LocationModif, idEdit->text().toUInt(), debut, fin, fin, emprunteur, exemplaire, assuranceEdit->isChecked(), 100, true))
            {
                QString message("La modification de la location " + marqueEdit->currentText() + " " + modeleEdit->currentText() + " a été effectuée avec succès.");
                QMessageBox::information(this, tr("Modification effectuée avec succès"), tr(message.toStdString().c_str()));
            }
            else
            {
                QMessageBox::warning(this, tr("Erreur dans la modification"), tr("La modification de la location n'a pu être effectuée correctement."));
                return;
            }
        }
        // Modifier
        currentItem->setIDExemplaire(idExemplaireEdit->currentText());
        currentItem->setMarque(marqueEdit->currentText());
        currentItem->setModele(modeleEdit->currentText());
        currentItem->setDJ(QString(IntToString(debut.getJour()).c_str()));
        currentItem->setDM(QString(IntToString(debut.getMois()).c_str()));
        currentItem->setDA(QString(IntToString(debut.getAnnee()).c_str()));
        currentItem->setFJ(QString(IntToString(fin.getJour()).c_str()));
        currentItem->setFM(QString(IntToString(fin.getMois()).c_str()));
        currentItem->setFA(QString(IntToString(fin.getAnnee()).c_str()));
        currentItem->setRJ(QString(IntToString(fin.getJour()).c_str()));
        currentItem->setRM(QString(IntToString(fin.getMois()).c_str()));
        currentItem->setRA(QString(IntToString(fin.getAnnee()).c_str()));
        currentItem->setDateDebut(QString(IntToString(debut.getJour()).c_str()) + "/" + QString(IntToString(debut.getMois()).c_str()) + "/" + QString(IntToString(debut.getAnnee()).c_str()));
        currentItem->setDateFin(QString(IntToString(fin.getJour()).c_str()) + "/" + QString(IntToString(fin.getMois()).c_str()) + "/" + QString(IntToString(fin.getAnnee()).c_str()));
        currentItem->setDateRetour(QString(IntToString(fin.getJour()).c_str()) + "/" + QString(IntToString(fin.getMois()).c_str()) + "/" + QString(IntToString(fin.getAnnee()).c_str()));
        currentItem->setAssurance(QString(BoolToString(assuranceEdit->isChecked()).c_str()));
        currentItem->setNom(nomEdit->currentText());
        currentItem->setPrenom(prenomEdit->text());
        currentItem->setIDEmprunteur(idEmprunteurEdit->text());
        currentItem->setNiveauCarburant("100");
        currentItem->setEtatVehicule("Bon état");

        QDialog::accept();
    }
}

void FenEditerLocation::changerSelectionModele(int index)
{
    listeExemplaires = liste->getListeExemplaires();
    listParcoursExemplaires = listeExemplaires->getListe();
    marqueEdit->setCurrentIndex(index);
    listeExemplaires->RechercherParKm(marqueEdit->currentText().toStdString());
    listParcoursExemplaires = listeExemplaires->getListeResult();

    modeleEdit->clear();
    // Liste les modèles
    for(itEx = listParcoursExemplaires.begin(); itEx != listParcoursExemplaires.end(); itEx++)
    {
        modeleEdit->addItem(QString(itEx->second->getVehicule()->getModele().c_str()));
    }
}

void FenEditerLocation::changerExemplaire(int index)
{
    listeExemplaires = liste->getListeExemplaires();
    listParcoursExemplaires = listeExemplaires->getListe();
    modeleEdit->setCurrentIndex(index);
    listeExemplaires->RechercherParKm(marqueEdit->currentText().toStdString() + "_" + modeleEdit->currentText().toStdString());
    listParcoursExemplaires = listeExemplaires->getListeResult();

    idExemplaireEdit->clear();
    // Liste les numéros des exemplaires
    for(itEx = listParcoursExemplaires.begin(); itEx != listParcoursExemplaires.end(); itEx++)
    {
        idExemplaireEdit->addItem(QString(IntToString(itEx->second->getNumero()).c_str()));
    }
}

void FenEditerLocation::changerSelectionNom(int index)
{
    listeEmprunteurs = liste->getListeEmprunteurs();
    listParcoursEmprunteurs = listeEmprunteurs->getListe();
    nomEdit->setCurrentIndex(index);
    listeEmprunteurs->RechercherParNom(nomEdit->currentText().toStdString());
    listParcoursEmprunteurs = listeEmprunteurs->getListeResult();

    prenomEdit->clear();
    idEmprunteurEdit->clear();
    // Sélection du prénom et ID de l'emprunteur en fonction du nom
    for(itEm = listParcoursEmprunteurs.begin(); itEm != listParcoursEmprunteurs.end(); itEm++)
    {
        prenomEdit->setText(QString(itEm->second->getPrenom().c_str()));
        idEmprunteurEdit->setText(QString(IntToString(itEm->second->getID()).c_str()));
    }
}

void FenEditerLocation::changerDateDebut(QDate dateStart)
{
    dateDebut = dateStart;
    rechargerPrixEstimer();
}

void FenEditerLocation::changerDateFin(QDate dateEnd)
{
    dateFin = dateEnd;
    rechargerPrixEstimer();
}

void FenEditerLocation::changerModele(int index)
{
    modeleEdit->setCurrentIndex(index);
    prix = listeExemplaires->getListeVehicules()->getPrixByMarqueModele(marqueEdit->currentText().toStdString(), modeleEdit->currentText().toStdString());
    rechargerPrixEstimer();
}

void FenEditerLocation::changerAssurance(bool valeur)
{
    assurance = valeur;
    rechargerPrixEstimer();
}

void FenEditerLocation::rechargerPrixEstimer()
{
    int soustract = dateDebut.daysTo(dateFin);

    if(assuranceEdit->isChecked())
    {
        assurance = 20;
    }
    else
    {
        assurance = 0;
    }

    prixEstime = (prix * (soustract + 1)) + assurance;

    if(soustract < 0)
    {
        buttonBox->setDisabled(true);
        prixEdit->setText("Invalide");
    }
    else
    {
        buttonBox->setDisabled(false);
        prixEdit->setText(QString(IntToString(prixEstime).c_str()));
    }
}
