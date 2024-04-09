/* ====================================================================================================================================
    Fichier qui contient les fonctions qui gèrent les images après "nouvelle partie"
   ====================================================================================================================================
*/

#include <stdlib.h>
#include <stdio.h>
#include <time.h> //pour donner aléatoirement  les noires soit au joueur soit au bot dans la partie joueur vs bot

// bibliothèques SDL
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

#include "jeu.h"
#include "variables.h"
#include "gestion.h"
#include "gestion.c"

// ================== Fonction de chargement ====================
void charger(int *coup_a,int *debut_a,int *difficulte)
{
    int contre;
    FILE *fichier=fopen(FICHIER,"r");
    // on vient renseigner toutes les données dans le fichier de sauvegarde
    fscanf(fichier,"%d",&contre);
    fscanf(fichier,"%d",coup_a);
    fscanf(fichier,"%d",debut_a);
    fscanf(fichier,"%d",difficulte);
    
    // on vient renseigner les positions des pions dans la grille
    for(int j=a; j<=h; j++)
    {
        for(int i=0; i<8; i++)
        {
            fscanf(fichier,"%d",&grille[i][j]);
        }
    }
    fclose(fichier);
}

// ==== Sauvegarde dans un fichier à part pour 'Reprendre' ====

void sauvgarder(int contre,int coup_a,int debut_a,int difficulte)
{
    FILE *fichier=fopen(FICHIER,"w");
    if(contre==HUMAIN)
    {
        fprintf(fichier,"%d ",HUMAIN);
        if(coup_a==NOIR)
            fprintf(fichier,"%d ",NOIR);
        else
            fprintf(fichier,"%d ",BLANC);
        fprintf(fichier,"%d ",debut_a); //dans cette partie il n'y a pas d'utilit� de la variable debut_a
        fprintf(fichier,"%d ",difficulte);  //dans cette partie il n'y a pas d'utilit� de la variable difficulte
    }
    else
    {
        fprintf(fichier,"%d ",BOT);
        if(coup_a==NOIR)
            fprintf(fichier,"%d ",NOIR);
        else
            fprintf(fichier,"%d ",BLANC);
        if(debut_a=HUMAIN)
            fprintf(fichier,"%d ",HUMAIN);
        else
            fprintf(fichier,"%d ",BOT);
        fprintf(fichier,"%d ",difficulte);
    }
    for(int j=a; j<=h; j++)
    {
        for(int i=0; i<8; i++)
        {
            fprintf(fichier,"%d ",grille[i][j]);
        }
    }
    fclose(fichier);
}

// ============== Fonction d'affichage des coups et résultats ==============
void afficher_coup_joue_et_resultat(SDL_Surface *ecran)
{
    SDL_Surface *texte_nb_pion_blanc=NULL,*texte_nb_pion_noir=NULL;
    SDL_Rect position_texte_blanc,position_texte_noir;

    // positionnement du score pour pion blanc
    position_texte_blanc.x=200;
    position_texte_blanc.y=35;
    
    // positionnement du score pour pion noir
    position_texte_noir.x=1170;
    position_texte_noir.y=35;

    // même méthode que précédemment (pointeurs // allocation de zone)
    SDL_Surface *pion_blanc=NULL,*pion_noir=NULL,*board=NULL,*resultat_blanc=NULL,*resultat_noir=NULL;//*retour=NULL,*recommencer=NULL;
    SDL_Rect position_board,position_pion,position_resultat_blanc,position_resultat_noir;//,position_retour,position_recommencer;

    // Police
    TTF_Init();
    TTF_Font *police=NULL;
    police=TTF_OpenFont("police.ttf",40);
    // couleur
    SDL_Color couleurBlanche = {255, 255, 255};
    char resultat[3];

    pion_blanc=IMG_Load("pion_blanc.jpg");
    pion_noir=IMG_Load("pion_noir.jpg");
    board=IMG_Load("grille.jpg");
    resultat_blanc=IMG_Load("resultat_blanc.png");
    resultat_noir=IMG_Load("resultat_noir.png");
    //retour=IMG_Load("retour.png");
    //recommencer=IMG_Load("recommencer.png");

    position_board.x=280;
    position_board.y=0;

    position_resultat_blanc.x=32;
    position_resultat_blanc.y=0;

    position_resultat_noir.x=1000;
    position_resultat_noir.y=0;

    //position_retour.x=20;
    //position_retour.y=490;

    //position_recommencer.x=20;
    //position_recommencer.y=590;

    SDL_BlitSurface(board,NULL,ecran,&position_board); // poser sur l'�cran noir l'image de la grille
    SDL_BlitSurface(resultat_blanc,NULL,ecran,&position_resultat_blanc);
    SDL_BlitSurface(resultat_noir,NULL,ecran,&position_resultat_noir);

    //SDL_BlitSurface(retour,NULL,ecran,&position_retour);
    //SDL_BlitSurface(recommencer,NULL,ecran,&position_recommencer);

    sprintf(resultat,"%d",nb_poin_blanc(grille));
    texte_nb_pion_blanc=TTF_RenderText_Blended(police,resultat,couleurBlanche);
    SDL_BlitSurface(texte_nb_pion_blanc,NULL,ecran,&position_texte_blanc);
    sprintf(resultat,"%d",nb_poin_noir(grille));
    texte_nb_pion_noir=TTF_RenderText_Blended(police,resultat,couleurBlanche);
    SDL_BlitSurface(texte_nb_pion_noir,NULL,ecran,&position_texte_noir);

    for(int i=0; i<8; i++)
    {
        for(int j=0; j<8; j++)
        {
            if(grille[i][j]==BLANC)
            {
                position_pion.x=90*i+280+5;
                position_pion.y=90*j+5;
                SDL_BlitSurface(pion_blanc,NULL,ecran,&position_pion);
            }
            if(grille[i][j]==NOIR)
            {
                position_pion.x=90*i+280+5;
                position_pion.y=90*j+5;
                SDL_BlitSurface(pion_noir,NULL,ecran,&position_pion);
            }
        }
    }
    SDL_Flip(ecran);

    SDL_FreeSurface(pion_blanc);
    SDL_FreeSurface(pion_noir);
    SDL_FreeSurface(resultat_blanc);
    SDL_FreeSurface(resultat_noir);
    SDL_FreeSurface(board);
    SDL_FreeSurface(texte_nb_pion_blanc);
    SDL_FreeSurface(texte_nb_pion_noir);

    TTF_CloseFont(police);
    TTF_Quit();
}

