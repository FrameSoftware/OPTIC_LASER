#ifndef VENTE_H
#define VENTE_H

#include <iostream>
#include <QMainWindow>
#include <QToolBar>
#include <QAction>
#include <QPushButton>
#include <QStringList>

#include <QSqlTableModel>

#include "internewvente.h"
#include "uificheclient.h"

namespace Ui {
  class Vente;
}

class Vente : public QMainWindow
{
  Q_OBJECT

public:
  explicit Vente(QWidget *parent = 0);
  ~Vente();

public slots:
  void affichInterVente();
  void reload();

private slots:
  void on_btnDetailCli_clicked();
  void affcihIndex(QModelIndex index);

  void on_btnDetailFact_clicked();

  void on_btnSupp_clicked();

private:
  Ui::Vente *ui;
  QAction *action;
  QToolBar *bare;
  interNewVente *interVente;
  QPushButton *btnReload,*btnActNew,*btnQuit;
  QSqlTableModel *model;
  QStringList *header;
  int select;
  UiFicheClient *fiche_cli_details;
};

#endif // VENTE_H
