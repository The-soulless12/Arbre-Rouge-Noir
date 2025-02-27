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
        perror("Erreur d'allocation du noeud nil");
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
        perror("Erreur d'allocation du noeud");
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
    if (racine != nil) {
        afficher_arbre(racine->droite, nil, niveau + 1);
        for (int i = 0; i < niveau; i++) {
            printf("    ");
        }
        printf("%d(%s)\n", racine->valeur, racine->couleur == ROUGE ? "R" : "N");
        afficher_arbre(racine->gauche, nil, niveau + 1);
    } else {
        if (niveau > 0) {
            for (int i = 0; i < niveau; i++) {
                printf("    ");
            }
            printf("..\n");
        }
    }
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

// Effectue la rotation gauche du noeud X
void rotation_gauche(ArbreRN *arbre, Noeud *x) {
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

// Effectue la rotation droite du noeud X
void rotation_droite(ArbreRN *arbre, Noeud *x) {
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

// Correction après insertion
void corriger_insertion(ArbreRN *arbre, Noeud *z) {
    while (z->parent->couleur == ROUGE) { // Tant que le parent est rouge
        if (z->parent == z->parent->parent->gauche) { // Si le parent est un fils gauche
            Noeud *y = z->parent->parent->droite; // Oncle à droite
            if (y->couleur == ROUGE) { // Cas 1 : Oncle rouge
                z->parent->couleur = NOIR;
                y->couleur = NOIR;
                z->parent->parent->couleur = ROUGE;
                z = z->parent->parent;
            } else {
                if (z == z->parent->droite) { // Cas 2 : z est un fils droit
                    z = z->parent;
                    rotation_gauche(arbre, z);
                }
                // Cas 3 : z est un fils gauche
                z->parent->couleur = NOIR;
                z->parent->parent->couleur = ROUGE;
                rotation_droite(arbre, z->parent->parent);
            }
        } else { // Cas symétrique si le parent est un fils droit
            Noeud *y = z->parent->parent->gauche; // Oncle à gauche
            if (y->couleur == ROUGE) { // Cas 1 : Oncle rouge
                z->parent->couleur = NOIR;
                y->couleur = NOIR;
                z->parent->parent->couleur = ROUGE;
                z = z->parent->parent;
            } else {
                if (z == z->parent->gauche) { // Cas 2 : z est un fils gauche
                    z = z->parent;
                    rotation_droite(arbre, z);
                }
                // Cas 3 : z est un fils droit
                z->parent->couleur = NOIR;
                z->parent->parent->couleur = ROUGE;
                rotation_gauche(arbre, z->parent->parent);
            }
        }
    }
    arbre->racine->couleur = NOIR; // La racine est toujours noire
}

// Insertion d'un nœud dans l'arbre rouge-noir
void inserer(ArbreRN *arbre, int valeur) {
    Noeud *z = creer_noeud(arbre, valeur); // Création du nouveau nœud rouge
    Noeud *y = arbre->nil;
    Noeud *x = arbre->racine;

    while (x != arbre->nil) { // Trouver l'emplacement d'insertion
        y = x;
        if (z->valeur < x->valeur) {
            x = x->gauche;
        } else if (valeur > x->valeur) {
            x = x->droite;
        } else {
            free(z);
            return; // Il s'agit d'un doublon, on ne l'insére pas dans l'arbre
        }
    }

    z->parent = y;
    if (y == arbre->nil) { // L'arbre était vide
        arbre->racine = z;
    } else if (z->valeur < y->valeur) {
        y->gauche = z;
    } else {
        y->droite = z;
    }

    z->gauche = arbre->nil;
    z->droite = arbre->nil;
    z->couleur = ROUGE; // Le nœud est inséré en rouge

    corriger_insertion(arbre, z); // Correction après insertion
}

// Recherche une valeur dans l'arbre rouge-noir
Noeud *rechercher(ArbreRN *arbre, int valeur) {
    Noeud *courant = arbre->racine;

    while (courant != arbre->nil) {
        if (valeur == courant->valeur) {
            return courant;
        } else if (valeur < courant->valeur) {
            courant = courant->gauche;
        } else {
            courant = courant->droite;
        }
    }

    return NULL;
}
