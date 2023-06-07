#include "lecteurVue.h"
#include <QDebug>
#include "ui_lecteurVue.h"
#include <QMessageBox>
#include <QSpacerItem>
#include <QTimer>
#include <QSpinBox>
#include <QVBoxLayout>
#include <QInputDialog>

LecteurVue::LecteurVue(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LecteurVue)
{
    ui->setupUi(this);
    // Création des widgets à ajouter à la barre de statut
    QLabel *modeDiapo = new QLabel("Manuel", this);
    QWidget *sbSpacer = new QWidget(this);
    QLabel *nomDiapo = new QLabel("nomDiapo", this);

    timer = new QTimer(this);
    timer->setInterval(INTERVALLE_DEFAUT_TIMER*1000);
    connect(timer, SIGNAL(timeout()), this, SLOT(modeAuto()));

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
    QObject::connect(ui->actionVitesseDefilement, SIGNAL(triggered()), this, SLOT(changerVitesse()));

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
    if (timer->isActive())
    {
        timer->stop();
    }
    else
    {
        qDebug() << "AVANCER() : timer inactif"<<Qt::endl;
    }

    //ui->lImage->setScaledContents(true);
    _leLecteur->avancer();
    Image *image = _leLecteur->imageCourante();
    QString imageChemin = QString::fromUtf8(image->getUrl());
    QString ImageCategorie = QString::fromUtf8(image->getCategorie());
    QString imageTitre = QString::fromUtf8(image->getTitre());
   // unsigned int imageRang = image->getRang();

    qDebug() << "AVANCER() : recupération infos image à afficher"<<Qt::endl;
        ui->lImage->setPixmap(QPixmap(imageChemin));
    //ui->lImage->setPixmap(QPixmap(QString::fromUtf8(":/appliV2/cartesDisney/Disney_1.gif")));
    qDebug() << "AVANCER() : image affichee"<<Qt::endl;
    ui->lIntitule->setText(imageTitre);
    ui->lCategorie->setText(ImageCategorie);

   //ui->lRang->setNum(imageRang);
}


void LecteurVue::reculer()
{
       qDebug() << "je vais à l'image précédente"<<Qt::endl;
    if (timer->isActive())
    {
        timer->stop();
    }
    else
    {
        qDebug() << "RECULER() : timer inactif"<<Qt::endl;
    }
    _leLecteur->reculer();

    Image *image = _leLecteur->imageCourante();
    QString imageChemin = QString::fromUtf8(image->getUrl());
    QString ImageCategorie = QString::fromUtf8(image->getCategorie());
    QString imageTitre = QString::fromUtf8(image->getTitre());
    int imageRang = image->getRang();

    ui->lImage->setPixmap(QPixmap(imageChemin));
    ui->lImage->setScaledContents(true);

    ui->lIntitule->setText(imageTitre);
    ui->lCategorie->setText(ImageCategorie);
    ui->lRang->setNum(imageRang);
    ui->lImage->setPixmap(QPixmap(imageChemin));
}

void LecteurVue::lancerDiapo()
{

      qDebug() << "je lance le diapo"<<Qt::endl;

      timer->start();
}

void LecteurVue::stopDiapo()
{
    timer->stop();
    qDebug() << "j'arrête le diapo"<<Qt::endl;

}

void LecteurVue::modeAuto()
{
    avancer();
    timer->start();
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

void LecteurVue::changerVitesse()
{
    bool ok;

    QSpinBox sbVitesse;
    sbVitesse.setRange(0, 100);
    sbVitesse.setValue(4);
    int choix = QInputDialog::getInt(&sbVitesse, "Changer la vitesse de défilement", "Choisissez une vitese (en secondes)", 4, 0, 100, 1, &ok);
    timer->setInterval(choix*1000);

    qDebug() << choix << Qt::endl;
}

void LecteurVue::vitesse()
{


}

void LecteurVue::chargerDiapo() //Lié à actionCharger_diapo
{
    qDebug() << "Diapo chargé"<<Qt::endl;
    ui->lImage->setText("Chien");
    ui->lCategorie->setText("animal");
    ui->lImage->setPixmap(QPixmap(":/appliV2/cartesDisney/Disney_1.gif"));
    ui->lRang->setNum(1);
    _leLecteur->changerDiaporama(0);
    ui->bPrecedent->setEnabled(true);
    ui->bSuivant->setEnabled(true);
    ui->bLancer->setEnabled(true);
    ui->bArreter->setEnabled(true);

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
