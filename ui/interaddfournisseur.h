#ifndef INTERADDFOURNISSEUR_H
#define INTERADDFOURNISSEUR_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>

#include <structure.h>
#include "fournisseur.h"
#include "fournisseurmanager.h"

namespace Ui {
class InterAddFournisseur;
}

class InterAddFournisseur : public QDialog
{
    Q_OBJECT

public:
    InterAddFournisseur(QWidget *parent = 0);
    InterAddFournisseur(int id,QString nom,QString ville,QString infoSupp, QWidget *parent=0);
    ~InterAddFournisseur();
     int count();

private:
    Ui::InterAddFournisseur *ui;
    Fournisseur *m_fournisseur,*mod_four;
    FournisseurManager *m_four_man;
    QSqlDatabase bd;
    ErrorManager err; //pour gerer les retour des fonctions
    QString *nom, *ville,*mat,*query;
   int val;
   bool modif;
   int id_mod;

public slots:
    void on_btnValid_clicked();

};

#endif // INTERADDFOURNISSEUR_H
