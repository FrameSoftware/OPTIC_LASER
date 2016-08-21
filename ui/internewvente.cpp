#include "internewvente.h"
#include "ui_internewvente.h"
#include <iostream>


interNewVente::interNewVente(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::interNewVente)
{
    //on cree les liste ici
  Patients::getListPatient();
  Monture::getListMontureCaract();
  Nettoyant::getListNettoyant();
  Verre::getListVerre();



  setWindowModality(Qt::WindowModal);
  ui->setupUi(this);
  //ui->centralwidget->setLayout(ui->layGen);

  //on commence a parametrer la lunnette

  this->lunnetes.vlOdNbr = 0;
  lunnetes.vlOdPu = 0;
  lunnetes.vlOgNbr = 0;
  lunnetes.vlOgPu = 0;
  lunnetes.vpOdNbr = 0;
  lunnetes.vpOdPu = 0;
  lunnetes.vpOgNbr = 0;
  lunnetes.vpOgPu = 0;


  //-----------------prevoir ici le chargement des combo box--------------------------//
  for(int i=0;i<Patients::listPatient.size();i++){
      ui->cmbPatient->addItem(Patients::listPatient.at(i).identity);//ici on affiche la liste en parcourant la boucle

  }
  if(Patients::listPatient.isEmpty() == false)
    this->id_client = Patients::listPatient.at(0).id_p;//on met l'id au premier

  ui->cmbMont->addItem("");
  for(int i=0;i<Monture::monturelist_carac.size();i++){
      ui->cmbMont->addItem(Monture::monturelist_carac.at(i).caracteristic);
      //on a recupere les caracteristiques ici
  }
  //this->id_mont = n; //Monture::monturelist_carac.at(0).id_monture;
  //on recupere le premier

  //les listes pour les nettoyants
  ui->cmbNett->addItem("");
  for(int i =0; i<Nettoyant::listNettoyant.size();i++){
      ui->cmbNett->addItem(Nettoyant::listNettoyant.at(i).caracteristic);
  }
  //this->id_net = Nettoyant::listNettoyant.at(0).id_monture;
  //la liste de nettoyant est ici

  //---------------------les quatre vergences ici
  //Oeil gauche vision de loin
  ui->OgVergVl->addItem("");
  for(int i = 0;i<Verre::listverrec.size();i++){
      ui->OgVergVl->addItem(Verre::listverrec.at(i).caracteris);
  }
  //this->id_ogvl = Verre::listverrec.at(0).id_verre;

  //oeil gauche vision de pres
  ui->OgVergVp->addItem("");
  for(int i = 0; i<Verre::listverrec.size();i++){
      ui->OgVergVp->addItem(Verre::listverrec.at(i).caracteris);
  }
  //this->id_ogvp = Verre::listverrec.at(0).id_verre;

  //oeuil droit vision de loin
  ui->OdVergVl->addItem("");
  for(int i= 0;i<Verre::listverrec.size();i++){
      ui->OdVergVl->addItem(Verre::listverrec.at(i).caracteris);
  }
  //this->id_odvl = Verre::listverrec.at(0).id_verre;

  //oeuil droit vision de pret
  ui->OdVergVp->addItem("");
  for(int i=0; i < Verre::listverrec.size();i++){
      ui->OdVergVp->addItem(Verre::listverrec.at(i).caracteris);
  }
  //this->ido_dvp = Verre::listverrec.at(0).id_verre;


  this->setCentralWidget(ui->centralwidget);

  this->setWindowTitle("Nouvelle vente");
  this->setFixedWidth(1029);
  this->setFixedHeight(489);

  //les connections ici
  connect(ui->cmbPatient,SIGNAL(activated(QString)),this,SLOT(select_patient(QString)));
  connect(ui->cmbMont,SIGNAL(activated(QString)),this,SLOT(select_monture(QString)));
  connect(ui->cmbNett,SIGNAL(activated(QString)),this,SLOT(select_nettoyant(QString)));
  connect(ui->btnReload,SIGNAL(clicked()),this,SLOT(reload()));
  connect(ui->btnNew,SIGNAL(clicked()),this,SLOT(addPatient()));
}

void interNewVente::select_patient(QString txt){
    for(int i =0; i<Patients::listPatient.size(); i++){
        if(Patients::listPatient.at(i).identity == txt){
            this->id_client = Patients::listPatient.at(i).id_p; //on recupere l'e matricule ici'id ici
        }
    }
}

void interNewVente::select_monture(QString txt){
    for(int i=0;i<Monture::monturelist_carac.size();i++){
        if(Monture::monturelist_carac.at(i).caracteristic == txt){
            this->id_mont = Monture::monturelist_carac.at(0).id_monture;
            //ici on recupere l'id
            nbrId.id_mont = this->id_mont;

        }
    }
}

void interNewVente::select_nettoyant(QString txt){
    for(int i=0;i<Nettoyant::listNettoyant.size();i++){
        if(Nettoyant::listNettoyant.at(i).caracteristic == txt){
            this->id_net = Nettoyant::listNettoyant.at(0).id_monture    ;
            //ici on recupere l'id
            nbrId.id_net = this->id_net;
        }
    }
}

