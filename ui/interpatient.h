#ifndef INTERPATIENT_H
#define INTERPATIENT_H

#include <QWidget>
#include <QMainWindow>
#include <QPushButton>
#include <QToolBar>
#include <QSqlTableModel>
#include <QTimer>
#include <QStatusBar>


namespace Ui {
class InterPatient;
}

class InterPatient : public QMainWindow
{
    Q_OBJECT

public:
    explicit InterPatient(QMainWindow *parent = 0);
    ~InterPatient();


private:
    Ui::InterPatient *ui;

};

#endif // INTERPATIENT_H
