#include <QApplication>
#include <QStyleFactory>

#include "appmanager.h"
#include "interauthentif.h"
#include "acceuil.h"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  QApplication::setStyle(QStyleFactory::create("Fusion"));
  a.setWindowIcon(QIcon("icon_op+.png"));
  //a.setStyleSheet("QPushButton{color:blue;}");
  //Acceuil w;
   AppManager app;
  ErrorManager erreur;
  erreur = app.initDB();
  InterAuthentif authentification;

  if(erreur.status != true){
      QMessageBox::critical(0,"Erreur de connexion",erreur.msg);
      exit(01);//lorsque la connectio physique a la bd echoue
  }else{
      authentification.show();
  }

  return a.exec();
}
