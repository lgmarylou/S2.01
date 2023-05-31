#include "lecteurVue.h"
#include <QDebug>
#include "ui_lecteurVue.h"
#include <QMessageBox>
#include <QSpacerItem>
#include <QListWidget>
#include <QListWidgetItem>

LecteurVue::LecteurVue(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LecteurVue)
{
    ui->setupUi(this);
    // Création des widgets à ajouter à la barre de statut
    QLabel *manuel = new QLabel("Manuel", this);
    QWidget *sbSpacer = new QWidget(this);
    QLabel *nomDiapo = new QLabel("nomDiapo", this);

    // Alignement des widgets
    ui->statusbar->addWidget(manuel);
    ui->statusbar->addWidget(sbSpacer,2);
    ui->statusbar->addWidget(nomDiapo);

    // Configuration des boutons
    QObject::connect(ui->bArreter, SIGNAL(clicked()), this, SLOT(stopDiapo()));
    QObject::connect(ui->bLancer, SIGNAL(clicked()), this, SLOT(lancerDiapo()));
    QObject::connect(ui->bPrecedent, SIGNAL(clicked()), this, SLOT(reculer()));
    QObject::connect(ui->bSuivant, SIGNAL(clicked()), this, SLOT(avancer()));

    // Configuration des actions
    QObject::connect(ui->actionQuitter, SIGNAL(triggered()), this, SLOT(quitterAppli()));
    QObject::connect(ui->action_a_propos, SIGNAL(triggered()), this, SLOT(aPropos()));
    QObject::connect(ui->actionCharger_diapo, SIGNAL(triggered()), this, SLOT(chargerDiapo()));
    QObject::connect(ui->actionVitesse_de_defilement, SIGNAL(triggered()), this, SLOT(changerVitesseDefilement()));
    QObject::connect(ui->actionEnlever_diapo, SIGNAL(triggered()), this, SLOT(enleverDiapo()));

    //Configuration des catégories
    QObject::connect(ui->cbPersonnage,SIGNAL(clicked()), this, SLOT(debugPerso()));
    QObject::connect(ui->cbAnimal,SIGNAL(clicked()), this, SLOT(debugAnimal()));
    QObject::connect(ui->cbObjet,SIGNAL(clicked()), this, SLOT(debugObjet()));

}

LecteurVue::~LecteurVue()
{
    delete ui;
}

Lecteur *LecteurVue::getLecteur()
{
    return _leLecteur;
}

void LecteurVue::setLecteur(Lecteur *l)
{
    _leLecteur = l;
}

void LecteurVue::avancer()
{
    qDebug() << "je vais à l'image suivante"<<Qt::endl;
    ui->lImage->setPixmap(QPixmap(QString::fromUtf8(":/appliV2/cartesDisney/Disney_1.gif")));
    ui->lImage->setScaledContents(true);
    cout << endl;

}

void LecteurVue::reculer()
{
    qDebug() << "je vais à l'image précédente"<<Qt::endl;
    ui->lImage->setPixmap(QPixmap(QString::fromUtf8(":/appliV2/cartesDisney/Disney_0.gif")));
    ui->lImage->setScaledContents(true);
}

void LecteurVue::lancerDiapo()
{
    qDebug() << "je lance le diapo"<<Qt::endl;
}

void LecteurVue::stopDiapo()
{
    qDebug() << "j'arrête le diapo"<<Qt::endl;
}

void LecteurVue::quitterAppli() //Lié à actionQuitter
{
    QMessageBox mbQuitter;

    mbQuitter.setWindowTitle("Quitter l'application");
    mbQuitter.setGeometry(0,1,1,1);
    mbQuitter.setText("Êtes-vous sûr(e) de vouloir quitter l'application ?");
    mbQuitter.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    int ret = mbQuitter.exec();

    switch(ret)
    {
        case QMessageBox::Ok:
            qDebug() << "je quitte l'appli"<<Qt::endl;
            QCoreApplication::instance()->quit();
        break;

    case QMessageBox::Cancel :
            qDebug() << "ne fais rien"<<Qt::endl;
        break;
    }

}

void LecteurVue::aPropos() //Lié à action_a_propos
{
    //qDebug() << "à propos de l'appli"<<Qt::endl;
    //Création de la boîte de message
     QMessageBox mbAPropos(nullptr);
      mbAPropos.setWindowTitle("A propos de l'application");
      mbAPropos.setText("Version : 2.0<br /><br />Date de création : 03/05/2023<br /><br />Auteurs : HAMCHOUCHE Kamelia, LOHIER Marylou et MAHSSINI Imane");
      mbAPropos.setDefaultButton(QMessageBox::Ok);
      int ret = mbAPropos.exec();
      if (ret==QMessageBox::Ok)
      {
            mbAPropos.close(); //Ferme seulement la boîte de dialogue
      }

}

void LecteurVue::debugAnimal()
{
    qDebug() << "Animal sélectionné"<<Qt::endl;
}

void LecteurVue::debugPerso()
{
    qDebug() << "Personnage sélectionné"<<Qt::endl;
}

void LecteurVue::debugObjet()
{
    qDebug() << "Objet sélectionné"<<Qt::endl;
}

void LecteurVue::chargerDiapo() //Lié à actionCharger_diapo
{
    qDebug() << "Diapo chargé"<<Qt::endl;


}

void LecteurVue::changerVitesseDefilement() //actionVitesse_de_defilement
{
    qDebug() << "vitesse changée"<<Qt::endl;
}

void LecteurVue::enleverDiapo() //actionEnlever_diapo
{
    qDebug() << "Diapo enlevé"<<Qt::endl;
}

/*
QListWidget *listeDisney = new QListWidget(nullptr);
QListWidgetItem *disney1 = new QListWidgetItem(QString::fromUtf8(":/appliV2/cartesDisney/Disney_1.gif"), nullptr, list);
listeDisney->insertItem(0, item1);
QListWidgetItem *disney2 = new QListWidgetItem(QIcon("C:\\Documents and Settings\\admin\\Desktop\\icons\\car.png"), "Sunset", list);

listeDisney->show();
*/