void affihcer_coup_propose(SDL_Surface *ecran)
{
    SDL_Surface *pion_blanc_propose=NULL,*pion_noir_propose=NULL;
    SDL_Rect position_pion;

    pion_blanc_propose=IMG_Load("pion_blanc.jpg");
    pion_noir_propose=IMG_Load("pion_noir.jpg");

    SDL_SetAlpha(pion_blanc_propose, SDL_SRCALPHA, 50);
    SDL_SetAlpha(pion_noir_propose, SDL_SRCALPHA, 50);

    for(int i=0; i<8; i++)
    {
        for(int j=0; j<8; j++)
        {
            if(grille[i][j]==BLANC_PROPOSE)
            {
                position_pion.x=90*i+280+5;
                position_pion.y=90*j+5;
                SDL_BlitSurface(pion_blanc_propose,NULL,ecran,&position_pion);
            }
            if(grille[i][j]==NOIR_PROPOSE)
            {
                position_pion.x=90*i+280+5;
                position_pion.y=90*j+5;
                SDL_BlitSurface(pion_noir_propose,NULL,ecran,&position_pion);
            }
        }
    }
    SDL_Flip(ecran);
    SDL_FreeSurface(pion_blanc_propose);
    SDL_FreeSurface(pion_noir_propose);
}

void afficher_gagnant(SDL_Surface *ecran)
{
    SDL_Surface *trophee=NULL;
    SDL_Rect position_trophee;
    trophee=IMG_Load("trophee.png");
    if(nb_poin_blanc(grille)>nb_poin_noir(grille))
    {
        position_trophee.x=0;
        position_trophee.y=200;
        SDL_BlitSurface(trophee,NULL,ecran,&position_trophee);
    }
    else if(nb_poin_blanc(grille)<nb_poin_noir(grille))
    {
        position_trophee.x=1000;
        position_trophee.y=200;
        SDL_BlitSurface(trophee,NULL,ecran,&position_trophee);
    }
    SDL_Flip(ecran);
    SDL_FreeSurface(trophee);
}

