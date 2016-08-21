/***********************************************************************
 * Module:  Articles.h
 * Author:  STEVE MARCO
 * Modified: dimanche 27 septembre 2015 16:17:20
 * Purpose: Declaration of the class Articles
 ***********************************************************************/
#ifndef ARTICLES_H
#define ARTICLES_H

#include <QObject>
#include <QDate>
#include <QString>

class Articles : public QObject{

public:
    Articles(QObject *parent =0);
    Articles(Articles const &aCopier,QObject *parent =0);//constructeur de copie
    Articles(int id,QObject *parent =0);//constructeur du initialise un article avec son ID
    Articles( int prix, int nbr,QDate datee, QString nom,QObject *parent =0);

   int getIDArticle(void);
   void setIDArticle(int newIDArticle);

   int getPrix() const;
   int getNombre() const;
   QDate getDateEntree() const;
   QString getNomArticle() const;
   QString getType() const;
   QString getInfoSupp() const;
   QString getIdFour() const;

   void setNombre( int nbr);
   void setPrix(int p);
   void setDateEntree(QDate d);
   void setNomArticle(QString n);
   void setType(QString t);
   void setInfoSupp(QString info);
   void setIdFour(QString i);

private:
   int idArticle;
   QString m_nomArticle;
    int m_prix;
   int m_nombre;
   QDate m_dateEntree;
   QString m_type,m_infos;
   QString mat_four;
};

#endif //ARTICLES_H
