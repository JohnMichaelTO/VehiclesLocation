#ifndef FENAIDE_H
#define FENAIDE_H

#include <QDialog>
#include "ui_ListeCommandes.h"

class FenAide : public QDialog, private Ui::AideDialog
{
    public:
        FenAide(QWidget *parent = 0);
};

#endif // FENAIDE_H
