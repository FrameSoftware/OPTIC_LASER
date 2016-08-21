#include "interaddarticle.h"
#include "ui_interaddarticle.h"
#include "fournisseurmanager.h"
#include "structure.h"


#define lis FournisseurManager::listFourMat;

InterAddArticle::InterAddArticle(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InterAddArticle)
{
    ui->setupUi(this);
    FournisseurManager::getFournisseurList(); // reinitialisation de la liste de fournisseur
    std::cout << "Inter Add article"<<std::endl;
    setLayout(ui->layGen);
    setFixedSize(385,377);
    //ajout de la liste des fournisseurs
    for(int i =0; i<FournisseurManager::listFourMat.size(); i++){
        ui->cmbList->addItem(FournisseurManager::listFourMat.at(i).nom_four);
        //qDebug() << FournisseurManager::listFourMat.at(i).nom_four;
    }//le listing est fini ici

    if(FournisseurManager::listFourMat.isEmpty() == false)
        this->matricule = FournisseurManager::listFourMat.at(0).matricule_four;
    //qDebug()<<matricule;

    setWindowModality(Qt::WindowModal);
    setWindowTitle("Ajout d'un article");
    connect(ui->btnAnnul,SIGNAL(clicked()),this,SLOT(close()));
    connect(ui->btnValider,SIGNAL(clicked()),this,SLOT(valider()));
    connect(ui->btnAddFour,SIGNAL(clicked()),this,SLOT(addFournisseur()));
    connect(ui->cmbList,SIGNAL(activated(QString)),this,SLOT(selectMatricule(QString)));
}

InterAddArticle::~InterAddArticle()
{
    delete ui;
}

void InterAddArticle::valider(){
    //slot appele lors de la validation de l'article
    //on verifie dabors les champs

    if(ui->lgnNom->text().isEmpty()){
        QMessageBox::warning(this,"Erreur formulaire","Vous devez remplir le champ nom au moins");
        return;//pour arrete la fonction
    }

    ArticleStruct  art ;/*= new Articles();**/
                art.prix =  (ui->lgnPU->value());//prix uni
                art.nombre= ui->lgnNbr->value();//nombre
                art.dateEntre = ui->lgnDateE->date();//date Entree
                 art.nom =  (ui->lgnNom->text().replace("'","''").toUpper());//nom
                 art.info_supp= (ui->txtInfoSupp->toPlainText().replace("'","''"));//ici on echappe la chaine

                 art.matricule_four = (matricule);//on definie le matricule de fournisseur

    artMan = new ArticleManager();//on instaci le manager
    ErrorManager err;//on gere le retour
    err= artMan->addArticle(art);

    if(err.status == true){
        QMessageBox::information(this,"Enregistrement reussi","L'ajout de l'article a reussit");
        this->close();
    }else{
        QString msg;
        msg = " "+err.msg +" Code : "+ QString::number(err.code);
        QMessageBox::critical(this,"Erreur enregistrement",msg);
        //prevoir les instructions pour les log ICI
    }
}

void InterAddArticle::addFournisseur(){
    inter_add_four = new InterAddFournisseur();
    inter_add_four->show();
    FournisseurManager::getFournisseurList();//on met a jour la liste ici

    for(int i =0; i<FournisseurManager::listFourMat.size(); i++){
        ui->cmbList->addItem(FournisseurManager::listFourMat.at(i).nom_four);
        //qDebug() << FournisseurManager::listFourMat.at(i).nom_four;
    }
}

void InterAddArticle::selectMatricule(QString text){
    //cette methode recoit le texte choisi par le nom du fournisseur choisi
    /*
     * On parcour la liste de FourMat et on cherche le fournisseur choisit puis on recupere son matricule que lon affecte
     * a la variable matricule et c'est fini
     * */
    for(int i =0; i<FournisseurManager::listFourMat.size(); i++){
        if(FournisseurManager::listFourMat.at(i).nom_four == text){
            this->matricule = FournisseurManager::listFourMat.at(i).matricule_four; //on recupere le matricule ici
            //qDebug()<< matricule;
        }
    }

}
