#include "recherche.h"
#include "ui_recherche.h"
#include "structure.h"



Recherche::Recherche(SearchStruct search,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Recherche),
    s(search)
{
    ui->setupUi(this);
    //on commence par tester la valeur du champs table pour connaitre ou faire la recherche
    std::cout << search.table.toStdString()<< std::endl;
    if(this->s.table == "Patients"){
        std::cout << "recherche de patients"<< std::endl;
        this->search_patient(s.data); //on effectue la rcherch et on affiche le resultat
    }

    if(this->s.table == "Fournisseur"){
        this->search_fournsseur(s.data);//on effectue la rcherch et on affiche le resultat
    }

    if(this->s.table == "Article"){
        this->search_article(s.data);//on effectue la rcherch et on affiche le resultat
    }
}

Recherche::~Recherche()
{
    delete ui;
}

void Recherche::search_patient(QString data)
{
    PatientStruct *patient;//un patiet de la liste
    QList <PatientStruct *> list_patient;//la liste des patients
    query = new QSqlQuery();
    QString requete("select idClient, nom,prenom from clients where nom like '%"+data.replace("'","''")+"%' or prenom like '%"+data.replace("'","''")+"%' ");
    //query->prepare("select idClient, nom,prenom  from clients where nom like '%:data%' or prenom like '%:pnom%' ");//
//    query->bindValue(":data",data);
//    query->bindValue(":pnom",data);

    if(query->exec(requete)){//si la requete s'execute
        //si sa a ete retrouver
        //std::cout << requete.toStdString()<< std::endl;
        while(query->next()){
            patient = new PatientStruct();

            patient->id = query->value(0).toInt();
            patient->nom = query->value(1).toString();
            patient->prenom = query->value(2).toString();

            list_patient << patient;//on ajoute le nouveau patient a la liste des patients
        }//on reprend la boucle

        if(list_patient.count() == 0){//si la liste est vide
            QMessageBox::information(0,"Resultat","Aucun resultat trouvé");

            return;
        }
        //sinon on entame la procedure d'affichage
        list << "id client"<< "Nom du patient" << "Prenom du patient";
        model = new QStandardItemModel(list_patient.count(),3); //3 colone le nombre de ligne dependra du nombre de resultat
        model->setHorizontalHeaderLabels(list);
        int i(0);
        while(i<list_patient.count()){//cette boucle va remplir le model

            model->setItem(i,0,new QStandardItem(QString::number(list_patient.at(i)->id)));
            model->setItem(i,1,new QStandardItem(list_patient.at(i)->nom));
            model->setItem(i,2,new QStandardItem(list_patient.at(i)->prenom));
            i++;
        }
        this->display_result(model,Recherche::Patient);//on lance l'affichage ici
        return;
    }else{
        QMessageBox::critical(0,"Erreur",query->lastError().text());
        return;
    }

}

void Recherche::search_article(QString data)
{
    //la recherche d'un article
    ArticleStruct *article;
    QList<ArticleStruct *> list_article;

    query = new QSqlQuery();
    QString requete = "select * from article where nom like '%"+data.replace("'","''")+"%' or info_supp like  '%"+data.replace("'","''")+"%' ";
//    query->prepare("select * from article where nom like '%:data%' or info_supp like  '%:nfo%' ");
//    query->bindValue(":data",data);
//    query->bindValue(":nfo",data);

    if(query->exec(requete)){//si la requete s'execute
        //si sa a ete retrouver
        while(query->next()){
            article = new ArticleStruct();

            article->nom = query->value(query->record().indexOf("nom")).toString();
            article->id = query->value(query->record().indexOf("idArticle")).toInt();
            article->dateEntre = query->value(query->record().indexOf("dateAchat")).toDate();
            article->info_supp = query->value(query->record().indexOf("info_supp")).toString();

            list_article<< article;//on ajoute le nouveau patient a la liste des patients
        }//on reprend la boucle
        if(list_article.count() == 0){//si la liste est vide
            QMessageBox::information(0,"Resultat","Aucun resultat trouvé");
            return;
        }
        //sinon on entame la procedure d'affichage

        list << "Numero article"<< "Nom de l'article" << "date d'achat" << "Information supplementaire";
        model = new QStandardItemModel(list_article.count(),4); //3 colone le nombre de ligne dependra du nombre de resultat
        model->setHorizontalHeaderLabels(list);

        int i(0);
        while(i<list_article.count()){//cette boucle va remplir le model

            model->setItem(i,0,new QStandardItem(QString::number(list_article.at(i)->id)));
            model->setItem(i,1,new QStandardItem(list_article.at(i)->nom));
            model->setItem(i,2,new QStandardItem(list_article.at(i)->dateEntre.toString("yyyy/MM/dd")));
            model->setItem(i,3,new QStandardItem(list_article.at(i)->info_supp));
            i++;
        }

        this->display_result(model,Recherche::Article);//on lance l'affichage ici
        return;
    }else{
        QMessageBox::critical(0,"Erreur",query->lastError().text());
        return;
    }
}

