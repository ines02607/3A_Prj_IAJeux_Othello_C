/* ====================================================================================================================================
    Fichier qui contient les fonctions qui gèrent le tableau "grille" & le bot
   ====================================================================================================================================
*/

// Bibliothèques
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

// Liens vers les fichiers contenant des fonctions utilisées ici
#include "jeu.h"
#include "variables.h"
#include "gestion.h"

// Eléments pour l'algo minmax
#define ROW 8
#define COL 8
#define MAX_DEPTH 8
#define MIN_SCORE -1000000
#define MAX_SCORE 1000000

// Directions pour MinMax
int direction[8][2] = {{-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1}};

// Déclaration des fonctions pour MinMax
bool isInBoard(int x, int y);
bool check(int board[ROW][COL], int color, int x, int y, int dirX, int dirY);
int evaluate(int board[ROW][COL], int color);
int minmax(int board[ROW][COL], int color, int depth);
bool putChess(int board[ROW][COL], int color, int x, int y);

// ================= Fonction d'initialisation de la grille =====================

void initialiser_grille(int grille[][8])
{
    // on parcourexit le tableau
    for(int i=0; i<8; i++)
    {
        for(int j=0; j<8; j++)
        {
            // on initialise toutes les cases vides
            grille[i][j]=VIDE;
        }
    }
    // on rempli les cases centrales selon l'initialisation du plateau Othello
    // position (4,4)
    grille[3][d]=BLANC;
    // position (4,5)
    grille[3][e]=NOIR;
    // position (5,4)
    grille[4][d]=NOIR;
    // position (5,5)
    grille[4][e]=BLANC;
}

// ==== Fonction de vérification de l'existance d'une case (coordonnées contenues dans la grille) ====

int case_existe (int ligne,int colonne)
{
    // on retourne si toutes les conditions sont vérifiées
    return ((colonne >= 0) && (colonne < 8) && (ligne >= 0) && (ligne < 8));
}

// ============== Fonction de la vérification de la validité d'un coup ================

