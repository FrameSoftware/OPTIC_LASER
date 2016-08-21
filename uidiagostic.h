#ifndef UIDIAGOSTIC_H
#define UIDIAGOSTIC_H

#include <QMainWindow>
#include <QToolBar>
#include <QSqlTableModel>
#include <QPushButton>
#include <QTimer>
#include <QString>
#include <iostream>
#include <iostream>
#include <QSqlError>

#include "uiadddiagnos.h"
#include "utilisateur.h"
#include "printdiagnos.h"

namespace Ui {
class UiDiagostic;
}

class UiDiagostic : public QMainWindow
{
    Q_OBJECT

public:
    explicit UiDiagostic(QWidget *parent = 0);
    ~UiDiagostic();

public slots:
    void reload();
    void affichIndex(QModelIndex index);
    void addDiag();

private slots:
    //void on_btnDetail_clicked();

    void on_btnMod_clicked();


    void on_btnPrint_clicked();

    void on_pushButton_clicked();

    void on_btnSupp_clicked();

private:
    Ui::UiDiagostic *ui;
    QToolBar *toolbar;
    QPushButton *btnNew, *btnRefresh, *btnQuit;
    QSqlTableModel *model;
    QTimer *tmp;
    int element;
    PrintDiagnos *prtDiag;
};

#endif // UIDIAGOSTIC_H
