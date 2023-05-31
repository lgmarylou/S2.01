#include "image.h"

Image::Image(unsigned int pRang, string pCategorie, string pTitre, string pUrl)
{
    _rang = pRang;
    _categorie = pCategorie;
    _titre = pTitre;
    _url = pUrl;
}

unsigned int Image::getRang()
{
    return _rang;
}

string Image::getCategorie()
{
    return _categorie;
}

string Image::getTitre()
{
    return _titre;
}

string Image::getUrl()
{
    return _url;
}

void Image::afficher()
{
    cout << "image( rang:" << getRang() << ", titre:" << getTitre() << ", categorie:"
         << getCategorie() << ")" << endl;
}
