#include <SDL/SDL.h>
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "termite.h"

#define LARGEUR_TILE 15  // hauteur et largeur des tiles.
#define HAUTEUR_TILE 15

#define NOMBRE_BLOCS_LARGEUR 40  // nombre a afficher en x et y
#define NOMBRE_BLOCS_HAUTEUR 40

using namespace std;

place Terrain[40][40];

int nbTermites = 0;

termite TableauTermites[20];

/**creer une coordonnées*/
coord NouvelleCoord(float x, float y)
{
    coord result;

    result.x = x;
    result.y = y;

    return result;
}

/**initialise une place vide*/
void PlaceVide(place &p)
{
    p.brindille = false;
    p.termite = -1;
}

/**permet de poser une brindille sur une place*/
void PoserBrindille(place &p)
{
    p.brindille = true;
}

/**permet de poser un termite sur une place vide*/
void PoserTermite(place &p, int indT)
{
    p.termite = indT;
}

/**creer un termite*/
void InitTermite(termite &t, int x, int y, int indT)
{
    t.c = NouvelleCoord(x,y);
    t.indT = indT;
    t.dir = rand() % 8;
    t.brindille = false;
    t.sablier = 0;
    t.tourneSurPlace = false;
}

/**creer une brindille*/
void setBrindille(termite &t, bool b)
{
    t.brindille = b;
}

/***/
bool proba(float p)
{
    int random = rand() % 100;

    if(random <= p*100)
        return true;
    else
        return false;
}

/**recupère les coordonnées devant un termite*/
coord CoordDevant(termite t)
{
    coord c;
    switch(t.dir)
    {
        case 0:
            c.x = t.c.x + 1;
            c.y = t.c.y;
        break;

        case 1:
            c.x = t.c.x + 1;
            c.y = t.c.y + 1;
        break;

        case 2:
            c.x = t.c.x;
            c.y = t.c.y + 1;
        break;

        case 3:
            c.x = t.c.x - 1;
            c.y = t.c.y + 1;
        break;

        case 4:
            c.x = t.c.x - 1;
            c.y = t.c.y;
        break;

        case 5:
            c.x = t.c.x - 1;
            c.y = t.c.y - 1;
        break;

        case 6:
            c.x = t.c.x;
            c.y = t.c.y - 1;
        break;

        case 7:
            c.x = t.c.x + 1;
            c.y = t.c.y - 1;
        break;
    }

    return c;
}

/**determine si une brindille se trouve devant un termite*/
bool BrindilleDevant(termite t)
{
    if(DansGrille(CoordDevant(t)) && Terrain[CoordDevant(t).x][CoordDevant(t).y].brindille)
        return true;
    else
        return false;
}

void ParcoursVoisin(int x, int y, vector<vector<place> > &T)
{
    termite temp;
    InitTermite(temp, x, y, -1);

    T[x][y].brindille = false;

    for(int i=0; i<8; ++i)
    {
        if(DansGrille(CoordDevant(temp)) && T[CoordDevant(temp).x][CoordDevant(temp).y].brindille)
        {
            ParcoursVoisin(CoordDevant(temp).x, CoordDevant(temp).y, T);
        }

        aDroite(temp);
    }
}

int nombreTas(place Terrain[40][40])
{
    vector<vector<place> > T;

    T = vector<vector<place> >(40);

    for(int i=0; i<T.size(); ++i)
        T[i] = vector<place>(40);

    int nbTas = 0;

    for(int i=0; i<40; ++i)
    {
        for(int j=0; j<40; ++j)
        {
            T[i][j].brindille = Terrain[i][j].brindille;
        }
    }

    for(int i=0; i<40; ++i)
    {
        for(int j=0; j<40; ++j)
        {
            if(T[i][j].brindille)
            {
                ++nbTas;
                ParcoursVoisin(i, j, T);
            }
        }
    }

    return nbTas;
}

/**permet a un termite de prendre une brindille*/
void chargerBrindille(termite &t)
{
    if(t.sablier >= 3)
    {
        if(!t.brindille) /**si un termite a pas de brindille alors il peut prendre une*/
        {
            coord cDevant = CoordDevant(t);
            PlaceVide(Terrain[cDevant.x][cDevant.y]);
            t.brindille = true;
            LancerSablier(t);
        }
    }
}

