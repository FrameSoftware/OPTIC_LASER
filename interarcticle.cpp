#include "interarcticle.h"
#include "ui_interarcticle.h"
#include <iostream>
#include <QTimer>

/*
 * prevoir ici une dexieme toolbar pour les options d'affichage
 * */

InterArcticle::InterArcticle(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::InterArcticle){
  std::cout << "Chargement de la vue"<< std::endl;

  ui->setupUi(this);

  barFichier = addToolBar("Fichier");
  barList = addToolBar("list");

  //reche = new InterRecherche(this);

  btnActNewArcticle = new QPushButton("Ajouter articles");
  btnActNewArcticle->setToolTip("Ajouter un nouvel article de type non definie");

  btnAddVerre = new QPushButton("Ajouter verres");
  btnAddVerre->setToolTip("Ajouter des articles de type verre");

  btnAddMont = new QPushButton("Ajouter montures");
  btnAddMont->setToolTip("Ajouter des articles de type montures");

  btnAddNet = new QPushButton("Ajouter nettoyant");
  btnAddNet->setToolTip("Ajouter des articles de type nettoyant");

  btnActReload = new QPushButton("Rafraichir");
  btnActQuitter = new QPushButton("Quitter");

  btnActQuitter->setStyleSheet("background-color: #d43f3a");

  btnListDefault = new QPushButton("Liste par defaut");
  btnListVerre = new QPushButton("Liste de verre");
  btnListNet = new QPushButton("Liste de nettoyant");
  btnListMont = new QPushButton("Liste de montures");

  alert = new QLabel();


  barFichier->addWidget(btnActReload);
  barFichier->addSeparator();
  barFichier->addWidget(btnActNewArcticle);//ajouter un article non repertorié
  barFichier->addSeparator();
  barFichier->addWidget(btnAddMont);//bouton pour ajouter un monture
  barFichier->addSeparator();
  barFichier->addWidget(btnAddVerre);//ajout de verre
  barFichier->addSeparator();
  barFichier->addWidget(btnAddNet);//ajouter nettoyan
  barFichier->addSeparator();
  barFichier->addWidget(btnActQuitter);

  barList->addWidget(btnListDefault);
  barList->addSeparator();
  barList->addWidget(btnListVerre);
  barList->addSeparator();
  barList->addWidget(btnListMont);
  barList->addSeparator();
  barList->addWidget(btnListNet);

  ui->centralwidget->setLayout(ui->layGen);
  this->setCentralWidget(ui->centralwidget);
  this->setWindowTitle("Module Arcticle");


  model = new QSqlTableModel(this,this->bd);
  model->setTable("Article_fournisseur");
  model->setEditStrategy(QSqlTableModel::OnFieldChange);

  if(model->select()){
      std::cout << model->lastError().text().toStdString()<< std::endl;
  }

  model->setHeaderData(0,Qt::Horizontal,"N° Arcticle");
  model->setHeaderData(1,Qt::Horizontal,"Nom de l'artice ");
  model->setHeaderData(2,Qt::Horizontal,"Nombre");
  model->setHeaderData(3,Qt::Horizontal,"Nom du fournisseur");
  model->setHeaderData(4,Qt::Horizontal,"Date de livraison");
  model->setHeaderData(5,Qt::Horizontal,"Information supplementaires");



  this->ui->tableView->setModel(this->model);
  this->ui->tableView->setSortingEnabled(true);
  this->ui->tableView->setGridStyle(Qt::DashLine);
  this->ui->tableView->horizontalHeader()->setStretchLastSection(true);
  this->ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
  this->ui->tableView->resizeColumnsToContents();


// tmp = new QTimer(this);
// connect(tmp,SIGNAL(timeout()),this,SLOT(reload()));
//  tmp->start(60000); //on attent 60 seconde avant de rafraichir

  connect(btnActReload,SIGNAL(clicked()),this,SLOT(reload()));
  connect(btnActQuitter,SIGNAL(clicked()),this,SLOT(close()));
  connect(ui->tableView,SIGNAL(clicked(QModelIndex)),this,SLOT(affcihIndex(QModelIndex)));
  connect(btnActNewArcticle,SIGNAL(clicked()),this,SLOT(addArticles()));

  connect(btnAddVerre,SIGNAL(clicked()),this,SLOT(addVerres()));
  connect(btnAddMont,SIGNAL(clicked()),this,SLOT(addMont()));
  connect(btnAddNet,SIGNAL(clicked()),this, SLOT(addNet()));

  //les connexion de la deuxieme toolbar

  connect(btnListDefault,SIGNAL(clicked()),this,SLOT(affich_list_default()));
  connect(btnListMont,SIGNAL(clicked()),this,SLOT(affich_list_mont()));
  connect(btnListNet,SIGNAL(clicked()),this,SLOT(affich_list_net()));
  connect(btnListVerre,SIGNAL(clicked()),this,SLOT(affich_list_verre()));
}

