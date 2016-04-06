#include <SDL/SDL.h>
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <time.h>

#define LARGEUR_TILE 15  // hauteur et largeur des tiles.
#define HAUTEUR_TILE 15

#define NOMBRE_BLOCS_LARGEUR 40  // nombre a afficher en x et y
#define NOMBRE_BLOCS_HAUTEUR 40

using namespace std;

struct coord
{
    float x;
    float y;
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
};

// constructeur coord début
coord NouvelleCoord(float x, float y)
{
    coord result;

    result.x = x;
    result.y = y;

    return result;
}
// fin

// constructeur place début
void PlaceVide(place &p)
{
    p.brindille = false;
    p.termite = -1;
}

void PoserBrindille(place &p)
{
    p.brindille = true;
}

void PoserTermite(place &p, int indT)
{
    p.termite = indT;
}
// fin

place Terrain[40][40];

int nbTermites = 0;

termite TableauTermites[16];

//constructeur termite début
void InitTermite(termite &t, int x, int y, int indT)
{
    t.c = NouvelleCoord(x,y);
    t.indT = indT;
    t.dir = rand() % 8;
}

bool proba(float p)
{
    int random = rand() % 100;

    if(random <= p*100)
        return true;
    else
        return false;
}

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

void Afficher(SDL_Surface* screen,SDL_Surface* tileset,int nombre_blocs_largeur,int nombre_blocs_hauteur)
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
                		Rect_source.x = 2*LARGEUR_TILE;
            		else
                		Rect_source.x = 0;

			Rect_source.y = 0;
			SDL_BlitSurface(tileset,&Rect_source,screen,&Rect_dest);
		}
	}
	SDL_Flip(screen);
}

int main(int argc,char** argv)
{
    	srand (time(NULL));

	SDL_Surface* screen,*tileset;
	SDL_Event event;
	SDL_Init(SDL_INIT_VIDEO);		// prepare SDL
	screen = SDL_SetVideoMode(LARGEUR_TILE*NOMBRE_BLOCS_LARGEUR, HAUTEUR_TILE*NOMBRE_BLOCS_HAUTEUR, 32,SDL_HWSURFACE|SDL_DOUBLEBUF);
	tileset = SDL_LoadBMP("tileset1.bmp");

	InitialiseTerrain();
	Afficher(screen,tileset,NOMBRE_BLOCS_LARGEUR,NOMBRE_BLOCS_HAUTEUR);

	 // garde le programme ouvert tant que l'utilisateur n'appuie pas sur une touche (pour les tests)
	do
	{
		SDL_WaitEvent(&event);
	} while (event.type!=SDL_KEYDOWN);

	SDL_FreeSurface(tileset);
	SDL_Quit();
	return 0;
}
