# Arbre-Rouge-Noir
Implémentation d’un programme manipulant les arbres rouge-noir en langage C, permettant l’insertion et la suppression des nœuds avec visualisation de l'arbre.

# Fonctionnalités 
- Insertion d'un nœud dans l'arbre en respectant les propriétés des arbres rouge-noir.
- Suppression d'un nœud avec rééquilibrage automatique.
- Recherche d'un nœud dans l'arbre.

# Structure de Données
Le nœud contient :
- Une valeur entière.
- Une couleur (🔴 ou ⚫).
- Un pointeur vers son parent.
- Un pointeur vers son fils gauche.
- Un pointeur vers son fils droit.
L'arbre contient :
- Un pointeur vers la racine.
- Un nœud nil, représentant les feuilles NULL noires.

# Prérequis
- Compilateur C.

# Note
- Un arbre rouge-noir est une structure de données autoéquilibrée qui garantit une insertion, une suppression et une recherche en temps logarithmique O(log n). Il respecte plusieurs propriétés :
1. Chaque nœud est soit rouge, soit noir.
2. La racine est toujours noire.
3. Toutes les feuilles (nil) sont noires.
4. Aucun nœud rouge ne peut avoir un parent rouge (pas de deux rouges consécutifs).
5. Chaque chemin d’un nœud à une feuille contient le même nombre de nœuds noirs.
- Grâce à ces propriétés, l'arbre rouge-noir garantit une hauteur proportionnelle à O(log n), assurant une efficacité optimale pour les opérations de base.
