#ifndef NETTOYANT_H
#define NETTOYANT_H

#include <QString>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QList>

#include "Articles.h"
#include"structure.h"

class Nettoyant : public Articles
{
public:
    Nettoyant(Articles *parent = 0);
    QString getReference();
    void setReference(QString r);
    ErrorManager addNettoyant(NettoyStruct nt);
    static void getListNettoyant();
    static QList<NettoyantCaractList> listNettoyant;
private:
    QString m_reference;

};

#endif // NETTOYANT_H
