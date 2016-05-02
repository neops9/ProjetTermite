#include <SDL/SDL.h>
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <SDL_ttf.h>
#include "termite.h"

#define LARGEUR_TILE 15  // hauteur et largeur des tiles.
#define HAUTEUR_TILE 15

#define NOMBRE_BLOCS_LARGEUR 40  // nombre a afficher en x et y
#define NOMBRE_BLOCS_HAUTEUR 40

using namespace std;

int main(int argc,char** argv)
{
    srand (time(NULL));

    int nbPasse = 0; //Compteur de passe
    bool pause = true;
    int StartPauseTicks = 0; //Nombre de tick au début de la pause
    int PauseTicks = 0; //Nombre de tick de la pause
    int Ticks = 0; //Nombre de ticks moins le nombre de tick de la pause
    bool done = false;
	bool pression = false;

	SDL_Surface* screen, *tileset; // Déclaration des surfaces
	SDL_Event event;
	TTF_Font *police = NULL; //Déclaration de la police pour le texte
	SDL_Surface *passe = NULL; //Déclaration d'une surface pour le nombre de passe
	SDL_Surface *temps = NULL; //Déclaration d'une surface pour le temps
	SDL_Surface *texte1 = NULL; //Déclaration d'une surface pour le texte 1
	SDL_Surface *texte2 = NULL; //Déclaration d'une surface pour le texte 2
	SDL_Color couleur = {0, 0, 0}; //Couleur du texte
	SDL_Init(SDL_INIT_VIDEO); // Chargement de la SDL
	TTF_Init(); //Chargement de la bibliothèque pour le texte
	char passeChar[10];
	char tempsChar[10];
	screen = SDL_SetVideoMode(LARGEUR_TILE*NOMBRE_BLOCS_LARGEUR + 200, HAUTEUR_TILE*NOMBRE_BLOCS_HAUTEUR, 32,SDL_HWSURFACE|SDL_DOUBLEBUF);

	//Chargement du tileset
	tileset = SDL_LoadBMP("tileset1.bmp");

    //Chargement de la police
	police = TTF_OpenFont("LemonMilk.otf", 15);

    //Titre de la fenêtre
	SDL_WM_SetCaption("Termite Simulator", NULL);

	texte1 = TTF_RenderText_Blended(police, "Nombre de passes :", couleur);
	texte2 = TTF_RenderText_Blended(police, "Temps (seconde) :", couleur);

    //position du texte 2
    SDL_Rect tposition1;
    tposition1.x = LARGEUR_TILE*NOMBRE_BLOCS_LARGEUR + 20;
    tposition1.y = HAUTEUR_TILE*NOMBRE_BLOCS_HAUTEUR - 180;

    //position du texte 2
    SDL_Rect tposition2;
    tposition2.x = LARGEUR_TILE*NOMBRE_BLOCS_LARGEUR + 20;
    tposition2.y = HAUTEUR_TILE*NOMBRE_BLOCS_HAUTEUR - 480;

	//position du texte de temps
    SDL_Rect position1;
    position1.x = LARGEUR_TILE*NOMBRE_BLOCS_LARGEUR + 50;
    position1.y = HAUTEUR_TILE*NOMBRE_BLOCS_HAUTEUR - 160;

    //position du texte de nombre de passe
    SDL_Rect position2;
    position2.x = LARGEUR_TILE*NOMBRE_BLOCS_LARGEUR + 50;
    position2.y = HAUTEUR_TILE*NOMBRE_BLOCS_HAUTEUR - 460;

    InitialiseTerrain();
	afficheTerrain(screen,tileset,NOMBRE_BLOCS_LARGEUR,NOMBRE_BLOCS_HAUTEUR);

	while(!done)
    {
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                //Gestion du clavier
                case SDL_KEYDOWN:
                {
                    switch(event.key.keysym.sym)
                    {
                        case SDLK_RETURN: // Entrée
                            StartPauseTicks = SDL_GetTicks();
                            PauseTicks = Ticks;
                            MouvTermite();
                            ++nbPasse;
                            Ticks = PauseTicks + SDL_GetTicks() - StartPauseTicks;
                            pause = true;
                        break;

                        case SDLK_SPACE: // Espace
                            if(pression)
                            {
                                pression = false;
                                pause = true;
                                PauseTicks = Ticks;
                            }
                            else
                            {
                                pression = true;
                                StartPauseTicks = SDL_GetTicks();
                            }
                        break;

                        case SDLK_ESCAPE: // Echap
                            done = true;
                        break;

                        default:
                            break;
                    }
                }
            }
        }


        if(pression)
        {
            pause = false;
            MouvTermite();
            ++nbPasse;
        }

        if(!pause)
            Ticks = PauseTicks + SDL_GetTicks() - StartPauseTicks;

        sprintf(tempsChar, "%d", Ticks/1000);
        sprintf(passeChar, "%d", nbPasse);
        temps = TTF_RenderText_Blended(police, tempsChar, couleur);
        passe = TTF_RenderText_Blended(police, passeChar, couleur);

        SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 239, 228, 176));
        SDL_BlitSurface(temps, NULL, screen, &position1);
        SDL_BlitSurface(texte1, NULL, screen, &tposition2);
        SDL_BlitSurface(texte2, NULL, screen, &tposition1);
        SDL_BlitSurface(passe, NULL, screen, &position2);
        afficheTerrain(screen,tileset,NOMBRE_BLOCS_LARGEUR,NOMBRE_BLOCS_HAUTEUR);
        SDL_Flip(screen); //Rechargement de l'écran

    }

	SDL_FreeSurface(screen);
	SDL_Quit();
	return 0;
}
