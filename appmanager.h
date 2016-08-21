#ifndef APPMANAGER_H
#define APPMANAGER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>
#include <QStringList>
#include "structure.h"

class AppManager : public QObject
{
    Q_OBJECT
public:
    explicit AppManager(QObject *parent = 0);
   ErrorManager initDB();//initialisa la connexion a la bd
    QSqlDatabase getDB();//retourne l'objet de connexion
    static QString trim(QString txt);

private:
     //QSqlDatabase appBD = QSqlDatabase::addDatabase("QMYSQL");
     QSqlDatabase appBD = QSqlDatabase::addDatabase("QSQLITE");
     struct ErrorManager err;
signals:

public slots:

};

#endif // APPMANAGER_H
