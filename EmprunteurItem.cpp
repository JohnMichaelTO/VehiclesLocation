#include "EmprunteurItem.h"

EmprunteurItem::EmprunteurItem(QTreeWidget *treeWidget) :
    QTreeWidgetItem(treeWidget)
{
}

void EmprunteurItem::setID(const QString &ID)
{
    setText(0, ID);
}

void EmprunteurItem::setNom(const QString &nom)
{
    setText(1, nom);
}

void EmprunteurItem::setPrenom(const QString &prenom)
{
    setText(2, prenom);
}

void EmprunteurItem::setAge(const QString &age)
{
    setText(3, age);
}

void EmprunteurItem::setNumero(const QString &numero)
{
    setText(4, numero);
}

void EmprunteurItem::setRue(const QString &rue)
{
    setText(5, rue);
}

void EmprunteurItem::setCP(const QString &CP)
{
    setText(6, CP);
}

void EmprunteurItem::setVille(const QString &ville)
{
    setText(7, ville);
}

void EmprunteurItem::Supprimer()
{
    delete this;
}
