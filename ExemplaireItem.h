#ifndef EXEMPLAIREITEM_H
#define EXEMPLAIREITEM_H

#include <QObject>
#include <QTreeWidgetItem>

class ExemplaireItem : public QObject, public QTreeWidgetItem
{
    Q_OBJECT
    public:
        ExemplaireItem(QTreeWidget *treeWidget);
        void setNumero(const QString &numero);
        void setMarque(const QString &marque);
        void setModele(const QString &modele);
        void setKm(const QString &Km);
        void setCouleur(const QString &couleur);
        void setDisponible(const QString &disponible);

        QString getNumero() const {return text(0);}
        QString getMarque() const {return text(1);}
        QString getModele() const {return text(2);}
        QString getKm() const {return text(3);}
        QString getCouleur() const {return text(4);}
        QString getDisponibilite() const {return text(5);}

    signals:

    public slots:
        void Supprimer();

};

#endif // EXEMPLAIREITEM_H
