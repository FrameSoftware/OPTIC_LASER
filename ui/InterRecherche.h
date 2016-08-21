#ifndef INTER_RECHERCHE
#define INTER_RECHERCHE

#include <QWidget>
#include <QString>
#include <QHBoxLayout>
#include <QPushButton>
#include <QComboBox>
#include <QLineEdit>

class InterRecherche : public QWidget
{
Q_OBJECT
public:
    InterRecherche(QWidget *parent = 0);
public slots:
    void ModifierCible(QString maCible);
private:
    QString *cible;
    QHBoxLayout *bareRech;
    QComboBox *choix;
    QLineEdit *argument;
    QPushButton *valid;
};
#endif
