#include "monture.h"
#include "Articles.h"



QList<MontureCaractList>Monture::monturelist_carac;

Monture::Monture(Articles *parent):
    Articles(parent)
{
}

QString Monture::getMatiere(){
    return m_matiere;
}

QString Monture::getTaille(){
    return m_taille;
}

void Monture::setTaille(QString t){
    m_taille = t;
}

void Monture::setMatiere(QString m){
    m_matiere = m;
}

ErrorManager Monture::addMonture(MontureStruct monture){
    ErrorManager err;

    QString query("insert into monture(idArticle,matiere,taille)values("+
                  QString::number(monture.id_art)+",'"+
                  monture.matiere+"', '"+
                  monture.taille+"')");

    QSqlQuery requete;
    if(!requete.exec(query)){
        err.code = 601;
        err.status = false;
        err.msgTech = requete.lastError().text();
        err.msg = "Echec d'enregistrement de la monture";
        return err;
    }else{
        err.code = 600;
        err.status = true;
        err.msg = "Enregistrement de la monture reussit ";
        return err;
        //ici l'enregistrement est fini ici
    }
}

void Monture::getListMontureCaract(){
    QSqlQuery query;
    QString requete("select idMonture, matiere , taille from monture");
    Monture::monturelist_carac.clear();//on nettoy la liste ici
    if(query.exec(requete)){
        while(query.next()){
            MontureCaractList mont;
        mont.caracteristic = query.value(query.record().indexOf("matiere")).toString()+ " "+query.value(query.record().indexOf("taille")).toString();
            //la caracteristique est defini ici
            mont.id_monture = query.value(query.record().indexOf("idMonture")).toInt();
            //on converti l'id en entier
            monturelist_carac << mont;//on ajoute a la liste
        }
    }
}
//void Patients::getListPatient(){
//    QSqlQuery query;
//    QString req("select idClient,nom, prenom from clients");
//    Patients::listPatient.clear();//on vide ici
//    if(query.exec(req)){
//        while(query.next()){
//            PatientListStruct p;
//            p.identity = query.value(query.record().indexOf("nom")).toString()+" "+query.value(query.record().indexOf("prenom")).toString();
//            p.id_p =  query.value(query.record().indexOf("idClient")).toInt();
//            std::cout << p.identity.toStdString() << std::endl;
//            Patients::listPatient << p; // ici on qjoute dans la liste
//        }
//    }
//}
