#ifndef PRINTFACTURE_H
#define PRINTFACTURE_H

#include <QWidget>

namespace Ui {
class PrintFacture;
}

class PrintFacture : public QWidget
{
    Q_OBJECT

public:
    explicit PrintFacture(QWidget *parent = 0);
    ~PrintFacture();

private:
    Ui::PrintFacture *ui;
};

#endif // PRINTFACTURE_H
