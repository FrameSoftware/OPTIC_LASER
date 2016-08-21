#ifndef DIAGNOSTICMANAGER_H
#define DIAGNOSTICMANAGER_H


#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QDebug>

#include "structure.h"

class DiagnosticManager
{
public:
    DiagnosticManager();
    ErrorManager addDiagnostic(DiagnosStruct d);//la methode qui permet d'ajouter le diagnostic
    ErrorManager updateDiagnostic(DiagnosStruct d, int id_D); //la methode de mise a jour
    DiagnosStruct getDiagnosticById(int id);//retourne un diagnostic
    ErrorManager deleteDiagnostic(int id_D);
};

#endif // DIAGNOSTICMANAGER_H
