#include "LocationItem.h"

LocationItem::LocationItem(QTreeWidget *treeWidget) :
    QTreeWidgetItem(treeWidget)
{
}

void LocationItem::setID(const QString &id)
{
    setText(0, id);
}
void LocationItem::setIDExemplaire(const QString &idExemplaire)
{
    setText(1, idExemplaire);
}
void LocationItem::setMarque(const QString &marque)
{
    setText(2, marque);
}
void LocationItem::setModele(const QString &modele)
{
    setText(3, modele);
}
void LocationItem::setDJ(const QString &DJ)
{
    setText(4, DJ);
}
void LocationItem::setDM(const QString &DM)
{
    setText(5, DM);
}
void LocationItem::setDA(const QString &DA)
{
    setText(6, DA);
}
void LocationItem::setFJ(const QString &FJ)
{
    setText(7, FJ);
}
void LocationItem::setFM(const QString &FM)
{
    setText(8, FM);
}
void LocationItem::setFA(const QString &FA)
{
    setText(9, FA);
}
void LocationItem::setRJ(const QString &RJ)
{
    setText(10, RJ);
}
void LocationItem::setRM(const QString &RM)
{
    setText(11, RM);
}
void LocationItem::setRA(const QString &RA)
{
    setText(12, RA);
}
void LocationItem::setDateDebut(const QString &dateDebut)
{
    setText(13, dateDebut);
}
void LocationItem::setDateFin(const QString &dateFin)
{
    setText(14, dateFin);
}
void LocationItem::setDateRetour(const QString &dateRetour)
{
    setText(15, dateRetour);
}
void LocationItem::setAssurance(const QString &assurance)
{
    setText(16, assurance);
}
void LocationItem::setIDEmprunteur(const QString &idEmprunteur)
{
    setText(17, idEmprunteur);
}
void LocationItem::setNom(const QString &nom)
{
    setText(18, nom);
}
void LocationItem::setPrenom(const QString &prenom)
{
    setText(19, prenom);
}
void LocationItem::setNiveauCarburant(const QString &niveauCarburant)
{
    setText(20, niveauCarburant);
}
void LocationItem::setEtatVehicule(const QString &etatVehicule)
{
    setText(21, etatVehicule);
}

void LocationItem::Supprimer()
{
    delete this;
}
