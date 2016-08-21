#include "acceuil.h"
#include "ui_acceuil.h"


Acceuil::Acceuil(Utilisateur *user, QWidget *parent) :
  QMainWindow(parent),m_user(user),
  ui(new Ui::Acceuil)
{
  ui->setupUi(this);

     connect(ui->btnArticle,SIGNAL(clicked()),this,SLOT(affichArticle()));
    up = new UserPreferences();
    up->setVisible(false);
     this->setFixedSize(604,435);
   //  setWindowFlags(Qt::FramelessWindowHint);
     this->setWindowTitle("Optic Plus");

     connect(ui->actionQuitter,SIGNAL(triggered()),qApp,SLOT(quit()));
     connect(ui->actionA_propos,SIGNAL(triggered()),this,SLOT(apropos()));
     connect(ui->actionPreferences,SIGNAL(triggered()),up,SLOT(show()));
}

Acceuil::~Acceuil()
{
  delete ui;
}

void Acceuil::on_btnQuitter_clicked(){
  //QMessageBox::warning(this,"Alert","Cette fonctionnalité n'est pas encore disponible");
  //QMessageBox::information(this,"Attention","Ceci est une maquette");

    intParam = new InterParam(this);
    intParam->show();
    intParam->setWindowModality(Qt::WindowModal);
}

void Acceuil::on_btnVente_clicked(){
  Vente *ven = new Vente(this);
  ven->show();
  ven->setWindowModality(Qt::WindowModal);

}

void Acceuil::affichArticle(){
 InterArcticle *art = new InterArcticle(this);
  art->show();
  art->setWindowModality(Qt::WindowModal);
}

void Acceuil::on_btnFour_clicked(){
    InterFournisseur *four = new InterFournisseur(this);
   four->show();
   four->setWindowModality(Qt::WindowModal);
   //this->setCentralWidget(four);
}

void Acceuil::on_btnFact_clicked(){
    UiDiagostic *m_interDiag = new UiDiagostic();
   m_interDiag->show();
   m_interDiag->setWindowModality(Qt::WindowModal);
}

void Acceuil::apropos(){
    QMessageBox::information(this,"A propos","Cette de version de optic plus n'est qu'une preversion\n contactez nous au 693539419 ou simoadonis@gmail.com");
}

void Acceuil::on_btnClient_clicked(){
   UiPatient *patient_ui = new UiPatient();
    patient_ui->show();
    patient_ui->setWindowModality(Qt::WindowModal);
}

void Acceuil::on_btnRechercher_clicked()
{
    if(ui->lgnSearch->text().isEmpty()){
        QMessageBox::information(this,"Attention","Vous devez saisir un texte de recherche");
        return;
    }

    //std::cout << "recherche"<< std::endl;
    SearchStruct search;
    search.data = ui->lgnSearch->text().trimmed();
    search.table = ui->cmbSearch->currentText();
    std::cout << ui->cmbSearch->currentIndex()<< std::endl;
    rech = new Recherche(search);
}
