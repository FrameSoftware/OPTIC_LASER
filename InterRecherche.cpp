#include <QWidget>
#include "InterRecherche.h"

InterRecherche::InterRecherche(QWidget *parent):
    QWidget(parent)
{
    bareRech=new QHBoxLayout;
    choix=new QComboBox;
    argument=new QLineEdit;
    valid=new QPushButton("RECHERCHE");

    choix->addItem("article");
    choix->addItem("client");
    choix->addItem("fournisseur");
    bareRech->addWidget(choix);
    bareRech->addWidget(argument);
    bareRech->addWidget(valid);
    this->setLayout(bareRech);
    connect(choix,SIGNAL(activated(QString)),this,SLOT(ModifierCible(QString)));
}

void InterRecherche::ModifierCible(QString maCible)
{
    cible=new QString;
    this->cible=&maCible;
}
