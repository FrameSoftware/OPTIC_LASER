#include "logengine.h"


LogEngine::LogEngine()
{
}

void LogEngine::add_log(QString logdata){

    QString file_path;
    QFile fichier("data/data.log");

    if(!fichier.open(QIODevice::WriteOnly | QIODevice::Text) )
        return;


    QTextStream out(&fichier);

    //l'on fait la sauvegarde ici
    out << QDate::currentDate().toString("yyyy-MM-dd")
        << " | "<< QTime::currentTime().toString("hh:mm:ss")
        << " | "<< logdata
        << " | "<< Utilisateur::m_nom << "\n";

}
