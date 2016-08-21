/***********************************************************************
 * Module:  Articles.cpp
 * Author:  STEVE MARCO
 * Modified: dimanche 27 septembre 2015 16:17:20
 * Purpose: Implementation of the class Articles
 ***********************************************************************/


#include "Articles.h"
Articles::Articles(QObject *parent):QObject(parent){

}

Articles::Articles(const Articles &aCopier,QObject *parent)://le constructeur de copie
    m_prix(aCopier.m_prix), m_nombre(aCopier.m_nombre),
    m_nomArticle(aCopier.m_nomArticle),idArticle(aCopier.idArticle),
    m_dateEntree(aCopier.m_dateEntree), QObject(parent)
{

}

Articles::Articles(int id, QObject *parent): idArticle(id)
{
    //ici prevoire le code pour charger une instance de la classe
    //a partir de la ligne correspondant a l'id recu
    //c'est une requete type SELECT * FROM ARTICLE WHERE ID = id
}

Articles::Articles( int prix,  int nbr, QDate datee, QString nom, QObject *parent):
   m_prix(prix),m_nombre(nbr),m_dateEntree(datee), m_nomArticle(nom)
{

}

int Articles::getIDArticle(void)
{
   return idArticle;
}
void Articles::setIDArticle(int newIDArticle)
{
   idArticle = newIDArticle;
}

int Articles::getPrix() const{
    return m_prix;
}

 int Articles::getNombre() const{
    return m_nombre;
}

QDate Articles::getDateEntree() const{
    return m_dateEntree;
}

QString Articles::getNomArticle() const{
    return m_nomArticle;
}

QString Articles::getType() const{
    return m_type;
}

QString Articles::getInfoSupp() const{
    return m_infos;
}

QString Articles::getIdFour() const{
    return mat_four;
}

void Articles::setNomArticle(QString n){
   this->m_nomArticle = n;
}

void Articles::setNombre(int nbr){
    this->m_nombre = nbr;
}

void Articles::setPrix( int p){
    this->m_prix = p;
}

void Articles::setDateEntree(QDate d){
    m_dateEntree = d;
}

void Articles::setType(QString t){
    m_type = t;
}

void Articles::setInfoSupp(QString info){
    m_infos = info;
}

void Articles::setIdFour(QString i) {
   mat_four = i;
}
