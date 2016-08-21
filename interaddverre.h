#ifndef INTERADDVERRE_H
#define INTERADDVERRE_H

#include <QWidget>
#include "structure.h"
#include "verre.h"
#include "articlemanager.h"

#include <QMessageBox>

namespace Ui {
class InterAddVerre;
}

class InterAddVerre : public QWidget
{
    Q_OBJECT

public:
    explicit InterAddVerre(QWidget *parent = 0);
    ~InterAddVerre();

public slots:
    void on_btnValider_clicked();
    void selectMatricule(QString text);

private:
    Ui::InterAddVerre *ui;
    QString matricule;
    ArticleManager *art_man;
    Verre vrr;
};

#endif // INTERADDVERRE_H
