#include "verre.h"
#include "Articles.h"

QList<VerreCaractList> Verre::listverrec;

Verre::Verre(Articles *parent):
    Articles(parent)
{
}

int Verre::getIdVerre(){
    return this->idVerre;
}

QString Verre::getMatiere(){
    return this->m_matiere;
}

QString Verre::getInfoSupp(){
    return m_info_supp;
}

int Verre::getVergence(){
    return m_vergence;
}

void Verre::setMatiere(QString mat){
    m_matiere = mat;
}

void Verre::setVergence(int v){
    m_vergence = v;
}

void Verre::setInfoSupp(QString i){
    m_info_supp = i;
}

void Verre::setIdVerre(int id){
    idVerre = id;
}

ErrorManager Verre::addVerre(VerreStruct verre){
    ErrorManager err;
    QSqlQuery requete;

    QString query("insert into verres (idArticle,matiere,type,vergence)values('"+QString::number(verre.id_art)+"' , '"+verre.matiere+"' , '"+verre.type+"' ,'"+verre.vergence+"' )");

    if(requete.exec(query)){
        err.status = true;
        err.code = 600;
        err.msg = "Ajout de verre reussit";
         return err;
    }else{
        err.status = false;
        err.code = 601;
        err.msg = requete.lastError().text();
        err.msgTech = requete.lastQuery();
        return err;
    }
}

void Verre::getListVerre(){
    QSqlQuery requeteur;
    QString query("select verres.idVerres,verres.vergence,verres.matiere,verres.type, article_verre.nombre from verres,article_verre where article_verre.nombre <> 0 ");
    Verre::listverrec.clear();
    if(requeteur.exec(query)){
        while(requeteur.next()){
            VerreCaractList verre;
            verre.caracteris = requeteur.value(1/*requeteur.record().indexOf("vergence")*/).toString() + " " +
                    requeteur.value(2/*requeteur.record().indexOf("matiere"*/).toString() + " "+
                    requeteur.value(3/*requeteur.record().indexOf("type")*/).toString();
            verre.id_verre = requeteur.value(0/*requeteur.record().indexOf("idVerres")*/).toInt();
            Verre::listverrec << verre;
        }
    }
}
