#-------------------------------------------------
#
# Project created by QtCreator 2015-12-19T19:35:08
#
#-------------------------------------------------

QT       += core gui sql printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OPTIC_LASER
TEMPLATE = app


SOURCES += main.cpp\
        acceuil.cpp \
    internewvente.cpp \
    interparam.cpp \
    interadduser.cpp \
    bdmanager.cpp \
    vente.cpp \
    utilisateurmanager.cpp \
    utilisateur.cpp \
    interauthentif.cpp \
    #article.cpp
    interarcticle.cpp \
    interfournisseur.cpp \
    interaddfournisseur.cpp\
 InterRecherche.cpp \
    appmanager.cpp \
    fournisseur.cpp \
    fournisseurmanager.cpp \
    Articles.cpp \
    verre.cpp \
    nettoyant.cpp \
    monture.cpp \
    interaddarticle.cpp \
    articlemanager.cpp \
    interaddverre.cpp \
    interaddmont.cpp \
    interaddnettoy.cpp \
    uipatient.cpp \
    uiaddpatient.cpp \
    patients.cpp \
    uidiagostic.cpp \
    uiadddialog.cpp \
    uiadddiagnos.cpp \
    diagnosticmanager.cpp \
    lunnettesmanager.cpp \
    facturemanager.cpp \
    printdiagnos.cpp \
    printfacture.cpp \
    userpreferences.cpp \
    logengine.cpp \
    recherche.cpp \
    uificheclient.cpp \
    facturevente.cpp

HEADERS  += \
    acceuil.h \
    internewvente.h \
    interparam.h \
    interadduser.h \
    bdmanager.h \
    vente.h \
    utilisateurmanager.h \
    utilisateur.h \
    structure.h \
    interauthentif.h \
   # interarticle.h \
    #article.h
    interarcticle.h \
    interfournisseur.h \
    interaddfournisseur.h\
    InterRecherche.h \
    appmanager.h \
    fournisseur.h \
    fournisseurmanager.h \
    Articles.h \
    verre.h \
    nettoyant.h \
    monture.h \
    interaddarticle.h \
    articlemanager.h \
    interaddverre.h \
    interaddmont.h \
    interaddnettoy.h \
    uipatient.h \
    uiaddpatient.h \
    patients.h \
    uidiagostic.h \
    uiadddialog.h \
    uiadddiagnos.h \
    diagnosticmanager.h \
    lunnettesmanager.h \
    facturemanager.h \
    printdiagnos.h \
    printfacture.h \
    userpreferences.h \
    logengine.h \
    recherche.h \
    uificheclient.h \
    facturevente.h

FORMS    += acceuil.ui \
    vente.ui \
    internewvente.ui \
    interparam.ui \
    interadduser.ui \
    interauthentif.ui \
    #article.ui
    interarcticle.ui \
    interfournisseur.ui \
    interaddfournisseur.ui \
    interaddarticle.ui \
    interaddnettoyant.ui \
    interaddverre.ui \
    interaddmont.ui \
    interaddnettoy.ui \
    uipatient.ui \
    uiaddpatient.ui \
    uidiagostic.ui \
    uiadddialog.ui \
    uiadddiagnos.ui \
    printdiagnos.ui \
    printfacture.ui \
    userpreferences.ui \
    recherche.ui \
    uificheclient.ui \
    facturevente.ui

OTHER_FILES += \
    OPTIC_LASER/Note_de_codage.txt \
    G:/images/articl.jpg

