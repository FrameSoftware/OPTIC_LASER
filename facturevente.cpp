#include "facturevente.h"
#include "ui_facturevente.h"

FactureVente::FactureVente(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FactureVente)
{
    ui->setupUi(this);
}

FactureVente::~FactureVente()
{
    delete ui;
}
