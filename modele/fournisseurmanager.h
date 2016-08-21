#ifndef FOURNISSEURMANAGER_H
#define FOURNISSEURMANAGER_H

#include <QSqlQuery>
#include <QSqlDatabase>
#include <QSqlRecord>
#include <QSqlError>
#include <QDebug>
#include <QList>

#include "fournisseur.h"
#include "structure.h"

class FournisseurManager
{

public:
    FournisseurManager();
    ErrorManager addFournisseur(Fournisseur *four);
    void delFournisseur(int id_four);
    FournisseurStruct getFournisseurById(int id);//retourne un fournisseur par son id
    ErrorManager updateFournisseur(FournisseurStruct f);
    ErrorManager deleteFrournisseurById(int id_fournisseur);//ermet la suppression
    static void getFournisseurList();
    static QList<FourMat> listFourMat;//la liste
    static FourMat m_listFour;//les elements de la liste
private:
    Fournisseur *m_four;


    //Fournisseur *m_fourniss;
    //ErrorManager *err;
};

#endif // FOURNISSEURMANAGER_H
