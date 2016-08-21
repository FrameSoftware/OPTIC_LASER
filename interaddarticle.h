#ifndef INTERADDARTICLE_H
#define INTERADDARTICLE_H

#include <QWidget>
#include <QMessageBox>
#include "Articles.h"
#include "articlemanager.h"
#include "interaddfournisseur.h"

namespace Ui {
class InterAddArticle;
}

class InterAddArticle : public QWidget
{
    Q_OBJECT

public:
    explicit InterAddArticle(QWidget *parent = 0);
    ~InterAddArticle();


private:
    Ui::InterAddArticle *ui;
    ArticleManager *artMan;
    InterAddFournisseur *inter_add_four;
    QString matricule;
public slots:
    void valider();
    void addFournisseur();
    void selectMatricule(QString text); //ce slot sert prendre le matricule
};

#endif // INTERADDARTICLE_H
