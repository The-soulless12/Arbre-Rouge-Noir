#ifndef BIBLIO_H_INCLUDED
#define BIBLIO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

// D�finition des couleurs possibles
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
    Noeud *nil; // Repr�sente les feuilles NULL noires
} ArbreRN;

// R�gles des arbres rouge noir
// 1. Chaque n�ud est soit rouge soit noir.
// 2. La racine est toujours noire.
// 3. Toutes les feuilles (nil) sont noires.
// 4. Un n�ud rouge a toujours des fils noirs.
// 5. Tout chemin d�un n�ud � ses feuilles contient le m�me nombre de n�uds noirs.

// Prototypes de la machine abstraite
ArbreRN *creer_arbre();
Noeud *creer_noeud(ArbreRN *arbre, int valeur);
void afficher_arbre(Noeud *racine, Noeud *nil, int niveau);
void liberer_noeuds(Noeud *noeud, Noeud *nil);
void liberer_arbre(ArbreRN *arbre);
void rotation_gauche(ArbreRN *arbre, Noeud *x);
void rotation_droite(ArbreRN *arbre, Noeud *x);

#endif // BIBLIO_H_INCLUDED
