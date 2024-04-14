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
        printf("8. Vérifier si le graphe contient une boucle \n");
        printf("9. Fusionner 2 sommets \n");
        printf("10 . Quitter \n");

        int input;
        scanf("%d", &input);
        switch (input)
        {
        case 1:
            // Code pour créer un graphe vide
            printf("Création d'un graphe vide...\n");
            G = creerGraphe();
            break;
        case 2:
            free(G);
            graphe* G = NULL;
            printf("Veuillez entrer le nombre de sommets que vous voulez ajouter \n");
            int N;
            scanf("%d", &N);
            G = construireGraphe(N);
            printf("Construction d'un graphe de %d sommets...\n", N);

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
                afficherGraphe(G);
            }
            else
            {
                printf("Graphe pas encore ajouté \n");
            }

            break;
        case 6:
            if (G != NULL)
            {
                printf("Calcul du degré maximal du graphe...\n");
                int deg = rechercherDegre(G);
                printf("Le degré maximal du graphe est de %d \n", deg);
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
        case 8:
            if (G != NULL)
            {
                printf("Vérifier si le graphe contient une boucle...\n");
                int resultat = contientBoucle(G);
                if (resultat == 1)
                    printf("Le graphe contient une boucle.\n");
                else
                    printf("Le graphe ne contient aucune boucle.\n");
            }
            else
                printf("Graphe pas encore ajouté\n");
            break;
        case 9:
            if (G != NULL)
            {
                printf("Fusionner des sommets...\n");
                int som1;
                printf("Veuillez choisir le numéro du 1er sommet à fusionner  .\n");
                scanf("%d", &som1);

                int som2;
                printf("Veuillez choisir le numéro du 2ème sommet à fusionner  .\n");
                scanf("%d", &som2);
                fusionnerSommet(G, som1, som2);
            }
            else
            {
                printf("Graphe pas encore ajouté \n");
            }
            break;
        case 10:
            libererMemoire(G);
            exit(1);
        default:
            printf("Option non valide. Veuillez choisir une option entre 1 et 10.\n");
            break;
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