#ifndef MONTURE_H
#define MONTURE_H

#include "Articles.h"
#include "structure.h"

#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QList>

class Monture : public Articles
{
public:
    Monture(Articles *parent = 0);
    QString getMatiere();
    QString getTaille();

    void setMatiere(QString m);
    void setTaille(QString t);
    ErrorManager addMonture(MontureStruct monture);
    static void getListMontureCaract();
    static QList<MontureCaractList> monturelist_carac;
private:

    /*
     * cette liste contient les caracteristiques d'une minture et leurs [id]
     * */
    QString m_matiere, m_taille;
};

#endif // MONTURE_H
