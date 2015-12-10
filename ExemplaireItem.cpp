#include "ExemplaireItem.h"

ExemplaireItem::ExemplaireItem(QTreeWidget *treeWidget) :
    QTreeWidgetItem(treeWidget)
{
}

void ExemplaireItem::setNumero(const QString &numero)
{
    setText(0, numero);
}

void ExemplaireItem::setMarque(const QString &marque)
{
    setText(1, marque);
}

void ExemplaireItem::setModele(const QString &modele)
{
    setText(2, modele);
}

void ExemplaireItem::setKm(const QString &Km)
{
    setText(3, Km);
}

void ExemplaireItem::setCouleur(const QString &couleur)
{
    setText(4, couleur);
}

void ExemplaireItem::setDisponible(const QString &disponible)
{
    setText(5, disponible);
}

void ExemplaireItem::Supprimer()
{
    delete this;
}