/**permet a une termite de poser une brindille sur une place vide*/
void dechargerBrindille(termite &t)
{
    if(t.sablier >= 3)
    {
            int c;

            aDroite(t);

            for(int i=0;i<8; ++i)
            {
                c = i;

                if(DansGrille(CoordDevant(t)) && EstVide(CoordDevant(t)))
                    break;

                aDroite(t);

                c = i;
            }

            if(c != 7)
            {
                int x = CoordDevant(t).x;
                int y = CoordDevant(t).y;
                aDroite(t);

                if(DansGrille(CoordDevant(t)) && EstVide(CoordDevant(t)))
                {
                    PoserBrindille(Terrain[x][y]);
                    t.brindille = false;
                    LancerSablier(t);
                }
            }

        }
}

/**recupère les coordonnées d'un termite*/
coord getCoord(termite t)
{
    return t.c;
}

/**recupère l'indice d'un termite*/
int getNum(termite t)
{
    return t.indT;
}

/**change les coordonnées*/
void setCoord(termite &t, coord c)
{
    t.c = c;
}

/**fait avancer un termite*/
void AvanceTermite(termite &t)
{
    coord c = getCoord(t);
    PlaceVide(Terrain[c.x][c.y]);
    coord cDevant = CoordDevant(t);
    setCoord(t, cDevant);
    PoserTermite(Terrain[cDevant.x][cDevant.y], getNum(t));
}

/**tourne à droite*/
void aDroite(termite &t)
{
     if(t.dir == 0)
        t.dir = 7;
     else
        t.dir -= 1;
}

/**determine si un termine est dans le terrain*/
bool DansGrille(coord c)
{
    if( c.x < 40 && c.x >= 0 && c.y < 40 && c.y >= 0)
        return true;
    else
        return false;
}

/**determine si une place est vide*/
bool EstVide(coord c)
{
    if(!Terrain[c.x][c.y].brindille && Terrain[c.x][c.y].termite == - 1 )
        return true;
    else
        return false;
}

/**permet de voir si un termite est bloqué ou non*/
bool EstBloque(termite t)
{
    termite temp = t;

    for(int i=0; i<8; ++i)
    {
        if(DansGrille(CoordDevant(temp)) && EstVide(CoordDevant(temp)))
            return false;

        aDroite(temp);
    }
    return true;
}

/**determine si la place devant le termite est vide*/
bool LaVoixEstLibre(termite t)
{
	coord c;

	c = CoordDevant(t);
	return (DansGrille(c) && EstVide(c));
}

/**lance le sablier d'un termite*/
void LancerSablier(termite &t)
{
    t.sablier = 0;
}

/**ecoule le temps du sablier d'un termite*/
void EcoulerSablier(termite &t)
{
    t.sablier = t.sablier + 1;
}

/**permet a une termite de changer de direction avec 1chance sur 10 et ainsi de se deplacer dans tous les sens*/
void MouvTermite()
{
    for(int i=0; i<nbTermites; ++i)
    {
        bool p = proba(0.1);

        if(p)
            TableauTermites[i].dir = rand() % 8; /**direction aleatoire de 0 à 7*/

        /**si une brindille se trouve dans le terrain devant un termite alors le termitepeut la prendre*/
        if(DansGrille(CoordDevant(TableauTermites[i])) && Terrain[CoordDevant(TableauTermites[i]).x][CoordDevant(TableauTermites[i]).y].brindille)
        {
            int nbTasAvant = nombreTas(Terrain);
            Terrain[CoordDevant(TableauTermites[i]).x][CoordDevant(TableauTermites[i]).y].brindille = false;
            int nbTasApres = nombreTas(Terrain);
            Terrain[CoordDevant(TableauTermites[i]).x][CoordDevant(TableauTermites[i]).y].brindille = true;

            if(nbTasApres <= nbTasAvant)
                chargerBrindille(TableauTermites[i]);
        }

        if(TableauTermites[i].brindille && DansGrille(CoordDevant(TableauTermites[i])) && BrindilleDevant(TableauTermites[i])) /**si un termite a une brindille, alors elle la decharge*/
                dechargerBrindille(TableauTermites[i]);

        if(LaVoixEstLibre(TableauTermites[i])) /**si la voix est libre, alors le termite peut avancer et son sablier s'ecoule*/
        {
            EcoulerSablier(TableauTermites[i]);
            AvanceTermite(TableauTermites[i]);
        }
        else /**sinon, il est bloque et il tourne a droite*/
        {
            if(!EstBloque(TableauTermites[i]))
            {
                aDroite(TableauTermites[i]); /**tourne a droite si obstacle*/
                i -= 1; /**permet de revenir sur le même termite*/
            }
        }
    }
}

