#ifndef BDMANAGER_H
#define BDMANAGER_H

#include <iostream>

#include <QString>
#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QStringList>
#include <QSqlRecord>


/*
 *
 * cette classe est chargée de manipuler les connexion a la base de données
 *   dans toute les methodes table represente le nom de la table dans la quelle il faudra
 * effectuer la resuette et cdt represente la condition de la requete (clause where)
 *
 * la procedure de control va consiter a verifier si la tables sur la quelle la requete va etre effectuer
 * existe reelement  et on verifie si l'utilisateur existe et peut effectuer cette action
 * *
 * pour sa on va cree un objet de type Utilisateur et va representer l'utilisateur en cour
 * et on va verifier son niveau d'acces
 * */
class BDManager : public QObject
{
    Q_OBJECT
public:
    BDManager();

    //virtual void method()  = 0;
    void execute(QString query);
    //les methode de gestion de la base de donnée

    void update(QString table, QString cdt=NULL);
    void select(QString table, QString cdt=NULL);
    void delet(QString table, QString cdt=NULL);
    void queryExec(QString query);
    void insert(QString table, QStringList champ, QList<QVariant> value);
    //champ la liste des champs et value la liste des valeurs
    //QString nettoyer(QString *txt);

    bool verifTableExist(QString tablName);
    bool verifUserExist(QString userName);
    void setUser(QString userName);
    int count(QString query);

private:
    QSqlRecord *m_champ;
    QSqlDatabase m_db;
    QStringList m_listTable;
    QString m_userName;
    QSqlRecord *champ;
    QString *listChamp;
    QSqlQuery requete;
};

#endif // BDMANAGER_H
