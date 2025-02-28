#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "biblio.h"
#include "biblio.c"
#define CLEAR "cls"

void afficher_menu() {
    printf("\nARBRE ROUGE ET NOIR - THE SOULLESS\n");
    printf("1. Ajouter un noeud\n");
    printf("2. Supprimer un noeud\n");
    printf("3. Rechercher un noeud\n");
    printf("4. Afficher l'arbre\n");
    printf("5. Quitter\n");
    printf("Votre choix : ");
}

int check_entier() {
    int valeur;
    if (scanf("%d", &valeur) != 1) {
        while (getchar() != '\n');
        return -1;
    }
    return valeur;
}

// Fonction pour insérer plusieurs valeurs séparées
void inserer_valeurs_multiples(ArbreRN *arbre) {
    char buffer[256];
    printf("\nEntrez plusieurs valeurs a inserer (separees par des espaces) : ");
    getchar();
    fgets(buffer, sizeof(buffer), stdin);

    char *token = strtok(buffer, " ");
    while (token != NULL) {
        int valeur;
        if (sscanf(token, "%d", &valeur) == 1) {
            inserer(arbre, valeur);
        }
        token = strtok(NULL, " ");
    }
}

int main() {
    ArbreRN *arbre = creer_arbre();
    int choix, valeur;

    do {
        system(CLEAR);
        afficher_menu();
        choix = check_entier();

        switch (choix) {
            case 1:
                do {
                    system(CLEAR);
                    printf("\nARBRE ROUGE ET NOIR - THE SOULLESS\n");
                    printf("\n1. Inserer une seule valeur.\n2. Inserer plusieurs valeurs.\nVotre choix : ");
                    int sub_choix = check_entier();

                    if (sub_choix == 1) {
                        printf("\nEntrez une valeur a inserer : ");
                        valeur = check_entier();
                        if (valeur != -1) {
                            inserer(arbre, valeur);
                        } else {
                            printf("Valeur incorrecte !\n");
                        }
                    } else if (sub_choix == 2) {
                        inserer_valeurs_multiples(arbre);
                    }

                    printf("Affichage de l'arbre:\n\n");
                    afficher_arbre(arbre->racine, arbre->nil, 0);

                    printf("\nPour inserer d'autres nombres, tapez 0.\nPour revenir au menu principal, tapez une autre touche.\nVotre choix : ");
                    choix = check_entier();
                } while (choix == 0);
                choix = 0;
                break;

            case 2:
                do {
                    system(CLEAR);
                    printf("\nARBRE ROUGE ET NOIR - THE SOULLESS\n");
                    printf("Entrez un nombre a supprimer : ");
                    valeur = check_entier();

                    if (valeur != -1) {
                        supprimer(arbre, rechercher(arbre, valeur));
                        printf("Affichage de l'arbre:\n\n");
                        afficher_arbre(arbre->racine, arbre->nil, 0);
                    } else {
                        printf("Valeur incorrecte !\n");
                    }

                    printf("\nPour supprimer un autre nombre, tapez 0.\nPour revenir au menu principal, tapez une autre touche.\nVotre choix : ");
                    choix = check_entier();
                } while (choix == 0);
                choix = 0;
                break;

            case 3:
                do {
                    system(CLEAR);
                    printf("\nARBRE ROUGE ET NOIR - THE SOULLESS\n");
                    printf("Entrez un nombre a rechercher : ");
                    printf("Entrez un nombre a rechercher : ");
                    valeur = check_entier();

                    if (valeur != -1) {
                        if (rechercher(arbre, valeur)) {
                            printf("\033[1;32mLa valeur %d existe dans l'arbre.\033[0m\n", valeur);
                        } else {
                            printf("\033[1;31mLa valeur %d n'existe pas dans l'arbre.\033[0m\n", valeur);
                        }
                    } else {
                        printf("Valeur incorrecte !\n");
                    }

                    printf("\nPour rechercher un autre nombre, tapez 0.\nPour revenir au menu principal, tapez une autre touche.\nVotre choix : ");
                    choix = check_entier();
                } while (choix == 0);
                choix = 0;
                break;

            case 4:
                system(CLEAR);
                printf("\nARBRE ROUGE ET NOIR - THE SOULLESS\n");
                printf("Affichage de l'arbre:\n\n");
                afficher_arbre(arbre->racine, arbre->nil, 0);
                printf("\nAppuyez sur une touche pour revenir au menu principal...");
                getchar(); getchar();
                break;

            default:
                system(CLEAR);
                break;
        }
    } while (choix != 5);

    liberer_arbre(arbre);
    return 0;
}
