#include "uiaddpatient.h"

#include <iostream>
#include "ui_uiaddpatient.h"

UiAddPatient::UiAddPatient(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UiAddPatient)
{
    ui->setupUi(this);//celui ce sert a l'ajout normal
    this->modif = false;

    this->setLayout(ui->layGen);
    this->setWindowTitle("Ajout d'un patient");
}

UiAddPatient::UiAddPatient(PatientStruct patient,int id, QWidget *parent) :
    QWidget(parent),id(id),
    ui(new Ui::UiAddPatient)
{

    ui->setupUi(this);
    ui->label->setText("Modification");
    this->setWindowTitle("Modification");

    //std::cout << patient.id << " l'ID" <<  std::endl;

    this->modif = true; // ce constructeur sert la modification
    ui->lgnNom->setText(patient.nom);
    ui->lgnPrenom->setText(patient.prenom);
    ui->txt->setPlainText(patient.info_supp);
    ui->dateNais->setDate(patient.dateNaiss);
    ui->cmbSex->setCurrentText(patient.sexe);

    //ici l'initialisation est terminer



    this->setLayout(ui->layGen);
}

void UiAddPatient::on_btnValider_clicked(){
    if(!ui->lgnNom->text().isEmpty()){
        PatientStruct patient;
        patient.nom = ui->lgnNom->text().replace("'","''");
        patient.prenom = ui->lgnPrenom->text().replace("'","''");
        patient.dateNaiss = ui->dateNais->date();
        patient.sexe = ui->cmbSex->currentText();
        patient.info_supp = ui->txt->document()->toPlainText().replace("'","''");

        std::cout <<id << " l'ID" <<  std::endl;
        ErrorManager err;
        Patients p;
        if(this->modif==false){//si on ajoute
            err = p.addPatient(patient); // ici on ajoute plutot
        }else{//sinon
            err = p.updatePatient(patient,this->id);//ici on lance la misz a jour
        }
        if(err.status== true){
            QMessageBox::information(this,"Succes",err.msg);
            this->close();
        }else{
            QMessageBox::warning(this,"Erreur",err.msg+" <br/>code ["+err.msgTech+" ]");
            this->close();
        }
    }else{
        QMessageBox::warning(this,"Erreur formulaire","Erreur le nom au moins doit etre reseigne");
    }
}

UiAddPatient::~UiAddPatient()
{
    delete ui;
}

void UiAddPatient::on_btnAnnul_clicked()
{
    this->close();
}
