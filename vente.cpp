#include "vente.h"
#include "ui_vente.h"

#include "internewvente.h"

Vente::Vente(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::Vente)
{
  ui->setupUi(this);

  this->setWindowTitle("Module vente");
  ui->centralwidget->setLayout(ui->layver);



  btnReload = new QPushButton("Rafraichir");
  btnActNew = new QPushButton("nouvelle vente");
  btnQuit = new QPushButton("Quitter");

  bare = addToolBar("Fichier");

  bare->addWidget(btnReload);
  bare->addSeparator();
  bare->addWidget(btnActNew);
  bare->addSeparator();
  bare->addWidget(btnQuit);

  connect(btnActNew,SIGNAL(clicked()),this,SLOT(affichInterVente()));
  //initialisation des données
  QStringList header;
  header << "Numeros" << "Date de realisation"<<"Nom achetteur"<<"Nom vendeur";

  model=new QSqlTableModel();
  model->setTable("view_facture");
  model->setSort(0,Qt::DescendingOrder);
  //model->setQuery(QSqlQuery("select idfournisseur, nom, ville, matriculeFour ,nbrFournisture from fournisseur"));
  //model->setEditStrategy(QSqlTableModel::OnFieldChange);

  if(!model->select()){
      std::cout << model->lastError().text().toStdString()<< std::endl;
  }


  this->ui->tableView->setModel(this->model);
  this->ui->tableView->setSortingEnabled(true);
  this->ui->tableView->setGridStyle(Qt::DashLine);
  this->ui->tableView->horizontalHeader()->setStretchLastSection(true);
  this->ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
  this->ui->tableView->resizeColumnsToContents();
  this->ui->tableView->setAlternatingRowColors(true);

  connect(btnQuit,SIGNAL(clicked()),this,SLOT(close()));
  connect(btnReload,SIGNAL(clicked()),this,SLOT(reload()));
  connect(ui->tableView,SIGNAL(clicked(QModelIndex)),this,SLOT(affcihIndex(QModelIndex)));

}

Vente::~Vente()
{
  delete ui;
}
void Vente::affichInterVente(){
  interVente = new interNewVente(this);
  interVente->show();
}

void Vente::reload(){
    if(!model->select()){
        QMessageBox::warning(this,"Probleme","Impossible de refraichir la page");
    }
}

void Vente::on_btnDetailCli_clicked()
{
    //ici on va recuepre la l'id de la facture et commence la recuperation des info du clients
    Patients patientManage;
    FactureManager factMan;
    int id_client = factMan.getIdClientFromIdFacture(this->select);

    if(id_client<= 0){
        QMessageBox::warning(this,"Erreur","Echec lors de la recuperation des données du patient code [ "+QString::number(id_client)+" ]");
        return;
    }

    fiche_cli_details = new UiFicheClient(id_client);
    fiche_cli_details->show();
}

void Vente::affcihIndex(QModelIndex index){

    if(index.column() != 0){
//        std::cout << "la colone est differente de zero" <<std::endl;
//        alert->setText("NOTE: vous devez choisir la colonne N° article pour selectionner un article");
//        alert->setStyleSheet("color : red");
        ui->statusBar->showMessage("NOTE: vous devez choisir la colonne Numero pour selectionner une facture");
        ui->statusBar->setStyleSheet("color:red");
        this->ui->btnDetailCli->setEnabled(false);
        this->ui->btnModif->setEnabled(false);
        ui->btnDetailFact->setEnabled(false);
        ui->btnSupp->setEnabled(false);
        //this->ui->btnSupp->setEnabled(false);
    }else{
        /*
         * si il a bien cliquer on lui montre le msg et on active les boutons
         * */
        this->select = index.data().toInt();
        //std::cout << index.data().toString().toStdString() << std::endl;
        //alert->setText("Article : ["+ index.data().toString()+ " ]selectionné");
         ui->statusBar->showMessage("Facture : ["+ index.data().toString()+ " ]selectionné");
         ui->statusBar->setStyleSheet("color: blue");
         this->ui->btnDetailCli->setEnabled(true);
         this->ui->btnModif->setEnabled(true);
         ui->btnDetailFact->setEnabled(true);
         ui->btnSupp->setEnabled(true);
         //ui->btnSupp->setEnabled(true);

    }
}

void Vente::on_btnDetailFact_clicked()
{
//    FactureManager fm;
//    //ici on va recupere les infos de la facture et les afficher
//    FactureStruct facture;
//    //facture = fm.getFactureById(this->select);
//    facture = fm.getFactureById(this->select);

}

void Vente::on_btnSupp_clicked()
{
    int res = QMessageBox::critical(this,"Confirmation","Etes-vous sur de vouloir supprimer cette facture?",QMessageBox::Yes  | QMessageBox::No);
    if(res != QMessageBox::Yes)
        return;

    FactureManager art;
    ErrorManager err;
    err = art.deleteFacture(this->select);
    if(err.status == true){
        QMessageBox::information(this,"Succes",err.msg);
    }else{
        QMessageBox::warning(this,"Echec",err.msg+" "+err.msgTech);
    }
}
