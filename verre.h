#ifndef VERRE_H
#define VERRE_H

#include <QString>
#include <structure.h>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>

#include "Articles.h"

class Verre : public Articles
{
public:
    Verre(Articles *parent = 0);

    int getIdVerre();
    QString getMatiere();
    QString getInfoSupp();
    int getVergence();

    void setMatiere(QString mat);
    void setVergence(int v);
    void setInfoSupp(QString i);
    void setIdVerre(int id);
    ErrorManager addVerre(VerreStruct verre);
    static void getListVerre();
    static QList<VerreCaractList> listverrec;

private:
    int m_vergence;
    int idVerre;
    QString m_matiere, m_info_supp;
    ErrorManager err;

};

#endif // VERRE_H
