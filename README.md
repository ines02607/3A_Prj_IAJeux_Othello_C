# ===============================================================
# ===================== PROJET IA & JEUX=========================
# ======== par Inès, Imène, Margot, Louna & Louise ==============

# Pour compiler sous SDL

$ gcc main.c -o othello -lSDLmain -lSDL -lSDL_ttf -lSDL_image
$ ./othello

# Que trouve t-on dans ce fichier ?

# Gestion

Les fichiers gestion.c & gestion .h
Contient les fonctions qui gèrent le tableau "grille" & le bot :

    Pour la gestion du jeu :
    - initialiser_grille
    - case_existe
    - coup_valide
    - jouez_coup
    - proposer_coup
    - nettoyer_grille
    - Partie_terminee

    Pour le calcul du score :
    - nb_poin_noir
    - nb_poin_blanc

    Pour la conversion d'un clic en position :
    - get_coup
    - encore_coup

    Pour le jeu :
    - bot_facile
    - bot_moyen
    - bot_difficile

# Jeu 

Les fichiers jeu.c & jeu.h
Contient les fonctions qui gèrent les images après "nouvelle partie" : 

    - afficher_coup_joue_et_resultat
    - affihcer_coup_propose
    - afficher_gagnant
    - jouer_vs_bot


# Plateau

Les fichiers plateau.c & plateau.h

# Variables

Le fichier variables.h

# Images

Un certain nombre d'images directement mise dans le même dossier (chemin d'accès difficilement supportable sous Windows) réalisé avec le logiciel CANVA

# Sauvegarde

Un fichier sauvegarde pour le bouton reprendre