#include "interaddnettoy.h"
#include "ui_interaddnettoy.h"

InterAddNettoy::InterAddNettoy(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InterAddNettoy)
{
    ui->setupUi(this);
    setLayout(ui->layGen);
    setFixedSize(380,373);
    setWindowTitle("Ajout d'un nettoyant");

    for(int i =0; i<FournisseurManager::listFourMat.size(); i++){
            ui->cmbFour->addItem(FournisseurManager::listFourMat.at(i).nom_four);
        }

    if(FournisseurManager::listFourMat.isEmpty() == false)
        this->matricule = FournisseurManager::listFourMat.at(0).matricule_four;

    setWindowModality(Qt::WindowModal);
    connect(ui->cmbFour,SIGNAL(activated(QString)),this,SLOT(selectMatricule(QString)));

    connect(ui->btnAnnul,SIGNAL(clicked()),this,SLOT(close()));
}

InterAddNettoy::~InterAddNettoy()
{
    delete ui;
}

void InterAddNettoy::on_btnValider_clicked(){
    ArticleStruct article;

    article.nom = "Nettoyant";
    article.nombre =  ui->lgnNbr->text().toInt();
    article.prix = ui->lgnPU->text().toInt();
    article.matricule_four = ui->txtInfoSupp->document()->toPlainText().replace("'","''");
    article.matricule_four = this->matricule;
    article.dateEntre = ui->dateAchat->date();

    //ici l'article a ete creer

    ArticleManager artMan;
    ErrorManager err;

    err = artMan.addArticle(article);

    if(err.status == true){
        NettoyStruct netStruct;

        netStruct.reference = ui->lgnRef->text().replace("'","''");
        netStruct.id_art = err.id;

        Nettoyant nettoyant;
        err = nettoyant.addNettoyant(netStruct);
        if(err.status == true){
            QMessageBox::information(this,"Succes",err.msg);
            this->close();
        }else{
            QString msg;
            msg = err.msg+" code <strong>[ "+err.msgTech+" ]</strong>";
            QMessageBox::information(this,"Erreur",msg);
            close();
        }
    }else{
        QString msg;
        msg = err.msg+" code <strong>[ "+err.msgTech+" ]</strong>";
        QMessageBox::information(this,"Erreur",msg);
        close();
    }
}

void InterAddNettoy::selectMatricule(QString text){
    //cette methode recoit le texte choisi par le nom du fournisseur choisi
    /*
     * On parcour la liste de FourMat et on cherche le fournisseur choisit puis on recupere son matricule que lon affecte
     * a la variable matricule et c'est fini
     * */
    for(int i =0; i<FournisseurManager::listFourMat.size(); i++){
        if(FournisseurManager::listFourMat.at(i).nom_four == text){
            this->matricule = FournisseurManager::listFourMat.at(i).matricule_four; //on recupere le matricule ici
            qDebug()<< matricule;
        }
    }
}
