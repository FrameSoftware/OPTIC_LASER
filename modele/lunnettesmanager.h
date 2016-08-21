#ifndef LUNNETTESMANAGER_H
#define LUNNETTESMANAGER_H

#include "structure.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QSqlResult>

class LunnettesManager
{
public:
    LunnettesManager();
    ErrorManager saveLunnettes(LunnettesStruct lunnete); //cette methode ajoute une
    //lunnette et retourne son ID
    //      ErrorManager lunUpdate();
};

#endif // LUNNETTESMANAGER_H
