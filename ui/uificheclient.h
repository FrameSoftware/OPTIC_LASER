#ifndef UIFICHECLIENT_H
#define UIFICHECLIENT_H

#include <iostream>

#include <QWidget>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlResult>
#include <QSqlError>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QStringList>


#include "patients.h"
#include "structure.h";

namespace Ui {
class UiFicheClient;
}

class UiFicheClient : public QWidget
{
    Q_OBJECT

public:
    explicit UiFicheClient(int id_client,QWidget *parent = 0);
    ~UiFicheClient();


private:
    Ui::UiFicheClient *ui;
    int m_id_client;
    PatientStruct m_patient;
    Patients *m_patientManager;
    QSqlQuery *requet;
    QStandardItemModel *model_achat, *model_diagnostique;
};

#endif // UIFICHECLIENT_H
