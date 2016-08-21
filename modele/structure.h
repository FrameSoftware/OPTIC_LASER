#ifndef STRUCTURE_H
#define STRUCTURE_H

#include <QString>
#include <QVariant>
#include <QDate>

struct ErrorManager {
    bool status; // voir le status de retour
    QString msg; //contient le message d'errreur
    int code;
    QVariant objet;
    int id;
    QString msgTech;
};

struct FourMat {
    QString nom_four;
    QString matricule_four;
};

struct FournisseurStruct{
    QString nom;
    QString ville;
    QString matricule;
    QString info_supp;
    int id;
};

struct ArticleStruct {
    QString nom,info_supp;
    int prix,nombre,id;
    QDate dateEntre;
    QString matricule_four;
};

struct MontureStruct : public ArticleStruct {
    int id_art; //id de l'article
    QString taille;
    QString matiere;
};

struct VerreStruct {
    int id_art;
    QString vergence;
    QString matiere;
    QString type;
};

struct NettoyStruct{
    QString reference;
    int id_art;
};

struct PatientStruct{
    int id;
    bool status;
    QString nom, prenom, sexe,info_supp ;
    QDate dateNaiss;
};

struct PatientListStruct{
    QString identity;
    int id_p;
};

struct DiagnosStruct{
    int idClient, idUser,idDiag ;
    QString observation,correction;
    QDate date;
};

struct FactureStruct{//cette structure va contenir les details d'une facture 
    int idFact , idUtil, idClie,idLunn;
    QDate dateAchat;
    int nmFct,nbrMon, nbrNettoy, nbrOther;
    int puMont , puNet , puOther,prixTotal,nbrArticle;
    QString caractMon, caracNettoy, caracOther;
};

struct LunnettesStruct{//celle ci va contenir les details des lunnettes
    QString VL_OD, VL_OG , VP_OD , VP_OG; // les vergences
    int vlOgPu,vlOdPu,vpOgPu,vpOdPu,//les valeurs prix qte
        vlOgNbr,vlOdNbr,vpOgNbr,vpOdNbr;
    QString ogTraitement, odTraitement;
};

struct MontureCaractList{//pour manipuler sa on va gere une liste de sa
    QString caracteristic;
    int id_monture;
};
struct NettoyantCaractList{
    QString caracteristic;
    int id_monture;
};

struct VerreCaractList{
    QString caracteris;
    int id_verre;
};

struct artIdNbrStruct{
    int id_mont,id_net;
    int nbr_mont,nbr_net;
};

struct UserStruct{
     int m_id;
     QString m_nivAcc;
     QString m_nom, m_pnom, m_loggin, m_postOcc,m_pass;
     QString niv_acc;
};

struct SearchStruct{
    QString table;//le nom de la table
    QString data;//la donnée a rechercher
};

#endif // STRUCTURE_H
