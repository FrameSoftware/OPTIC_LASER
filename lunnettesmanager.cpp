#include "lunnettesmanager.h"
#include <iostream>

LunnettesManager::LunnettesManager()
{
}

ErrorManager LunnettesManager::saveLunnettes(LunnettesStruct lunnete){
    //ici on va ecrire le code pour la sauvegarde des lunnettes

    QSqlQuery requeteur;
    ErrorManager err;

    QString requete("INSERT INTO lunnettes(vl_od,vl_od_qte,vl_od_pu,vl_og,vl_og_qte,vl_og_pu,vp_od,vp_od_qte,vp_od_pu,vp_og,vp_og_qte,vp_og_pu,og_traitement,od_traitement)"
    "VALUES ('"+ lunnete.VL_OD+"','"+QString::number(lunnete.vlOdNbr)+"','"+QString::number(lunnete.vlOdPu)+"','"+ lunnete.VL_OG+"','"+QString::number(lunnete.vlOgNbr)+"','"+QString::number(lunnete.vlOgPu)+"','"+lunnete.VP_OD+"','"
    +QString::number(lunnete.vpOdNbr)+"','"+QString::number(lunnete.vpOdPu)+"','"+lunnete.VP_OG+"','"+QString::number(lunnete.vpOgNbr)+"','"+QString::number(lunnete.vpOgPu)+"','"+lunnete.ogTraitement+"','"+lunnete.odTraitement+"')");
    if(requeteur.exec(requete)){
        std::cout << "insertion dans lunnete "<< requete.toStdString()<< std::endl;
        requete = "select max(id_lun) as max from lunnettes";
        if(requeteur.exec(requete)){
            requeteur.next();
            std::cout << "insertion dans lunnete "<< requete.toStdString()<< std::endl;
            err.code = 900;
            err.status = true;
            err.id = requeteur.value(requeteur.record().indexOf("max")).toInt();
            //on met les nombres a jour
            //if(requeteur.exec("select nbr as nbr from article where idArticle = 1"))
            return err;
        }else{
            err.code = 901;
            err.status = false;
            err.msg = "Echec lors de la selection des lunnettes";
            err.msgTech = "[ "+requeteur.lastError().text() +" ] Erreur ["+requeteur.lastQuery()+"]";
            return err;
        }
    }else{
        err.code = 902;
        err.status = false;
        err.msg = "Echec lors de la sauvegarde de lunne";
        err.msgTech = "[ "+requeteur.lastError().text() +" ] Erreur ["+requeteur.lastQuery()+"]";
        return err;
    }
}
