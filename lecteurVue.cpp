#include "lecteurVue.h"
#include <QDebug>
#include "ui_lecteurVue.h"

LecteurVue::LecteurVue(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LecteurVue)
{
    ui->setupUi(this);
   // ui->statusbar->setStyleSheet("background-color:white");
    ui->statusbar->showMessage("Manuel");
    //Pour aligner les éléments das la status bar : tout mettre dans un layout puis mettre le layout dans le status bar
    //https://stackoverflow.com/questions/45791136/pyqt5-how-to-align-the-elements-of-the-status-bar

    QObject::connect(ui->bArreter, SIGNAL(clicked()), this, SLOT(stopDiapo()));
    QObject::connect(ui->bLancer, SIGNAL(clicked()), this, SLOT(lancerDiapo()));
    QObject::connect(ui->bPrecedent, SIGNAL(clicked()), this, SLOT(reculer()));
    QObject::connect(ui->bSuivant, SIGNAL(clicked()), this, SLOT(avancer()));

}

LecteurVue::~LecteurVue()
{
    delete ui;
}

void LecteurVue::avancer()
{
    qDebug() << "j'avance"<<Qt::endl;
}

void LecteurVue::reculer()
{
    qDebug() << "je recule"<<Qt::endl;
}

void LecteurVue::lancerDiapo()
{
    qDebug() << "je lance le diapo"<<Qt::endl;
}

void LecteurVue::stopDiapo()
{
    qDebug() << "je stop le diapo"<<Qt::endl;
}
