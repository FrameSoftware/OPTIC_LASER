#ifndef INTERADDMONT_H
#define INTERADDMONT_H

#include <QWidget>
#include "fournisseurmanager.h"

namespace Ui {
class InterAddMont;
}

class InterAddMont : public QWidget
{
    Q_OBJECT

public:
    explicit InterAddMont(QWidget *parent = 0);
    ~InterAddMont();

private:
    Ui::InterAddMont *ui;
    QString matricule;

public slots:
    void selectMatricule(QString text);
    void on_btnValider_clicked();
};

#endif // INTERADDMONT_H