/**Initizlise le trrain en placant des brindilles avec une proba de 5% ou des termites avec une proba de 1%*/
void InitialiseTerrain()
{
    for(int i=0; i<40; ++i)
    {
        for(int j=0; j<40; ++j)
        {
            PlaceVide(Terrain[i][j]);
            if(proba(0.05))
                PoserBrindille(Terrain[i][j]);
            else if(proba(0.01))
            {
                InitTermite(TableauTermites[nbTermites], i, j, nbTermites);
                PoserTermite(Terrain[i][j], nbTermites);
                ++nbTermites;
            }
        }
    }
}


void afficheTerrain(SDL_Surface* screen,SDL_Surface* tileset,int nombre_blocs_largeur,int nombre_blocs_hauteur)
{
	int i,j;
	SDL_Rect Rect_dest;
	SDL_Rect Rect_source;
	Rect_source.w = LARGEUR_TILE;
	Rect_source.h = HAUTEUR_TILE;

	for(i=0;i<nombre_blocs_largeur;i++)
	{
		for(j=0;j<nombre_blocs_hauteur;j++)
		{
			Rect_dest.x = i*LARGEUR_TILE;
			Rect_dest.y = j*HAUTEUR_TILE;

			if(Terrain[i][j].brindille)
                Rect_source.x = 1*LARGEUR_TILE;
            else if(Terrain[i][j].termite != -1)
            {
                switch(TableauTermites[Terrain[i][j].termite].dir)
                {
                    case 0:
                        if(TableauTermites[Terrain[i][j].termite].brindille)
                            Rect_source.x = (0+10)*LARGEUR_TILE;
                        else
                            Rect_source.x = (0+2)*LARGEUR_TILE;
                    break;

                    case 1:
                        if(TableauTermites[Terrain[i][j].termite].brindille)
                            Rect_source.x = (7+10)*LARGEUR_TILE;
                        else
                            Rect_source.x = (7+2)*LARGEUR_TILE;
                    break;

                    case 2:
                        if(TableauTermites[Terrain[i][j].termite].brindille)
                            Rect_source.x = (6+10)*LARGEUR_TILE;
                        else
                            Rect_source.x = (6+2)*LARGEUR_TILE;
                    break;

                    case 3:
                        if(TableauTermites[Terrain[i][j].termite].brindille)
                            Rect_source.x = (5+10)*LARGEUR_TILE;
                        else
                            Rect_source.x = (5+2)*LARGEUR_TILE;
                    break;

                    case 4:
                        if(TableauTermites[Terrain[i][j].termite].brindille)
                            Rect_source.x = (4+10)*LARGEUR_TILE;
                        else
                            Rect_source.x = (4+2)*LARGEUR_TILE;
                    break;

                    case 5:
                        if(TableauTermites[Terrain[i][j].termite].brindille)
                            Rect_source.x = (3+10)*LARGEUR_TILE;
                        else
                            Rect_source.x = (3+2)*LARGEUR_TILE;
                    break;

                    case 6:
                        if(TableauTermites[Terrain[i][j].termite].brindille)
                            Rect_source.x = (2+10)*LARGEUR_TILE;
                        else
                            Rect_source.x = (2+2)*LARGEUR_TILE;
                    break;

                    case 7:
                        if(TableauTermites[Terrain[i][j].termite].brindille)
                            Rect_source.x = (1+10)*LARGEUR_TILE;
                        else
                            Rect_source.x = (1+2)*LARGEUR_TILE;
                    break;
                }
            }
            else
                Rect_source.x = 0;

			Rect_source.y = 0;
			SDL_BlitSurface(tileset,&Rect_source,screen,&Rect_dest);
		}
	}
}
