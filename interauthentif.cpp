#include "interauthentif.h"
#include "ui_interauthentif.h"

InterAuthentif::InterAuthentif(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::InterAuthentif)
{
    setWindowFlags(Qt::FramelessWindowHint);
    ui->setupUi(this);

    this->setVisible(false);
}

InterAuthentif::~InterAuthentif()
{
    delete ui;
}

void InterAuthentif::on_btnAnnul_clicked(){
    qApp->exit();//on ferme l'application
}

void InterAuthentif::on_btnOk_clicked(){
    //on cherche a authentifier l'user
    m_user = new UtilisateurManager();
    err = m_user->authentificate(ui->lgnNom->text(),ui->lgnPass->text());
    if(err.status == true){
        m_curr_user = new Utilisateur(m_user->getUtilsateur());
        start = new Acceuil(m_curr_user);
        start->show();

        this->close();
    }else{
        QMessageBox::warning(this,"Echec authentification",err.msg);
        this->ui->lgnNom->setText("");
        this->ui->lgnPass->setText("");
    }
}

void InterAuthentif::show(){
    this->setVisible(true);
}
