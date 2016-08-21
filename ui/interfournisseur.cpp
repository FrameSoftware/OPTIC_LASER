#include "interfournisseur.h"
#include "ui_interfournisseur.h"

InterFournisseur::InterFournisseur(QMainWindow *parent) :
    QMainWindow(parent),
    ui(new Ui::InterFournisseur)
{
    ui->setupUi(this);
   // initDB();

    barFichier = addToolBar("fichier");


    btnActNewFour = new QPushButton(/*QIcon("C:/Users/SIMO/Pictures/ajouter_eleve.png"),*/"Nouveau fournisseur");
    btnActReload = new QPushButton("Rafraichir");
    btnActQuitter = new QPushButton("Quitter");

    barFichier->addWidget(btnActNewFour);
    barFichier->addSeparator();
    barFichier->addWidget(btnActReload);
    barFichier->addSeparator();
    barFichier->addWidget(btnActQuitter);
//    barFichier->addSeparator();
    //barFichier->addWidget(alert);

    ui->centralwidget->setLayout(ui->layGen);
    this->setCentralWidget(ui->centralwidget);
    this->setWindowTitle("Fournisseur");

    std::cout << "Creation du model "<< std::endl;
    model=new QSqlTableModel();
    model->setTable("fournisseur");
    model->setSort(0,Qt::DescendingOrder);
    //model->setQuery(QSqlQuery("select idfournisseur, nom, ville, matriculeFour ,nbrFournisture from fournisseur"));
    //model->setEditStrategy(QSqlTableModel::OnFieldChange);

    if(!model->select()){
        std::cout << model->lastError().text().toStdString()<< std::endl;
    }

    model->setHeaderData(0,Qt::Horizontal,"Numero");
    model->setHeaderData(1,Qt::Horizontal,"Nom du fournisseur ");
    model->setHeaderData(2,Qt::Horizontal,"Ville");
    model->setHeaderData(3,Qt::Horizontal,"Matricule");
    model->setHeaderData(4,Qt::Horizontal,"Informations supplementaires");

    this->ui->tableView->setModel(this->model);
    this->ui->tableView->setColumnHidden(5,true);
    this->ui->tableView->setSortingEnabled(true);
    this->ui->tableView->setGridStyle(Qt::DashLine);
    this->ui->tableView->horizontalHeader()->setStretchLastSection(true);
    this->ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->ui->tableView->resizeColumnsToContents();
    this->ui->tableView->setAlternatingRowColors(true);

    //std::cout<< "Demarage du timer"<< std::endl;
//    tmp = new QTimer(this);
//    connect(tmp,SIGNAL(timeout()),this,SLOT(reload()));
//     tmp->start(60000); //on attent 60 seconde avant de rafraichir
     /*
      * on grise les bouttons pour ne pas les cliquer
      * */
     this->ui->btnDetails->setEnabled(false);
     this->ui->btnModif->setEnabled(false);
     this->ui->btnSupp->setEnabled(false);

     //std::cout<< "connection"<< std::endl;
     connect(btnActReload,SIGNAL(clicked()),this,SLOT(reload()));
     connect(btnActQuitter,SIGNAL(clicked()),this,SLOT(close()));
     connect(ui->tableView,SIGNAL(clicked(QModelIndex)),this,SLOT(affcihIndex(QModelIndex)));
     connect(this->btnActNewFour,SIGNAL(clicked()),this,SLOT(affichAddFour()));

     setWindowModality(Qt::WindowModal);
}



InterFournisseur::~InterFournisseur()
{
    delete ui;
}

void InterFournisseur::initDB(){
    QSqlDatabase  bd = QSqlDatabase::addDatabase("QMYSQL");
    bd.setHostName("localhost");
    bd.setDatabaseName("optic_plus");
    bd.setUserName("root");
    bd.setPassword("");

    if(bd.open()){
//    QMessageBox::warning(this,"Erreur de connexion a la base de donnée", " <strong>Message :</strong>"+err);
       // std::cout << "ouverture"<<std::endl;
        this->bd = bd;
    }else{
        errMsg = new QString(bd.lastError().text());
    }
}

