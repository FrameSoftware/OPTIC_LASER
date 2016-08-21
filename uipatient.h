#ifndef UIPATIENT_H
#define UIPATIENT_H

#include <iostream>
#include <QMainWindow>
#include <QSqlTableModel>
#include <QPushButton>
#include <QToolBar>
#include <QSqlError>
#include <QStatusBar>
#include <QTimer>
#include <QAction>

#include "uiaddpatient.h"
#include "uificheclient.h"

namespace Ui {
class UiPatient;
}

class UiPatient : public QMainWindow
{
    Q_OBJECT

public:
    explicit UiPatient(QWidget *parent = 0);
    ~UiPatient();

public slots:
    void reload();
    void affichIndex(QModelIndex index);
    void addPatient();
    void on_btnModif_clicked();

private slots:
    void on_btnSupp_clicked();

    void on_btnFiche_clicked();

private:
    //QAction *quit, *refresh;
    Ui::UiPatient *ui;
    QToolBar *barOutil;
    QPushButton *btnRefresh, *btnQuit, *btnNew;
    QSqlTableModel *model;
    QTimer *tmp;
    int element;//l'id de lelement choidi
    UiAddPatient *adpatient;
    UiFicheClient *fiche_client;
};

#endif // UIPATIENT_H
