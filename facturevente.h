#ifndef FACTUREVENTE_H
#define FACTUREVENTE_H

#include <QWidget>

namespace Ui {
class FactureVente;
}

class FactureVente : public QWidget
{
    Q_OBJECT

public:
    explicit FactureVente(QWidget *parent = 0);
    ~FactureVente();

private:
    Ui::FactureVente *ui;
};

#endif // FACTUREVENTE_H
