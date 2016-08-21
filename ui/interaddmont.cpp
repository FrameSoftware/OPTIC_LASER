#include "interaddmont.h"
#include "ui_interaddmont.h"
#include "fournisseurmanager.h"
#include "articlemanager.h"
#include <QMessageBox>
#include "monture.h"

InterAddMont::InterAddMont(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InterAddMont)
{
    FournisseurManager::getFournisseurList(); // reinitialisation de la liste de fournisseur
    ui->setupUi(this);
    setLayout(ui->layGen);


    setFixedSize(380,378);
    setWindowTitle("Ajout d'une monture");

    for(int i =0; i<FournisseurManager::listFourMat.size(); i++){
        ui->cmbForn->addItem(FournisseurManager::listFourMat.at(i).nom_four);
        //qDebug() << FournisseurManager::listFourMat.at(i).nom_four;
    }//le listing est fini ici

    if(FournisseurManager::listFourMat.isEmpty() == false)
        this->matricule = FournisseurManager::listFourMat.at(0).matricule_four;

    setWindowModality(Qt::WindowModal);
    connect(ui->btnAnnul,SIGNAL(clicked()),this,SLOT(close()));
    connect(ui->cmbForn,SIGNAL(activated(QString)),this,SLOT(selectMatricule(QString)));
}

InterAddMont::~InterAddMont()
{
    delete ui;
    delete this;
}

void InterAddMont::selectMatricule(QString text){
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

void InterAddMont::on_btnValider_clicked(){
    ArticleStruct art;
    //on cree l'article ici
    art.nom = "Monture";
    art.nombre = ui->spnNbr->value();
    art.prix = ui->lgnPrix->value();
    art.matricule_four = this->matricule;
    art.dateEntre = ui->dateAchat->date();
    art.info_supp = ui->txtInfoSupp->document()->toPlainText();

    ArticleManager artMan;
    ErrorManager err;
    err = artMan.addArticle(art);
    if(err.status == true){//si reussite on commence avec la table monture
        MontureStruct mon;
        mon.id_art = err.id;
        mon.taille = ui->lgnTaill->text();
        mon.matiere = ui->lgnMat->text();
        //ici on q fini d'initialiser la monture

        Monture monture;
        err =  monture.addMonture(mon);
        if(err.status == true){
            QMessageBox::information(this,"Succes",err.msg);
            this->close();
        }else{
            QString msg;
            msg = err.msg+" code <strong>[ "+err.msgTech+" ]</strong>";
            QMessageBox::information(this,"Erreur",msg);
            close();
        }
    }
}
