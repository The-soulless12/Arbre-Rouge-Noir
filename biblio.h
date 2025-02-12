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

// Régles des arbres rouge noir
// 1. Chaque nœud est soit rouge soit noir.
// 2. La racine est toujours noire.
// 3. Toutes les feuilles (nil) sont noires.
// 4. Un nœud rouge a toujours des fils noirs.
// 5. Tout chemin d’un nœud à ses feuilles contient le même nombre de nœuds noirs.

// Prototypes de la machine abstraite
ArbreRN *creer_arbre();
Noeud *creer_noeud(ArbreRN *arbre, int valeur);
void afficher_arbre(Noeud *racine, Noeud *nil, int niveau);
void liberer_noeuds(Noeud *noeud, Noeud *nil);
void liberer_arbre(ArbreRN *arbre);
void rotation_gauche(ArbreRN *arbre, Noeud *x);
void rotation_droite(ArbreRN *arbre, Noeud *x);

#endif // BIBLIO_H_INCLUDED
