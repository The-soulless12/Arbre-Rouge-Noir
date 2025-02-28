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
Noeud *rechercher(ArbreRN *arbre, int valeur);
void inserer(ArbreRN *arbre, int valeur);

/* En ce qui concerne l'insertion d'un nœud X dans l'arbre :
1. On insère X dans l'arbre en rouge.

2. On corrige les problèmes de violations des règles 4 & 5 :
   ● Cas 01 : X est la racine
     ❥❥ On recolorie X en noir.

   ● Cas 02 : X est le fils de A.
     ❥❥ A et D sont les fils de B.
     ❥❥ D est considéré comme l'oncle de X et B comme étant le grand-père.
     - Si l'oncle de X est rouge (D) :
         - On colorie le père (A) en noir.
         - On colorie l'oncle (D) en noir.
         - On colorie le grand-père (B) en rouge.

   ● Cas 03 : Si l'oncle (D) était déjà noir ET QUE :
     ❥❥ X est le fils gauche de A, A est le fils droit de B et D est le fils gauche de B
     OU alors
     ❥❥ X est le fils droit de A, A est le fils gauche de B et D est le fils droit de B
     - On effectue une rotation à A dans le sens opposé de X
     (une rotation gauche à A si X était le fils droit de A et inversement).

   ● Cas 04 : Si l'oncle (D) était déjà noir ET QUE :
     ❥❥ X est le fils droit de A, A est le fils droit de B et D est le fils gauche de B
     OU alors
     ❥❥ X est le fils gauche de A, A est le fils gauche de B et D est le fils droit de B
     - On effectue une rotation à B dans le sens opposé de X
     (une rotation gauche à B si X était le fils droit de A et inversement).
     - On recolorie A en noir et B en rouge.*/

void greffe_sous_arbre(ArbreRN *arbre, Noeud *u, Noeud *v);
Noeud* minimum(ArbreRN *arbre, Noeud *noeud);
void supprimer(ArbreRN *arbre, Noeud *x);
void corriger_suppression(ArbreRN *arbre, Noeud *x);

/* En ce qui concerne la suppression d'un nœud X dans l'arbre :
1. On supprime X en respectant les règles de l’arbre binaire de recherche.

2. On corrige les violations des règles 4 & 5 si nécessaire :
   ● Cas 01 : X n’a qu’un seul fils ou aucun
     ❥❥ On greffe le sous-arbre à la place de X.

   ● Cas 02 : X a deux fils
     ❥❥ On trouve son successeur Y (le plus petit élément du sous-arbre droit).
     ❥❥ On retient la couleur et les valeurs de Y dans X.
     ❥❥ On supprime Y (qui n’aura au maximum qu’un seul fils).

   ● Si la couleur originale de Y était noire, il faut corriger l'arbre :
     - Cas 01 : X a un frère W rouge
         ❥❥ On recolore W en noir et son parent en rouge.
         ❥❥ On effectue une rotation vers la gauche/droite sur le parent.

     - Cas 02 : X a un frère W noir dont les deux fils sont noirs
         ❥❥ On recolore W en rouge.
         ❥❥ On applique la correction au parent de X.

     - Cas 03 : X a un frère W noir, dont un de ses fils est rouge et l’autre est noir
         ❥❥ On recolore ce fils en noir et W en rouge.
         ❥❥ On effectue une rotation sur W.

     - Cas 04 : X a un frère W noir et son fils extérieur est rouge
         ❥❥ On recolore W avec la couleur du parent.
         ❥❥ On colore le parent en noir et le fils extérieur en noir.
         ❥❥ On effectue une rotation sur le parent.*/

#endif // BIBLIO_H_INCLUDED
