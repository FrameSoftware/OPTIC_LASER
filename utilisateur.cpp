#include "utilisateur.h"

/*
 *
 * Classe qui represente un utilisateur
 *  methodes : getNom() , getPrenom(),getLoggin() , getNivAcces(), getPostOcc()
 *
 * */

int Utilisateur::m_id = 0;
QString Utilisateur::m_loggin = " ";
QString Utilisateur::m_nom =" ";
QString Utilisateur::m_pass=" ";
QString Utilisateur::m_pnom=" ";
QString Utilisateur::m_postOcc= " ";
QString Utilisateur::niv_acc = " ";

Utilisateur::Utilisateur(QObject *parent) :
    QObject(parent)
{

}

Utilisateur::Utilisateur(Utilisateur const &utilisateurCopier,QObject *parent) :
    QObject(parent)/*, m_nom(utilisateurCopier.m_nom),m_pnom(utilisateurCopier.m_pnom),
    m_id(utilisateurCopier.m_id),m_loggin(utilisateurCopier.m_loggin),
    niv_acc(utilisateurCopier.niv_acc),m_postOcc(utilisateurCopier.m_postOcc),
    m_pass(utilisateurCopier.m_pass)*/
{

}

Utilisateur::Utilisateur(QString nom, QString pnom, QString loggin, QString pass, QString  nivAcc, QString postOc, QObject *parent):
    /*m_nom(nom),m_pnom(pnom),m_loggin(loggin),m_pass(pass),niv_acc(nivAcc),m_postOcc(postOc),*/QObject(parent)
{

}

Utilisateur::Utilisateur(int id,QString nom, QString pnom, QString loggin, QString pass, QString  nivAcc, QString postOc, QObject *parent)
    :/*m_id(id),m_nom(nom),m_pnom(pnom),m_loggin(loggin),m_pass(pass),niv_acc(nivAcc),m_postOcc(postOc),*/QObject(parent)
{
    Utilisateur::m_id = id;
    Utilisateur::m_nom =nom;
    Utilisateur::m_pnom = pnom;
    Utilisateur::m_pass = pass;
    Utilisateur::m_postOcc = postOc;
    Utilisateur::m_loggin = loggin;
    Utilisateur::niv_acc = nivAcc;
}

QString Utilisateur::getNom() const{
    return m_nom;
}

QString Utilisateur::getPrenom() const{
    return m_pnom;
}

QString Utilisateur::getLoggin() const{
    return m_loggin;
}

QString Utilisateur::getNivAcc() const{
    return niv_acc;
}

QString Utilisateur::getPostOcc()const{
    return m_postOcc;
}

QString Utilisateur::getPassword() const{
    return m_pass;
}

//---------------- fin des getters ----------------------

void Utilisateur::setPassword(QString pass){
    m_pass = pass;
}

void Utilisateur::setNom(QString nom){
    m_nom = nom;
}

void Utilisateur::setPrenom(QString pnom){
    m_pnom = pnom;
}

void Utilisateur::setLoggin(QString loggin){
    m_loggin = loggin;
}

void Utilisateur::setNivAcc(int niv_acc){
    niv_acc = niv_acc;
}

void Utilisateur::setPostOcc(QString postOcc) {
    m_postOcc = postOcc;
}
