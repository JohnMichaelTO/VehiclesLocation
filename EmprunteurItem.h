#ifndef EMPRUNTEURITEM_H
#define EMPRUNTEURITEM_H

#include <QObject>
#include <QTreeWidgetItem>

class EmprunteurItem : public QObject, public QTreeWidgetItem
{
    Q_OBJECT
public:
    EmprunteurItem(QTreeWidget *treeWidget);
    void setID(const QString &ID);
    void setNom(const QString &nom);
    void setPrenom(const QString &prenom);
    void setAge(const QString &age);
    void setNumero(const QString &numero);
    void setRue(const QString &rue);
    void setCP(const QString &CP);
    void setVille(const QString &ville);

    QString getID() const {return text(0);}
    QString getNom() const {return text(1);}
    QString getPrenom() const {return text(2);}
    QString getAge() const {return text(3);}
    QString getNumero() const {return text(4);}
    QString getRue() const {return text(5);}
    QString getCP() const {return text(6);}
    QString getVille() const {return text(7);}
    
signals:
    
public slots:
    void Supprimer();
    
};

#endif // EMPRUNTEURITEM_H
