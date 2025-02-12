#ifndef BIBLIO_H_INCLUDED
#define BIBLIO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

// Définition des couleurs possibles
typedef enum { ROUGE, NOIR } Couleur;

// Structure d'un noeud de l'arbre rouge-noir
typedef struct Noeud {
    int valeur;
    Couleur couleur;
    struct Noeud *gauche, *droite, *parent;
} Noeud;

// Structure de l'arbre rouge-noir
typedef struct {
    Noeud *racine;
    Noeud *nil; // Représente les feuilles NULL noires
} ArbreRN;

// Prototypes de la machine abstraite
ArbreRN *creer_arbre();
Noeud *creer_noeud(ArbreRN *arbre, int valeur);
void afficher_arbre(Noeud *racine, Noeud *nil, int niveau);
void liberer_noeuds(Noeud *noeud, Noeud *nil);
void liberer_arbre(ArbreRN *arbre);

#endif // BIBLIO_H_INCLUDED
