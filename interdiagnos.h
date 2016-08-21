#ifndef INTERDIAGNOS_H
#define INTERDIAGNOS_H

#include <QWidget>

namespace Ui {
class InterDiagnos;
}

class InterDiagnos : public QWidget
{
    Q_OBJECT

public:
    explicit InterDiagnos(QWidget *parent = 0);
    ~InterDiagnos();

public slots:
    void on_btnQuit_clicked();

private:
    Ui::InterDiagnos *ui;
};

#endif // INTERDIAGNOS_H
