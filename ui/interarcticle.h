#ifndef INTERARCTICLE_H
#define INTERARCTICLE_H

#include <QMainWindow>
#include <QToolBar>
#include <QPushButton>
#include <QDebug>
#include <QStringList>
#include <QStandardItemModel>
#include <QSqlTableModel>
#include <QSqlError>
#include <QHBoxLayout>
#include <QLabel>

#include "InterRecherche.h"
#include "interaddarticle.h"
#include "interaddverre.h"
#include "interaddmont.h"
#include "interaddnettoy.h"



namespace Ui {
class InterArcticle;
}

class InterArcticle : public QMainWindow
{
    Q_OBJECT

  public:
    explicit InterArcticle(QWidget *parent = 0);
    ~InterArcticle();
    void getListArcticle();//methode que recupere la liste d'Arcticle et effich

  public slots:
    void reload();
    void affcihIndex(QModelIndex index);
    void on_btnSupp_clicked();
    void addArticles();
    void addVerres();
    void addMont();
    void addNet();//slots pour les different ajouts
    void affich_list_default();
    void affich_list_mont();
    void affich_list_verre();
    void affich_list_net();


  private:
    Ui::InterArcticle *ui;
    QToolBar *barFichier,*barList;
    QPushButton *btnActNewArcticle, *btnActReload,*btnActQuitter,
    *btnAddVerre, *btnAddMont, *btnAddNet, *btnBilan/*pour le bilan total*/;
    QPushButton *btnListDefault, *btnListVerre, *btnListMont, *btnListNet;
    QSqlTableModel *model;
    QSqlDatabase bd;
    QString *errMsg;
    QHBoxLayout *layTab;
    QLabel *alert;
    int element;
    QTimer *tmp ;
    InterRecherche *reche;
    InterAddArticle *addArt;
    InterAddMont *addMontt;
    InterAddNettoy *addNett;
    InterAddVerre *addVer;

};

#endif // INTERARCTICLE_H
