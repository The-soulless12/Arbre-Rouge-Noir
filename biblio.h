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

/* Régles des arbres rouge noir
1. Chaque nœud est soit rouge soit noir.
2. La racine est toujours noire.
3. Toutes les feuilles (nil) sont noires.
4. Un nœud rouge a toujours des fils noirs.
5. Tout chemin d’un nœud à ses feuilles contient le même nombre de nœuds noirs.*/

// Prototypes de la machine abstraite
ArbreRN *creer_arbre();
Noeud *creer_noeud(ArbreRN *arbre, int valeur);
void afficher_arbre(Noeud *racine, Noeud *nil, int niveau);
void liberer_noeuds(Noeud *noeud, Noeud *nil);
void liberer_arbre(ArbreRN *arbre);

void rotation_gauche(ArbreRN *arbre, Noeud *x);
void rotation_droite(ArbreRN *arbre, Noeud *x);
void corriger_coloration(ArbreRN *arbre, Noeud *x);
void inserer(ArbreRN *arbre, int valeur);
Noeud *rechercher(ArbreRN *arbre, int valeur);

/*En ce qui concerne l'insertion d'un noeud X dans l'arbre :
1. On insére X dans l'arbre en rouge
2. On corrige les problèmes de violations de règles 4 & 5
● cas 01 : X est la racine donc on recolorie X en noir
● cas 02 : X est le fils de A. A et D sont les fils de B. D est considéré comme l'oncle de X et B comme étant le grand père.
Si l'oncle de X est rouge (D), on colorie alors le père (A) en noir, l'oncle (D) en noir et le grand père (B) en rouge
● cas 03 : Si l'oncle (D) était déjà noir ET QUE :
❥❥ X est le fils gauche de A, A est le fils droit de B et D est le fils gauche de B
OU alors
❥❥ X est le fils droit de A, A est le fils gauche de B et D est le fils droit de B
Alors, on effectue une rotation à A dans le sens opposé de X (une rotation gauche à A si X était le fils droit de A et inversement)
● cas 04 : Si l'oncle (D) était déjà noir ET QUE :
❥❥ X est le fils droit de A, A est le fils droit de B et D est le fils gauche de B
OU alors
❥❥ X est le fils gauche de A, A est le fils gauche de B et D est le fils droit de B
Alors, on effectue une rotation à B dans le sens opposé de X (une rotation gauche à B si X était le fils droit de A et inversement)
PUIS, on recolorie A en noir et B en rouge*/

#endif // BIBLIO_H_INCLUDED
