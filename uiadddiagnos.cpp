#include "uiadddiagnos.h"
#include "ui_uiadddiagnos.h"
#include <iostream>

UiAddDiagnos::UiAddDiagnos(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UiAddDiagnos)
{
    this->state = true; // c'est un nouveau dans ce cas
    ui->setupUi(this);
    this->setLayout(ui->layGen);

    // ici on doit prevoir l'ajout
    std::cout << "teste 2"<< std::endl;
     Patients::getListPatient(); // on initialise la liste ici
    //std::cout << Patients::listPatient.at(3).identity.toStdString() << std::endl;
    for(int i =0 ; i< Patients::listPatient.size(); i++){
        ui->cmbNom->addItem(Patients::listPatient.at(i).identity);//on charge les identite dans la liste ici
        //ici on charge la liste des nom et des prenom
    }
    //this->id_client = Patients::listPatient.at(0).id_p;
    //ici on selectionne le premier id
    //car c'est ce qui va s'afficher

    ui->date->setDate(QDate::currentDate());// on net la date a aujourd'hui

}

UiAddDiagnos::UiAddDiagnos(DiagnosStruct d,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UiAddDiagnos)
{
     this->state = false; // c'est une modification dans ce cas ci
    id = d.idDiag;
    std::cout << "constructeur 2"<< std::endl;
    ui->setupUi(this);
    this->setLayout(ui->layGen);

    // ici on doit prevoir l'ajout

     Patients::getListPatient(); // on initialise la liste ici
    //std::cout << Patients::listPatient.at(3).identity.toStdString() << std::endl;
    for(int i =0 ; i< Patients::listPatient.size(); i++){
        ui->cmbNom->addItem(Patients::listPatient.at(i).identity);//on charge les identite dans la liste ici
        //ici on charge la liste des nom et des prenom
    }
    //this->id_client = Patients::listPatient.at(0).id_p;
    //ici on selectionne le premier id
    //car c'est ce qui va s'afficher

    // on commence l'initialisation
    QString txt; int i;

    ui->date->setDate(d.date);
    //this->getIdentityById(&txt, &i);
    //ui->cmbNom->setItemText();
    ui->txtCorrection->setText(d.correction);
    ui->txtObsrvation->setText(d.observation);

}

UiAddDiagnos::~UiAddDiagnos()
{
    delete ui;
}

QString UiAddDiagnos::getIdentityById(int *id,QString *txt)//va prendre l'addresse en parametre
{
    //cette methode retourne le texte qui sera afficher sur le combobox
    //en prenant un id pour rechercher ce texte dans Patients::ListePatient
}

void UiAddDiagnos::on_btnValider_clicked()
{
    //le slot de validation
    //a ce niveau on a deja l'id

    //on recupere la date
    DiagnosStruct diagnostic;
    diagnostic.idClient = this->id_client;
    diagnostic.date = ui->date->date();
    diagnostic.idUser = Utilisateur::m_id; //on recuper l'id de l'utilisateur connecter
    diagnostic.observation = ui->txtObsrvation->toPlainText().replace("'","''");
    diagnostic.correction = ui->txtCorrection->toPlainText().replace("'","''");
    //on a fini d'hydrater le diagnostique

    //prevoire les insstructions pour enregistrer ici
    diag =new DiagnosticManager;
    ErrorManager err;
    if(this->state == true){//si c'est true il s'agit d'une insertion
        err = diag->addDiagnostic(diagnostic);
    }else{//sinon il s'agt d'une mise a jour
        err = diag->updateDiagnostic(diagnostic,this->id);
    }


    if(err.status == true){
        QMessageBox::information(this,"Succes",err.msg);
        this->close();
    }else{
        QMessageBox::warning(this,"Echec",err.msg+" \ncode [ "+err.msgTech+" ]");
        this->close();
    }

}

void UiAddDiagnos::on_cmbNom_currentIndexChanged(const QString &arg1)
{
    for(int i =0 ;  i < Patients::listPatient.size(); i++){
       // QString txt(list.at(i).nom+" "+list.at(i).prenom);
        /*
         * le principe on parcour la liste et on chercje le txt que l'user aurra selectionner
         * arg1 et on compare avec les info de la liste si c'est trouve on chioisit l'id
         * */
        if(Patients::listPatient.at(i).identity == arg1){
            this->id_client =Patients::listPatient.at(i).id_p; //on recupere l'id ici
        }
    }
}

void UiAddDiagnos::on_btnAddPatient_clicked()
{
    addPass = new UiAddPatient();
    addPass->show();
}

void UiAddDiagnos::on_btnRefreshCmb_clicked()
{
    Patients::getListPatient();
    ui->cmbNom->clear();
    //on met a jour la liste ici
    for(int i =0 ; i< Patients::listPatient.size(); i++){
        ui->cmbNom->addItem(Patients::listPatient.at(i).identity);//on charge les identite dans la liste ici
        //ici on charge la liste des nom et des prenom
    }
}

void UiAddDiagnos::on_cmbNom_activated(const QString &arg1)
{
    for(int i=0; i<Patients::listPatient.size();i++){
        if(Patients::listPatient.at(i).identity == arg1){
            this->id_client = Patients::listPatient.at(i).id_p;
        }

    }
}
