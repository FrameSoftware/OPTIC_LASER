#ifndef INTERPARAM_H
#define INTERPARAM_H

#include "interadduser.h"

#include <iostream>
#include <QMainWindow>
#include <QToolBar>
#include <QPushButton>
#include  <QStringList>
#include  <QStandardItem>
#include <QSqlTableModel>
#include <QStandardItemModel>
#include <QList>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlResult>
#include "utilisateur.h"
#include "utilisateurmanager.h"


namespace Ui {
class InterParam;
}

class InterParam : public QMainWindow
{
    Q_OBJECT

public:
    explicit InterParam(QWidget *parent = 0);
    ~InterParam();

public slots:
    //void addUser();
    void on_btnAdd_clicked();
    void reload();


private slots:
    void on_pushButton_clicked();

    void on_btnLog_clicked();

    void on_btnData_clicked();

    void on_btnValider_clicked();

    void on_btnErase_clicked();

    void on_btnEnTete_clicked();

    void on_btnSaveFact_clicked();

private:
    Ui::InterParam *ui;
    QToolBar *barFich;
    UtilisateurManager *userMan;
    QList <Utilisateur *> listUser;
    QList <Utilisateur *> liste;
    QPushButton *btnActQuit;
    QPushButton *btnActAddUser;
    QPushButton *btnReload;
    QSqlTableModel *model;/*,*modelReload;*/
    InterAddUser *intAddUser ;
     QStringList listeEntete;
};

#endif // INTERPARAM_H
