#ifndef ACCEUIL_H
#define ACCEUIL_H

#include <iostream>

#include <QMainWindow>
#include <QMessageBox>
#include <QLineEdit>


#include "vente.h"
#include "interarcticle.h"
#include "interparam.h"
#include "utilisateur.h"
#include "interfournisseur.h"
#include "uidiagostic.h"
#include "uipatient.h"
#include "userpreferences.h"
#include "recherche.h"

namespace Ui {
  class Acceuil;
}

class Acceuil : public QMainWindow
{
  Q_OBJECT

public:
  explicit Acceuil(QWidget *parent = 0);

    Acceuil(Utilisateur *user, QWidget *parent = 0);
  ~Acceuil();

public slots:
  void on_btnQuitter_clicked();
  void on_btnVente_clicked();
  void affichArticle();
  void on_btnFour_clicked();
  void on_btnFact_clicked();
  void on_btnClient_clicked();
  void apropos();

private slots:
  void on_btnRechercher_clicked();

private:
  Ui::Acceuil *ui;
  InterParam *intParam;
  Utilisateur *m_user;
  UserPreferences *up;
  Recherche *rech;
};

#endif // ACCEUIL_H
