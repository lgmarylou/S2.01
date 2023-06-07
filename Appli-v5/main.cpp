#include "lecteurVue.h"
#include "lecteur.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LecteurVue w;
    Lecteur *l = new Lecteur();
    l->changerDiaporama(1);

    w.setLecteur(l);
    w.show();
    return a.exec();
}
