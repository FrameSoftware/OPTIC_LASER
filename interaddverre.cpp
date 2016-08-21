#include "interaddverre.h"
#include "ui_interaddverre.h"

#include "fournisseurmanager.h"

InterAddVerre::InterAddVerre(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InterAddVerre)
{
    ui->setupUi(this);
    setLayout(ui->layGen);
    setFixedSize(380,421);
    setWindowTitle("Ajout de verre");
    connect(ui->btnAnnul,SIGNAL(clicked()),this,SLOT(close()));

    for(int i =0; i<FournisseurManager::listFourMat.size(); i++){
            ui->cmbNew->addItem(FournisseurManager::listFourMat.at(i).nom_four);
        }

    if(FournisseurManager::listFourMat.isEmpty() == false)
        this->matricule = FournisseurManager::listFourMat.at(0).matricule_four;

    setWindowModality(Qt::WindowModal);
    connect(ui->cmbNew,SIGNAL(activated(QString)),this,SLOT(selectMatricule(QString)));

}

void InterAddVerre::on_btnValider_clicked(){
    ArticleStruct art;//on utilisqe pour gere la PArti article du verrre

    art.nom = "Verres";
    art.nombre = ui->lgnNbr->text().toInt();
    art.prix = ui->lgnPU->text().toInt();
    art.info_supp = ui->txtInfoSupp->document()->toPlainText().replace("'","''");
    art.matricule_four = this->matricule;
    //on va dabors lance lajout de l'article puis du verrre
    ArticleManager art_man;
    ErrorManager err;

    err = art_man.addArticle(art);
    if(err.status == true){
        VerreStruct verre_str;
        verre_str.id_art = err.id;//on recupere l'id de l'article
        verre_str.matiere = ui->lgnMat->text().replace("'","''");
        verre_str.vergence= ui->lgnVerg->text().replace("'","''");
        verre_str.type = ui->lgnType->text().replace("'","''");

        err = vrr.addVerre(verre_str);
        if(err.status == true) {
            QMessageBox::information(this,"Succes",err.msg);
            this->close();
        }else{
            QMessageBox::warning(this,"Erreur",err.msg+" "+ err.msgTech);
            this->close();
        }
    }else{
        QMessageBox::warning(this,"Erreur",err.msg+" "+err.msgTech);
        this->close();
    }

}

InterAddVerre::~InterAddVerre()
{
    delete ui;
}

void InterAddVerre::selectMatricule(QString text){
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
