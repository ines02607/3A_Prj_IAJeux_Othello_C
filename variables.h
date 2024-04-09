/* ================================================================================
   Fichier qui contient les constantes et les variables utilisées
   ================================================================================
*/

#ifndef VARIABLES_H_INCLUDED
#define VARIABLES_H_INCLUDED

    #define LARGEUR_FENETRE 1280        // largeur de la fenêtre en pixels
    #define HAUTEUR_FENETRE 720         // hauteur de la fenêtre en pixels
    #define TAILLE_BLOC 90              
    #define POSITION_GRILLE_X 280       // décalement de la grille au centre de la fenêtre, soit 280 pixels à droite
    #define POSITION_GRILLE_Y 0         // la grille est positionnée en haut de la fenêtre, sans décalement
    #define FICHIER "sauvgarde.othello" //le fichier qui contient la dernière partie jouée utilisé pour "reprendre la partie"
    // on définit la structure coup avec une position x et y
    
    struct coup{
        int x;
        int y;
    };
    typedef struct coup coup;
    // elle se nommera coup (position x,y)

    enum{a,b,c,d,e,f,g,h}; // représentation des colonnes (8 colonnes de a à h)

    enum{VIDE,NOIR,BLANC,NOIR_PROPOSE,BLANC_PROPOSE}; // case vide, case avec pion noir, blanc, case avec proposition de déplacement noire ou blanche
    enum{HUMAIN,BOT}; // humain et bot
    
    enum{FACILE,MOYEN,DIFFICILE}; // 3 niveaux de difficultés

#endif
