#ifndef LOGENGINE_H
#define LOGENGINE_H

#include <QString>
#include <QFile>
#include <QIODevice>
#include <QTextStream>
#include <QTime>
#include <QDate>

#include "utilisateur.h"

/*
 * Cette classe a pour role de gerer les logs dans toutes l'application
 * elle stocke les donnees dans le fichier data.log
 * avec la fonction add_log() qui sera static
 * */
class LogEngine
{

private:

public:
    LogEngine();
    static void add_log(QString logdata); //cette methode sera appele partout dans le programme pour ajoute les log
};

#endif // LOGENGINE_H
