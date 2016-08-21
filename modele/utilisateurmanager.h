#ifndef UTILISATEURMANAGER_H
#define UTILISATEURMANAGER_H


/*
 * Cette classse gere les utilisateurs
 *              ---ajout
 *              ---supp et autre
 * */

#include <iostream>
#include <QObject>
#include "utilisateur.h"
#include "structure.h"
#include "bdmanager.h"
#include <QStringList>
#include <QSqlDatabase>
#include <QSqlQuery>



class UtilisateurManager : public QObject
{
    Q_OBJECT
public:
    UtilisateurManager(QObject *parent = 0);
    //UtilisateurManager( Utilisateur *user = 0);
    QList<Utilisateur *> getUserList();
    bool addUser(UserStruct user);
    ErrorManager updateUser(UserStruct user, bool pass);
    void delUser(Utilisateur user);
    void initBD();
    ErrorManager authentificate(QString nom, QString pass);
    Utilisateur getUtilsateur(); // doit etre appele pour retourner l'utilistateur en
    //cour apres connexion

private:
    //Utilisateur *m_user;
    QSqlDatabase m_db;
    QStringList *m_listTable;
    QList<Utilisateur *> m_listUser;
    Utilisateur *m_user;
    QString *errMsg;


signals:

public slots:

};

#endif // UTILISATEURMANAGER_H
