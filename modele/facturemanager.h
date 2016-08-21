#ifndef FACTUREMANAGER_H
#define FACTUREMANAGER_H

#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlResult>
#include <QSqlError>

#include "structure.h"

class FactureManager
{
public:
    FactureManager();
    ErrorManager addFacture(FactureStruct facture);
    ErrorManager deleteFacture(int id);
    int getIdClientFromIdFacture(int id_facture); // cette methode prend l'id d'une facture et retourne l'id du client
    FactureStruct getFactureById(int idFacture);//retourne une facture a artir de l'id
    //correspondant
};

#endif // FACTUREMANAGER_H
