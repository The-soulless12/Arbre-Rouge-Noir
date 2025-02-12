#include "biblio.h"
#include "biblio.c"

int main() {
    ArbreRN *arbre = creer_arbre();

    int valeurs[] = {10, 20, 30, 15, 25, 5};
    int taille = sizeof(valeurs) / sizeof(valeurs[0]);

    for (int i = 0; i < taille; i++) {
        Noeud *nouveau = creer_noeud(arbre, valeurs[i]);
        printf("Noeud cree : %d\n", nouveau->valeur);
    }

    printf("Affichage de l'arbre:\n");
    afficher_arbre(arbre->racine, arbre->nil, 0);

    liberer_arbre(arbre);
    return 0;
}
