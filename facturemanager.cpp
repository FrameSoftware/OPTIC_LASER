#include "facturemanager.h"
#include <QDebug>
#include <QString>

FactureManager::FactureManager()
{
}

ErrorManager FactureManager::addFacture(FactureStruct facture){
    QSqlQuery requetteur;
    ErrorManager err;
    QString e;
    QString requete;
    requete = "INSERT INTO facture(idClient,idUtilisateur,id_lun,dateCreation,montTotal,nbrArticle,caract_mon,nbr_mon,pu_mon,caract_nettoy,nbr_nettoy,pu_nettoy,lib_autres,nbr_other,pu)VALUES('"+
    QString::number(facture.idClie)+"','"+QString::number(facture.idUtil)+"','"+ QString::number(facture.idLunn)+"','"+QDate::currentDate().toString()+"','"+QString::number(facture.prixTotal)+"','"+QString::number(facture.nbrArticle)+
    "','"+facture.caractMon+"','"+QString::number(facture.nbrMon)+"','"+QString::number(facture.puMont)+
    "','"+facture.caracNettoy+"','"+QString::number(facture.nbrNettoy)+"','"+QString::number(facture.puNet)+"','"+facture.caracOther+"','"+QString::number(facture.nbrOther)+"','"+QString::number(facture.puOther)+"')";

    if(requetteur.exec(requete)){

        e = "select max(idFacture) as id from facture";

        if(requetteur.exec(e)){

            qDebug()<< "lancement";
            int id_fact = requetteur.value(requetteur.record().indexOf("id")).toInt();

            //on va commence a sauvegarde l'operation maintenant que c'est fait
            requetteur.prepare("insert into operations(id_client,id_facture,type_operation,date_operation) values (:is_cli, :id_diag, :tp_op, :date)");
            requetteur.bindValue(":is_cli",QString::number(facture.idClie));
            requetteur.bindValue(":id_diag",id_fact);
            requetteur.bindValue(":tp_op","Achat");
            requetteur.bindValue(":date",QDate::currentDate().toString("yyyy-MM-dd"));//le forma generale est requis ici

            if(!requetteur.exec()){
                err.status = false;
                err.code = 958;
                err.msg = "Erreur lors de la creation de l'operation";
                err.msgTech = "[ "+requetteur.lastError().text()+" ] \n["+requetteur.lastQuery()+" ]";
                return err;
            }

            err.status = true;
            err.id = id_fact;
            err.code = 950;
            err.msg = "Insertion reusie";
            return err;
        }else{
            err.status = false;
            err.code = 951;
            err.msg = "Erreur lors de la recuperation de la facture";
            err.msgTech = "[ "+requetteur.lastError().text()+" ] ["+requetteur.lastQuery()+" ]";
            return err;
        }
    }else{
        err.status = false;
        err.code = 952;
        err.msg = "Erreur lors de la sauvegarde de la facture";
        err.msgTech = "[ "+requetteur.lastError().text()+" ] ["+requetteur.lastQuery()+" ]";
        return err;
    }
}

int FactureManager::getIdClientFromIdFacture(int id_facture){
    QSqlQuery query;
    query.prepare("select idClient from facture where idFacture = :idFact");
    query.bindValue(":idFact", id_facture);
    if(query.exec()){
        if(query.next()){
            return query.value(0).toInt();//on retourn l'id selectionner
        }else{
            return -1;//si c'est next qui echou
        }
    }else{
        return -2; // si c'est select qui echoue
    }
}

ErrorManager FactureManager::deleteFacture(int id){
    QSqlQuery requete;
    ErrorManager err;
    requete.prepare("delete from facture where idFacture = :i");
    requete.bindValue(":i",id);

    if(requete.exec()){
        err.status = true;
        err.msg = "Suppression de la facture reussie";
        return err;
    }else{
        err.status = false;
        err.msg = "Echec de suppression de la facture";
        err.msgTech = requete.lastError().text();
        return err;
    }
}
