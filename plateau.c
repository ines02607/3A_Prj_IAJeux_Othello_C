/* ====================================================================================================================================
    Fichier qui contient les fonctions qui affichent les images avant le début du jeu
   ====================================================================================================================================
*/

#include <stdlib.h>
#include <stdio.h>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

#include "plateau.h"
#include "jeu.h"
#include "jeu.c"

// ================== Affichage "Règles du jeu" =================

void plateau3(SDL_Surface* ecran)
{
    SDL_Surface *regles=NULL;
    SDL_Event event3;
    SDL_Rect position_menu;
    //initialisation continuer2 (0 => on quitte le jeu)
    int continuer3=1;
    //on charge l'image du menu 3
    regles=IMG_Load("regles.jpg");

    //on initialise les positions à 0,0
    position_menu.x=0;
    position_menu.y=0;

    while(continuer3)
    {
        SDL_BlitSurface(regles,NULL,ecran,&position_menu); // poser sur l'écran noir l'image de menu
        SDL_Flip(ecran); // actualisation
        SDL_WaitEvent(&event3); //attendre un clic
        switch(event3.type)
        {
        case SDL_QUIT: // clic sur "Fermer" "X"
            continuer3=0;
            break;
        case SDL_KEYDOWN: // clic sur un bouton
            switch(event3.key.keysym.sym)
            {
            case SDLK_ESCAPE: // arrêter le jeu par la touche Echap
                continuer3 = 0;
                break;
            }
            break;
        case SDL_MOUSEBUTTONUP: // clic sur un bouton de la souris
            switch(event3.button.button)
            {
            case SDL_BUTTON_LEFT: // clic gauche par la souris
                if(event3.button.x>=20 && event3.button.x<=205) //clic dans le retour
                {                            
                    if(event3.button.y>=25 && event3.button.y<=85)
                    {
                        plateau2(ecran);
                        continuer3=0;
                    }
                }
                break;
            }
            break;
        }
    }
    SDL_FreeSurface(regles);
}

// ================== Affichage "Jouer contre l'IA/règles du jeu" =================

void plateau2(SDL_Surface* ecran)
{
    SDL_Surface *menu3=NULL;
    SDL_Event event2;
    SDL_Rect position_menu;
    //initialisation continuer2 (0 => on quitte le jeu)
    int continuer2=1;
    //on charge l'image du menu 3
    menu3=IMG_Load("menu3.jpg");

    //on initialise les positions à 0,0
    position_menu.x=0;
    position_menu.y=0;
    //afficher "Vs joueur" ou "Vs bot"
    while(continuer2)
    {
        SDL_BlitSurface(menu3,NULL,ecran,&position_menu); // poser sur l'écran noir l'image de menu
        SDL_Flip(ecran); // actualisation
        SDL_WaitEvent(&event2); //attendre un clic
        switch(event2.type)
        {
        case SDL_QUIT: // clic sur "Fermer" "X"
            continuer2=0;
            break;
        case SDL_KEYDOWN: // clic sur un bouton
            switch(event2.key.keysym.sym)
            {
            case SDLK_ESCAPE: // arrêter le jeu par la touche Echap
                continuer2 = 0;
                break;
            }
            break;
        case SDL_MOUSEBUTTONUP: //clic sur un bouton de la souris
            switch(event2.button.button)
            {
            case SDL_BUTTON_LEFT: // clic gauche par la souris
                if(event2.button.x>=370 && event2.button.x<=910) //clic dans le menu3
                {                            
                    if(event2.button.y>=275 && event2.button.y<=385) // clic sur "Jouer contre l'IA"
                    {
                        //début de la partie joueur vs ordinateur
                        jouer_vs_bot(ecran,0);
                        continuer2=0;
                        break;
                    }
                    
                    if(event2.button.y>=395 && event2.button.y<=510) // clic sur "Règles du jeu"
                    {
                        //début de la partie joueur vs ordinateur
                        plateau3(ecran);
                        continuer2=0;
                    }

                }
                break;
            }
            break;
        }
    }
    // On libère
    SDL_FreeSurface(menu3);
}

// =============== Affichage du plateau après reprise ==============
void plateau_reprendre(SDL_Surface *ecran)
{
    int vs;
    // on vient lire le fichier de sauvegarde et l'afficher
    FILE *fichier=fopen(FICHIER,"r");
    fscanf(fichier,"%d",&vs);
    fclose(fichier);
    // on lance le jeu
    jouer_vs_bot(ecran,1);
}
