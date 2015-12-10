#include "VehiculeItem.h"

VehiculeItem::VehiculeItem(QTreeWidget *treeWidget) :
    QTreeWidgetItem(treeWidget)
{
}

void VehiculeItem::setID(const QString &ID)
{
    setText(0, ID);
}

void VehiculeItem::setMarque(const QString &marque)
{
    setText(1, marque);
}

void VehiculeItem::setModele(const QString &modele)
{
    setText(2, modele);
}

void VehiculeItem::setType(const QString &type)
{
    setText(3, type);
}

void VehiculeItem::setNbRoues(const QString &nbRoues)
{
    setText(4, nbRoues);
}

void VehiculeItem::setPoids(const QString &poids)
{
    setText(5, poids);
}

void VehiculeItem::setECO2(const QString &eCO2)
{
    setText(6, eCO2);
}

void VehiculeItem::setPrix(const QString &prix)
{
    setText(7, prix);
}

void VehiculeItem::setTypePropulsion(const QString &typePropulsion)
{
    setText(8, typePropulsion);
}

void VehiculeItem::setNbPortes(const QString &nbPortes)
{
    setText(9, nbPortes);
}

void VehiculeItem::setNbSieges(const QString &nbSieges)
{
    setText(10, nbSieges);
}

void VehiculeItem::setCylindree(const QString &cylindree)
{
    setText(11, cylindree);
}

void VehiculeItem::Supprimer()
{
    delete this;
}
