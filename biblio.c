#include "biblio.h"

// Création d'un arbre rouge-noir
ArbreRN *creer_arbre() {
    ArbreRN *arbre = (ArbreRN *)malloc(sizeof(ArbreRN));
    if (!arbre) {
        perror("Erreur d'allocation de l'arbre");
        exit(EXIT_FAILURE);
    }

    // Création du noeud nil (feuille noire)
    arbre->nil = (Noeud *)malloc(sizeof(Noeud));
    if (!arbre->nil) {
        perror("Erreur d'allocation du nœud nil");
        exit(EXIT_FAILURE);
    }
    arbre->nil->couleur = NOIR;
    arbre->nil->gauche = arbre->nil->droite = arbre->nil->parent = NULL;

    arbre->racine = arbre->nil;
    return arbre;
}

// Création d'un noeud avec une valeur donnée
Noeud *creer_noeud(ArbreRN *arbre, int valeur) {
    Noeud *n = (Noeud *)malloc(sizeof(Noeud));
    if (!n) {
        perror("Erreur d'allocation du nœud");
        exit(EXIT_FAILURE);
    }
    n->valeur = valeur;
    n->couleur = ROUGE;
    // Les noeud insérés sont toujours de couleur rouge afin de ne pas changer le nombre de noeuds noirs dans l'arbre
    n->gauche = n->droite = n->parent = arbre->nil;
    return n;
}

// Affichage de l'arbre
void afficher_arbre(Noeud *racine, Noeud *nil, int niveau) {
    if (racine == nil) return;

    afficher_arbre(racine->droite, nil, niveau + 1);

    for (int i = 0; i < niveau; i++) printf("   ");
    printf("%d(%s)\n", racine->valeur, racine->couleur == ROUGE ? "R" : "N");

    afficher_arbre(racine->gauche, nil, niveau + 1);
}

void liberer_noeuds(Noeud *noeud, Noeud *nil) {
    if (noeud == nil) return;
    liberer_noeuds(noeud->gauche, nil);
    liberer_noeuds(noeud->droite, nil);
    free(noeud);
}

void liberer_arbre(ArbreRN *arbre) {
    liberer_noeuds(arbre->racine, arbre->nil);
    free(arbre->nil);
    free(arbre);
}

void rotation_gauche(ArbreRN *arbre, Noeud *x) {
    // Effectue la rotation gauche du noeud X
    Noeud *y = x->droite; // Y devient le fils droit de X
    x->droite = y->gauche; // Le sous-arbre gauche de Y devient le sous-arbre droit de X
    if (y->gauche != arbre->nil) { // Si Y avait un sous-arbre gauche, mettre à jour son parent
        y->gauche->parent = x;
    }
    y->parent = x->parent; // Y prend la place de X en tant que fils de son parent
    if (x->parent == arbre->nil) { // Si X était la racine, Y devient la nouvelle racine
        arbre->racine = y;
    } else if (x == x->parent->gauche) { // Si X était un fils gauche, Y devient le fils gauche du parent de X
        x->parent->gauche = y;
    } else { // Sinon, Y devient le fils droit du parent de X
        x->parent->droite = y;
    }
    y->gauche = x; // X devient le fils gauche de Y
    x->parent = y; // Mettre à jour le parent de X
}

void rotation_droite(ArbreRN *arbre, Noeud *x) {
    // Effectue la rotation droite du noeud X
    Noeud *y = x->gauche; // Y devient le fils gauche de X
    x->gauche = y->droite; // Le sous-arbre droit de Y devient le sous-arbre gauche de X
    if (y->droite != arbre->nil) { // Si Y avait un sous-arbre droit, mettre à jour son parent
        y->droite->parent = x;
    }
    y->parent = x->parent; // Y prend la place de X en tant que fils de son parent
    if (x->parent == arbre->nil) { // Si X était la racine, Y devient la nouvelle racine
        arbre->racine = y;
    } else if (x == x->parent->droite) { // Si X était un fils droit, Y devient le fils droit du parent de X
        x->parent->droite = y;
    } else { // Sinon, Y devient le fils gauche du parent de X
        x->parent->gauche = y;
    }
    y->droite = x; // X devient le fils droit de Y
    x->parent = y; // Mettre à jour le parent de X
}

