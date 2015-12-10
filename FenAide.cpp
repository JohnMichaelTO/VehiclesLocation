#include <QMessageBox>
#include "FenAide.h"

FenAide::FenAide(QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);
    setWindowTitle(tr("Aide : Liste des commandes principales"));
}
