#ifndef INTERADDNETTOY_H
#define INTERADDNETTOY_H

#include <QWidget>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>

#include "fournisseurmanager.h"
#include "articlemanager.h"
#include "structure.h"


namespace Ui {
class InterAddNettoy;
}

class InterAddNettoy : public QWidget
{
    Q_OBJECT

public:
    explicit InterAddNettoy(QWidget *parent = 0);
    ~InterAddNettoy();

public slots:
    void selectMatricule(QString text);
    void on_btnValider_clicked();

private:
    Ui::InterAddNettoy *ui;
    QString matricule;
};

#endif // INTERADDNETTOY_H
