#ifndef USERPREFERENCES_H
#define USERPREFERENCES_H

#include <QDialog>
#include <QSql>
#include <QDebug>
#include <QMessageBox>

#include "utilisateurmanager.h"
#include "utilisateur.h"
#include "structure.h"
#include "utilisateurmanager.h"

namespace Ui {
class UserPreferences;
}

class UserPreferences : public QDialog
{
    Q_OBJECT

public:
    explicit UserPreferences(QWidget *parent = 0);
    ~UserPreferences();
    ErrorManager control_pass();

private slots:
    void on_btnFinish_clicked();

private:
    Ui::UserPreferences *ui;
    UserStruct *user_struct;
    UtilisateurManager *user_man;
    ErrorManager *err_man;
};

#endif // USERPREFERENCES_H