int coup_valide(int grille[][8],int ligne,int colonne,int joueur)
{   
    // initialisation
    int i, j, trouver;
    int caractere_joueur, caractere_adversaire;

    // si le joueur est blanc
    if (joueur == BLANC)
    {
        // joueur = blanc
        caractere_joueur = BLANC;
        // adversaire = noir
        caractere_adversaire = NOIR;
    }
    else
    {   
        // sinon l'inverse, joueur = noir
        caractere_joueur = NOIR;
        // adversaire = blanc
        caractere_adversaire = BLANC;
    }

    // si la case n'est pas contenu dans la grille ou la case est déjà remplie
    if (!case_existe(ligne, colonne) || grille[ligne][colonne] !=VIDE)
        // on retourne 0
        return 0;

    // on initialise la ligne i à ligne-1 (pour rentrer dans le cadre)
    i = ligne-1;
    // on pose trouver = 0 (non trouvé) et on retournera 1 si trouvé
    trouver = 0;
    while (case_existe(i, colonne) && grille[i][colonne] == caractere_adversaire)
    {
        // on décrémente la ligne
        i--;
        // on a trouvé une position valide
        trouver = 1;
    }
    // on a trouvé un coup valide dans la ligne inférieur
    if (case_existe(i, colonne) && grille[i][colonne] == caractere_joueur && trouver == 1)
        return 1;

    // on incrémente la ligne    
    i = ligne + 1;
    // on initialise trouver à 0 (non trouvé) et 1 si trouvé
    trouver = 0;

    // si la case existe & on trouve des pions de l'adversaire
    while (case_existe(i, colonne) && grille[i][colonne] == caractere_adversaire)
    {
        // on incrémente la ligne
        i++;
        // on trouve
        trouver = 1;
    }
    // on a trouvé un coup valide dans la ligne supérieure
    if (case_existe(i, colonne) && grille[i][colonne] == caractere_joueur && trouver == 1)
        return 1;

    // on décrémente la colonne
    j = colonne-1;
    // on initialise trouver à 0 (non trouvé)
    trouver = 0;

    // la case existe & pion NOIR OU BLANC
    while (case_existe(ligne, j) && grille[ligne][j] == caractere_adversaire)
    {
        // on a trouvé
        j--;
        trouver = 1;
    }

    // on déclare un coup possible trouvé
    if (case_existe(ligne, j) && grille[ligne][j] == caractere_joueur && trouver == 1)
        return 1;

    // on cherche la colonne suivante
    j = colonne + 1;
    trouver = 0;
    // on part de trouver=0
    while (case_existe(ligne, j) && grille[ligne][j] == caractere_adversaire)
    {
        // trouver = 1
        j++;
        trouver = 1;
    }
    // on comptabilise les coup possibles
    if (case_existe(ligne, j) && grille[ligne][j] == caractere_joueur && trouver == 1)
        return 1;

    // on cherche une ligne en dessous dans la colonne précédente
    i = ligne - 1;
    j = colonne - 1;
    // on remet trouver à 0 (non trouvé)
    trouver = 0;
    // on renvoie 1 si trouvé
    while (case_existe(i, j) && grille[i][j] == caractere_adversaire)
    {
        i--;
        j--;
        trouver = 1;
    }
    // retourne 1
    if (case_existe(i, j) && grille[i][j] == caractere_joueur && trouver == 1)
        return 1;
    // on essaie la ligne au dessus et la colonne suivante
    i = ligne + 1;
    j = colonne + 1;
    // tjrs trouver à 0 et 1 si trouvé
    trouver = 0;

    // trouvé == 1 si la case existe & si on est autour du caractère adv
    while (case_existe(i, j) && grille[i][j] == caractere_adversaire)
    {
        i++;
        j++;
        trouver = 1;
    }
    // si case existe & autour & trouvé = 1
    if (case_existe(i, j) && grille[i][j] == caractere_joueur && trouver == 1)
        return 1;
    
    // on essaie une ligne en dessous et une colonne suivante
    i = ligne - 1;
    j = colonne + 1;
    // tjrs trouver à 0 et 1 si trouvé
    trouver = 0;
    
    // idem que précédemment
    while (case_existe(i, j) && grille[i][j] == caractere_adversaire)
    {
        i--;
        j++;
        // on passe trouvé à 1
        trouver = 1;
    }
    // si on a trouvé un coup valade on renvoie 1
    if (case_existe(i, j) && grille[i][j] == caractere_joueur && trouver == 1)
        return 1;

    // dernier cas : on essaie une ligne au dessus et une colonne précédente
    i = ligne + 1;
    j = colonne - 1;
    // tjrs trouver à 0 et 1 si trouvé
    trouver = 0;
    // on passe trouvé à 1 si case existe et autour d'un adv
    while (case_existe(i, j) && grille[i][j] == caractere_adversaire)
    {
        i++;
        j--;
        trouver = 1;
    }
    // on retourne 1 si trouvé et case existe & autour adv => coup possible
    if (case_existe(i, j) && grille[i][j] == caractere_joueur && trouver == 1)
        return 1;
    
    // cas de sorti return 0
    return 0;
}

// ================ Fonction de gestion des coups joués ===============

