#ifndef FENEDITEREMPRUNTEUR_H
#define FENEDITEREMPRUNTEUR_H

#include <QDialog>
#include "ui_EditerEmprunteur.h"
#include "ClassEmprunteur.h"
#include "ClassEmprunteurs.h"

class QTreeWidget;
class EmprunteurItem;

class FenEditerEmprunteur : public QDialog, private Ui::FenEmprunteur
{
    Q_OBJECT
    public:
        FenEditerEmprunteur(QTreeWidget *treeWidget, ClassEmprunteurs *liste, QWidget *parent = 0);
        FenEditerEmprunteur(EmprunteurItem *item, ClassEmprunteurs *liste, QWidget *parent = 0);

        void accept();

    private:
        QTreeWidget *treeWidget;
        EmprunteurItem *currentItem;
        ClassEmprunteur emprunteurModif;
        ClassEmprunteurs *liste;
};

#endif // FENEDITEREMPRUNTEUR_H
