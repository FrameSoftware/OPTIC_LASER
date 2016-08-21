#include "interdiagnos.h"
#include "ui_interdiagnos.h"

InterDiagnos::InterDiagnos(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InterDiagnos)
{
    ui->setupUi(this);
    setLayout(ui->layGen);
}

InterDiagnos::~InterDiagnos()
{
    delete ui;
}

void InterDiagnos::on_btnQuit_clicked(){
    this->close();
}