void jouez_coup(int grille[][8],int ligne,int colonne,int joueur)
{
    // initialisation
    int i, j;
    int caractere_joueur, caractere_adversaire;
    // initialisation du joueur
    // si le joueur est blanc
    if (joueur == BLANC)
    {
        // joueur = blanc
        caractere_joueur = BLANC;
        // adv = noir
        caractere_adversaire = NOIR;
    }
    // sinon l'inverse
    else if(joueur==NOIR)
    {
        // joueur = noir
        caractere_joueur =NOIR;
        // adv = blanc
        caractere_adversaire = BLANC;
    }

    // la case choisi en paramètre est celle du joueur
    grille[ligne][colonne] = caractere_joueur;

    // on décrémente la ligne
    i = ligne - 1;
    // si la case existe & on trouve des cases adv
    while (case_existe(i, colonne) && grille[i][colonne] == caractere_adversaire)
        i--;
    // on cherhce
    if (case_existe(i, colonne) && grille[i][colonne] == caractere_joueur)
    {
        i = ligne - 1;
        while (grille[i][colonne] == caractere_adversaire)
        {
            grille[i][colonne] = caractere_joueur;
            i--;
        }
    }

    // Vertical vers le bas
    i = ligne + 1;
    while (case_existe(i, colonne) && grille[i][colonne] == caractere_adversaire)
        i++;
    if (case_existe(i, colonne) && grille[i][colonne] == caractere_joueur)
    {
        i = ligne + 1;
        while (grille[i][colonne] == caractere_adversaire)
        {
            grille[i][colonne] = caractere_joueur;
            i++;
        }
    }

    /* Horizontal vers la gauche */
    j = colonne - 1;
    while (case_existe(ligne, j) && grille[ligne][j] == caractere_adversaire)
        j--;
    if (case_existe(ligne, j) && grille[ligne][j] == caractere_joueur)
    {
        j = colonne - 1;
        while (grille[ligne][j] == caractere_adversaire)
        {
            grille[ligne][j] = caractere_joueur;
            j--;
        }
    }

    /* Horizontal vers la droite */
    j = colonne + 1;
    while (case_existe(ligne, j) && grille[ligne][j] == caractere_adversaire)
        j++;
    if (case_existe(ligne, j) && grille[ligne][j] == caractere_joueur)
    {
        j = colonne + 1;
        while (grille[ligne][j] == caractere_adversaire)
        {
            grille[ligne][j] = caractere_joueur;
            j++;
        }
    }

    /* Diagonal vers le haut */
    i = ligne - 1;
    j = colonne - 1;
    while (case_existe(i, j) && grille[i][j] == caractere_adversaire)
    {
        i--;
        j--;
    }
    if (case_existe(i, j) && grille[i][j] == caractere_joueur)
    {
        i = ligne - 1;
        j = colonne - 1;
        while (grille[i][j] == caractere_adversaire)
        {
            grille[i][j] = caractere_joueur;
            i--;
            j--;
        }
    }

    /* Diagonal \ vers le bas */
    i = ligne + 1;
    j = colonne + 1;
    while (case_existe(i, j) && grille[i][j] == caractere_adversaire)
    {
        i++;
        j++;
    }
    if (case_existe(i, j) && grille[i][j] == caractere_joueur)
    {
        i = ligne + 1;
        j = colonne + 1;
        while (grille[i][j] == caractere_adversaire)
        {
            grille[i][j] = caractere_joueur;
            i++;
            j++;
        }
    }

    /* Diagonal / vers le haut */
    i = ligne - 1;
    j = colonne + 1;
    while (case_existe(i, j) && grille[i][j] == caractere_adversaire)
    {
        i--;
        j++;
    }
    if (case_existe(i, j) && grille[i][j] == caractere_joueur)
    {
        i = ligne - 1;
        j = colonne + 1;
        while (grille[i][j] == caractere_adversaire)
        {
            grille[i][j] = caractere_joueur;
            i--;
            j++;
        }
    }

    /* Diagonal vers le bas */
    i = ligne + 1;
    j = colonne - 1;
    while (case_existe(i, j) && grille[i][j] == caractere_adversaire)
    {
        i++;
        j--;
    }
    if (case_existe(i, j) && grille[i][j] == caractere_joueur)
    {
        i = ligne + 1;
        j = colonne - 1;
        while (grille[i][j] == caractere_adversaire)
        {
            grille[i][j] = caractere_joueur;
            i++;
            j--;
        }
    }
}

// ==================== Fonction proposant des coups valides au joueur =================

void proposer_coup(int grille[][8],int joueur)
{
    // selon la couleur du joueur
    int caractere_joueur=(joueur==BLANC) ? BLANC_PROPOSE:NOIR_PROPOSE;
    // parcourt de tableau
    for(int i=0; i<8; i++)
    {
        for(int j=0; j<8; j++)
        {
            // on utilise la fonction coup valide (précédente)
            if(coup_valide(grille,i,j,joueur))
                // on place la proposition dans la grille
                grille[i][j]=caractere_joueur;
        }
    }
}

// ======================= Nettoyage de la grille avant une nouvelle partie ===================

