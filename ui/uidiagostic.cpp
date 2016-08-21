#include "uidiagostic.h"
#include "ui_uidiagostic.h"

UiDiagostic::UiDiagostic(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UiDiagostic)
{
    std::cout << "teste"<< std::endl;
    ui->setupUi(this);
    ui->centralwidget->setLayout(ui->layGen);
    this->setWindowTitle("Module diagnostique");

    btnNew = new QPushButton("Nouveau...");
    btnRefresh = new QPushButton("Rafraichir");
    btnQuit = new QPushButton("Quitter");
    toolbar = addToolBar("boutil");

    toolbar->addWidget(btnNew);
    toolbar->addSeparator();
    toolbar->addWidget(btnRefresh);
    toolbar->addSeparator();
    toolbar->addWidget(btnQuit);

    model = new QSqlTableModel();
    model->setTable("view_diagnostic");

    if(model->select()){//si on reussit a selectionner on configure le tableview
        ui->tableView->setModel(model);

        model->setHeaderData(0,Qt::Horizontal,"Numero");
        model->setHeaderData(1,Qt::Horizontal,"Nom du client ");
        model->setHeaderData(2,Qt::Horizontal,"Prenom du client");
        model->setHeaderData(3,Qt::Horizontal,"Date de diagnostique");
        model->setHeaderData(4,Qt::Horizontal,"Libelle du diagnostique");
       /* model->setHeaderData(5,Qt::Horizontal,"Information supplementaires")*/;

        //this->ui->tableView->setColumnHidden(5,true);
        this->ui->tableView->setSortingEnabled(true);
        this->ui->tableView->setGridStyle(Qt::DashLine);
        this->ui->tableView->horizontalHeader()->setStretchLastSection(true);
        this->ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
        this->ui->tableView->resizeColumnsToContents();
        this->ui->tableView->setAlternatingRowColors(true);

    }else{
        std::cout << "Erreur ici" <<model->lastError().text().toStdString()<< std::endl;
    }
//    tmp = new QTimer(this);
//    connect(tmp,SIGNAL(timeout()),this,SLOT(reload()));
//     tmp->start(60000); //on attent 60 seconde avant de rafraichir

     //ui->btnDetail->setEnabled(false);
     ui->btnMod->setEnabled(false);
     ui->btnPrint->setEnabled(false);
     ui->btnSupp->setEnabled(false);
     //les connections ici
     connect(btnNew,SIGNAL(clicked()),this,SLOT(addDiag()));
     connect(btnQuit,SIGNAL(clicked()),this,SLOT(close()));
     connect(btnRefresh,SIGNAL(clicked()),this,SLOT(reload()));
     connect(ui->tableView,SIGNAL(clicked(QModelIndex)),this,SLOT(affichIndex(QModelIndex)));


}

UiDiagostic::~UiDiagostic()
{
    delete ui;
}

void UiDiagostic::reload(){
    if(this->model->select()){//si on reussit a refaire la selection
        std::cout << "Selection a retourner true" << std::endl;
        //ui->btnDetail->setEnabled(false);
        ui->btnMod->setEnabled(false);
        ui->btnPrint->setEnabled(false);
        statusBar()->showMessage(" ");
        ui->btnSupp->setEnabled(false);
    }else{
        std::cout << "Selection a retourner false" << std::endl;
    }
}

void UiDiagostic::affichIndex(QModelIndex index){

    if(index.column() != 0){
        //std::cout << "la colone est differente de zero" <<std::endl;
        //alert->setText("NOTE: vous devez choisir la colonne N° article pour selectionner un article");
       // alert->setStyleSheet("color : red");

        statusBar()->showMessage(tr("NOTE: vous devez choisir la colonne N° article pour selectionner un diagnostique"));
        //ui->btnDetail->setEnabled(false);
        ui->btnMod->setEnabled(false);
        ui->btnPrint->setEnabled(false);
        ui->btnSupp->setEnabled(false);
    }else{
        /*
         * si il a bien cliquer on lui montre le msg et on active les boutons
         * */
        //std::cout << index.data().toString().toStdString() << std::endl;
        //alert->setText("Article : ["+ index.data().toString()+ " ]selectionné");
        this->element =  index.data().toInt();
        //alert->setStyleSheet("color : blue");
        statusBar()->showMessage(tr("Diagnostique : [")+ index.data().toString()+ tr(" ] selectionné"));

        //ui->btnDetail->setEnabled(true);
        ui->btnMod->setEnabled(true);
        ui->btnPrint->setEnabled(true);
        ui->btnSupp->setEnabled(true);
    }
}

void UiDiagostic::addDiag(){
    UiAddDiagnos *addDiagn = new UiAddDiagnos;
    addDiagn->setWindowTitle("Nouvau diagnostique");
    addDiagn->setWindowModality(Qt::WindowModal);
    addDiagn->show();
}

    //void UiDiagostic::on_btnDetail_clicked()
    //{
    //    Patients *pm = new Patients;
    //    PatientStruct p = pm->getPatientById(this->element);
    //    QString txt;
    //    txt = "<strong>Nom :</strong> "+p.nom + "\n"+
    //            "<strong>Prenom</strong>"+p.prenom + "\n"
    //            +"<strong>"
    //}

void UiDiagostic::on_btnMod_clicked()
{
    DiagnosticManager dm;

    UiAddDiagnos *addDiagn = new UiAddDiagnos(dm.getDiagnosticById(this->element)); // on cree le constructeur avec
    //le nouveau diagnostique
    addDiagn->setWindowTitle("Nouvau diagnostique");
    addDiagn->setWindowModality(Qt::WindowModal);
    addDiagn->show();
}

void UiDiagostic::on_btnPrint_clicked()
{
    //ceci est le code prevu pour lancer l'impression
    prtDiag = new PrintDiagnos(this->element);
    prtDiag->show();
    prtDiag->setWindowModality(Qt::WindowModal);
}

void UiDiagostic::on_pushButton_clicked()
{
    this->close();
}

void UiDiagostic::on_btnSupp_clicked()
{
    int res = QMessageBox::critical(this,"Confirmation","Etes-vous sur de vouloir supprimer ce diagnostique ?",QMessageBox::Yes  | QMessageBox::No);
    if(res != QMessageBox::Yes)
        return;

    DiagnosticManager art;
    ErrorManager err;
    err = art.deleteDiagnostic(this->element);
    if(err.status == true){
        QMessageBox::information(this,"Succes",err.msg);
    }else{
        QMessageBox::warning(this,"Echec",err.msg+" "+err.msgTech);
    }
}
