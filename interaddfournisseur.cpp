#include "interaddfournisseur.h"
#include "ui_interaddfournisseur.h"
#include <iostream>
#include <QDebug>
#include <QSqlQuery>

InterAddFournisseur::InterAddFournisseur(QWidget *parent) : //constructeur pour l'ajout
    QDialog(parent),
    ui(new Ui::InterAddFournisseur)
{
   // this->bd = bd;
    modif = false;//an ajoute plutot
    std::cout << "C'est ici" << std::endl;
    ui->setupUi(this);
    ui->lgnNom->setPlaceholderText("Le nom du fournisseur");
    ui->lgnVille->setPlaceholderText("Le nom de la ville");
    this->setModal(true);
    this->setLayout(ui->layGen);

    setWindowModality(Qt::WindowModal);
    this->setFixedSize(408,318);
    setWindowTitle("Ajouter un fournisseur");
    std::cout << "C'est ici" << std::endl;
     //ui->lgnMat->setText(QString::number(this->count()));
}

InterAddFournisseur::InterAddFournisseur(int id,QString nom,QString ville,QString infoSupp,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InterAddFournisseur)//constructeur pour la modification
{
   // this->bd = bd;
    modif = true;
    this->id_mod = id;

    mod_four = new Fournisseur();
    mod_four->setId(id);
    mod_four->setNom(nom);
    mod_four->setVille(ville);
    mod_four->setInfoSupp(infoSupp);

    ui->setupUi(this);
   // ui->lgnNom->setPlaceholderText("Le nom du fournisseur");
    ui->lgnNom->setText(mod_four->getNom());

    //ui->lgnVille->setPlaceholderText("Le nom de la ville");
    ui->lgnVille->setText(mod_four->getVille());

    ui->textInfo->setText(mod_four->getInfoSupp());

    this->setModal(true);
    this->setLayout(ui->layGen);
    this->setFixedSize(408,318);
    setWindowTitle("Ajouter un fournisseur");
    std::cout << "C'est ici" << std::endl;
     //ui->lgnMat->setText(QString::number(this->count()));
}

InterAddFournisseur::~InterAddFournisseur()
{
    delete ui;
}


int InterAddFournisseur::count(){
    //this->initDB();//on initialise la BD ici
    QSqlQuery req;
    req.exec("select count(idfournisseur) as nbr from fournisseur");

         if(req.next())
          std::cout<< req.value("idfournisseur").toInt() +1<< std::endl;
}

void InterAddFournisseur::on_btnValid_clicked(){

  if(this->modif==false){//si on ne modifie pas on ajoute
      qDebug()<< "Valeur de modif "<< modif;
    if(ui->lgnNom->text().isEmpty() && ui->lgnVille->text().isEmpty()){
        QMessageBox::warning(this,"Erreur formulaire","Vous devez remplir les deux champs, svp!!!",QMessageBox::Yes);
        ui->lgnNom->setFocus();
    }else{
        m_fournisseur = new Fournisseur();
        m_fournisseur->setNom(ui->lgnNom->text().trimmed());
        m_fournisseur->setNbrLiv(0);
        m_fournisseur->setVille(ui->lgnVille->text().trimmed());
        m_fournisseur->setInfoSupp(ui->textInfo->toPlainText().trimmed());
        //m_fournisseur->dump();
        //qDebug() << ui->textInfo->toPlainText();

        m_four_man = new FournisseurManager();
        std::cout << "ajout avec le model"<<std::endl;
        err = m_four_man->addFournisseur(m_fournisseur);
        //on recupere le retour de l'ajout du fournisseur et on pourra afficher
        if(err.status == false){
            QString msg = err.msg + QString::number(err.code);
             QMessageBox::critical(this,"Erreur enregistrement",msg);
             this->close();
        }else{
            QMessageBox::information(this,"Ajout reussit",err.msg);
            this->close();
        }
    }
  }else{//ici on controle l'etat de modif (bool) true
      qDebug()<< "Valeur de modif "<< modif;
      if(ui->lgnNom->text().isEmpty() && ui->lgnVille->text().isEmpty()){
          QMessageBox::warning(this,"Erreur formulaire","Vous devez remplir les deux champs, svp!!!",QMessageBox::Yes);
          ui->lgnNom->setFocus();
      }else{

          //m_fournisseur = new Fournisseur();
          FournisseurStruct  m_fournisseur;
          m_fournisseur.nom = (ui->lgnNom->text().trimmed().replace("'","''"));
          //m_fournisseur->setNbrLiv(0);
          m_fournisseur.ville = (ui->lgnVille->text().trimmed().replace("'","''"));
          m_fournisseur.info_supp = (ui->textInfo->document()->toPlainText().trimmed().replace("'","''"));//on echape les apostrohe
          m_fournisseur.id = (this->id_mod);//on recupere l'id ici

          //qDebug() << ui->textInfo->toPlainText();
          //m_fournisseur.dump(" Lors de la mise ajour ");

          m_four_man = new FournisseurManager();

           ErrorManager err(m_four_man->updateFournisseur(m_fournisseur));//fonction de mise a jour
          //on recupere le retour de l'ajout du fournisseur et on pourra afficher
          if(err.status == false){
              QString msg = err.msg + QString::number(err.code);
               QMessageBox::critical(this,"Erreur lors de la modification",msg);
               this->close();
          }else{
              QMessageBox::information(this,"Modification  reussit",err.msg);
              this->close();
          }
  }
}
  FournisseurManager::getFournisseurList(); // reinitialisation de la liste de fournisseur
}
