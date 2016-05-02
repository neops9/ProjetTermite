#include <vector>

struct coord
{
    int x;
    int y;
};

struct place
{
    coord c;
    bool brindille;
    int termite;
};

struct termite
{
    coord c;
    int indT;
    int dir;
    bool brindille;
    bool tourneSurPlace;
    int sablier;
};

/**
 *fonction NouvelleCoord
 * creer une coordonnée
 * @param deux float x et y
 * @return result une coord
 */
coord NouvelleCoord(float x, float y);

/**
 *procédure PlaceVide:
 * creer une place vide/initialie une place avec rien dessus
 * @param une place p
 */
void PlaceVide(place &p);

/**
 *procédure PoserBrindille:
 * pose une brindille sur une place vide
 * @param une place p
 */
void PoserBrindille(place &p);

/**
 *procédure PoserTermite:
 * place un termite sur une place vide
 * @param une place p
 * @param un entier indT qui represente l'indice du termite
 */
void PoserTermite(place &p, int indT);

/**
 *procédure InitTermite
 * creer un termite
 * @param un termite t
 * @param trois entier x, y et indT l'incice de la termite
 */
void InitTermite(termite &t, int x, int y, int indT);

/**
 *procédure setBrindille
 * change l'etat d'une brindille
 * @param un termite t
 * @param un booleen b
 */
void setBrindille(termite &t, bool b);

/**
 *fonction proba:
 * probabilité de p
 * @param une décimal p
 * @return un booléen
 */
bool proba(float p);

/**
 *fonction CoordDevant:
 * donne les coordonnées c de la place devant un termite
 * @param un termite t
 * @return coordonnée c
 */
coord CoordDevant(termite t);

/**
 *fonction BrindilleDevant:
 * determine si une brindille est devant un termite
 * @param un termite t
 * @return un booléen
 */
bool BrindilleDevant(termite t);

/**
 *procédure chargerBrindille:
 * permet à un termite de prendre une brindille
 * @param un termite t
 */
void chargerBrindille(termite &t);

/**
 *procedure dechargerBrindille:
 * pose une brindille sur une place vide
 * @param un termite t
 */
void dechargerBrindille(termite &t);

/**
 *fonction getCoord:
 * recupère les coordonnées d'un termite
 * @param un termite t
 * @return les nouvelles coordonnée d'un termite t.c
 */
coord getCoord(termite t);

int getNum(termite t);
/**
 *procédure setCoord:
 * change les coordonnées
 * @param un termite t
 * @param une coordonnée c
 */
void setCoord(termite &t, coord c);

/**
 *procédure AvanceTermite:
 * fait avancer un termite tout droit
 * @param un termite t
 */
void AvanceTermite(termite &t);

/**
 *procédure aDroite:
 * fait tourner un termite à droite
 * @param un termite t
 */
void aDroite(termite &t);
/**
 *fonction DansGrille:
 * determine si un termite est dans le terrain
 * @param une coordonnée c
 * @return un booléen
 */
bool DansGrille(coord c);

/**
 *fonction EstVide:
 * determine si une place est vide
 * @param une coordonnée c
 * @return un booléen
 */
bool EstVide(coord c);

/**
 *fonction EstBloque:
 * permet de savoir si un termite est completement bloqué ou non
 * @param un termite t
 * @return un booléen
 */
bool EstBloque(termite t);

/**
 *fonction LaVoixEstLibre:
 * determine si la place devant un termite est vide
 * @param un termite t
 * @return un booléen
 */
bool LaVoixEstLibre(termite t);

/**
 *procédure LancerSablier:
 * lance le sablier d'un termite
 * @param un termite t
 */
void LancerSablier(termite &t);

/**
 *procédure EcoulerSablier:
 * decompte le temps du sablier d'un termite
 * @param un termite t
 */
void EcoulerSablier(termite &t);

/**
 *procédure MouvTermite:
 * permet de faire bouger un termite
 */
void MouvTermite();

/**
 *procédure InitialiseTerrain:
 * initialise le terrain avec des brindilles, des termites, des places vide
 */
void InitialiseTerrain();

/**
 *procédure afficheTerrain:
 * affiche le terrain
 * @param surface de l'ecran
 * @param deux entiers nombre_blocs_largeur et nombre_blocs_hauteur
 */
void afficheTerrain(SDL_Surface* screen,SDL_Surface* tileset,int nombre_blocs_largeur,int nombre_blocs_hauteur);

/**
 *procédure ParcoursVoisin:
 * retourne un terrain moins une brindille et toutes les brindilles qui lui sont voisines
 * @param x
 * @param y
 * @param un tableau de place
 */
void ParcoursVoisin(int x, int y, std::vector<std::vector<place> > &T);

/**
 *procédure nombreTas:
 * retourne le nombre de tas sur un terrain
 * @param un terrain de place
 */
int nombreTas(place Terrain[40][40]);

