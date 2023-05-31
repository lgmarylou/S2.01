#include "lecteurVue.h"
#include <QDebug>
#include "ui_lecteurVue.h"
#include <QMessageBox>
#include <QSpacerItem>

LecteurVue::LecteurVue(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LecteurVue)
{
    ui->setupUi(this);
    // Création des widgets à ajouter à la barre de statut
    QLabel *modeDiapo = new QLabel("Manuel", this);
    QWidget *sbSpacer = new QWidget(this);
    QLabel *nomDiapo = new QLabel("nomDiapo", this);

    // Alignement des widgets
    ui->statusbar->addWidget(modeDiapo);
    ui->statusbar->addWidget(sbSpacer,1);
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
    QObject::connect(ui->actionEnlever_diapo, SIGNAL(triggered()), this, SLOT(enleverDiapo()));

    //Vitesses de défilement
    QObject::connect(ui->action0_5, SIGNAL(triggered()), this, SLOT(vitesse0_5()));
    QObject::connect(ui->action1, SIGNAL(triggered()), this, SLOT(vitesse1()));
    QObject::connect(ui->action2, SIGNAL(triggered()), this, SLOT(vitesse2()));

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
    if (timer->isActive())
    {
        timer->stop();
        timer->~QTimer(); //Détruit le timer
    }
    qDebug() << "je vais à l'image suivante"<<Qt::endl;
    ui->lImage->setPixmap(QPixmap(QString::fromUtf8(":/appliV2/cartesDisney/Disney_1.gif")));
    ui->lImage->setScaledContents(true);
    Image *image = _leLecteur->imageCourante();
    QString imageChemin = QString::fromStdString(image->getUrl());
    QString ImageCategorie = QString::fromStdString(image->getCategorie());
    QString imageTitre = QString::fromStdString(image->getTitre());
    int imageRang = image->getRang();

    ui->lIntitule->setText(imageTitre);
    ui->lCategorie->setText(ImageCategorie);
    ui->lRang->setNum(imageRang);
    ui->lImage->setPixmap(QPixmap(imageChemin));

    cout << endl;

}

void LecteurVue::reculer()
{
    if (timer->isActive())
    {
        timer->stop();
        timer->~QTimer(); //Détruit le timer
    }
    qDebug() << "je vais à l'image précédente"<<Qt::endl;
    ui->lImage->setPixmap(QPixmap(QString::fromUtf8(":/appliV2/cartesDisney/Disney_1.gif")));
    ui->lImage->setScaledContents(true);
    Image *image = _leLecteur->imageCourante();
    QString imageChemin = QString::fromStdString(image->getUrl());
    QString ImageCategorie = QString::fromStdString(image->getCategorie());
    QString imageTitre = QString::fromStdString(image->getTitre());
    int imageRang = image->getRang();

    ui->lIntitule->setText(imageTitre);
    ui->lCategorie->setText(ImageCategorie);
    ui->lRang->setNum(imageRang);
    ui->lImage->setPixmap(QPixmap(imageChemin));
}

void LecteurVue::lancerDiapo()
{

    if (timer->isActive())
    {
        qDebug() << "Timer déjà lancé"<<Qt::endl;
    }
    else
    {
        QTimer *timer = new QTimer;
      qDebug() << "je lance le diapo"<<Qt::endl;
      timer->connect(timer, SIGNAL(timeout()), this, SLOT(modeAuto));
      timer->start();
    }
}

void LecteurVue::stopDiapo()
{
    timer->~QTimer();
    qDebug() << "j'arrête le diapo"<<Qt::endl;

}

void LecteurVue::modeAuto()
{
    avancer();
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

void LecteurVue::vitesse0_5()
{
    qDebug() << "Je change la vitesse à x0.5"<<Qt::endl;
}

void LecteurVue::vitesse1()
{
    qDebug() << "Je change la vitesse à x1"<<Qt::endl;
}

void LecteurVue::vitesse2()
{
    qDebug() << "Je change la vitesse à x2"<<Qt::endl;
}

void LecteurVue::chargerDiapo() //Lié à actionCharger_diapo
{
    qDebug() << "Diapo chargé"<<Qt::endl;


}

void LecteurVue::enleverDiapo() //actionEnlever_diapo
{
    qDebug() << "Diapo enlevé"<<Qt::endl;
    ui->lImage->setText("Titre");
    ui->lCategorie->setText("");
    ui->lImage->setPixmap(QPixmap(""));
    ui->lRang->setNum(0);
    _leLecteur->changerDiaporama(0);
    ui->bPrecedent->setEnabled(false);
    ui->bSuivant->setEnabled(false);
    ui->bLancer->setEnabled(false);
    ui->bArreter->setEnabled(false);
}
