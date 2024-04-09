/* ===========================================================================================================================
   Fichier qui contient les prototypes des fonctions du fichier jeu.c et le tableau qui représente la grille 8x8
   ===========================================================================================================================
*/

#ifndef JEU_H_INCLUDED
#define JEU_H_INCLUDED

int grille[8][8];
void charger(int *coup_a,int *debut_a,int *difficulte);
void sauvgarder(int contre,int coup_a,int debut_a,int difficulte);
void afficher_coup_joue_et_resultat(SDL_Surface *ecran);
void affihcer_coup_propose(SDL_Surface *ecran);
void afficher_gagnant(SDL_Surface *ecran);
void jouer_vs_bot(SDL_Surface *ecran,int reprendre);

#endif // JEU_H_INCLUDED
