#ifndef UIADDPATIENT_H
#define UIADDPATIENT_H

#include <QWidget>
#include <QMessageBox>
#include <QString>
#include "structure.h"
#include "patients.h"

namespace Ui {
class UiAddPatient;
}

class UiAddPatient : public QWidget
{
    Q_OBJECT

public:
    explicit UiAddPatient(QWidget *parent = 0);
    UiAddPatient(PatientStruct patient, int id, QWidget *parent = 0) ;
    ~UiAddPatient();

public slots:
    void on_btnValider_clicked();
private slots:
    void on_btnAnnul_clicked();

private:
    Ui::UiAddPatient *ui;
    bool modif;
    int id;
};

#endif // UIADDPATIENT_H
