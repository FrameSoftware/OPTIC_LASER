#include <QDebug>
#include <QSqlDriver>
#include "appmanager.h"
#include "fournisseurmanager.h"



AppManager::AppManager(QObject *parent) :
    QObject(parent)
{
    //prevoir un fichier de configuration pour ces données
   //appBD.setHostName("localhost");
   //appBD.setDatabaseName("optic_plus");
    appBD.setDatabaseName("C:/Users/adonis_97/Documents/data/optic_plus_db.db");
   //appBD.setUserName("root");
   //appBD.setPassword("");
    //qDebug() << appBD.driver()->hasFeature(QSqlDriver::PreparedQueries);

}

ErrorManager AppManager::initDB(){
    if(appBD.open()) {
        QStringList list = appBD.tables();
        qDebug() << list;
        FournisseurManager::getFournisseurList(); // initialisation de la liste de fournisseur
       this->err.status = true;
        err.msg = "Connexion reussit";
        err.code = 200;
        return err;
    }else{
        this->err.status =false;
         err.msg = "Base de donnée introuvable \n <strong>["+appBD.lastError().text()+" ]</strong>";
         err.code = 404;
         return err;
    }
}

QSqlDatabase AppManager::getDB(){
    return this->appBD;
}

