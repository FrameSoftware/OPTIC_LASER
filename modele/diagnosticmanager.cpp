#include "diagnosticmanager.h"
#include <iostream>
DiagnosticManager::DiagnosticManager()
{
}

ErrorManager DiagnosticManager::addDiagnostic(DiagnosStruct d){
    QSqlQuery requeteur;
//    QString query("insert into diagnostic (idClient,idUtilisateur,date,observation,correction) values ("+QString::number(d.idClient)
//                  + " , "+QString::number(d.idUser)+ " , '"+d.date.toString("yyyy-MM-dd") + "' ,'"+d.libelle+"' )");
    requeteur.prepare("insert into diagnostic (idClient,idUtilisateur,date,observation,correction) values (:idCli,:idUtil,:date,:obs,:corr)");
    requeteur.bindValue(":idCli",QString::number(d.idClient));
    requeteur.bindValue(":idUtil",QString::number(d.idUser));
    requeteur.bindValue(":date",d.date.toString("yyyy-MM-dd"));
    requeteur.bindValue(":obs",d.observation);
    requeteur.bindValue(":corr",d.correction);

    //l'on utilise maintenant le requette prepare pour l'insertion dans la BD
    ErrorManager err;
    int id_diag;
    if(!requeteur.exec()){//si bien executer on commence le reporting dans operation
        err.status = false;
        err.msg = "Echec de l'enregistrement du diagnostic";
        err.msgTech = requeteur.lastError().text() + "\n"+requeteur.lastQuery();
        err.code = 701;
        return err;
    }

    if(!requeteur.exec("select max(diagnostic.idDiagnostic)  as max_id from diagnostic")){
        err.status = false;
        err.msg = "Echec de l'enregistrement du diagnostic";
        err.msgTech = requeteur.lastError().text() + "\n"+requeteur.lastQuery();
        err.code = 702;
        return err;
    }

    if(!requeteur.next()){
        err.status = false;
        err.msg = "Echec de la recuperation de l'id du  diagnostique";
        err.msgTech = requeteur.lastError().text() + "\n"+requeteur.lastQuery();
        err.code = 705  ;
        return err;
    }
    id_diag = requeteur.value(0).toInt();//on recupere l'id du diagnostic enregistre
    qDebug() <<  id_diag;
    //on commence l'ajout dans operations
    requeteur.prepare("insert into operations(id_client,id_diag,type_operation,date_operation) values (:is_cli, :id_diag, :tp_op, :date)");
    //requeteur.prepare("insert into operations(idClient,idDiag,type_operation,date_operation) values (?, ?, ?, ?)");
    requeteur.bindValue(":is_cli",QString::number(d.idClient));
    requeteur.bindValue(":id_diag",id_diag);
    requeteur.bindValue(":tp_op","Diagnostique");
    requeteur.bindValue(":date",QDate::currentDate().toString("yyyy-MM-dd"));//le forma generale est requis ici
//        requeteur.bindValue(0,QString::number(d.idClient));
//        requeteur.bindValue(1,id_diag);
//        requeteur.bindValue(2,"Diagnostique");
//        requeteur.bindValue(3,QDate::currentDate().toString("yyyy-MM-dd"));//le forma generale est requis ici

    if(!requeteur.exec()){
        err.status = false;
        err.msg = "Echec de la creation de l'operation pendant l'enregistrement";
        err.msgTech = requeteur.lastError().text() + "\n"+requeteur.lastQuery();
        err.code = 703;
        return err;
    }

    err.status = true;
    err.msg = "Enregitrement du diagnostique reussit";

    err.code = 700;
    return err;

}

ErrorManager DiagnosticManager::updateDiagnostic(DiagnosStruct d, int id_D){
    QSqlQuery requeteur;

    QString query("update diagnostic set idClient = "+QString::number(d.idClient)+
                  ",idUtilisateur = "+QString::number(d.idUser)+",date = '"+d.date.toString("yyyy-MM-dd")+"' ,"+
                  "observation = '"+d.observation+"' , correction = '"+d.correction+"' where idDiagnostic = "+QString::number(id_D));//la requete de mise a jour est prete
    ErrorManager err;
    //requeteur.prepare("insert into diagnostic (idClient,idUtilisateur,date,observation,correction) values (:idCli,:idUtil,:date,:obs,:corr)");
//    requeteur.prepare("update diagnostic set idClient = :idCli , idUtlisateur = :idUtil , date = :date , observation = :obs , correction = :corr where idDiagnostic = :idDiag");
//    requeteur.bindValue(":idCli",d.idClient);
//    requeteur.bindValue(":idUtil",d.idUser);
//    requeteur.bindValue(":date",d.date.toString("yyyy-MM-dd"));
//    requeteur.bindValue(":obs",d.observation);
//    requeteur.bindValue(":corr",d.correction);
//    requeteur.bindValue(":idDiag",id_D);


    if(requeteur.exec(query)){
        err.status = true;
        err.msg = "Le diagnostic a bien ete mis a jour";
        err.code = 888;
        return err;
    }else{
        err.status = false;
        err.msg = "Echec de mise a jour du diagnostic";
        err.msgTech = requeteur.lastError().text() + "\n----"+requeteur.lastQuery();
        err.code = 889;
        return err;
    }
}

DiagnosStruct DiagnosticManager::getDiagnosticById(int id){
    QSqlQuery requeteur;
    QString query("select * from diagnostic where idDiagnostic="+QString::number(id));
    DiagnosStruct d;
    if(requeteur.exec(query)){

        while(requeteur.next()){
            d.date = requeteur.value(requeteur.record().indexOf("date")).toDate();
            d.idClient = requeteur.value(requeteur.record().indexOf("idClient")).toInt();
            d.idDiag = id;
            d.idUser = requeteur.value(requeteur.record().indexOf("idUtilisateur")).toInt();
            d.observation = requeteur.value(requeteur.record().indexOf("observation")).toString();
            d.correction = requeteur.value(requeteur.record().indexOf("correction")).toString();
        }
        return d;
    }else{
        d.observation = "vide";
        d.correction = "Vide";
        return d;
    }
}

ErrorManager DiagnosticManager::deleteDiagnostic(int id_D)
{
    ErrorManager err;
    QSqlQuery requeteur;
    requeteur.prepare("delete from diagnostic where idDiagnostic = :id");
    requeteur.bindValue(":id",id_D);
    if(requeteur.exec()){
        err.status = true;
        err.msg = "Suppression reussie";
        return err;
    }else {
        err.status = false;
        err.msg = "Echec de suppression";
        err.msgTech = requeteur.lastError().text();
        return err;
    }
}