interNewVente::~interNewVente()
{
  delete ui;
}

void interNewVente::on_btnAnnul_clicked(){
  this->close();
}

void interNewVente::on_btnValider_clicked()
{

    //on va dabors verifier si rien n'est coche

    if(!ui->groupBox->isChecked() && !ui->groupMonture->isChecked()
            && !ui->groupNettoyant->isChecked() && !ui->groupOther->isChecked()
            && !ui->groupVerre->isChecked()){
        QMessageBox::warning(this,"Attention","Vous devez activer au moins un group");
        return;
    }

    //prevoir le code qui va servir a
    //la sauvegarde et a l'impression
    //on commence par la recuperation des donnees pour les lunnettes
    LunnettesManager lunMan;
    if(ui->groupVerre->isChecked()){
        //viosion de preoche
        lunnetes.VP_OG = ui->OgVergVp->itemText(ui->OgVergVp->currentIndex());
        lunnetes.vpOgNbr = ui->OgQteVp->value();
        lunnetes.vpOgPu = ui->OgPuVp->value();

        lunnetes.VP_OD = ui->OdVergVp->itemText(ui->OdVergVp->currentIndex());
        lunnetes.vpOdNbr = ui->OdQteVp->value();
        lunnetes.vpOdPu = ui->OdPuVp->value();

        //vision de loin
        lunnetes.VL_OD = ui->OdVergVl->itemText(ui->OdVergVp->currentIndex());
        lunnetes.vlOdNbr = ui->OdQteVl->value();
        lunnetes.vlOdPu = ui->OdPuVl->value();

        lunnetes.VL_OG = ui->OgVergVl->itemText(ui->OgVergVl->currentIndex());
        lunnetes.vlOgNbr = ui->OgQteVl->value();
        lunnetes.vlOgPu = ui->OgPuVl->value();

        //les tarairements
        lunnetes.ogTraitement = ui->OgTrait->toPlainText();
        lunnetes.odTraitement = ui->OdTrait->toPlainText();
    }else{
        lunnetes.VP_OG = "";
        lunnetes.vpOgNbr = 0;
        lunnetes.vpOgPu = 0;

        lunnetes.VP_OD = "";
        lunnetes.vpOdNbr = 0;
        lunnetes.vpOdPu = 0;

        //viossion de loin
        lunnetes.VL_OD = "";
        lunnetes.vlOdNbr = 0;
        lunnetes.vlOdPu = 0;

        lunnetes.VL_OG = "";
        lunnetes.vlOgNbr = 0;
        lunnetes.vlOgPu = 0;

        //les tarairements
        lunnetes.ogTraitement ="";
        lunnetes.odTraitement ="";
    }
    ErrorManager err(lunMan.saveLunnettes(this->lunnetes));
    //ici on cree un objet de resultat et on y affecte le retour de la fonction
    //d'ajout des lunnettes
    if(err.status == true){//si on a ajoute la lunnette
        //on va commencer a cree la facture
        FactureStruct facture;
        facture.idLunn = err.id; //on recupere l'id de la lunnette
        facture.idUtil = Utilisateur::m_id; //on recupere l'id de l'user en cour
        std::cout << err.id <<"adons"<<std::endl;
        facture.idClie = this->id_client;
        //nous devons prevois les codes pour recuperation des combos box



        //prevoir lajout du nombres d'article pour la sauvegarde


        int res_temp(0);
        int nbrArt(0);
        if(ui->groupVerre->isChecked()){
            res_temp = (ui->OgQteVl->value() * ui->OgPuVl->value()) + ( ui->OgQteVp->value() * ui->OgPuVp->value() )
                    + (ui->OdQteVl->value() * ui->OdPuVl->value()) + (ui->OdPuVp->value() * ui->OdQteVp->value());
            nbrArt = ui->OgQteVl->value() + ui->OgQteVp->value() + ui->OdQteVl->value() + ui->OdPuVp->value();
        }else{
            res_temp =0;
            nbrArt = 0;
        }


        if(ui->groupMonture->isChecked()){
            facture.nbrMon = ui->nbrMont->value();
            facture.puMont = ui->puMon->text().toInt();
            res_temp = res_temp + (ui->nbrMont->text().toInt() * ui->puMon->text().toInt());
            facture.caractMon = ui->cmbMont->itemText(ui->cmbMont->currentIndex());//on recuper le texte en cour avec son index
            nbrArt = nbrArt + ui->nbrMont->text().toInt();
            nbrId.nbr_mont =  ui->nbrMont->value();
        }else{//sinon on remet les compteurs a zero
            facture.nbrMon = 0;
            facture.puMont = 0;
            res_temp = res_temp;
            facture.caractMon ="";
            nbrArt = nbrArt + 0;
        }

        if(ui->groupNettoyant->isChecked()){
            facture.nbrNettoy = ui->nbrNet->value();
            facture.puNet = ui->puNet->text().toInt();
            res_temp = res_temp + (ui->nbrNet->text().toInt() * ui->puNet->text().toInt());
            facture.caracNettoy = ui->cmbNett->itemText(ui->cmbNett->currentIndex());
            nbrArt = nbrArt + ui->nbrNet->text().toInt();
            nbrId.nbr_net = ui->nbrNet->value();
        }else{
            facture.nbrNettoy = 0;
            facture.puNet = 0;
            res_temp = res_temp + 0;
            facture.caracNettoy = "";
            nbrArt = nbrArt +0;
        }

        if(ui->groupOther->isChecked()){
            res_temp = res_temp + (ui->nbrOther->text().toInt() * ui->puOther->text().toInt());
            facture.nbrOther = ui->nbrOther->value();
            facture.puOther = ui->puOther->text().toInt();
            facture.caracOther = ui->txtOther->toPlainText();
            nbrArt = nbrArt + ui->nbrOther->text().toInt();
        }else{
            res_temp = res_temp + 0;
            facture.nbrOther = 0;
            facture.puOther =0;
            facture.caracOther = "";
             nbrArt = nbrArt +0;
        }

        facture.nbrArticle = nbrArt;
        facture.prixTotal = res_temp;

        FactureManager factu;
        ErrorManager err(factu.addFacture(facture));
        if(err.status == true){
            //on commence la mise a jour ici
            QMessageBox::information(this,"Succes",err.msg);
            this->close();
        }else{
            QMessageBox::information(this,"Echec",err.msgTech);
            this->close();
        }

    }else{
        QMessageBox::critical(this,"Echec",err.msgTech);
        this->close();
    }
}
    



