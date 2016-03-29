#include <SDL/SDL.h>
#include <vector>

#define LARGEUR_TILE 15  // hauteur et largeur des tiles.
#define HAUTEUR_TILE 15

#define NOMBRE_BLOCS_LARGEUR 40  // nombre a afficher en x et y
#define NOMBRE_BLOCS_HAUTEUR 40

typedef std::vector<std::vector<int> > Terrain;

void Afficher(SDL_Surface* screen,SDL_Surface* tileset,Terrain table,int nombre_blocs_largeur,int nombre_blocs_hauteur)
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
			Rect_source.x = (table[j][i])*LARGEUR_TILE;
			Rect_source.y = 0;
			SDL_BlitSurface(tileset,&Rect_source,screen,&Rect_dest);
		}
	}
	SDL_Flip(screen);
}

int main(int argc,char** argv)
{
    Terrain t;

    t = std::vector<std::vector<int> >(40);

    for(int i=0; i<t.size(); ++i)
        t[i] = std::vector<int>(40);

    for(int i=0; i<t.size(); ++i)
    {
        for(int j=0; j<t[i].size(); ++j)
        {
            t[i][j] = 0; // On initialise le terrain avec de l'herbe
        }
    }

    // Test d'ajout d'éléments sur le terrain (termite, brindille, herbe)
    t[1][1] = 1;
    t[34][16] = 1;
    t[32][5] = 2;
    t[9][24] = 1;
    t[18][17] = 2;
    t[30][20] = 1;

	SDL_Surface* screen,*tileset;
	SDL_Event event;
	SDL_Init(SDL_INIT_VIDEO);		// prepare SDL
	screen = SDL_SetVideoMode(LARGEUR_TILE*NOMBRE_BLOCS_LARGEUR, HAUTEUR_TILE*NOMBRE_BLOCS_HAUTEUR, 32,SDL_HWSURFACE|SDL_DOUBLEBUF);
	tileset = SDL_LoadBMP("tileset1.bmp");

	Afficher(screen,tileset,t,NOMBRE_BLOCS_LARGEUR,NOMBRE_BLOCS_HAUTEUR);

    // garde le programme ouvert tant que l'utilisateur n'appuie pas sur une touche (pour les tests)
	do
	{
		SDL_WaitEvent(&event);
	} while (event.type!=SDL_KEYDOWN);

	SDL_FreeSurface(tileset);
	SDL_Quit();
	return 0;
}
