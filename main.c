#include <stdio.h>
#include <stdlib.h>
<<<<<<< HEAD
=======
#include <math.h>
>>>>>>> 1a18e4987aa74bc7d7854b7840aaf26c3c4aff75
#include "tp3.h"

int main() {
    graphe *G = NULL;

    // Ce code sert à initialiser un graphe par défaut 
    // Cela permet de partir avec une base fixe pour notre graphe et ne pas refaire à chaque fois le même
    /*G = creeGraphe() ; 
    creerSommet(G, 1 , 1);
    creerSommet(G, 2 , 1);
    creerSommet(G, 3 , 1);
    ajouterArete(G, 1, 2 , 1) ;
    ajouterArete(G, 2, 3 , 1);
    ajouterArete(G, 1, 3 ,1) ;
    */



    while (1) {
        printf("1. Creer un graphe vide \n");
        printf("2. Construire un graphe de N sommets \n");
        printf("3. Ajouter un sommet \n");
        printf("4. Ajouter une arete \n");
        printf("5. Afficher un graphe \n");
        printf("6. Donner le degre maximal du graphe \n");
        printf("7. Supprimer un sommet \n");
        printf("8. Verifier si le graphe contient une boucle \n");
        printf("9. Fusionner 2 sommets \n");
        printf("10. Quitter \n");
        int input;
        scanf("%d", &input);
        switch (input) {
            case 1:
                printf("Creation d'un graphe vide...\n");
                G = creeGraphe();
                break;
            case 2:
                free(G);
                printf("Veuillez entrer le nombre de sommets que vous voulez ajouter \n");
                int N;
                scanf("%d", &N);
                if (N <= 0) {
                    printf("Construction du graphe impossible. Nombre de sommet invalide \n");
                    break;
                }
                G = construireGraphe(N);
                printf("Construction d'un graphe de N sommets...\n");
                break;
            case 3:
                if (G != NULL) {
                    printf("Ajout d'un sommet...\n");
                    printf("Veuillez entrer le numero du sommet a ajouter \n");
                    int som;
                    scanf("%d", &som);
                    creerSommet(G, som , 1);
                    printf("ajout du sommet\n");
                } else {
                    printf("Graphe pas encore ajoute \n");
                }
                break;
            case 4:
                if (G != NULL) {
                    printf("Ajout d'une arete...\n");
                    printf("Veuillez entrer le numero du premier sommet pour lequel ajouter l'arete \n");
                    int som1;
                    scanf("%d", &som1);

                    printf("Veuillez entrer le numero du deuxieme sommet pour lequel ajouter l'arete \n");
                    int som2;
                    scanf("%d", &som2);

                    ajouterArete(G, som1, som2 , 1);
                } else {
                    printf("Graphe pas encore ajoute \n");
                }
                break;
            case 5:
                if (G != NULL) {
                    printf("Affichage du graphe...\n");
                    printGraphe(G);
                } else {
                    printf("Graphe pas encore ajoute \n");
                }
                break;
            case 6:
                if (G != NULL) {
                    printf("Calcul du degre maximal du graphe...\n");
                    int deg = rechercherDegre(G);
                    printf("Le degre maximal du graphe est de %d \n", deg);
                } else {
                    printf("Graphe pas encore ajoute \n");
                }
                break;
            case 7:
                if (G != NULL) {
                    printf("Supprimer un sommet...\n");
                    int som;
                    printf("Veuillez choisir un sommet a supprimer.\n");
                    scanf("%d", &som);
                    supprimerSommet(G, som , 1);
                } else {
                    printf("Graphe pas encore ajoute \n");
                }
                break;
            case 8:
            if (G != NULL)
            {
                printf("Verifier si le graphe contient une boucle...\n");
                int resultat = contientBoucle(*G);
                if (resultat == 1){
                    printf("Le graphe contient au moins une boucle.\n");
                }else{
                    printf("Le graphe ne contient aucune boucle.\n");
                }
                    
            
                    
            }
            else
                printf("Graphe pas encore ajoute\n");
            break;
            case 9:
                if (G != NULL) {
                    printf("Fusionner des sommets...\n");
                    int som1;
                    printf("Veuillez choisir le numero du 1er sommet a fusionner.\n");
                    scanf("%d", &som1);

                    int som2;
                    printf("Veuillez choisir le numero du 2eme sommet a fusionner.\n");
                    scanf("%d", &som2);
                    fusionnerSommet(G, som1, som2);
                } else {
                    printf("Graphe pas encore ajoute \n");
                }
                break;
            case 10:
                libererMemoire(G) ; 
                exit(1);
            default:
                printf("Option non valide. Veuillez choisir une option entre 1 et 10.\n");
                break;
        }
    }

    return 0;
}
