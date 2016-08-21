#include <QDebug>
#include <QSqlQuery>
#include "interparam.h"
#include "ui_interparam.h"


InterParam::InterParam(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::InterParam)
{
    ui->setupUi(this);

//    ui->centralwidget->setLayout(ui->layGen);
//    ui->tabUser->setLayout(ui->layVer);
    ui->centralwidget->setLayout(ui->layGen);
    this->setCentralWidget(ui->centralwidget);
    //setFixedSize(753,433);
    setWindowTitle("Parametres");
    setWindowModality(Qt::WindowModal);
    barFich = addToolBar("BareFichier");
    btnActQuit  = new QPushButton("Retour");
    btnReload = new QPushButton("Recharger");

    barFich->addWidget(btnActQuit);
    barFich->addWidget(btnReload);


    listeEntete << "Nom"<< "Prenom"<<"loggin"<<"Niveau d'acces"<<"Poste occupée";

    model = new QSqlTableModel();
    model->setTable("view_utilisateur");
   // model->setQuery(QSqlQuery("select idutilisateur,nom,prenom,nivAcc,poste  from utilisateur order by idUtilisateur ASC"));
   model->setSort(0,Qt::AscendingOrder);

    if(!model->select())
        qDebug()<< model->lastError().text();

    model->setHeaderData(0,Qt::Horizontal,"Numero");
    model->setHeaderData(1,Qt::Horizontal,"Nom de l'utilisateur ");
    model->setHeaderData(2,Qt::Horizontal,"prenom");
    model->setHeaderData(3,Qt::Horizontal,"Niveau d'accès");
    model->setHeaderData(4,Qt::Horizontal,"Poste occupé");
    //model->setHorizontalHeaderLabels(listeEntete);

    this->ui->tableList->setModel(this->model);

    this->ui->tableList->setSortingEnabled(true);
    ui->tableList->setGridStyle(Qt::DashLine);
    ui->tableList->horizontalHeader()->setStretchLastSection(true);
    this->ui->tableList->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableList->resizeColumnsToContents();



    this->centralWidget()->setLayout(ui->layGen);

    connect(btnActQuit,SIGNAL(clicked()),this,SLOT(close()));
    connect(btnReload,SIGNAL(clicked()),this,SLOT(reload()));

    //on commence les requetes ici
    QString req = "select entete as e, entete_fact as f from app_param where id_param = 1 limit 1";
    QSqlQuery requet;
    if(requet.exec(req)){
        if(requet.next()){
            ui->txtEntete->setText(requet.value("e").toString());
            ui->txtFact->setText(requet.value("f").toString());
        }
        std::cout << requet.lastError().text().toStdString();
    }
}

InterParam::~InterParam()
{
    delete ui;
}

void InterParam::on_btnAdd_clicked(){
    intAddUser = new InterAddUser();
    intAddUser->show();
}

void InterParam::reload(){ //ce slot a pour role de recharcger l'affichage de la page
//   // this->model = NULL; // on efface dabord le model

//    //modelReload = new QStandardItemModel(model);//on le recree pour les nouvelle donnée
//    //modelReload->setHorizontalHeaderLabels(listeEntete);
//    //liste =  new QList <Utilisateur *>;
//    listUser.clear();
//    listUser = userMan->getUserList(); // on recuperer la liste des utilisateurs
//    qDebug() << listUser.count();
//    int row = 0;
//    QList<Utilisateur *>::iterator i;
//   // while(row  <= listUser.count()){ //pour le nbr d'user de la liste
//    for(i = listUser.begin(); i!=listUser.end();i++){
//                modelReload->setItem(row,0,new QStandardItem( listUser.at(row)->getNom()));
//                modelReload->setItem(row,1,new QStandardItem( listUser.at(row)->getPrenom()));
//                modelReload->setItem(row,2,new QStandardItem( listUser.at(row)->getLoggin()) );
//                modelReload->setItem(row,3,new QStandardItem( listUser.at(row)->getNivAcc()));
//                modelReload->setItem(row,4,new QStandardItem( listUser.at(row)->getPostOcc() ) );
//        row++;
//    }

//    //on applique les parametres de la vue
//    this->ui->tableList->setModel(this->modelReload);

//    this->ui->tableList->setSortingEnabled(true);
//    this->ui->tableList->setSelectionBehavior(QAbstractItemView::SelectRows);
}

void InterParam::on_pushButton_clicked()//les utilisateurs
{
    ui->stackedWidget->setCurrentIndex(0);
}

void InterParam::on_btnLog_clicked()//les log
{
    ui->stackedWidget->setCurrentIndex(1);
}

void InterParam::on_btnEnTete_clicked()//les entetes
{
    ui->stackedWidget->setCurrentIndex(2);
}

void InterParam::on_btnData_clicked()//les donnes que l'on pourra effacer
{
    ui->stackedWidget->setCurrentIndex(3);
}

void InterParam::on_btnValider_clicked()//cette fonction doit permettre de mettre a jour l'entete des diagnostic
{
//    QString req = "update app_param set entete = '"+ui->txtEntete->toPlainText().replace("'","''").trimmed()+"' where id_param = 1";
    QString req2 = "select entete as e from app_param where id_param = 1 limit 1";
    QSqlQuery requet;
    requet.prepare("update app_param set entete = :ent where id_param = 1 ");
    requet.bindValue(":ent",ui->txtEntete->toPlainText().replace("'","''").trimmed());

    if(requet.exec()){
        QMessageBox::information(this,"Succes","Mise a jour reussie");
        if(requet.exec(req2)){
            if(requet.next()){
                ui->txtEntete->setText(requet.value("e").toString());
            }
            //QMessageBox::warning(this,"Erreur",requet.lastError().text());

        }
    }else{
        QMessageBox::critical(this,"Echec","Erreur lors de la mise a jour");
    }
}

void InterParam::on_btnErase_clicked()
{
    //cet slot va vider toutes les tables de la bases de données

    int res;
    res = QMessageBox::critical(this,"Attention","Vous etes sur le point de supprimer toutes les données de l'application\nVoulez-vous continuez ?",
                                QMessageBox::Yes | QMessageBox::No,QMessageBox::No);
    if(res != QMessageBox::Yes)
        return;

    //QMessageBox::information(this,"DAco","suppression en cour");
    QSqlDatabase db = QSqlDatabase::database();//on recupere la BD
    QStringList listTable = db.tables();
    QSqlQuery requete;

    for(int i =0;i<listTable.size();++i){
        //requete.prepare("delete from :table_name");
        if(listTable.at(i) != "utilisateur" && listTable.at(i) != "app_param"){
            requete.exec("delete from '"+listTable.at(i)+"'");
        }
    }
    QMessageBox::information(this,"Succes","Suppression terminer");
}



void InterParam::on_btnSaveFact_clicked()//cette fonction doit permettre de mettre a jour l'entete des facture
{
    QString req2 = "select entete_fact as f from app_param where id_param = 1 limit 1";
    QSqlQuery requet;
    requet.prepare("update app_param set  entete_fact = :efact where id_param = 1 ");
    requet.bindValue(":efact",ui->txtFact->toPlainText().replace("'","''").trimmed());

    if(requet.exec()){
        QMessageBox::information(this,"Succes","Mise a jour reussie");
        if(requet.exec(req2)){
            if(requet.next()){
                ui->txtFact->setText(requet.value("f").toString());
            }
            //QMessageBox::warning(this,"Erreur",requet.lastError().text());

        }
    }else{
        QMessageBox::critical(this,"Echec","Erreur lors de la mise a jour");
    }
}
