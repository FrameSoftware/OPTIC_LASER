#include "uificheclient.h"
#include "ui_uificheclient.h"
#include <QMessageBox>
#include <QDebug>
#include <QSqlQueryModel>
#include <QList>

UiFicheClient::UiFicheClient(int id_client,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UiFicheClient),
    m_id_client(id_client)
{
    ui->setupUi(this);
    //on commance d'abord par recuperer le patient
    m_patientManager = new Patients();
    m_patient = m_patientManager->getPatientById(this->m_id_client);

    //on a la les detail du patient on commence la recuperation des operation
    requet = new QSqlQuery();
    //on selectionne les données pour le model d'achat
//    requet->prepare("select idFacture , type_operation , date_operation from operation_achat where idClient = :id_cli");
//    requet->bindValue(":id_cli",this->m_id_client);

    if(!requet->exec("select idFacture , type_operation , date_operation from operation_achat where idClient ="+QString::number(this->m_id_client))){
       QMessageBox::warning(0,"Erreur 1",requet->lastQuery());
       return;
    }

    int i = requet->record().count(), cpteur(0);

    QStringList head_achat;
    head_achat << "Facture No"<< "Type d'operation"<< "Date d'achat";

    qDebug()<< i << "  liste achat";

    model_achat = new QStandardItemModel(i,2);
    model_achat->setHorizontalHeaderLabels(head_achat);


    while(cpteur<= i && requet->next()){
        qDebug() << cpteur<<" dans la boucle pour achat";
        model_achat->setItem(cpteur,0,new QStandardItem(requet->value(0).toString()));
        model_achat->setItem(cpteur,1,new QStandardItem(requet->value(1).toString()));
        model_achat->setItem(cpteur,2,new QStandardItem(requet->value(2).toString()));

        cpteur++;
    }
    std::cout << "------------ boucle sur les achat operation -------------------"<< std::endl;
    //le model pour les achat est maintenant pret

    cpteur = 0;

//    requet->prepare("select idDiagnostic , type_operation , date_operation from operation_diagnostic where idClient = :id_cli");
//    requet->bindValue(":id_cli",this->m_id_client);
//    requet->exec();




    QStringList head_diag;
    head_diag << "Diagnostique No"<< "Type d'operation"<<"Date operation";

    if(!requet->exec("select idDiagnostic , type_operation , date_operation from operation_diagnostic where idClient = "+QString::number(this->m_id_client))){
           QMessageBox::warning(0,"Erreur 2",requet->lastQuery());
           return;
     }

    int j = requet->record().count();//taille de la liste de diagnostic
    qDebug()<< j<< "  liste diagnostique";

    model_diagnostique = new QStandardItemModel(j, 2);
    model_diagnostique->setHorizontalHeaderLabels(head_diag);
    while(/*cpteur<= j &&*/ requet->next()){
       QList<QStandardItem *> lst;
        lst<< new QStandardItem(requet->value(0).toString()) << new QStandardItem(requet->value(1).toString()) <<new QStandardItem(requet->value(2).toString());
        //model_diagnostique->appendRow(QList<>);
//        model_diagnostique->setItem(cpteur,0,new QStandardItem(requet->value(0).toString()));
//        model_diagnostique->setItem(cpteur,1,new QStandardItem(requet->value(1).toString()));
//        model_diagnostique->setItem(cpteur,2,new QStandardItem(requet->value(2).toString()));
        model_diagnostique->appendRow(lst);

    }
    std::cout << "------------ boucle sur les diagnostiques operation -------------------"<< std::endl;
    //ici tout est finit

    ui->lgnNom->setText(m_patient.nom);
    ui->lgnPrenom->setText(m_patient.prenom);
    ui->lgnSex->setText(m_patient.sexe);
    ui->txtDetails->setText(m_patient.info_supp);
    ui->dateNaiss->setDate(m_patient.dateNaiss);




    ui->tableView_achat->setModel(model_achat);
    ui->tableView_diag->setModel(model_diagnostique);

    this->ui->tableView_achat->setSortingEnabled(true);
    this->ui->tableView_achat->setGridStyle(Qt::DashLine);
    this->ui->tableView_achat->horizontalHeader()->setStretchLastSection(true);
    this->ui->tableView_achat->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->ui->tableView_achat->resizeColumnsToContents();
    //this->ui->tableView_achat->setAlternatingRowColors(true);

    this->ui->tableView_diag->setSortingEnabled(true);
    this->ui->tableView_diag->setGridStyle(Qt::DashLine);
    this->ui->tableView_diag->horizontalHeader()->setStretchLastSection(true);
    this->ui->tableView_diag->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->ui->tableView_diag->resizeColumnsToContents();
}

UiFicheClient::~UiFicheClient()
{
    delete ui;
}