/*
 *
 * ces slot vont estres alncer lorsque l'user rempli un champ du formulaire
 * et comme sa l'on aurra toutes les valeurs importantes pour la lunnette
 * lors de l'impression
 *
 * L'on doit prevoir le fait que certain champs ne seront pas activer
 * c'est pour sa que nous devons prevoir que les chmps de la lunnette
 * doivent avoir des valeurs par defaut
 * */
void interNewVente::on_OgVergVl_activated(const QString &arg1)
{
    this->lunnetes.VL_OG = arg1;
    //ici a chaque fois chaque fois aue l'on va
    //choisir une valeur dans la combo box elle sera mose a jour ici
}

void interNewVente::on_OgQteVl_valueChanged(int arg1)
{
    this->lunnetes.vlOgNbr = arg1;
}

void interNewVente::on_OgPuVl_valueChanged(int arg1)
{
    this->lunnetes.vlOgPu = arg1;
}

void interNewVente::on_OgVergVp_activated(const QString &arg1)
{
    this->lunnetes.VP_OG = arg1;
}



void interNewVente::on_OgQteVp_valueChanged(int arg1)
{
    this->lunnetes.vpOgNbr = arg1;
}

void interNewVente::on_OgPuVp_valueChanged(int arg1)
{
    this->lunnetes.vpOgPu = arg1;
}

void interNewVente::on_OgTrait_textChanged()
{
    this->lunnetes.ogTraitement = this->ui->OgTrait->toPlainText();
}

void interNewVente::on_OdVergVl_activated(const QString &arg1)
{
    this->lunnetes.VL_OD = arg1;
}

void interNewVente::on_OdQteVl_valueChanged(int arg1)
{
    this->lunnetes.vlOdNbr = arg1;
}

void interNewVente::on_OdPuVl_valueChanged(int arg1)
{
    this->lunnetes.vlOdPu = arg1;
}

void interNewVente::on_OdVergVp_activated(const QString &arg1)
{
    this->lunnetes.VP_OD = arg1;
}

void interNewVente::on_OdQteVp_valueChanged(int arg1)
{
    this->lunnetes.vpOdNbr = arg1;
}

void interNewVente::on_OdPuVp_valueChanged(int arg1)
{
    this->lunnetes.vpOdPu = arg1;
}

void interNewVente::on_OdTrait_textChanged()
{
    this->lunnetes.odTraitement = this->ui->OdTrait->toPlainText();
}

void interNewVente::reload(){
    this->ui->cmbPatient->clear();
    //std::cout << "this->ui->cmbPatient->clear()" << std::endl;
    //on nettoy dabord la liste
    Patients::listPatient.clear();
    //std::cout << "listPatient.clear()" << std::endl;
    //puis on reselectionne
    Patients::getListPatient();
   // std::cout << "Patients::getListPatient()" << std::endl;
    //on boucle pour afficher
    if(Patients::listPatient.size() == 0)//ici je teste si la liste est vide
        return;
    for(int i=0;i<Patients::listPatient.size();i++){
        ui->cmbPatient->addItem(Patients::listPatient.at(i).identity);//ici on affiche la liste en parcourant la boucle

    }
    this->id_client = Patients::listPatient.at(0).id_p;//on met l'id au premier
}

void interNewVente::addPatient(){
    new_patient = new UiAddPatient();
    new_patient->show();
    new_patient->setWindowModality(Qt::WindowModal);
}
