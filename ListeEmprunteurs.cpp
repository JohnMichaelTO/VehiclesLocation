#include <QtGui>
#include <iostream>
#include <string>
#include <vector>
#include "Fonctions.h"
#include "ClassDate.h"
#include "ClassAdresse.h"
#include "ClassEmprunteur.h"
#include "ClassEmprunteurs.h"
#include "ListeEmprunteurs.h"
#include "EmprunteurItem.h"
#include "FenEditerEmprunteur.h"
#include "FenRechercherNom.h"

ListeEmprunteurs::ListeEmprunteurs()
{
    ListeDataEmprunteurs.Charger("data/emprunteurs.txt");

    listeLabels = new QStringList();
    *listeLabels << tr("ID") << tr("Nom") << tr("Prénom") << tr("Age") << tr("N°") << tr("Rue") << tr("CP") << tr("Ville");

    liste = new QTreeWidget();
    liste->setHeaderLabels(*listeLabels);
    liste->setSortingEnabled(true);
    setCentralWidget(liste);

    refreshModele(ListeDataEmprunteurs.getListe());
}

void ListeEmprunteurs::closeEvent(QCloseEvent *event)
{
    event->accept();
}

void ListeEmprunteurs::refreshModele(std::map<std::string, ClassEmprunteur*> listeEmprunteurs)
{
    liste->clear();
    liste->setHeaderLabels(*listeLabels);

    //On ajoute une ligne d'éléments
    std::map<std::string, ClassEmprunteur*>::iterator _it;

    for(_it = listeEmprunteurs.begin(); _it != listeEmprunteurs.end(); _it++)
    {
        QString id = IntToString(_it->second->getID()).c_str();
        QString nom = _it->second->getNom().c_str();
        QString prenom = _it->second->getPrenom().c_str();
        QString age = IntToString(_it->second->getAge()).c_str();
        QString numero = _it->second->getAdresse().getNumero().c_str();
        QString rue = _it->second->getAdresse().getRue().c_str();
        QString CP = _it->second->getAdresse().getCP().c_str();
        QString ville = _it->second->getAdresse().getVille().c_str();

        EmprunteurItem *item = new EmprunteurItem(liste);
        item->setID(id);
        item->setNom(nom);
        item->setPrenom(prenom);
        item->setAge(age);
        item->setNumero(numero);
        item->setRue(rue);
        item->setCP(CP);
        item->setVille(ville);
    }
}

void ListeEmprunteurs::Ajout()
{
    FenEditerEmprunteur dialog(liste, &ListeDataEmprunteurs, this);
    dialog.exec();
    refreshModele(ListeDataEmprunteurs.getListe());
}

void ListeEmprunteurs::Modif()
{
    EmprunteurItem *item = static_cast<EmprunteurItem *>(liste->currentItem());
    if(item)
    {
        FenEditerEmprunteur dialog(item, &ListeDataEmprunteurs, this);
        dialog.exec();
        refreshModele(ListeDataEmprunteurs.getListe());
    }
}

void ListeEmprunteurs::Suppr()
{
    if(liste->currentItem() != NULL)
    {
        EmprunteurItem *item = static_cast<EmprunteurItem *>(liste->currentItem());
        ClassEmprunteur e;
        ClassAdresse a;
        e.setID(item->getID().toUInt());
        e.setNom(item->getNom().toStdString());
        e.setPrenom(item->getPrenom().toStdString());
        e.setAge(item->getAge().toUInt());

        a.setAdresse(item->getNom().toStdString(), item->getRue().toStdString(), item->getCP().toStdString(), item->getVille().toStdString());
        e.setAdresse(a);

        ListeDataEmprunteurs.Supprimer(e);
        ListeDataEmprunteurs.Sauvegarder("data/emprunteurs.txt");

        refreshModele(ListeDataEmprunteurs.getListe());
    }

    delete liste->currentItem();
}

void ListeEmprunteurs::List()
{
    refreshModele(ListeDataEmprunteurs.getListe());
}

void ListeEmprunteurs::RechercherNom()
{
    FenRechercherNom dialog(&ListeDataEmprunteurs, this);
    dialog.exec();
    refreshModele(ListeDataEmprunteurs.getListeResult());
}
