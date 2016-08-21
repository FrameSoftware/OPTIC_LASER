#include "articlemanager.h"

ArticleManager::ArticleManager()
{
}



ErrorManager ArticleManager::addArticle(ArticleStruct art_strct){
    ErrorManager err;
    QSqlQuery requete;
    //qDebug()<< art_strct.matricule_four;

    QString value = "INSERT INTO article (nom,nbr,dateAchat,prix,info_supp)VALUES ('"+
            art_strct.nom+"', '"+QString::number(art_strct.nombre)+"', '"+
            art_strct.dateEntre.toString("yyyy/MM/dd")+"', '"+QString::number(art_strct.prix)+"', '"+
            art_strct.info_supp+"')";
    QString query_id = "SELECT MAX(idArticle)  FROM article as nbr"/*"select last_insert_id() from article"*/;//l'id du last (artificiel)


    if(requete.exec(value)){//on insere le nouvel article
        //qDebug() << requete.lastQuery();
//        std::cout <<std::endl;
//        std::cout <<value.toStdString()<< std::endl;
//        std::cout <<std::endl;

        int id_art;
        if(requete.exec(query_id)){//in selectionne l'id du dernier article max(id)
            if(requete.next()==true)
             id_art = requete.value(0).toInt();

            std::cout <<std::endl;
            std::cout <<requete.lastQuery().toStdString()<< std::endl;
            std::cout <<std::endl;

            QString query_finish ="insert into fournir(idArticle,matriculeFour,date,heure)values('"+
                    QString::number(id_art)+"', '"+art_strct.matricule_four+"','"+QDate::currentDate().toString("yyyy/MM/dd")+"','"+QDate::currentDate().toString("yyyy/MM/dd")+"') ";

            if(requete.exec(query_finish)){
                err.status = true;
                err.code = 200;
                err.id = id_art;
                err.msg = "Ajout de l'article reussit";
                return err;
            }else{
                err.status = false;
                err.code = 216; // code d'erreur lors de l'ajout dans la table fournir
                err.msg = requete.lastError().text() + "[ "+requete.lastQuery()+" ]";
                qDebug()<< requete.lastQuery();
                return err;
            }//requete 3
        }else{
            err.status = false;
            err.code = 217; // code d'erreur lors de la selection du dernier ID
            err.msg = requete.lastError().text()+"[ "+requete.lastQuery()+" ]";
            qDebug()<< requete.lastQuery();
            return err;
        }//requete 2
    }else{
        err.status = false;
        err.code = 215; // code d'erreur lors de l'ajout d'un article
        err.msg = requete.lastError().text()+"[ "+requete.lastQuery()+" ]";
        qDebug()<< requete.lastQuery();
        return err;
    }//requete 1


}

ErrorManager ArticleManager::addMonture(Monture m){

}

ErrorManager ArticleManager::addVerre(Verre v){

}

ErrorManager ArticleManager::addNettoy(Nettoyant n){

}

ErrorManager ArticleManager::deleteArticle(int id){
    QSqlQuery requete;
    ErrorManager err;
    requete.prepare("delete from article where idArticle = :i");
    requete.bindValue(":i",id);

    if(requete.exec()){
        err.status = true;
        err.msg = "Suppression de l'article reussit";
        return err;
    }else{
        err.status = false;
        err.msg = "Echec de suppression de l'article";
        err.msgTech = requete.lastError().text();
        return err;
    }
}
