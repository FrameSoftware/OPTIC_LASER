
/*
 * Cette classe permettra la gestion des connections a la base de donnée
 * */

#include "bdmanager.h"

BDManager::BDManager()
{
    QSqlDatabase  db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("optic_plus");
    db.setUserName("root");
    db.setPassword("");

    if(!db.open()){
         QString err = db.lastError().text();
//        QMessageBox::warning(this,"Erreur de connexion a la base de donnée", " <strong>Message :</strong>"+err);
        std::cout << "le message est "+err.toStdString();
    }else{
         this->m_db = db;
         //on doit recuperer la liste des tables pour des control uterieur

        this->m_listTable =  db.tables(QSql::Tables);
    }
}

bool BDManager::verifTableExist(QString tablName){
   return  this->m_listTable.contains(tablName);
}

void BDManager::setUser(QString userName){
    this->m_userName = userName;
}

void BDManager::update(QString table, QString cdt){

}

void BDManager::select(QString table, QString cdt){

}

void BDManager::delet(QString table, QString cdt){

}

void BDManager::queryExec(QString query){

}

int BDManager::count(QString query){
    QSqlQuery req;

    if( req.exec("select count(idUtilisateur) from utilisateur")){

    }
}

void BDManager::insert(QString table, QStringList champ, QList<QVariant> value){

    /*
     * on doit permettre plutot d'envoyer la liste des champs pour insertion
     * et la liste des données a inserer
     * on va parcourir la liste et tester si les champ appartiennen t a la table
     * */

//    if(verifTableExist(table)){

//        listChamp = new QString("");
//        m_champ = new QSqlRecord();
//        m_champ = this->m_db.record(table); // on recupere la liste des champs

//        for(int i=0;i<= champ.length();i++ ){//ici on parcour liste des champs recus
//            if(this->m_champ->contains(champ.at(i)) ){ //on les compares avec ceux dans le tables
//                listChamp = listChamp +","+ champ.at(i);
//            }
//        }//in for i=a ce niveau la liste des champ a mettre dans le code sql est prete

//        listChamp = this->nettoyer(listChamp);// on nettoye la liste  pour enlever les virgules au tour des a chaine

//        //on doit maintenant preparer la liste des valeurs
//        QString cle;
//        for(int j = 0; j<=value.count();j++){
//            cle =cle + ","+ " :t"+j;
//        }

//        cle = this->nettoyer(cle); //on nettoy la cle

//        //on prepare la requete
//        QString *req = new QString("INSERT INTO" + table+"("+listChamp+")VALUES("+cle+")");//on cree la requete
//        requete.exec(req);
 //   }

}

bool BDManager::verifUserExist(QString userName){
    return true;
}

//QString BDManager::nettoyer(QString *txt){
//    int g = txt->length()-1;
//    if(txt[0] == ' ' || txt[0] == ',' || txt[g] == ','){
//        txt[0] = ' ';
//        txt[g] = ' ';
//    }
//    return txt;
//}

