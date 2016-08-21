#include "utilisateurmanager.h"
#include <QDebug>

UtilisateurManager::UtilisateurManager(QObject *parent) :
    QObject(parent)
{

}

QList<Utilisateur *> UtilisateurManager::getUserList(){//retourne la liste des utilisateurs dans la BD
    //this->initBD();
    QSqlQuery req;
    m_listUser.clear();
    req.exec("select nom,prenom,loggin,nivAcc,poste from utilisateur");
    int idChamp = req.record().indexOf("idUtilisateur");
    int nomChamp = req.record().indexOf("nom");
    int pnomChamp = req.record().indexOf("prenom");
    int logginChamp = req.record().indexOf("loggin");
    int nivChamp = req.record().indexOf("nivAcc");
    int postChamp = req.record().indexOf("poste");

     std::cout << req.lastError().text().toStdString()<<std::endl;

    while(req.next()){ //on boucle sur le resultat et on cree un objet user que lon initialise et on le stock dans la liste
        m_user = new Utilisateur (req.value(idChamp).toInt(),
                                                    req.value(nomChamp).toString(),
                                                    req.value(pnomChamp).toString(),
                                                    req.value(logginChamp).toString(),
                                                    req.value(logginChamp).toString(),
                                                    req.value(nivChamp).toString(),
                                                    req.value(postChamp).toString());

        m_listUser << m_user; //stockage ici

    }
    return m_listUser;
}



bool UtilisateurManager::addUser(UserStruct user){//a retravailler
   // this->initBD();
    //std::cout<< user->getNom().toStdString()<< "ici";
    std::cout << user.m_nom.toStdString();
    QSqlQuery req;
    req.prepare("insert into utilisateur(nom,prenom,loggin,pass,nivAcc,poste) values(:n,:p,:l,:pss,:na,:po)");
    req.bindValue(":n",user.m_nom);
    req.bindValue(":p",user.m_pnom);
    req.bindValue(":l",user.m_loggin);
    req.bindValue(":pss",user.m_pass);
    req.bindValue(":na",user.m_nivAcc);
    req.bindValue(":po",user.m_postOcc);
        if(req.exec()){
            std::cout << "reussi"<<std::endl;
            return true;
        }else{
             //QMessageBox::warning(this,"Echec",req.lastError().text());
            std::cout << "echec"<< req.lastError().text().toStdString()<<std::endl;
            return false;
        }
}

void UtilisateurManager::delUser(Utilisateur user){

}

void UtilisateurManager::initBD(){
    QSqlDatabase  db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("optic_plus");
    db.setUserName("root");
    db.setPassword("");

    if(db.open()){
//        QMessageBox::warning(this,"Erreur de connexion a la base de donnée", " <strong>Message :</strong>"+err);
        std::cout << "ouverture"<<std::endl;
    }else{
        errMsg = new QString(db.lastError().text());
    }

}

ErrorManager UtilisateurManager::authentificate(QString nom, QString pass){
   // this->initBD();
     ErrorManager err;
    QSqlQuery query;
   // qDebug()<< "SELECT * FROM utilisateur WHERE nom =  '"+nom+" ' AND pass = '"+pass+"' ";
    //----------------------------------------------------------------------------------------------------------------------------
    if(query.exec("SELECT * FROM utilisateur WHERE loggin =  '"+nom+"' AND pass = '"+pass+"' limit 0, 1")){
         //qDebug()<< "ici";
        int id = query.record().indexOf("idUtilisateur");
        int nomChamp = query.record().indexOf("nom");
        int pnomChamp = query.record().indexOf("prenom");
        int logginChamp = query.record().indexOf("loggin");
        int passChamp = query.record().indexOf("pass");
        int nivChamp = query.record().indexOf("nivAcc");
        int postChamp = query.record().indexOf("poste");

       if(query.next()){ ///ici on verifie dabors que la requete a retourner quelque chose
            m_user = new Utilisateur(query.value(id).toInt(),
                                    query.value(nomChamp).toString(),
                                     query.value(pnomChamp).toString(),
                                      query.value(logginChamp).toString(),
                                      query.value(passChamp).toString(),
                                      query.value(nivChamp).toString(),
                                      query.value(postChamp).toString()
                         );
           err.status = true;   // on renseigne le statud
           err.code = query.value(id).toInt();  //la valeur de code (id de l'utilisateur)
           //qDebug()<<  query.lastQuery();
           query.exec("uptdate utilisateur set statut = 1 where nom = '"+nom+"' and pass='"+pass+"' ");
           return err;//on retourne la structure

       }else {//dans ce cas si les credentials ne se trouvent pas dans la BD
            //qDebug()<<query.lastError().text();
           err.status = false;
           err.msg = "Nom ou mot de passe inexistant  erreur";
           return err;
       }

    }else{//dans ce cas ci il ya erreur dans la requete
         //qDebug()<<query.lastError().text();
        err.status = false;
        QString msgErr = query.lastError().text();
        err.msg = "Erreur: <strong> ["+query.lastError().text()+"]</strong>";
        return err;
    }
}

Utilisateur UtilisateurManager::getUtilsateur(){
    return this->m_user; // on retourne l'utilisateur
}

/**
 * Cette methode retourne un pointeur sur err qui contient le retour sur la mise a jour des data de l'utilisateur courant
 *
 * @brief UtilisateurManager::updateUser
 * @param user
 * @param pass
 * @return *ErrorManager
 */
ErrorManager UtilisateurManager::updateUser(UserStruct user , bool pass){
    ErrorManager err ;
    QSqlQuery *req = new QSqlQuery();

    if(pass == true){//dans le cas ou on modifie le mot de passe
        req->prepare("update utilisateur set nom = :n ,prenom = :pn  ,  loggin = :log , pass = :pss  where idUtilisateur = :id");
        req->bindValue(":n",user.m_nom);
        req->bindValue(":pn",user.m_pnom);
        req->bindValue(":log",user.m_loggin);
        req->bindValue(":pss", user.m_pass);
        req->bindValue(":id", user.m_id);
    }else{//le cas contraire
        req->prepare("update utilisateur set nom = :n , prenom = :pn  , loggin = :log  where idUtilisateur = :id ");
        req->bindValue(":n",user.m_nom);
        req->bindValue(":pn",user.m_pnom);
        req->bindValue(":log",user.m_loggin);
        req->bindValue(":id", user.m_id);
    }



    //qDebug()<<  req <<" le requetteur ;) !!!";

    if(!req->exec()){
        err.status = false;
        err.code = 404;
        err.msg = "Erreur de mise a jour";
        err.msgTech = req->lastError().text();
        qDebug()<< req->lastError().databaseText();
        return err;
    }

    err.status = true;
    err.code = 400;
    err.msg = "Mise a jour reussie";
    return err;
}
