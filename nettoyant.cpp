#include "nettoyant.h"

QList<NettoyantCaractList> Nettoyant::listNettoyant;

Nettoyant::Nettoyant(Articles *parent):
    Articles(parent)
{
}

QString Nettoyant::getReference(){
    return m_reference;
}

void Nettoyant::setReference(QString r){
    this->m_reference = r;
}

ErrorManager Nettoyant::addNettoyant(NettoyStruct nt){

    ErrorManager err;

    QString query("INSERT INTO nettoyant (idArticle, reference)values("+
                  QString::number(nt.id_art)+" , '"+nt.reference+"' )");

    QSqlQuery requete;
    if(!requete.exec(query)){
        err.code = 601;
        err.status = false;
        err.msgTech = requete.lastError().text();
        err.msg = "Echec d'enregistrement du nettoyant";
        return err;
    }else{
        err.code = 600;
        err.status = true;
        err.msg = "Enregistrement du nettoyant reussit ";
        return err;
        //ici l'enregistrement est fini ici
    }
}

void Nettoyant::getListNettoyant(){
    QSqlQuery requeteur;
    QString query("select idArticle, reference from nettoyant");
    Nettoyant::listNettoyant.clear();
    if(requeteur.exec(query)){
        while(requeteur.next()){//tant qu'on recupere
            NettoyantCaractList net;
            net.caracteristic = requeteur.value(requeteur.record().indexOf("reference")).toString();
            net.id_monture = requeteur.value(requeteur.record().indexOf("idArticle")).toInt();
            Nettoyant::listNettoyant << net;
        }
    }
}


