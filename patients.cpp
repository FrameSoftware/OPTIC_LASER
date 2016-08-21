#include "patients.h"
#include <iostream>


QList<PatientListStruct>Patients::listPatient ;

Patients::Patients()
{
}


ErrorManager Patients::addPatient(PatientStruct patient){
    std::cout << patient.info_supp.toStdString() <<  std::endl;
    QString query("INSERT INTO clients(nom,prenom,dateNaiss,sexe,info_supp) values('"+patient.nom+"' ,'"+patient.prenom+"','"
                  +patient.dateNaiss.toString("yyyy-MM-dd")+"' ,'"+patient.sexe+"','"+patient.info_supp+"')");

     QSqlQuery requete;
    if(requete.exec(query)){
        ErrorManager err;
        err.code = 700;
        err.status = true;
        err.msg = "Ajout du patients reussit";
        return err;
    }else{
        ErrorManager err;
        err.code = 701;
        err.status = false;
        err.msg = "Echec de sauvegarde du patient";
        err.msgTech = requete.lastError().text();
        return err;
    }
}

ErrorManager Patients::deletePatient(int id)
{
    ErrorManager err;
    QSqlQuery requeteur;
    requeteur.prepare("delete from clients where idClient = :id");
    requeteur.bindValue(":id",id);
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

ErrorManager Patients::updatePatient(PatientStruct patient, int id){
std::cout << patient.id <<  std::endl;
    QString query("update clients set nom = '"+patient.nom+"',prenom = '"+patient.prenom+"',dateNaiss = '"+patient.dateNaiss.toString("yyyy-MM-dd")
                  +"',sexe = '"+patient.sexe+"' ,info_supp = '"+patient.info_supp+"' where idClient = "+QString::number(id));

     QSqlQuery requete;
    if(requete.exec(query)){
        ErrorManager err;
        err.code = 700;
        err.status = true;
        err.msg = "Mise a jour  du patients reussit";
        std::cout <<requete.lastQuery().toStdString()<<  std::endl;
        return err;
    }else{
        ErrorManager err;
        err.code = 701;
        err.status = false;
        err.msg = "Echec de sauvegarde du patient";
        err.msgTech = requete.lastError().text();
        return err;
    }
}

PatientStruct Patients::getPatientById(int id){
    std::cout << id<<  std::endl;
    QString req("select * from clients where idClient = "+QString::number(id));
    std::cout << req.toStdString()<<  std::endl;
    QSqlQuery query;
    PatientStruct p;
    if(query.exec(req)){
        //std::cout <<"Reussit"<<  std::endl;
        if(query.next()){
            p.status = true;

            p.id = query.value(query.record().indexOf("idClient")).toInt();
            //std::cout <<"hydratation "<< p.id<<  std::endl;
            p.nom = query.value(query.record().indexOf("nom")).toString();
            p.prenom = query.value(query.record().indexOf("prenom")).toString();
            p.sexe = query.value(query.record().indexOf("sexe")).toString();
            p.info_supp = query.value(query.record().indexOf("info_supp")).toString();
            p.dateNaiss = query.value(query.record().indexOf("dateNaiss")).toDate();
            //la recuperation estterminer ici
            return p;
        }else{
            p.status = false;
            //std::cout << "echec hydratation"<<  std::endl;
            return p;
        }
    }else{
        p.status = false;
        std::cout <<"echec de la requete"<< p.status<<  std::endl;
        return p;
    }
}

void Patients::getListPatient(){
    QSqlQuery query;
    QString req("select idClient,nom, prenom from clients");
    Patients::listPatient.clear();//on vide ici
    if(query.exec(req)){
        while(query.next()){
            PatientListStruct p;
            p.identity = query.value(query.record().indexOf("nom")).toString()+" "+query.value(query.record().indexOf("prenom")).toString();
            p.id_p =  query.value(query.record().indexOf("idClient")).toInt();
            std::cout << p.identity.toStdString() << std::endl;
            Patients::listPatient << p; // ici on qjoute dans la liste
        }
    }
}
