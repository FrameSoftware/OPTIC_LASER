#include "userpreferences.h"
#include "ui_userpreferences.h"

UserPreferences::UserPreferences(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserPreferences)
{
    ui->setupUi(this);
    this->setFixedSize(this->width(),this->height());

    ui->lgnNom->setText(Utilisateur::m_nom);
    ui->lgnPrenom->setText(Utilisateur::m_pnom);
    ui->lgnLoggin->setText(Utilisateur::m_loggin);
}

UserPreferences::~UserPreferences()
{
    delete ui;
    delete user_man;
    delete user_struct;
    delete err_man;
}

void UserPreferences::on_btnFinish_clicked()
{
    bool etat(false);
    user_struct = new UserStruct;
    //on commence par verifier si la modification du password a eu lieu et doit etre prise
    //en compte
    if(ui->groupPassword->isChecked() == true){
        etat = true;
        ErrorManager err = this->control_pass();
        if(err.status != true){// si il ya erreur quelque par
            QMessageBox::warning(this,"Echec",err.msg);
            return;//on arrete l'execution de cette methode
        }
    }
    user_struct->m_id = Utilisateur::m_id;
    user_struct->m_nom = this->ui->lgnNom->text();
    qDebug()<<  user_struct->m_nom<< " le premier !!!! :) ";
    user_struct->m_pnom = this->ui->lgnPrenom->text();
    user_struct->m_loggin = this->ui->lgnLoggin->text();

    user_man = new UtilisateurManager();

    err_man = new ErrorManager;
    *err_man= user_man->updateUser(*user_struct,etat);// on recupere le resultat ici

    if(!err_man->status == true){
        QMessageBox::warning(this,"Echec",err_man->msgTech);
        this->close();
        return;
    }

    //dans le cas de succes
    QMessageBox::information(this,"Succes","La mise a jour de vos information a reussie");
    Utilisateur::m_loggin = this->ui->lgnLoggin->text();
    Utilisateur::m_nom = this->ui->lgnNom->text();
    Utilisateur::m_pnom = this->ui->lgnPrenom->text();
    if(etat == true){//si la pass a ete mis a jour
        Utilisateur::m_pnom = this->ui->newPass->text();
    }
    this->close();
    return;

}


/**
 * Cette methode est utilisée pout verifier la partie du formulaire qui concerne le mot de passe
 * @brief UserPreferences::control_pass
 * @return
 */
ErrorManager UserPreferences::control_pass(){
    ErrorManager err;
    if(ui->odlPss->text() != Utilisateur::m_pass){// si l'ancien password est different de celui en session on arrete
        //QMessageBox::warning(this,"Erreur  formulaire","L'ancien mot de passe specifier est incorrect");
        err.msg = "L'ancien mot de passe specifier est incorrect";
        err.status = false;
        return err;
    }

    //si le new et le repeat password sont different
    if(ui->newPass->text() != ui->rNewPass->text()){
        //QMessageBox::warning(this,"Erreur  formulaire","Le nouveau mot de passe est different");
        err.msg = "Le nouveau mot de passe est different";
        err.status = false;
        return err;
    }

    user_struct->m_pass = this->ui->newPass->text();
    err.status = true;
    return err;

}
