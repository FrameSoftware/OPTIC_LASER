#ifndef PATIENTS_H
#define PATIENTS_H

#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QString>
#include <QList>

#include "structure.h"

class Patients
{
public:
    Patients();
    ErrorManager addPatient(PatientStruct patient);
    ErrorManager deletePatient(int id);
    ErrorManager updatePatient(PatientStruct patient, int id);
    PatientStruct getPatientById(int id); // retourne toutes les donnee sur un client
    static void getListPatient();
    static QList<PatientListStruct> listPatient;//la liste des patient utilise partout

private:

};

#endif // PATIENTS_H
