#ifndef LISTEVEHICULES_H
#define LISTEVEHICULES_H

#include <QMainWindow>
#include <QTreeView>
#include <map>
#include "ClassVehicule.h"
#include "ClassVehicules.h"
#include "VehiculeItem.h"
#include "FenEditerMoto.h"
#include "FenEditerAuto.h"
#include "FenRechercherMarque.h"

class ListeVehicules : public QMainWindow
{
    Q_OBJECT
    public:
        ListeVehicules();
        void refreshModele(std::map<std::string, ClassVehicule*> listeVehicules);
        ClassVehicules* getList() {return &ListeDataVehicules;}

    public slots:
        void AjoutVoiture();
        void AjoutMoto();
        void Modif();
        void Suppr();
        void List();
        void RechercherMarque();

    protected:
        void closeEvent(QCloseEvent *event);

    private:
        ClassVehicules ListeDataVehicules;
        QTreeWidget *liste;
        QStringList *listeLabels;
};

#endif // LISTEVEHICULES_H
