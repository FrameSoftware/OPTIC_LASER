#ifndef PRINTDIAGNOS_H
#define PRINTDIAGNOS_H

#include <iostream>

#include <QWidget>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QtPrintSupport/QPrinter>
#include <QPainter>
#include <QtPrintSupport/QPrintDialog>
#include <QtPrintSupport/QAbstractPrintDialog>
#include <QtPrintSupport/QPageSetupDialog>
#include <QtPrintSupport/QPrintEngine>
#include <QtPrintSupport/QPrinterInfo>
#include <QtPrintSupport/QPrintPreviewWidget>
#include <QtPrintSupport/QtPrintSupport>
#include <QMessageBox>

#include "structure.h"
#include "patients.h"

namespace Ui {
class PrintDiagnos;
}

class PrintDiagnos : public QWidget
{
    Q_OBJECT

public:
    explicit PrintDiagnos(int id, QWidget *parent = 0);
    ~PrintDiagnos();
    void selectData();
    void afficheData();

private slots:
    void on_pushButton_2_clicked();

    void on_btnPrint_clicked();

private:
    Ui::PrintDiagnos *ui;
    int m_id;//va contenir l'id du diagnostic a prendre
    QSqlQuery *requetteur;
    PatientStruct *m_patient;//le patient en cour
    DiagnosStruct *m_diagnostic;
    QString enteteData;
    //inter;

};

#endif // PRINTDIAGNOS_H