void nettoyer_grille(int grille[][8])
{
    // parcours de tableau
    for(int i=0; i<8; i++)
    {
        for(int j=0; j<8; j++)
        {
            // on efface les propositions (NOIR_PROPOSE ou BLANC_PROPOSE)
            if(grille[i][j]==BLANC_PROPOSE || grille[i][j]==NOIR_PROPOSE)
            {
                // on vide
                grille[i][j]=VIDE;
            }
        }
    }
}

// ======================= Vérifie si il reste des coups valide à jouer =1 sinon 0 ===================

int Partie_terminee(int grille[][8])
{
    int valide=1;
    // On parcourt le tableau
    for(int i=0; i<8; i++)
    {
        for(int j=0; j<8; j++)
        {
            // s'il reste des coups à jouer
            if(coup_valide(grille,i,j,BLANC) || coup_valide(grille,i,j,NOIR))
            {
                valide=0;
                break;
            }
        }
        // sinon la partie est terminée
        if(!valide)
            break;
    }
    return valide;
}

// ===================================== SCORE ========================================
// ================ Calcul du nombre de pion noir dans la grille (score)===============

int nb_poin_noir(int grille[][8])
{
    int noir=0;
    // simple parcours de tableau (ligne colonne)
    for(int i=0; i<8; i++)
    {
        for(int j=0; j<8; j++)
        {
            // si on trouve NOIR
            if(grille[i][j]==NOIR)
                // on incrémente le score noir
                noir++;
        }
    }
    // retourne score noir
    return noir;
}

// ================ Calcul du nombre de pion noir dans la grille (score)===============

int nb_poin_blanc(int grille[][8])
{
    int blanc=0;
    // parcours de tab
    for(int i=0; i<8; i++)
    {
        for(int j=0; j<8; j++)
        {
            // si on trouve BLANC
            if(grille[i][j]==BLANC)
                // on incrémente le score blanc
                blanc++;
        }
    }
    // on retourne le score
    return blanc;
}

// ===================================== FIN SCORE ========================================

// ================= On récupère la position i, j à partir du clic ========================
coup get_coup(int a,int b)
{
    coup position;
    for(int i=0; i<8; i++)
    {
        // si on clic sur une valeur entre 2 indice (abscisse)
        if(a>i*90+280 && a<(i+1)*90+280)
            position.x=i;
        // si on clic sur une valeur entre 2 indice (ordonnée)
        if(b>i*90 && b<(i+1)*90)
            position.y=i;
    }
    return position;
}

// ================= s'il y a encore de coup valide pour un joueur ========================

int encore_coup(int grille[][8],int joueur)
{
    int valide=0;
    // on parcourt le tableau
    for(int i=0; i<8; i++)
    {
        for(int j=0; j<8; j++)
        {
            // si le coup est valide = 1
            if(coup_valide(grille,i,j,joueur))
            {
                valide=1;
                break;
            }
        }
        // sinon on sort
        if(valide)
            break;
    }
    return valide;
}

// =============================== Fonction de choix de la difficulté =======================

coup bot(int grille[][8],int couleur,int difficulte)
{
    switch(difficulte)
    {
        // Facile renvoie la fonction de jeu Bot Facile
        case FACILE:
            return bot_facile(grille,couleur);
            break;
        // Moyen renvoie la fonction de jeu Bot Moyen
        case MOYEN:
            return bot_moyen(grille,couleur);
            break;
        // Difficile renvoie la fonction de jeu Bot Difficile
        case DIFFICILE:
            return bot_difficile(grille,couleur);
            break;
    }
}

// ======================== Fonction de jeu FACILE ==============================

coup bot_facile(int grille[][8],int couleur)
{
    // ne capture pas les extr�mités: lignes et colonnes extérieures
    // cherche de jouer un coup à l'interieur de la grille sinon il cherche un coup possible
    coup bot;
    // on cherche à l'interieur de la grille
    for(int i=1; i<=6; i++)
    {
        // entre les colonnes b et g
        for(int j=b; j<g; j++)
        {
            // si on trouve un coup valide ici
            if(coup_valide(grille,i,j,couleur))
            {
                // on renvoie la position i, j
                bot.x=i;
                bot.y=j;
                return bot;
            }
        }
    }
    // s'il ne trouve pas un coup possible à l'interieur
    // on parcout entre les colonnes a et h
    for(int j=a; j<=h; j++)
    {
        // si on trouve des coups valides
        if(coup_valide(grille,0,j,couleur))
        {
            bot.x=0;
            bot.y=j;
            return bot;
        }
        if(coup_valide(grille,7,j,couleur))
        {
            bot.x=7;
            bot.y=j;
            return bot;
        }
    }
    // entre les lignes 1 à 7
    for(int i=1;i<7;i++)
    {
        if(coup_valide(grille,i,a,couleur))
        {
            bot.x=i;
            bot.y=a;
            return bot;
        }
        if(coup_valide(grille,i,h,couleur))
        {
            bot.x=i;
            bot.y=h;
            return bot;
        }
    }
}

