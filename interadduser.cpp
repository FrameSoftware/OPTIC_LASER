#include "interadduser.h"
#include "ui_interadduser.h"
#include <QDebug>
#include "structure.h"

InterAddUser::InterAddUser(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InterAddUser)
{
    ui->setupUi(this);
    ui->groupAces->setLayout(ui->layGroup);
    this->setLayout(ui->layGen);
    this->valNivAcc = "0000";
    setFixedSize(300,350);
    this->setWindowTitle("Ajout d'un nouvel utilisateur");
    setWindowModality(Qt::WindowModal);
}

InterAddUser::~InterAddUser()
{
    delete ui;
}

void InterAddUser::on_chkAjout_stateChanged(int state){
    //QMessageBox::information(this,"exemple","sa donne");
    if(state == 2){  //si c'est cocher
        this->valNivAcc[1]  = QChar('1');
    } else{
        this->valNivAcc[1]= QChar('0');
    }
    ui->lgnNivAcc->setText(this->valNivAcc);
}

void InterAddUser::on_chkSupp_stateChanged(int state){
    if(state == 2){  //si c'est cocher
        this->valNivAcc[2]  = QChar('1');
    } else{
        this->valNivAcc[2]= QChar('0');
    }
    ui->lgnNivAcc->setText(this->valNivAcc);
}

void InterAddUser::on_chkParam_stateChanged(int state){
    if(state == 2){  //si c'est cocher
        this->valNivAcc[3]  = QChar('1');
    } else{
        this->valNivAcc[3]= QChar('0');
    }
    ui->lgnNivAcc->setText(this->valNivAcc);
}

void InterAddUser::on_chkModif_stateChanged(int state){
    if(state == 2){  //si c'est cocher
        this->valNivAcc[0]  = QChar('1');
    } else{
        this->valNivAcc[0]= QChar('0');
    }
    ui->lgnNivAcc->setText(this->valNivAcc);
}

ErrorManager InterAddUser::testFormulaire(){
    /*
     * Cette fonction teste si le formulairs est bien remplit est si
     * au moin 1 droit est specifier
     * */

    struct ErrorManager err;

    //test des formulaires
    if(ui->lgnNom->text().isEmpty() || ui->lgnPnom->text().isEmpty() || ui->lgnPost->text().isEmpty()){
        err.status = false;
        err.msg = "Le nom ou le prenom ou le post n'est pas remplit";
        return err;
    }else{
        if(this->valNivAcc == "0000"){
             err.status = false;
             err.msg = "Erreur vous devez entrer au moins un niveau d'acces";
            return err;
        }else {
            err.status = true;
            err.msg = "oK";
            return err; //si c'est bon on retourne ok
        }
    }
}

void InterAddUser::on_btnValider_clicked(){

   //QMessageBox::information(this,"exemple","sa donne");
    struct ErrorManager *err = new ErrorManager(testFormulaire());//on teste le formulaire et retourne le resultat
    if(err->status == false){

        QMessageBox::warning(this,"Erreur formulaire",err->msg);
    }else{
        //on initialise la connexion a la base de données
        //qDebug()<< ui->lgnNom->text() << " depuis le ui";

        QString newUser = "newuser";
        QString pass = "password";

//        m_user = new Utilisateur(ui->lgnNom->text(),
//                                 ui->lgnPnom->text(),
//                                 newUser,
//                                 pass,
//                                 ui->lgnNivAcc->text(),
//                                 ui->lgnPost->text()); // on cree un utilisateur
        //std::cout << "L'utilisateur a ete cree"<< std::endl;

        //qDebug()<< m_user->getNom() << " depuis l'objet";
        //m_userMan = new UtilisateurManager();
        //serStruct m_user;
        UserStruct m_user;
        m_user.m_nom = ui->lgnNom->text();
        m_user.m_pnom = ui->lgnPnom->text();
        m_user.m_postOcc =  ui->lgnPost->text();
        m_user.m_loggin =  ui->lgnNom->text();
        m_user.m_pass = "password";
        m_user.m_nivAcc = ui->lgnNivAcc->text();


        if(m_userMan->addUser(m_user)){
            QMessageBox::information(this,"Enregitrement effectuer","L'utilisateur a ete ajouter avec succes");
            this->close();
        }else{
            QMessageBox::information(this,"Echec enregitrement","L'utilisateur n'a pas pu etre ajouter");
        }
        // et on ajoute l'utilisateur
    }
}

void InterAddUser::on_btnAnnul_clicked(){
    this->close();
}