InterArcticle::~InterArcticle(){
    this->tmp->stop();
  delete ui;
    delete this;
}

void InterArcticle::getListArcticle(){

}


void InterArcticle::reload(){//le slot qui se charge de recharger le tableView
    //this->model->clear();

    if(this->model->select()){//si on reussit a refaire la selection
        std::cout << "Selection a retourner true" << std::endl;
        this->ui->btnDetailA->setEnabled(false);
        this->ui->btnDetailF->setEnabled(false);
        this->ui->btnModif->setEnabled(false);
        this->ui->btnSupp->setEnabled(false);
       //alert->setText(" ");
        statusBar()->showMessage(" ");
    }else{
        std::cout << "Selection a retourner false" << std::endl;
    }
    //this->ui->tableView->setModel(this->model);

    //std::cout << model->data(new QModelIndex()) ; << std::endl;
}

void InterArcticle::affcihIndex(QModelIndex index){

    if(index.column() != 0){
        std::cout << "la colone est differente de zero" <<std::endl;
        //alert->setText("NOTE: vous devez choisir la colonne N° article pour selectionner un article");
       // alert->setStyleSheet("color : red");

        statusBar()->showMessage("NOTE: vous devez choisir la colonne N° article pour selectionner un article");

        this->ui->btnDetailA->setEnabled(false);
        this->ui->btnDetailF->setEnabled(false);
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
        statusBar()->showMessage("Article : ["+ index.data().toString()+ " ] selectionné");

        this->ui->btnDetailA->setEnabled(true);
        this->ui->btnDetailF->setEnabled(true);
        this->ui->btnModif->setEnabled(true);
        this->ui->btnSupp->setEnabled(true);
    }
}

void InterArcticle::on_btnSupp_clicked(){
    int res = QMessageBox::critical(this,"Confirmation","Etes-vous sur de vouloir supprimer cet article ?",QMessageBox::Yes  | QMessageBox::No);
    if(res != QMessageBox::Yes)
        return;

    ArticleManager art;
    ErrorManager err;
    err = art.deleteArticle(this->element);
    if(err.status == true){
        QMessageBox::information(this,"Succes",err.msg);
    }else{
        QMessageBox::warning(this,"Echec",err.msg+" "+err.msgTech);
    }
}

void InterArcticle::addArticles(){

    addArt = new InterAddArticle();
    std::cout << "Add article"<< element <<std::endl;
    addArt->show();
    addArt->setWindowModality(Qt::WindowModal);
}

void InterArcticle::addVerres(){
    addVer = new InterAddVerre;
    addVer->show();
    addVer->setWindowModality(Qt::WindowModal);
}
void InterArcticle::addMont(){
    addMontt = new InterAddMont;
    addMontt->show();
    addMontt->setWindowModality(Qt::WindowModal);
}

void InterArcticle::addNet(){
    addNett = new InterAddNettoy;
    addNett->show();
    addNett->setWindowModality(Qt::WindowModal);
}