void jouer_vs_bot(SDL_Surface *ecran,int reprendre)
{
    int difficulte;
    if(!reprendre)
    {
        //Configuration de la difficult�
        SDL_Surface *menu=NULL;
        SDL_Rect position_menu;
        SDL_Event clic_menu;
        int continuer=1;

        menu=IMG_Load("Vs_BOT.jpg");
        position_menu.x=0;
        position_menu.y=0;
        SDL_BlitSurface(menu,NULL,ecran,&position_menu);
        SDL_Flip(ecran);
        while(continuer)
        {
            SDL_WaitEvent(&clic_menu);
            switch(clic_menu.type)
            {
            case SDL_QUIT:
                continuer=0;
                break;
            case SDL_KEYDOWN:
                switch(clic_menu.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    continuer = 0;
                    break;
                }
                break;
            case SDL_MOUSEBUTTONUP:
                switch(clic_menu.button.button)
                {
                case SDL_BUTTON_LEFT:
                    if(clic_menu.button.y>165 && clic_menu.button.y<455)
                    {
                        if(clic_menu.button.x>155 && clic_menu.button.x<445)
                        {
                            difficulte=FACILE;
                            continuer=0;
                        }
                        if(clic_menu.button.x>495 && clic_menu.button.x<785)
                        {
                            difficulte=MOYEN;
                            continuer=0;
                        }
                        if(clic_menu.button.x>835 && clic_menu.button.x<1125)
                        {
                            difficulte=DIFFICILE;
                            continuer=0;
                        }
                    }
                    break;
                }
            }
        }
        SDL_FreeSurface(menu);
    }

    //début de la partie humain vs bot
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format,0,0,0));// l'écran est en noir
    srand(time(NULL));
    int debut_a=(rand()%2); //qui va commencer HUMAIN=0 ou BOT=1

    int quitter=0,coup_a=NOIR,a,b;
    SDL_Event clic;

    if(!reprendre)
    {
        initialiser_grille(grille); //remplir le tableau qui repr�sente la grille
        afficher_coup_joue_et_resultat(ecran);
        
        if(debut_a==HUMAIN) //si l'humain commence le premier , on lui affihce les coup propos�s
        {
            proposer_coup(grille,coup_a); //proposer les coups au noir

            affihcer_coup_propose(ecran);

            nettoyer_grille(grille); //supprimer les coup propos�s dans le tableau
        }
        else //sinon le bot joue le premier coup , puis on affihce les coup propos�s
        {
            SDL_Delay(500); //attendre 0.5s avant de jouer le le coup
            jouez_coup(grille,bot(grille,NOIR,difficulte).x,bot(grille,NOIR,difficulte).y,coup_a);
            
            afficher_coup_joue_et_resultat(ecran);

            coup_a=BLANC;

            proposer_coup(grille,coup_a); //proposer les coups au noir

            affihcer_coup_propose(ecran);

            nettoyer_grille(grille); //supprimer les coup propos�s dans le tableau */
        }
    }

    if(reprendre)
    {
        charger(&coup_a,&debut_a,&difficulte);
        
        afficher_coup_joue_et_resultat(ecran);
        if((debut_a==HUMAIN && coup_a==NOIR) || (debut_a==BOT && coup_a==BLANC))
        {
            proposer_coup(grille,coup_a);
            affihcer_coup_propose(ecran);
            nettoyer_grille(grille);
        }
    }


    while(!Partie_terminee(grille) && !quitter)
    {
        if((debut_a==HUMAIN && coup_a==NOIR) || (debut_a==BOT && coup_a==BLANC)) 
        {
            SDL_WaitEvent(&clic);
            switch(clic.type)
            {
            case SDL_QUIT:
                quitter=1;
                break;
            case SDL_KEYDOWN:
                switch(clic.key.keysym.sym)
                {
                case SDLK_ESCAPE: // arr�ter le jeu par la touche Echap
                    quitter = 1;
                    break;
                }
                break;
            
            case SDL_MOUSEBUTTONUP:
                switch(clic.button.button)
                {
                case SDL_BUTTON_LEFT: // clique gauche par la souris
                    a=clic.button.x;
                    b=clic.button.y;
                    if(a>280 && a<1000)
                    {
                        if(coup_valide(grille,get_coup(a,b).x,get_coup(a,b).y,coup_a))
                        {
                            jouez_coup(grille,get_coup(a,b).x,get_coup(a,b).y,coup_a);

                            afficher_coup_joue_et_resultat(ecran);

                            if(coup_a==NOIR)
                            {
                                if(encore_coup(grille,BLANC))
                                    coup_a=BLANC;
                                else if(!encore_coup(grille,NOIR))
                                    quitter=1;
                            }
                            else if(coup_a==BLANC)
                            {
                                if(encore_coup(grille,NOIR))
                                    coup_a=NOIR;
                                else if(!encore_coup(grille,BLANC))
                                    quitter=1;
                            }
                        }
                    }
                    break;
                }
            }
        }
        
        else
        {
            SDL_Delay(500); //attendre 0.5s avant de jouer le le coup
            jouez_coup(grille,bot(grille,coup_a,difficulte).x,bot(grille,coup_a,difficulte).y,coup_a);
            afficher_coup_joue_et_resultat(ecran);

            if(coup_a==NOIR)
            {
                if(encore_coup(grille,BLANC))
                    coup_a=BLANC;
                else if(!encore_coup(grille,NOIR))
                    quitter=1;
            }
            else if(coup_a==BLANC)
            {
                if(encore_coup(grille,NOIR))
                    coup_a=NOIR;
                else if(!encore_coup(grille,BLANC))
                    quitter=1;
            }

            proposer_coup(grille,coup_a); //proposer les coups au noir

            affihcer_coup_propose(ecran);

            nettoyer_grille(grille); //supprimer les coup propos�s dans le tableau
        }
    }
    afficher_coup_joue_et_resultat(ecran);

    if(Partie_terminee(grille)) // affihcer qui a gagn�
    {
        afficher_gagnant(ecran);
        quitter=0;
        while(!quitter)
        {
            SDL_WaitEvent(&clic);
            switch(clic.type)
            {
            case SDL_QUIT:
                quitter=1;
                break;
            case SDL_KEYDOWN:
                switch(clic.key.keysym.sym)
                {
                case SDLK_ESCAPE: // arr�ter le jeu par la touche Echap
                    quitter = 1;
                    break;
                }
                break;
            }
        }

    }
    sauvgarder(BOT,coup_a,debut_a,difficulte); //sauvgarder avant de quitter
}
