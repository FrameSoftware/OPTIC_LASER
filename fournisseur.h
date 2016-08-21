#ifndef FOURNISSEUR_H
#define FOURNISSEUR_H

#include <iostream>
#include <QObject>
#include <QString>

class Fournisseur//contient la definition d'un fournisseur
{
public:
    Fournisseur();
    Fournisseur(QString nom, QString ville,QString matric,QString InfoSupp,int nbrLiv =0 );
    Fournisseur(int id); //pour avoir un fournisseur avec son id
    Fournisseur(Fournisseur const &aCopier);
    QString getNom();
    QString getVille();
    int getNbrLiv();
    int getId();
    QString getMatricule();
    QString getInfoSupp();

    void setNbrLiv(int nbr);
    void setNom(QString nom);
    void setVille(QString ville);
    void setId(int id);
    void setMatricule(QString mat);
    void setInfoSupp(QString info);

    void dump(QString txt = " ");

private:
    QString m_nom;
    QString m_ville;
    QString m_matric;
    QString m_infoSupp;
    int m_nbrLiv;
    int m_id;

};

#endif // FOURNISSEUR_H