void InterArcticle::affich_list_default(){
    model->setTable("Article_fournisseur");
    model->setEditStrategy(QSqlTableModel::OnFieldChange);

    if(model->select()){
        std::cout << model->lastError().text().toStdString()<< std::endl;
    }

    model->setHeaderData(0,Qt::Horizontal,"N° Arcticle");
    model->setHeaderData(1,Qt::Horizontal,"Nom de l'artice ");
    model->setHeaderData(2,Qt::Horizontal,"Nombre");
    model->setHeaderData(3,Qt::Horizontal,"Nom du fournisseur");
    model->setHeaderData(4,Qt::Horizontal,"Date de livraison");
    model->setHeaderData(5,Qt::Horizontal,"Information supplementaires");

    std::cout << "Chargement de la vue"<< std::endl;

    this->ui->tableView->setModel(this->model);
//    this->ui->tableView->setSortingEnabled(true);
//    this->ui->tableView->setGridStyle(Qt::DashLine);
//    this->ui->tableView->horizontalHeader()->setStretchLastSection(true);
//    this->ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
//    this->ui->tableView->resizeColumnsToContents();
}

void InterArcticle::affich_list_mont(){//la liste pour les montures
    model->setTable("article_monture");
    model->setEditStrategy(QSqlTableModel::OnFieldChange);

    if(model->select()){
        std::cout << model->lastError().text().toStdString()<< std::endl;
    }

//    model->setHeaderData(0,Qt::Horizontal,"N° Arcticle");
//    model->setHeaderData(1,Qt::Horizontal,"Nom de l'artice ");
//    model->setHeaderData(2,Qt::Horizontal,"Nombre");
//    model->setHeaderData(3,Qt::Horizontal,"Nom du fournisseur");
//    model->setHeaderData(4,Qt::Horizontal,"Date de livraison");
//    model->setHeaderData(5,Qt::Horizontal,"Information supplementaires");

    //std::cout << "Chargement de la vue"<< std::endl;

    this->ui->tableView->setModel(this->model);
//    this->ui->tableView->setSortingEnabled(true);
//    this->ui->tableView->setGridStyle(Qt::DashLine);
//    this->ui->tableView->horizontalHeader()->setStretchLastSection(true);
//    this->ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
//    this->ui->tableView->resizeColumnsToContents();
}

void InterArcticle::affich_list_verre(){
    model->setTable("article_verre");
    model->setEditStrategy(QSqlTableModel::OnFieldChange);

    if(model->select()){
        std::cout << model->lastError().text().toStdString()<< std::endl;
    }

//    model->setHeaderData(0,Qt::Horizontal,"N° Arcticle");
//    model->setHeaderData(1,Qt::Horizontal,"Nom de l'artice ");
//    model->setHeaderData(2,Qt::Horizontal,"Nombre");
//    model->setHeaderData(3,Qt::Horizontal,"Nom du fournisseur");
//    model->setHeaderData(4,Qt::Horizontal,"Date de livraison");
//    model->setHeaderData(5,Qt::Horizontal,"Information supplementaires");

//    std::cout << "Chargement de la vue"<< std::endl;

    this->ui->tableView->setModel(this->model);
//    this->ui->tableView->setSortingEnabled(true);
//    this->ui->tableView->setGridStyle(Qt::DashLine);
//    this->ui->tableView->horizontalHeader()->setStretchLastSection(true);
//    this->ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
//    this->ui->tableView->resizeColumnsToContents();
}

void InterArcticle::affich_list_net(){
    model->setTable("article_nettoyant");
    model->setEditStrategy(QSqlTableModel::OnFieldChange);

    if(model->select()){
        std::cout << model->lastError().text().toStdString()<< std::endl;
    }

//    model->setHeaderData(0,Qt::Horizontal,"N° Arcticle");
//    model->setHeaderData(1,Qt::Horizontal,"Nom de l'artice ");
//    model->setHeaderData(2,Qt::Horizontal,"Nombre");
//    model->setHeaderData(3,Qt::Horizontal,"Nom du fournisseur");
//    model->setHeaderData(4,Qt::Horizontal,"Date de livraison");
//    model->setHeaderData(5,Qt::Horizontal,"Information supplementaires");

//    std::cout << "Chargement de la vue"<< std::endl;

    this->ui->tableView->setModel(this->model);
//    this->ui->tableView->setSortingEnabled(true);
//    this->ui->tableView->setGridStyle(Qt::DashLine);
//    this->ui->tableView->horizontalHeader()->setStretchLastSection(true);
//    this->ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
//    this->ui->tableView->resizeColumnsToContents();
}




