#ifndef LISTEEMPRUNTEURS_H
#define LISTEEMPRUNTEURS_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QTreeView>
#include <QVBoxLayout>
#include <map>
#include "ClassEmprunteur.h"
#include "ClassEmprunteurs.h"
#include "EmprunteurItem.h"
#include "FenEditerEmprunteur.h"

class ListeEmprunteurs : public QMainWindow
{
    Q_OBJECT
    public:
        ListeEmprunteurs();
        void refreshModele(std::map<std::string, ClassEmprunteur*> listeEmprunteurs);
        ClassEmprunteurs* getList() {return &ListeDataEmprunteurs;}

    public slots:
        //EmprunteurItem* Ajouter(const QString &contact);
        void Ajout();
        void Modif();
        void Suppr();
        void List();
        void RechercherNom();

    protected:
        void closeEvent(QCloseEvent *event);

    private:
        ClassEmprunteurs ListeDataEmprunteurs;
        QTreeWidget *liste;
        // QStandardItemModel *modele;
        QStringList *listeLabels;
        /*
        QTreeView *vue;
        QVBoxLayout *layout;
        QWidget *rien;
        */
};

#endif // LISTEEMPRUNTEURS_H
