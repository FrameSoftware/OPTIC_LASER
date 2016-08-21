#ifndef INTERADDUSER_H
#define INTERADDUSER_H


#include <QMessageBox>
#include "structure.h"
#include "bdmanager.h"
#include "utilisateur.h"
#include "utilisateurmanager.h"
#include <iostream>

namespace Ui {
class InterAddUser;
}

class InterAddUser : public QWidget
{
    Q_OBJECT

public:
    explicit InterAddUser(QWidget *parent = 0);
    ~InterAddUser();
    ErrorManager testFormulaire();//verifi que le formulaire est bien rempli


private:
    Ui::InterAddUser *ui;
    QString valNivAcc;
    struct ErrorManager retour;
    UtilisateurManager *m_userMan;


public slots:
    void on_chkAjout_stateChanged(int state);
    void on_chkSupp_stateChanged(int state);
    void on_chkParam_stateChanged(int state);
    void on_chkModif_stateChanged(int state);
    void on_btnValider_clicked();
    void on_btnAnnul_clicked();
};

#endif // INTERADDUSER_H
