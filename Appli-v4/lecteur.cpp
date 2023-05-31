#include "lecteur.h"

Lecteur::~Lecteur()
{

}

Lecteur::Lecteur()
{
    _numDiaporamaCourant = 0;   // =  le lecteur est vide
}

void Lecteur::avancer()
{
    _posImageCourante = (_posImageCourante + 1) % nbImages();
    cout << endl;
}

void Lecteur::reculer()
{
    if (_diaporama.empty()) {
        // le diaporama est vide, rien à faire
        return;
    }

    // décrémente _posImageCourante en prenant en compte le modulo nbImages()
    _posImageCourante = (_posImageCourante + nbImages() - 1) % nbImages();
}

void Lecteur::changerDiaporama(unsigned int pNumDiaporama)
{
    // s'il y a un diaporama courant, le vider, puis charger le nouveau Diaporama
    if (numDiaporamaCourant() > 0)
    {
        viderDiaporama();
    }
    _numDiaporamaCourant = pNumDiaporama;
    if (numDiaporamaCourant() > 0)
    {
        chargerDiaporama(); // charge le diaporama courant
    }

}

void Lecteur::chargerDiaporama()
{
    /* Chargement des images associées au diaporama courant
       Dans une version ultérieure, ces données proviendront d'une base de données,
       et correspondront au diaporama choisi */
    Image* imageACharger;
    imageACharger = new Image(3, "personne", "Blanche Neige", ":/appliV2/cartesDisney/Disney_0.gif");
    _diaporama.push_back(imageACharger);
    imageACharger = new Image(2, "personne", "Cendrillon", ":/appliV2/cartesDisney/Disney_1.gif");
    _diaporama.push_back(imageACharger);
    imageACharger = new Image(4, "animal", "Mickey", ":/appliV2/cartesDisney/Disney_10.gif");
    _diaporama.push_back(imageACharger);
    imageACharger = new Image(1, "personne", "Grincheux", ":/appliV2/cartesDisney/Disney_21.gif");
    _diaporama.push_back(imageACharger);


     // trier le contenu du diaporama par ordre croissant selon le rang de l'image dans le diaporama
	 // A FAIRE
    // trier le contenu du diaporama par ordre croissant selon le rang de l'image dans le diaporama avec le tri à bulle
       bool sorted = false;
       int n = _diaporama.size();
       while (!sorted) {
           sorted = true;
           for (int i = 1; i < n; i++) {
               if (_diaporama[i-1]->getRang() > _diaporama[i]->getRang()) {
                   swap(_diaporama[i-1], _diaporama[i]);
                   sorted = false;
               }
           }
           n--;
       }
	 
     _posImageCourante = 0;

     cout << "Diaporama num. " << numDiaporamaCourant() << " selectionne. " << endl;
     cout << nbImages() << " images chargees dans le diaporama" << endl;

}

void Lecteur::viderDiaporama()
{
    if (nbImages () > 0)
    {
        unsigned int taille = nbImages();
        for (unsigned int i = 0; i < taille ; i++)
        {
            _diaporama.pop_back(); /* Removes the last element in the vector,
                                      effectively reducing the container size by one.
                                      AND deletes the removed element */
        }
     _posImageCourante = 0;
    }
    cout << nbImages() << " images restantes dans le diaporama." << endl;

}

void Lecteur::afficher()
{
    /* affiche les informations sur le lecteur :
     * 1) vide (si num. de diaporama = 0) OU BIEN  numéro de diaporama affiché
     * 2) Si un diaporama courant est chargé (num. de diaporama > 0), affiche l'image courante OU BIEN 'diaporama vide'
     *     si ce diaporama n'a aucun image */
    if (numDiaporamaCourant() == 0)
    {
        cout << "Lecteur vide"<<endl;
    }
    else
    {
        cout << "Diaporama num. " << numDiaporamaCourant() << endl;
        if (this->nbImages() > 0)
        {
            _diaporama[0]->afficher();
        }
        else
        {
            cout << "Diaporama vide" <<endl;
        }
    }
}

unsigned int Lecteur::nbImages()
{
    return _diaporama.size();
}

Image *Lecteur::imageCourante()
{
    if (_diaporama.empty()) {
        // Si le diaporama est vide, il n'y a pas d'image courante

        return nullptr;
    }
    // Sinon, on renvoie l'image courante
    return _diaporama[_posImageCourante];
}

unsigned int Lecteur::numDiaporamaCourant()
{
    return _numDiaporamaCourant;
}
