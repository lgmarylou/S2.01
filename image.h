#ifndef IMAGE_H
#define IMAGE_H
#include <iostream>
using namespace std;

class Image
{
public:
    ~Image();
    Image(unsigned int pRang=0,
              string pCategorie="", string pTitre="", string pUrl="");
    unsigned int getRang();
    string getCategorie();
    string getTitre();
    string getUrl();
    void afficher();           // affiche tous les champs de l'image

private:
    unsigned int _rang;         /* rang de l'image au sein du diaporama
                                   auquel l'image est associée */
    string _titre;              // intitulé de l'image
    string _categorie;          // catégorie de l'image (personne, animal, objet)
    string _url;
};

#endif // IMAGE_H
