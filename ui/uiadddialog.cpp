#include "uiadddialog.h"
#include "ui_uiadddialog.h"

uiAddDialog::uiAddDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::uiAddDialog)
{
    ui->setupUi(this);
}

uiAddDialog::~uiAddDialog()
{
    delete ui;
}
