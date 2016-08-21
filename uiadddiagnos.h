#ifndef UIADDDIAGNOS_H
#define UIADDDIAGNOS_H

#include <QWidget>
#include <QMessageBox>

#include "patients.h"
#include "utilisateur.h"
#include "diagnosticmanager.h"
#include "uiaddpatient.h"

namespace Ui {
class UiAddDiagnos;
}

class UiAddDiagnos : public QWidget
{
    Q_OBJECT

public:
    explicit UiAddDiagnos(QWidget *parent = 0);
    UiAddDiagnos(DiagnosStruct d, QWidget *parent = 0);
    ~UiAddDiagnos();
    QString getIdentityById(int *id, QString *txt);

private slots:
    void on_btnValider_clicked();

    void on_cmbNom_currentIndexChanged(const QString &arg1);

    void on_btnAddPatient_clicked();

    void on_btnRefreshCmb_clicked();

    void on_cmbNom_activated(const QString &arg1);


private:
    bool state;
    int id;
    Ui::UiAddDiagnos *ui;
    QList<PatientListStruct> list; //la liste a afficher
    int id_client; //l'id du client selectionner actuellement
    DiagnosticManager *diag;
    UiAddPatient *addPass;
};

#endif // UIADDDIAGNOS_H
