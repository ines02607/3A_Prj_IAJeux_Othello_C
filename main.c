/* ====================================================================================================================================
    Fichier qui va être compilé contenant le lancement de SDL
   ====================================================================================================================================
*/

#include <stdlib.h>
#include <stdio.h>

// bibliothèque SDL
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

// on rattache les fichiers
#include "variables.h"
#include "plateau.h"
#include "plateau.c"

/* On pense à réaliser des cas d'erreur pour la sortie du logiciel à chaque étape */

int main ( int argc, char** argv )
{
    // au démarrage, pas d'écran
    SDL_Surface *ecran=NULL,*menu=NULL,*menu2=NULL;
    // on positionne le menu selon les variables plus bas
    SDL_Rect position_menu;
    // on affiche (c'est un évènement)
    SDL_Event event;

    // on initialise la variable 'continuer' à 1
    int continuer=1;

    SDL_Init(SDL_INIT_VIDEO); // initialisation de SDL_video
    if(SDL_Init(SDL_INIT_VIDEO)<0) // vérification de l'initialisation de la SDL_video
    {
        // si l'initialisation n'a pas marché
        printf("Erreur d'initialisation de la SDL : %s\n",SDL_GetError());
        exit(EXIT_FAILURE); //on sort du programme
    }

    //nom du jeu (pour le téléchargement sous windows)
    SDL_WM_SetCaption("Othello",NULL);
    SDL_WM_SetIcon(IMG_Load("icon.jpg"),NULL); // icone affiché

    ecran=SDL_SetVideoMode(LARGEUR_FENETRE,HAUTEUR_FENETRE,32, SDL_HWSURFACE | SDL_DOUBLEBUF); // création d'une fenetre

    if(ecran==NULL) // tester si la fenetre a été crée
    {
        // message d'erreur
        printf("Erreur de la creation de la fenetre : %s\n",SDL_GetError());
        exit(EXIT_FAILURE);
    }

    // au départ l'écran est noir
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));

    // on initialise les variables 'menu' et 'menu2' avec les images
    menu=IMG_Load("menu.gif"); //chargement
    menu2=IMG_Load("menu2.jpg"); //menu de départ

    position_menu.x=0;
    position_menu.y=0;
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));// l'écran est en noir
    SDL_BlitSurface(menu,NULL,ecran,&position_menu); // poser sur l'écran noir l'image de menu
    
    SDL_Flip(ecran); // actualisation
    
    SDL_Delay(3000); //attend 3 secondes pour l'effet chargement
    SDL_BlitSurface(menu2,NULL,ecran,&position_menu); // poser sur l'écran noir l'image de menu2
    
    SDL_Flip(ecran); // actualisation
    
    SDL_FreeSurface(menu); //on retire l'image 'menu' du fond
    
    while(continuer) // tant qu'on ne demande pas de quitter (tant que continuer =1)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
        case SDL_QUIT: // 0 signifie arret du jeu
            continuer=0;
            break;
        case SDL_KEYDOWN:
            switch(event.key.keysym.sym)
            {
            case SDLK_ESCAPE: // arrêter le jeu par la touche Echap
                continuer = 0;
                break;
            }
            break;

        case SDL_MOUSEBUTTONUP:
            switch(event.button.button)
            {
            case SDL_BUTTON_LEFT: // clique gauche par la souris
                if(event.button.x>=370 && event.button.x<=910) //on détermine les boutons à l'aide des pixels de l'image (Gimp)
                {
                    if(event.button.y>=190 && event.button.y<=305) // clic sur "nouvelle partie"
                    {
                        //alors on lance la fonction plateau2 sur l'écran
                        plateau2(ecran);
                        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0)); // l'écran est en noir
                        SDL_BlitSurface(menu2,NULL,ecran,&position_menu); // poser sur l'écran noir l'image de menu2
                        SDL_Flip(ecran); // actualisation
                    }
                    else if(event.button.y>=330 && event.button.y<=445) // clic sur "Reprendre"
                    {
                        //pour reprendre la partie sauvegardée on lance la fonction plateau_reprendre
                        plateau_reprendre(ecran);
                        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 100, 93, 84));// l'écran est en noir
                        SDL_BlitSurface(menu2,NULL,ecran,&position_menu); // poser sur l'écran noir l'image de menu2
                        SDL_Flip(ecran); // actualisation
                    }
                    else if(event.button.y>=475 && event.button.y<=580) //clic sur "Quitter"
                    {
                        //quitter le jeu
                        continuer=0;
                    }
                }
                break;
            }
        }

    }

    //on libère la feuille menu2 & ecran
    SDL_FreeSurface(menu2);
    SDL_FreeSurface(ecran);
    SDL_Quit(); //sortie

    // sortie en cas de bug à toujours mettre 
    return EXIT_SUCCESS;

}
