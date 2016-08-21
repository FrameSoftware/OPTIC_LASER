#include "printfacture.h"
#include "ui_printfacture.h"

PrintFacture::PrintFacture(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PrintFacture)
{
    ui->setupUi(this);
}

PrintFacture::~PrintFacture()
{
    delete ui;
}
