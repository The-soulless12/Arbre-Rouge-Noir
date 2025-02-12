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
