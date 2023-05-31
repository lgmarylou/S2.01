#ifndef LECTEURVUE_H
#define LECTEURVUE_H

#include <QMainWindow>
#include "image.h"
#include "lecteur.h"
#include <QTimer>
#include <vector>


QT_BEGIN_NAMESPACE
namespace Ui { class LecteurVue; }
QT_END_NAMESPACE

typedef vector<Image*> Diaporama;   // Structure de données contenant les infos sur les image

class LecteurVue : public QMainWindow
{
    Q_OBJECT

public:
    LecteurVue(QWidget *parent = nullptr);
    ~LecteurVue();
    QTimer *timer;

public:
    //Méthodes get et set
    Lecteur* getLecteur();
    void setLecteur(Lecteur* l);

private:
    Ui::LecteurVue *ui;
    Lecteur* _leLecteur;

private slots:

     void avancer();
     void reculer();
     void lancerDiapo();
     void stopDiapo();
     void modeAuto();
    //Slots des actions
    void aPropos(); //Lié à action_a_propos
    void chargerDiapo(); //Lié à actionCharger_diapo
    void enleverDiapo(); //Lié à actionEnlever_diapo
    void quitterAppli();//+ quit() pour actionQuitter

    //Slots pour les catégories
    void debugAnimal();
    void debugPerso();
    void debugObjet();

    //Paramétrage des vitesses de défilement
    void vitesse0_5();
    void vitesse1();
    void vitesse2();


};
#endif // LECTEURVUE_H
