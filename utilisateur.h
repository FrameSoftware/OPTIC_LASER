#ifndef UTILISATEUR_H
#define UTILISATEUR_H

#include <QObject>

class Utilisateur : public QObject
{
    Q_OBJECT
public:
    Utilisateur(QObject *parent = 0);
    Utilisateur(QString nom, QString pnom, QString loggin,QString pass,
                QString nivAcc, QString postOcc,QObject *parent = 0);
    Utilisateur(int id,QString nom, QString pnom, QString loggin,QString pass,
                QString nivAcc, QString postOcc,QObject *parent = 0);
    Utilisateur(Utilisateur const &utilisateurCopier,QObject *parent = 0);
    QString getNom() const;
    QString getPrenom() const;
    QString getLoggin() const;
    QString getNivAcc() const;
    QString getPostOcc( )const;
    QString getPassword() const;

    void setPassword(QString pass); //devra etre surchargee
    void setNom(QString nom);
    void setPrenom(QString pnom);
    void setLoggin(QString loggin);
    void setNivAcc(int niv_acc);
    void setPostOcc(QString postOcc);
    static int m_id;

    static QString m_nom, m_pnom, m_loggin, m_postOcc,m_pass;
    static QString niv_acc;


signals:

public slots:

};

#endif // UTILISATEUR_H