void Recherche::search_fournsseur(QString data)
{
    //la recherche d'un fournisseur
    FournisseurStruct *fournisseur;
    QList<FournisseurStruct *> list_fournisseur;

    query = new QSqlQuery();
    QString reuete = "select * from fournisseur where nom like '%"+data.replace("'","''")+"%' ";

    list << "Numero fournisseur"<< "Nom du fournisseur" << "Matricule" << "Informations suppelentaire";
    if(query->exec(reuete)){//si la requete s'execute
        //si sa a ete retrouver
        while(query->next()){
            fournisseur= new FournisseurStruct();

            fournisseur->nom = query->value(query->record().indexOf("nom")).toString();
            fournisseur->matricule  = query->value(query->record().indexOf("matriculeFour")).toString();
            fournisseur->id = query->value(query->record().indexOf("idFournisseur")).toInt();
            fournisseur->info_supp = query->value(query->record().indexOf("info_supp")).toString();

            qDebug()<< "chargement dans la liste";
            list_fournisseur<<fournisseur;//on ajoute le nouveau patient a la liste des patients
            //qDebug()<< list_fournisseur;
        }

        if(list_fournisseur.count() == 0){
            QMessageBox::information(0,"Resultat","Aucun resultat trouvé");
            return;
        }

            model = new QStandardItemModel(list_fournisseur.count(),4); //3 colone le nombre de ligne dependra du nombre de resultat
            model->setHorizontalHeaderLabels(list);

            int i(0);
            while(i<list_fournisseur.count()){//cette boucle va remplir le model

                model->setItem(i,0,new QStandardItem(QString::number(list_fournisseur.at(i)->id)));
                model->setItem(i,1,new QStandardItem(list_fournisseur.at(i)->nom));
                model->setItem(i,2,new QStandardItem(list_fournisseur.at(i)->matricule));
                model->setItem(i,3,new QStandardItem(list_fournisseur.at(i)->info_supp));
                i++;
            }
            list_fournisseur.clear();
            this->display_result(model,Recherche::Fournisseur);//on lance l'affichage ici
            return;

        //on reprend la boucle
        if(list_fournisseur.count() == 0){//si la liste est vide
            QMessageBox::information(0,"Resultat","Aucun resultat trouvé");
            return;
        }
        //sinon on entame la procedure d'affichage
    }else{
        QMessageBox::critical(0,"Erreur",query->lastError().text());
        return;
    }

}

void Recherche::display_result(QStandardItemModel *model, Recherche::Search s)
{
    //std::cout << "mise en place du model"<< std::endl;
    this->ui->tableView->setModel(model);

    this->ui->tableView->setSortingEnabled(true);
    this->ui->tableView->setGridStyle(Qt::DashLine);
    this->ui->tableView->horizontalHeader()->setStretchLastSection(true);
    this->ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->ui->tableView->resizeColumnsToContents();
    this->ui->tableView->setAlternatingRowColors(true);

    this->setLayout(ui->layVer);
    this->show();
    ui->btnValider->setEnabled(false);

    switch (s) {
        case Article://prevoir le code pour
            this->cible = "article";
            break;
        case Patient:
            this->cible = "patients";
            break;
         case Fournisseur:
            qDebug()<< "fkournisseur";
            this->cible = "Fournisseur";
            break;
        }


}

void Recherche::on_btnValider_clicked()
{

    if(this->cible == "article"){
        //prevoir l'affichage de la fiche d'un article
    }

    if(this->cible == "patients"){
        //prevoir l'affichage de la fiche du patient
        fich_client = new UiFicheClient(this->id_choix);
        fich_client->show();
        this->close();
    }

    if(this->cible == "Fournisseur"){
        four_man = new FournisseurManager();
        fournisseur  = four_man->getFournisseurById(this->id_choix);
        inter_addFournisseur = new InterAddFournisseur(this->id_choix,fournisseur.nom,
                                                       fournisseur.ville,fournisseur.info_supp);
        this->close();
        inter_addFournisseur->show();
    }

}

void Recherche::on_tableView_clicked(const QModelIndex &index)
{
    if(index.column() != 0){
        ui->btnValider->setEnabled(false);
        return;
    }else{
        this->id_choix = index.data().toInt();
        ui->btnValider->setEnabled(true);
    }
}