// ======================== Fonction de jeu MOYEN ==============================
coup bot_moyen(int grille[][8],int couleur)
{
    //Cherche à capturer les extrémités et à ne pas jouer si possible un coup qui aide à le capturer
    coup bot;
    //on vérifie les extrémités
    // vérifier s'il est possible de jouer un coup en (1,a)
    if(coup_valide(grille,0,a,couleur))
    {
         bot.x=0;
         bot.y=a;
         return bot;
    }
    // en (1,h)
    if(coup_valide(grille,0,h,couleur))
    {
         bot.x=0;
         bot.y=h;
         return bot;
    }
    // en (8,a)
    if(coup_valide(grille,7,a,couleur))
    {
         bot.x=7;
         bot.y=a;
         return bot;
    }
    // en (8,h)
    if(coup_valide(grille,7,h,couleur))
    {
         bot.x=7;
         bot.y=h;
         return bot;
    }

    //sinon on joue aux extrémités
    for(int j=b; j<h; j++)
    {
        // on cherche les coins
        if(coup_valide(grille,0,j,couleur))
        {
            bot.x=0;
            bot.y=j;
            return bot;
        }
        if(coup_valide(grille,7,j,couleur))
        {
            bot.x=7;
            bot.y=j;
            return bot;
        }
    }
    for(int i=1;i<7;i++)
    {
        if(coup_valide(grille,i,a,couleur))
        {
            bot.x=i;
            bot.y=a;
            return bot;
        }
        if(coup_valide(grille,i,h,couleur))
        {
            bot.x=i;
            bot.y=h;
            return bot;
        }
    }
    //sinon on reprend le bot facile (on joue à l'intérieur)
    for(int j=c;j<=f;j++)
    {
        // on cherche à l'intérieur
        if(coup_valide(grille,2,j,couleur))
        {
            bot.x=2;
            bot.y=j;
            return bot;
        }
        if(coup_valide(grille,5,j,couleur))
        {
            bot.x=5;
            bot.y=j;
            return bot;
        }
    }
    // entre la ligne 3 et 4
    for(int i=3;i<=4;i++)
    {
        if(coup_valide(grille,i,c,couleur))
        {
            bot.x=i;
            bot.y=c;
            return bot;
        }
        if(coup_valide(grille,i,f,couleur))
        {
            bot.x=i;
            bot.y=f;
            return bot;
        }
    }
    //sinon  on cherche une case restante (si les autres possibilités n'aboutissent pas)
    for(int j=c;j<g;j++)
    {
        if(coup_valide(grille,1,j,couleur))
        {
            bot.x=1;
            bot.y=j;
            return bot;
        }
        if(coup_valide(grille,6,j,couleur))
        {
            bot.x=6;
            bot.y=j;
            return bot;
        }
    }
    // entre les lignes 2 et 6
    for(int i=2;i<6;i++)
    {
        if(coup_valide(grille,i,b,couleur))
        {
            bot.x=i;
            bot.y=b;
            return bot;
        }
        if(coup_valide(grille,i,g,couleur))
        {
            bot.x=i;
            bot.y=g;
            return bot;
        }
    }

    // on étudie les derniers cas
    if(coup_valide(grille,1,b,couleur))
    {
         bot.x=1;
         bot.y=b;
         return bot;
    }
    if(coup_valide(grille,6,b,couleur))
    {
         bot.x=6;
         bot.y=b;
         return bot;
    }
    if(coup_valide(grille,1,g,couleur))
    {
         bot.x=1;
         bot.y=g;
         return bot;
    }
    if(coup_valide(grille,6,g,couleur))
    {
         bot.x=6;
         bot.y=g;
         return bot;
    }
}

