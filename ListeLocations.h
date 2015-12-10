#ifndef LISTELOCATIONS_H
#define LISTELOCATIONS_H

#include <QMainWindow>
#include <QTreeView>
#include <map>
#include "ClassExemplaire.h"
#include "ClassExemplaires.h"
#include "ClassLocation.h"
#include "ClassLocations.h"
#include "LocationItem.h"

class ListeLocations : public QMainWindow
{
    Q_OBJECT
    public:
        ListeLocations(ClassExemplaires *listEx, ClassEmprunteurs *listEm);
        void refreshModele(std::map<std::string, ClassLocation*> listeLocations);

    public slots:
        void Ajout();
        void Modif();
        void Suppr();
        void List();
        void RechercherLocation();
        void AfficherDevis();
        void RestituerLocation();
        void AfficherFacture();

    protected:
        void closeEvent(QCloseEvent *event);

    private:
        ClassLocations *ListeDataLocations;
        QTreeWidget *liste;
        QStringList *listeLabels;
        ClassExemplaires *listExemplaires;
        ClassEmprunteurs *listEmprunteurs;
};

#endif // LISTELOCATIONS_H
