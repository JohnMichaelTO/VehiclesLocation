#ifndef LISTEEXEMPLAIRES_H
#define LISTEEXEMPLAIRES_H

#include <QMainWindow>
#include <QTreeView>
#include <map>
#include "ClassExemplaire.h"
#include "ClassExemplaires.h"
#include "ExemplaireItem.h"
//#include "FenEditerExemplaire.h"

class ListeExemplaires : public QMainWindow
{
    Q_OBJECT
    public:
        ListeExemplaires(ClassVehicules *listeV);
        void refreshModele(std::map<std::string, ClassExemplaire*> listeExemplaires);
        ClassExemplaires* getList() {return ListeDataExemplaires;}

    public slots:
        void Ajout();
        void Modif();
        void Suppr();
        void List();
        void RechercherKm();

    protected:
        void closeEvent(QCloseEvent *event);

    private:
        ClassExemplaires *ListeDataExemplaires;
        QTreeWidget *liste;
        QStringList *listeLabels;
        ClassVehicules *listeVehicules;
};

#endif // LISTEEXEMPLAIRES_H
