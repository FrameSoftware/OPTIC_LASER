#ifndef INTERAUTHENTIF_H
#define INTERAUTHENTIF_H

#include "utilisateurmanager.h"
#include <QMainWindow>
#include "structure.h"
#include <QMessageBox>
#include "acceuil.h"
#include <QDebug>

namespace Ui {
class InterAuthentif;
}

class InterAuthentif : public QMainWindow
{
    Q_OBJECT

public:
    explicit InterAuthentif(QWidget *parent = 0);
    ~InterAuthentif();
    void show();
public slots:
    void on_btnOk_clicked();
    void on_btnAnnul_clicked();
private:
    Ui::InterAuthentif *ui;
    UtilisateurManager *m_user;
    ErrorManager err;
    Acceuil *start;
    Utilisateur *m_curr_user;
};

#endif // INTERAUTHENTIF_H
