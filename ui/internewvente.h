#ifndef INTERNEWVENTE_H
#define INTERNEWVENTE_H

#include <iostream>
#include <QMainWindow>
#include <QMessageBox>
#include "structure.h"
#include "lunnettesmanager.h"
#include "utilisateur.h"
#include "facturemanager.h"
#include "patients.h"
#include "monture.h"
#include "verre.h"
#include "uiaddpatient.h"
#include "nettoyant.h"

namespace Ui {
  class interNewVente;
}

class interNewVente : public QMainWindow
{
  Q_OBJECT

public:
  explicit interNewVente(QWidget *parent = 0);
  ~interNewVente();

public slots:

  void select_patient(QString txt);
  void select_monture(QString txt);
  void select_nettoyant(QString txt);
  void reload();
  void addPatient();


  void on_btnAnnul_clicked();
  void on_btnValider_clicked();

  void on_OgVergVl_activated(const QString &arg1);

  void on_OgQteVl_valueChanged(int arg1);

  void on_OgPuVl_valueChanged(int arg1);

  void on_OgVergVp_activated(const QString &arg1);

  void on_OgQteVp_valueChanged(int arg1);

  void on_OgPuVp_valueChanged(int arg1);

  void on_OgTrait_textChanged();

  void on_OdVergVl_activated(const QString &arg1);

  void on_OdQteVl_valueChanged(int arg1);

  void on_OdPuVl_valueChanged(int arg1);

  void on_OdVergVp_activated(const QString &arg1);

  void on_OdQteVp_valueChanged(int arg1);

  void on_OdPuVp_valueChanged(int arg1);

  void on_OdTrait_textChanged();

private slots:


private:
  Ui::interNewVente *ui;
  LunnettesStruct lunnetes;
  int id_client,id_mont,id_net;//va etre gere par un slot
  int id_ogvl, id_ogvp, id_odvl, ido_dvp;
  UiAddPatient *new_patient;
  artIdNbrStruct nbrId;

};

#endif // INTERNEWVENTE_H
