#include "lecteurVue.h"
#include "lecteur.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LecteurVue w;
    Lecteur *l;
    l = new Lecteur();
    w.setLecteur(l);
    w.show();
    return a.exec();
}