// ======================== Fonction BOT Difficle ============================================

coup bot_difficile(int grille[][8],int couleur) // ce bot cherche de jouer un coup via l'algo MiniMax
{
    coup bot;
    int bestMove = minmax(grille, couleur, MAX_DEPTH);
    //coup bestMove = minmax(grille, couleur, MAX_DEPTH);
    for (int i=0; i<ROW; i++)
    {
        for (int j=0; j<COL; j++)
        {
           if(coup_valide(grille,i,j,couleur))
           {    
    		bot.x=i;
    		bot.y=j;
    		return bot;
    	   }   

        }
    }
}

// ======================== Vérification que la case est dans le tableau ========================
bool isInBoard(int x, int y)
{
    if (x<0 || x>=ROW || y<0 || y>=COL)
        return false;
    return true;
}

// ===== Fonction booléenne pour tester si on est dans le plateau & si la case est nulle ========
bool check(int board[ROW][COL], int color, int x, int y, int dirX, int dirY)
{
    int x2=x+dirX, y2=y+dirY;
    if (!isInBoard(x2, y2) || board[x2][y2]==0)
        return false;
    if (board[x2][y2]==color)
        return true;
    return check(board, color, x2, y2, dirX, dirY);
}

// ======================== Evalue le score si on place tel ou tel couleur ==========================
int evaluate(int board[ROW][COL], int color)
{
    int score = 0;
    for (int i=0; i<ROW; i++)
        for (int j=0; j<COL; j++)
            if (board[i][j] == color)
                score++;
    return score;
}

// =================== Renvoie du Max ==================
int max(int a, int b)
{
    return a>b ? a : b;
}

// ================== Renvoie du Min ===================

int min(int a, int b)
{
    return a<b ? a : b;
}

// ============================= Algorithme MinMax =========================
int minmax(int board[ROW][COL], int color, int depth)
{
    // on pose maxScore est - l'infini
    // on pose minScore est + l'infini
    int maxScore=-1000000, minScore=1000000;    

    // on évalue simplement si la profondeur est == à la profondeur max
    if (depth==MAX_DEPTH)
        return evaluate(board, color);

    // on parcourt le tableau
    for (int i=0; i<ROW; i++)
        for (int j=0; j<COL; j++)
        {

            if (putChess(board, color, i, j))
            {
                int score=minmax(board, 3-color, depth+1);
                // en renvoie le score max possible pr une couleur fixée
                if (color==1)
                {
                    maxScore=max(maxScore, score);
                }
                else
                // ou le min possible pour l'autre couleur
                {
                    minScore=min(minScore, score);
                }
                // position dans une grille à 0 si on l'a visité
                board[i][j]=0;
            }
        }
    
    return color==1? maxScore: minScore;
}

// ============================ Fonction de mise sur le plateau ===========================
bool putChess(int board[ROW][COL], int color, int x, int y)
{
    // cas d'erreur si on ne respecte pas les dimensions
    if (!isInBoard(x, y) || board[x][y]!=0)
        return false;
    // on déclare un booleen grâce à une bibliothèque spéciale (voir début de code)
    bool isPlaced = false;

    // on parcourt
    for (int i=0; i<8; i++)
    {
        int x2=x+direction[i][0], y2=y+direction[i][1];
        // si on n'est pasdans le tableau
        if (!isInBoard(x2, y2) || board[x2][y2]==0)
            continue;
        // déplacement
        if (board[x2][y2]!=color && check(board, color, x, y, direction[i][0], direction[i][1]))
        {
            isPlaced = true;
            int x3=x+direction[i][0], y3=y+direction[i][1];
            while (board[x3][y3]!=color)
            {
                board[x3][y3]=color;
                x3+=direction[i][0];
                y3+=direction[i][1];
            }
        }
    }
    // si il est placé (== TRUE)
    if (isPlaced)
        // on place un pion NOIR ou BLANC dans la grille
        board[x][y]=color;
        
    return isPlaced;
}
