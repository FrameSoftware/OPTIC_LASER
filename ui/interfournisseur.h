    #ifndef INTERFOURNISSEUR_H
#define INTERFOURNISSEUR_H


#include <iostream>
#include <QCloseEvent>
#include <QDebug>
#include <QMainWindow>
#include <QSqlTableModel>
#include <QSqlDatabase>
#include <QString>
#include <QPushButton>
#include <QTimer>
#include <QSqlError>
#include <QSqlRecord>
#include <QToolBar>
#include "interaddfournisseur.h"

namespace Ui {
class InterFournisseur;
}

class InterFournisseur : public QMainWindow
{
    Q_OBJECT

public:
    explicit InterFournisseur(QMainWindow *parent = 0);

    ~InterFournisseur();

public slots:
    void reload();
    void affcihIndex(QModelIndex index);
    void affichAddFour();
    void initDB();
    void closeEvent(QCloseEvent *evt);
    void on_btnDetails_clicked();
    void on_btnModif_clicked();
    void on_btnSupp_clicked();
private:
    Ui::InterFournisseur *ui;
    QSqlTableModel *model;
    QToolBar *barFichier;
    QPushButton *btnActNewFour, *btnActReload,*btnActQuitter;
    QSqlDatabase   bd;
    QString *errMsg;
    QTimer *tmp;
    InterAddFournisseur *addFour;
    FournisseurManager *four_man;
    int select;
};

#endif // INTERFOURNISSEUR_H
