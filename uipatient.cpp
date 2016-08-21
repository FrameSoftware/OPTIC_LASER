#include "uipatient.h"
#include "ui_uipatient.h"

UiPatient::UiPatient(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UiPatient)
{
    ui->setupUi(this);

    setWindowTitle("Module patient");
    ui->centralwidget->setLayout(ui->layGen);
    this->setCentralWidget(ui->centralwidget);

    //on parametre les boutons
    barOutil = addToolBar("Fichier");

    btnQuit = new QPushButton("Quitter");
    btnRefresh = new QPushButton("Rafraichir");
    btnNew = new QPushButton("Nouveau ...");

    //quit = new QAction("Quitter");
  //  refresh = new QAction("Rafraicir");

    //on cree dabord la bar d'outils

    barOutil->addWidget(btnQuit);
    barOutil->addSeparator();
    barOutil->addWidget(btnRefresh);
    barOutil->addSeparator();
    barOutil->addWidget(btnNew);

    model = new QSqlTableModel();
    model->setTable("clients");//la table qui contient la liste des patients ils doivent etre a ppele patient dans ce
    //module

    if(model->select()){
        ui->tableView->setModel(model);

        model->setHeaderData(0,Qt::Horizontal,"Numero");
        model->setHeaderData(1,Qt::Horizontal,"Nom du patient ");
        model->setHeaderData(2,Qt::Horizontal,"Prenom");
        model->setHeaderData(3,Qt::Horizontal,"Date de naissance");
        model->setHeaderData(4,Qt::Horizontal,"Sexe");
        model->setHeaderData(5,Qt::Horizontal,"Information supplementaires");

        this->ui->tableView->setModel(this->model);
        //this->ui->tableView->setColumnHidden(5,true);
        this->ui->tableView->setSortingEnabled(true);
        this->ui->tableView->setGridStyle(Qt::DashLine);
        this->ui->tableView->horizontalHeader()->setStretchLastSection(true);
        this->ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
        this->ui->tableView->resizeColumnsToContents();
        this->ui->tableView->setAlternatingRowColors(true);

//        tmp = new QTimer(this);
//        connect(tmp,SIGNAL(timeout()),this,SLOT(reload()));
//         tmp->start(60000); //on attent 60 seconde avant de rafraichir

         ui->btnFiche->setEnabled(false);
         ui->btnModif->setEnabled(false);
         ui->btnSupp->setEnabled(false);
         //on a desactiver les boutons

         connect(btnQuit,SIGNAL(clicked()),this,SLOT(close()));
         connect(btnRefresh,SIGNAL(clicked()),this,SLOT(reload()));
         connect(ui->tableView,SIGNAL(clicked(QModelIndex)),this,SLOT(affichIndex(QModelIndex)));
         connect(btnNew,SIGNAL(clicked()),this,SLOT(addPatient()));
         //connect()

    }else{
        std::cout << "Erreur ici" <<model->lastError().text().toStdString()<< std::endl;
    }
}

UiPatient::~UiPatient()
{
    delete ui;
}


void UiPatient::affichIndex(QModelIndex index){

    if(index.column() != 0){
        std::cout << "la colone est differente de zero" <<std::endl;
        //alert->setText("NOTE: vous devez choisir la colonne N° article pour selectionner un article");
       // alert->setStyleSheet("color : red");

        statusBar()->showMessage("NOTE: vous devez choisir la colonne Numero pour selectionner un patient");

        this->ui->btnFiche->setEnabled(false);
        this->ui->btnModif->setEnabled(false);
        this->ui->btnSupp->setEnabled(false);
    }else{
        /*
         * si il a bien cliquer on lui montre le msg et on active les boutons
         * */
        std::cout << index.data().toString().toStdString() << std::endl;
        //alert->setText("Article : ["+ index.data().toString()+ " ]selectionné");
        this->element =  index.data().toInt();
        //alert->setStyleSheet("color : blue");
        statusBar()->showMessage("Patient : ["+ index.data().toString()+ " ] selectionné");

        this->ui->btnFiche->setEnabled(true);
        this->ui->btnModif->setEnabled(true);
        this->ui->btnSupp->setEnabled(true);
    }
}

void UiPatient::reload(){
    if(this->model->select()){//si on reussit a refaire la selection
        //std::cout << "Selection a retourner true" << std::endl;
        this->ui->btnFiche->setEnabled(false);
        this->ui->btnSupp->setEnabled(false);
        this->ui->btnModif->setEnabled(false);
        //this->ui->btnSupp->setEnabled(false);
       //alert->setText(" ");
        statusBar()->showMessage(" ");
    }else{
        std::cout << "Selection a retourner false" << std::endl;
    }
}

void UiPatient::addPatient(){//ajout
    adpatient = new UiAddPatient;
    adpatient->show();
}

void UiPatient::on_btnModif_clicked(){//modification
    PatientStruct  p ;
    Patients pm;
    std::cout << element<<std::endl;
    p = pm.getPatientById(this->element);
    if(p.status == true){
        //std::cout <<"avant l'instance"<< p.id<<  std::endl;
        adpatient = new UiAddPatient(p,this->element);
        adpatient->show();
    }else{
        QMessageBox::warning(this,"Erreur","Impossible de selectionner le patient");
    }
}


void UiPatient::on_btnSupp_clicked()
{
    int res = QMessageBox::critical(this,"Confirmation","Etes-vous sur de vouloir supprimer ce patient ?",QMessageBox::Yes  | QMessageBox::No);
    if(res != QMessageBox::Yes)
        return;

   Patients  art;
    ErrorManager err;
    err = art.deletePatient(this->element);
    if(err.status == true){
        QMessageBox::information(this,"Succes",err.msg);
    }else{
        QMessageBox::warning(this,"Echec",err.msg+" "+err.msgTech);
    }
}

void UiPatient::on_btnFiche_clicked()
{
    fiche_client = new UiFicheClient(this->element);
    fiche_client->show();
}
