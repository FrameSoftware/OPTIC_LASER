#include "printdiagnos.h"
#include "ui_printdiagnos.h"

PrintDiagnos::PrintDiagnos(int id, QWidget *parent) :
    QWidget(parent),
    m_id(id),
    ui(new Ui::PrintDiagnos)
{
    ui->setupUi(this);
    ui->zonePrintable->setLayout(ui->layZone);
    this->setFixedWidth(this->width());
    //on selectionne les data ici
    this->selectData();
    this->afficheData();


}

PrintDiagnos::~PrintDiagnos()
{
    delete ui;
}

void PrintDiagnos::selectData(){
    //on commence pr seectionner les donnée a afficher
    QString query("select * from diagnostic where idDiagnostic ='"+QString::number(this->m_id)+"'");
    requetteur = new QSqlQuery();

    if(!requetteur->exec(query)){//si la selection a reussit
        QMessageBox::critical(this,"Erreur","Echec lors de la recuperation de la facture");
        this->close();
    }

    if(!requetteur->next()){
        QMessageBox::critical(this,"Erreur","Echec lors de la recuperation de la facture");

    }
    m_diagnostic = new DiagnosStruct;
    m_diagnostic->idClient = requetteur->value(requetteur->record().indexOf("idClient")).toInt();
    m_diagnostic->observation = requetteur->value(requetteur->record().indexOf("observation")).toString();
    m_diagnostic->date = requetteur->value(requetteur->record().indexOf("date")).toDate();
    m_diagnostic->correction =  requetteur->value(requetteur->record().indexOf("correction")).toString();

    //on selectionne les data du clients
    std::cout << m_diagnostic->idClient << std::endl;
    query = "select * from clients where idClient = "+QString::number(m_diagnostic->idClient);
    if(!requetteur->exec(query)){
        QMessageBox::critical(this,"Erreur",requetteur->lastError().text());
        this->close();
    }

    if(!requetteur->next()){
        QMessageBox::critical(this,"Erreur",requetteur->lastError().text());
        this->close();
    }

    m_patient = new PatientStruct;
    m_patient->nom = requetteur->value(requetteur->record().indexOf("nom")).toString();
    m_patient->prenom = requetteur->value(requetteur->record().indexOf("prenom")).toString();
    m_patient->dateNaiss = requetteur->value(requetteur->record().indexOf("dateNaiss")).toDate();
    m_patient->sexe  = requetteur->value(requetteur->record().indexOf("sexe")).toString();
    m_patient->info_supp = requetteur->value(requetteur->record().indexOf("info_supp")).toString();

    //on lance la selection des datas parametres

    query = "select entete from app_param where id_param = 1 limit 1";
    if(!requetteur->exec(query)){//si la selection a reussit
        QMessageBox::critical(this,"Erreur","Echec lors de la recuperation de l'entete");
        this->close();
    }

    if(!requetteur->next()){
        QMessageBox::critical(this,"Erreur","Echec lors de la recuperation de l'entete");
        this->close();
    }

    enteteData = requetteur->value(requetteur->record().indexOf("entete")).toString().
            replace(";","\n");//pour aller a la ligne
    //toutes les data sont selectionner ici
}

void PrintDiagnos::afficheData(){
    //les donnes du patient sont afficher ici
    ui->lblNom->setText(this->m_patient->nom);
    ui->lblPnom->setText(this->m_patient->prenom);
    ui->lblSex->setText(this->m_patient->sexe);
    ui->lblInfoSupp->setText(this->m_patient->info_supp);
    ui->lblDateNaiss->setText(this->m_patient->dateNaiss.toString("yyyy-MM-dd"));
    ui->lblEntete->setText(this->enteteData);
    ui->lblObs->setText(this->m_diagnostic->observation);
    ui->txtCorr->setText(this->m_diagnostic->correction);
}

void PrintDiagnos::on_pushButton_2_clicked()
{
    this->close();
}

void PrintDiagnos::on_btnPrint_clicked()
{
    //on commance l'impression ici
    //imprimante = new QPrinter(/*QPrinter::HighResolution*/);
    QString nom = "Diagnostic pour "+this->m_patient->nom;
   QPrinter imprimante;
   imprimante.setFullPage(true);
   imprimante.setDocName(nom);
    QPainter dessinateur;
    QPrintDialog dialog( &imprimante,this);
    if(dialog.exec()){
    dessinateur.begin(&imprimante);
    double xscale = imprimante.pageRect().width()/double(ui->zonePrintable->width());
    double yscale = imprimante.pageRect().height()/double(ui->zonePrintable->height());

    double scale = qMin(xscale,yscale);

    dessinateur.translate(imprimante.paperRect().x() + imprimante.pageRect().width()/2,
                           imprimante.paperRect().y() + imprimante.pageRect().height()/2);
    dessinateur.scale(scale,scale);
    dessinateur.translate(-width()/2,-height()/2);
    ui->zonePrintable->render(&dessinateur);
    }
}
