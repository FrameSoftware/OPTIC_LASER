#include <iostream>
#include <exception>
#include <QVariant>
#include "structure.h"
#include "fournisseurmanager.h"
/*
 * les code :
 * 123 erreur dans la reque exec() pour le count
 * 124 erreur dans la requete next() pour le count
 * 125 erreur dans la requete exec() pour l'insertion
 * 126 erreur dans la requet next pour l'insertion
 *
 * Nous devons prevoir la gestion et le control automatique du nbr de livraison
 *
 * */
QList<FourMat> FournisseurManager::listFourMat ;
FourMat  FournisseurManager::m_listFour ;//les elements de la liste
//cette list static sera la seule dans la memoire a contenir le nom et matricule des fournisseur

FournisseurManager::FournisseurManager()
{
    std::cout << "Initialisateion de fournisseur manager "<< std::endl;

}

ErrorManager FournisseurManager::addFournisseur(Fournisseur *four){
    //insertion du fournisseur dans la BD
   // initDB();
    ErrorManager err;
    QString count = "SELECT count(idfournisseur) +1 from fournisseur as val";
    QSqlQuery query;
    //on selectionne d'abord l'id actuel

   std::cout<< count.toStdString();
    if(!query.exec(count)) {
        err.status = false;
        err.code = 123;
        err.msg = query.lastError().text();
        return err;
    }else{
        //ici la requete s'est bien executer
        err.msg = query.lastError().text();
    }

    if(query.next() == true){ //s'il ya au moin un resultat
        four->setId(query.value(0).toInt());//on lui donne directement un id
       // std::cout << query.value(0).toInt()<< " l'id suivant";
    }else{//s'il nya rien
        err.status = false;
        err.code = 124;
        err.msg = query.lastError().text();
        return err;
    }
    //a ce niveau on a recuperer l'id suivant
    QString nom = four->getNom().left(1);
    //nom = nom.left(1); //les 1 premiers caractères du nom

    QString ville = four->getVille().left(3);
    //ville = ville.left(3);

    QString matricule;
    matricule = QString::number(four->getId()) + nom + ville; //le matricule est fini
    std::cout << four->getId();
    count = "INSERT INTO fournisseur(nom,ville,matriculefour,info_supp)values(' "+
            four->getNom().replace("'","''")+"' ,'"+four->getVille().replace("'","''")+"' ,'"+matricule+"', '"+four->getInfoSupp().replace("'","''")+"')";

    QSqlQuery req;
    req.prepare("insert into fournisseur (nom,ville,matriculefour,info_supp) values( ?,?,? ,?)");
    req.bindValue(0, four->getNom(),QSql::In);
    req.bindValue(1, four->getVille(),QSql::In);
    req.bindValue(2, matricule,QSql::In);
    req.bindValue(3,four->getInfoSupp(),QSql::In);

    //requete fini
    if(!req.exec(count)){
        err.status = false;
        err.code = 125;
        err.msg = req.lastError().text() +"<strong> [ "+req.lastQuery()+" ]</strong> ";
        return err;
    }else{
        err.status = true;
        err.code = 200;
        err.msg = "Ajout du fournisseur reussit";
        FournisseurManager::getFournisseurList();//mise a jour
        return err;
    }
    return err;
    }

FournisseurStruct FournisseurManager::getFournisseurById(int id){
    QSqlQuery requete;
   // requete.prepare("SELECT * FROM fournisseur where id = :id");
    //requete.bindValue(":id",id);

    QString com = "SELECT * FROM fournisseur where idFournisseur = "+QString::number(id);
    if(requete.exec(com)){

       int id = requete.record().indexOf("idFournisseur");
       std:: cout << "le nbr est " << requete.record().count()<< " "<< id << std::endl;

        while (requete.next()) {
        //Fournisseur  fournisseur(
            FournisseurStruct f;
                    f.nom = requete.value(1).toString(),//nom
                    f.ville =  requete.value(2).toString(),//ville
                     f.matricule = requete.value(3).toString(),//matricule
                    f.info_supp =  requete.value(4).toString(),//infoSupp
                     f.id = requete.value(0).toInt();
                     //requete.value(5).toInt());   //nombre de livraison
            //fournisseur.dump();
            //std::cout << requete.value(2).toString().toStdString()<< std::endl;
            return f; //on retourne le fournisseur
        }
    }else{
        qDebug()<< requete.lastError().text();
    }
}

void FournisseurManager::delFournisseur(int id_four){

}



ErrorManager FournisseurManager::updateFournisseur(FournisseurStruct f){
    QSqlQuery query;
    /*
     * pour le matricule on doit prendre l'id + 1 ere lettre du nom +3 premiere lettre de la ville
     * quand le fournisseur arrive ici les QString sont deja trimed()
     * */
    QString newMat = QString::number(f.id)+f.nom.left(1)+f.ville.left(3);
    //trimmed pour enlever les espaces au debut et a la fin

    ErrorManager h;
    //f.dump(); ici ON NE GERE PLUS QUE LES STRUCTURE FOURNISSEUR STRUCT
    QString com = "update fournisseur set nom ='"+f.nom+"' , ville ='"
            +f.ville+"' ,info_supp='"+f.info_supp+"', matriculeFour = '"
            +newMat+"' where idfournisseur ="+QString::number(f.id)+" ";

    if(!query.exec(com)){
        h.code = 125;//code d'echec de la requete
        h.msg = query.lastError().text()+" <br/><strong > requete : [ "+query.lastQuery()+" ] </strong>";
        h.status = false;
        return h;
    }else{
        h.code = 100; //code qui stipule que la mise a jour a reussit
        h.msg = "Mise a jour reussit";
        h.status = true;
        FournisseurManager::getFournisseurList();
        return h;
    }
}

void FournisseurManager::getFournisseurList(){
    //cette methode static retourne la liste des fournisseus
    listFourMat.clear();
    QSqlQuery req;
    QString query("select nom, matriculeFour from fournisseur");
    if(req.exec(query)){
        while(req.next()){
             FournisseurManager::m_listFour.nom_four = req.value(0).toString();
             FournisseurManager::m_listFour.matricule_four = req.value(1).toString();
            listFourMat << m_listFour;
        }//kan c'est fini on a rempli la liste
    }else{
        qDebug() << req.lastError().text();//prevoir les instruction pour les log ici
    }
}

ErrorManager FournisseurManager::deleteFrournisseurById(int id_fournisseur){
    ErrorManager err;
    QSqlQuery requeteur;
    requeteur.prepare("delete from fournisseur where idFournisseur = :id");
    requeteur.bindValue(":id",id_fournisseur);
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
