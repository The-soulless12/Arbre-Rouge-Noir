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

        // Affichage en rouge si le nœud est ROUGE, sinon en couleur normale
        if (racine->couleur == ROUGE) {
            printf("\033[1;31m%d(R)\033[0m\n", racine->valeur);
        } else {
            printf("\033[1;34m%d(N)\033[0m\n", racine->valeur);
        }

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

// Corrige les couleurs après une insertion
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

// Insertion d'un noeud dans un arbre rouge-noir
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

// Recherche d'une valeur dans un arbre rouge-noir
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

// Effectue la greffe d'un sous arbre
void greffe_sous_arbre(ArbreRN *arbre, Noeud *u, Noeud *v) {
    // Si u était la racine, v devient la nouvelle racine
    if (u->parent == arbre->nil) {
        arbre->racine = v;
    }
    else if (u == u->parent->gauche) {
        u->parent->gauche = v; // u était un fils gauche
    } else {
        u->parent->droite = v; // u était un fils droit
    }
    // Si v n'est pas NULL, on met à jour son parent
    if (v != arbre->nil) {
        v->parent = u->parent;
    }
}

// Trouve le noeud avec la plus petite valeur dans un sous-arbre
Noeud* minimum(ArbreRN *arbre, Noeud *noeud) {
    while (noeud->gauche != arbre->nil) {
        noeud = noeud->gauche;
    }
    return noeud;
}

// Suppression d'un noeud dans un arbre rouge-noir
void supprimer(ArbreRN *arbre, Noeud *x) {
    Noeud *y = x;
    Couleur couleur_origine = y->couleur;
    Noeud *z;

    if (x->gauche == arbre->nil) { // Cas 1 : X n'a pas de fils gauche
        z = x->droite;
        greffe_sous_arbre(arbre, x, x->droite);
    } else if (x->droite == arbre->nil) { // Cas 2 : X n'a pas de fils droit
        z = x->gauche;
        greffe_sous_arbre(arbre, x, x->gauche);
    } else { // Cas 3 : X a deux fils
        y = minimum(arbre, x->droite);
        couleur_origine = y->couleur;
        z = y->droite;

        if (y->parent == x) {
            z->parent = y;
        } else {
            greffe_sous_arbre(arbre, y, y->droite);
            y->droite = x->droite;
            y->droite->parent = y;
        }

        greffe_sous_arbre(arbre, x, y);
        y->gauche = x->gauche;
        y->gauche->parent = y;
        y->couleur = x->couleur;
    }

    if (couleur_origine == NOIR) {
        corriger_suppression(arbre, z);
    }
}

// Corrige les couleurs après une suppression
void corriger_suppression(ArbreRN *arbre, Noeud *x) {
    while (x != arbre->racine && x->couleur == NOIR) {
        if (x == x->parent->gauche) { // Si X est un fils gauche
            Noeud *w = x->parent->droite; // W est le frère de X

            // Cas 1 : W est rouge, on recolore et effectue une rotation gauche
            if (w->couleur == ROUGE) {
                w->couleur = NOIR;
                x->parent->couleur = ROUGE;
                rotation_gauche(arbre, x->parent);
                w = x->parent->droite;
            }

            // Cas 2 : W et ses enfants sont noirs, on recolore W en rouge
            if (w->gauche->couleur == NOIR && w->droite->couleur == NOIR) {
                w->couleur = ROUGE;
                x = x->parent;
            } else {
                // Cas 3 : W est noir mais son fils droit est noir et son fils gauche est rouge
                if (w->droite->couleur == NOIR) {
                    w->gauche->couleur = NOIR;
                    w->couleur = ROUGE;
                    rotation_droite(arbre, w);
                    w = x->parent->droite;
                }

                // Cas 4 : W est noir et son fils droit est rouge
                w->couleur = x->parent->couleur;
                x->parent->couleur = NOIR;
                w->droite->couleur = NOIR;
                rotation_gauche(arbre, x->parent);
                x = arbre->racine;
            }
        } else { // Même logique que ci-dessus, mais inversée pour le fils droit
            Noeud *w = x->parent->gauche;

            if (w->couleur == ROUGE) {
                w->couleur = NOIR;
                x->parent->couleur = ROUGE;
                rotation_droite(arbre, x->parent);
                w = x->parent->gauche;
            }

            if (w->droite->couleur == NOIR && w->gauche->couleur == NOIR) {
                w->couleur = ROUGE;
                x = x->parent;
            } else {
                if (w->gauche->couleur == NOIR) {
                    w->droite->couleur = NOIR;
                    w->couleur = ROUGE;
                    rotation_gauche(arbre, w);
                    w = x->parent->gauche;
                }

                w->couleur = x->parent->couleur;
                x->parent->couleur = NOIR;
                w->gauche->couleur = NOIR;
                rotation_droite(arbre, x->parent);
                x = arbre->racine;
            }
        }
    }
    x->couleur = NOIR; // La racine est toujours noire
}
