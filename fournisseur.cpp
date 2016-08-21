#include "fournisseur.h"

Fournisseur::Fournisseur()
{
}

Fournisseur::Fournisseur(QString nom, QString ville, QString matric, QString InfoSupp, int nbrLiv):
    m_nom(nom),m_ville(ville),m_nbrLiv(nbrLiv),m_matric(matric)
{
    //construction d'un fournisseur de toute piece
}

Fournisseur::Fournisseur(int id):
    m_id(id)
{

}

//constructeur de copie
Fournisseur::Fournisseur(Fournisseur const  &aCopier):
    m_id(aCopier.m_id),
    m_nbrLiv(aCopier.m_nbrLiv),
    m_nom(aCopier.m_nom),
    m_ville(aCopier.m_ville)
{
    //constructeur de copie
    //std::cout << "Le constructeur de copie"<< std::endl;
}

QString Fournisseur::getNom(){
    return this->m_nom;
}

QString Fournisseur::getVille(){
    return this->m_ville;
}

int Fournisseur::getNbrLiv(){
    return this->m_nbrLiv;
}

void Fournisseur::setNbrLiv(int nbr){
    this->m_nbrLiv = nbr;
}

void Fournisseur::setNom(QString nom){
    this->m_nom = nom;
}

void Fournisseur::setVille(QString ville){
    this->m_ville = ville;
}

void Fournisseur::setId(int id){
    this->m_id = id;
}

int Fournisseur::getId(){
    return this->m_id;
}
//matricule
QString Fournisseur::getMatricule(){
    return this->m_matric;
}

void Fournisseur::setMatricule(QString mat){
    this->m_matric = mat;
}

//info supp
QString Fournisseur::getInfoSupp(){
    return this->m_infoSupp;
}

void Fournisseur::setInfoSupp(QString info){
    this->m_infoSupp = info;
}

void Fournisseur::dump(QString txt){
    std::cout << "Dump d'un objet fournisseur-------------------debut--------------------- ["<< txt.toStdString() << std::endl;
    std::cout << "Id : "<< this->m_id <<  std::endl;
    std::cout << "Nom : "<< this->m_nom.toStdString() << std::endl;
    std::cout << "Ville :"<< this->m_ville.toStdString()<< std::endl;
    std::cout << "Matricule :" << this->m_matric.toStdString() << std::endl;
    std::cout << "Infos supplementaires :" << this->m_infoSupp.toStdString()<< std::endl;
    std::cout << "Dump de l'objet fournisseur terminier------------------fin-------" << std::endl;

}
