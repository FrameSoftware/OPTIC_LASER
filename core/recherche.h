#ifndef RECHERCHE_H
#define RECHERCHE_H

#include <iostream>
#include <exception>
#include <QList>
#include <QWidget>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlResult>
#include <QSqlRecord>
#include <QMessageBox>
#include <QStandardItem>
#include <QSqlTableModel>
#include <QStandardItemModel>
#include <QStringList>
#include <QDebug>

#include "structure.h"
#include "interaddfournisseur.h"
#include "fournisseurmanager.h"
#include "uificheclient.h"

namespace Ui {
class Recherche;
}

class Recherche : public QWidget
{
    Q_OBJECT
    enum Search{
        Patient,
        Article,
        Fournisseur
    };

public:
    explicit Recherche(SearchStruct search, QWidget *parent = 0);
    ~Recherche();
    void search_patient(QString data);
    void search_article(QString data);
    void search_fournsseur(QString data);
    void display_result(QStandardItemModel *model, Recherche::Search s);

private slots:
    void on_btnValider_clicked();

    void on_tableView_clicked(const QModelIndex &index);

private:
    int id_choix;
    QString cible;
    SearchStruct s;
    Ui::Recherche *ui;
    QSqlQuery *query;
    QStandardItemModel *model;
    QStringList list;
    InterAddFournisseur *inter_addFournisseur;
    FournisseurManager *four_man;
    FournisseurStruct fournisseur;
    UiFicheClient *fich_client;
};

#endif // RECHERCHE_H
