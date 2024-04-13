#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include "tp4.h"

// Menu
int main()
{

    // 1. Créer un graphe vide
    //  2. Construire un graphe de N sommets
    //  3. Ajouter un sommet
    //  4. Ajouter une arête
    //  5. Afficher un graphe
    //  6. Donner le degré maximal du graphe
    // 7. Supprimer un sommet
    //  8.  Vérifier si le graphe contient une boucle
    // 9. Fusionner deux sommets
    //  10 . Quitter

    graphe *G = NULL;

    while (1)
    {
        printf("1. Créer un graphe vide \n");
        printf("2. Construire un graphe de N sommets \n");
        printf("3. Ajouter un sommet \n");
        printf("4. Ajouter une arête \n");
        printf("5. Afficher un graphe \n");
        printf("6. Donner le degré maximal du graphe \n");
        printf("7. Supprimer un sommet \n");

        int input;
        scanf("%d", &input);
        switch (input)
        {
        case 1:
            // Code pour créer un graphe vide
            printf("Création d'un graphe vide...\n");
            G = creeGraphe();
            break;
        case 2:
            if (G == NULL)
            {
                printf("Graphe pas encore ajouté \n");
            }
            else
            {
                printf("Veuillez entrer le nombre de sommets que vous voulez ajouter \n");
                int N;
                scanf("%d", &N);
                G = construireGraphe(N);
                printf("Construction d'un graphe de N sommets...\n");
            }

            break;
        case 3:
            // Code pour ajouter un sommet
            if (G != NULL)
            {
                printf("Ajout d'un sommet...\n");
                printf("Veuillez entrer le numéro du sommet à ajouter \n");
                int som;
                scanf("%d", &som);
                creerSommet(G, som);
                printf("ajout du sommet\n");
            }
            else
            {
                printf("Graphe pas encore ajouté \n");
            }

            break;
        case 4:
            // Code pour ajouter une arête
            if (G != NULL)
            {
                printf("Ajout d'une arête...\n");
                printf("Veuillez entrer le numéro du premier sommet pour lequel ajouter l'arête \n");
                int som1;
                scanf("%d", &som1);

                printf("Veuillez entrer le numéro du deuxième sommet pour lequel ajouter l'arête \n");
                int som2;
                scanf("%d", &som2);

                ajouterArete(G, som1, som2);
            }
            else
            {
                printf("Graphe pas encore ajouté \n");
            }

            break;
        case 5:
            // Code pour afficher un graphe
            if (G != NULL)
            {
                printf("Affichage du graphe...\n");
                printGraphe(G);
            }
            else
            {
                printf("Graphe pas encore ajouté \n");
            }

            break;
        case 6:
            if (G != NULL)
            {
                printf("calcul du degrès maximal du graphe du graphe...\n");
                int deg = rechercherDegre(G);
                printf("Le degrès maximal du graphe est de %d \n", deg);
            }
            else
            {
                printf("Graphe pas encore ajouté \n");
            }
            break;

        case 7:
            if (G != NULL)
            {
                printf("Supprimer un sommet...\n");
                int som;
                printf("Veuillez choisir un sommet à supprimer .\n");
                scanf("%d", &som);
                supprimerSommet(G, som);
            }
            else
            {
                printf("Graphe pas encore ajouté \n");
            }
            break;
        default:
            printf("Option non valide. Veuillez choisir une option entre 1 et 5.\n");
            exit(1);
        }
    }
    

    /*
    graphe *a = NULL;
    a = creeGraphe();
    creerSommet(a, 2);
    printGraphe(a);
    if (rechercherSommet(a, 2) != NULL)
        printf("Sommet trouve ! \n");
    */

    return 0;
}
