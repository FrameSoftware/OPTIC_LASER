#ifndef ARTICLEMANAGER_H
#define ARTICLEMANAGER_H

#include <iostream>

#include <QSqlQuery>
#include <QSqlError>
#include <QString>
#include<QDebug>
#include <QSqlRecord>

#include "Articles.h"
#include "verre.h"
#include "monture.h"
#include "nettoyant.h"
#include "structure.h"

class ArticleManager : public Articles
{
public:
    ArticleManager();
    ErrorManager addArticle(Articles art,QString mat, QString txt = " ");//ajout d'un article de base
    ErrorManager addArticle(ArticleStruct art_strct);
    ErrorManager addVerre(Verre v);//ajout de verre
    ErrorManager addMonture(Monture m);//ajout de monture
    ErrorManager addNettoy(Nettoyant n);//ajout de nettoyant
    ErrorManager deleteArticle(int id);//suppression d'article

private:

};

#endif // ARTICLEMANAGER_H