void InterFournisseur::reload(){
   // initDB();
    if(this->model->select()){//si on reussit a refaire la selection
        std::cout << "Selection a retourner true" << std::endl;
        this->ui->btnDetails->setEnabled(false);
        this->ui->btnModif->setEnabled(false);
        this->ui->btnSupp->setEnabled(false);
        ui->statusbar->setStyleSheet("color: black");
        this->ui->statusbar->showMessage("Rafraichissement reussit");
         //alert->setText(" ");
    }else{
        std::cout << "Selection a retourner false" << std::endl;
    }
}

void InterFournisseur::affcihIndex(QModelIndex index){

    if(index.column() != 0){
//        std::cout << "la colone est differente de zero" <<std::endl;
//        alert->setText("NOTE: vous devez choisir la colonne N° article pour selectionner un article");
//        alert->setStyleSheet("color : red");
        ui->statusbar->showMessage("NOTE: vous devez choisir la colonne Numero pour selectionner un fournisseur");
        ui->statusbar->setStyleSheet("color:red");
        this->ui->btnDetails->setEnabled(false);
        this->ui->btnModif->setEnabled(false);
        this->ui->btnSupp->setEnabled(false);
        //this->ui->btnSupp->setEnabled(false);
    }else{
        /*
         * si il a bien cliquer on lui montre le msg et on active les boutons
         * */
        this->select = index.data().toInt();
        //std::cout << index.data().toString().toStdString() << std::endl;
        //alert->setText("Article : ["+ index.data().toString()+ " ]selectionné");
         ui->statusbar->showMessage("Article : ["+ index.data().toString()+ " ]selectionné");
         ui->statusbar->setStyleSheet("color: blue");
         ui->btnDetails->setEnabled(true);
         ui->btnModif->setEnabled(true);
         ui->btnSupp->setEnabled(true);
         //ui->btnSupp->setEnabled(true);

    }
}

void InterFournisseur::affichAddFour(){
    std::cout << "an ajoute le fournisseur" << std::endl;
    addFour = new InterAddFournisseur();
    addFour->show();
}

void InterFournisseur::closeEvent(QCloseEvent *evt){
    //this->tmp->stop();
    //qDebug() << "fermeture";
    evt->accept();
}

void InterFournisseur::on_btnDetails_clicked(){
    //affichage des details
    QString details;
    four_man = new FournisseurManager();
    //four_man->getFournisseurById(this->select);
   //Fournisseur  fournisseur(four_man->getFournisseurById(select));
    //fournisseur.dump();
    FournisseurStruct fournisseur = four_man->getFournisseurById(select);
    //fournisseur->dump();
    details = "<strong>Nom : </strong>"+fournisseur.nom+"<br/>"+//creation du message
            "<strong>Ville : </strong>"+fournisseur.ville+ "<br/>"+
            "<strong>Matricule : </strong>"+fournisseur.matricule +"<br/>"+
            "<strong>Informations supplementaires: </strong><br/>"+fournisseur.info_supp+".";

    QMessageBox::information(this,"Detail de fournisseur",details,QMessageBox::Ok);
}

void InterFournisseur::on_btnModif_clicked(){
    FournisseurStruct  fournisseur = four_man->getFournisseurById(select);//on selectionne le fournisseur
    addFour = new InterAddFournisseur( select,fournisseur.nom,fournisseur.ville,fournisseur.info_supp,this);
    addFour->show();

}

void InterFournisseur::on_btnSupp_clicked(){//le slot de
    int res = QMessageBox::critical(this,"Confirmation","Etes-vous sur de vouloir supprimer ce fournisseur ?",QMessageBox::Yes  | QMessageBox::No);
    if(res != QMessageBox::Yes)
        return;


    four_man = new FournisseurManager();
    ErrorManager err = four_man->deleteFrournisseurById(select);
    if(err.status == true){
        QMessageBox::information(this,"Succes",err.msg);
    }else{
        QMessageBox::warning(this,"Echec",err.msg+" "+err.msgTech);
    }
}
