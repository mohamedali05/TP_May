#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include "tp4.h"

// commentaire
// commentaire2
graphe *creeGraphe()
{
    graphe *g = (graphe *)malloc(sizeof(graphe));
    //g->tete = NULL;
    // autre commentaire
    return g;
}
/*
void creerSommet(graphe *g, int id)
{
    if (rechercherSommet(g, id) != NULL)
    {
        printf("Le sommet que vous essayez d'ajouter existe déjà \n");
        return;
    }
    sommet *som = (sommet *)malloc(sizeof(sommet));
    som->indice = id;

    sommet *buff = g->tete;

    if (buff == NULL || id < buff->indice)
    {
        g->tete = som;
        return;
    }
    else
    {
        sommet *buff = g->tete;
        while (buff->suivant != NULL && id > buff->suivant->indice)
        {
            buff = buff->suivant;
        }
        som->suivant = buff->suivant;
        buff->suivant = som;
    }
}
*/

void creerSommet(graphe *g, int id) {
    // Vérifier si le sommet existe déjà
    if (rechercherSommet(g, id) != NULL) {
        printf("Le sommet que vous essayez d'ajouter existe déjà\n");
        return;
    }
    
    // Créer un nouveau sommet
    sommet *nouveauSommet = (sommet *)malloc(sizeof(sommet));
    if (nouveauSommet == NULL) {
        printf("Erreur: Impossible d'allouer de la mémoire pour le nouveau sommet\n");
        return;
    }
    nouveauSommet->indice = id;
    nouveauSommet->suivant = NULL;
    nouveauSommet->voisins = NULL; // Initialisation des voisins à NULL

    // Si le graphe est vide, le nouveau sommet devient la tête du graphe
    if (g->tete == NULL || id < g->tete->indice) {
        nouveauSommet->suivant = g->tete;
        g->tete = nouveauSommet;
        return;
    }

    // Recherche de l'emplacement où insérer le nouveau sommet dans la liste triée
    sommet *precedent = g->tete;
    while (precedent->suivant != NULL && id > precedent->suivant->indice) {
        precedent = precedent->suivant;
    }

    // Insérer le nouveau sommet après 'precedent'
    nouveauSommet->suivant = precedent->suivant;
    precedent->suivant = nouveauSommet;
}


sommet *rechercherSommet(graphe *g, int id)
{
    sommet *buff = g->tete;
    while (buff != NULL)
    {
        if (buff->indice == id)
        {
            return buff;
        }
        buff = buff->suivant;
    }
    return NULL;
}

void ajouterArete(graphe *g, int id1, int id2)
{

    sommet *s1 = rechercherSommet(g, id1);
    sommet *s2 = rechercherSommet(g, id2);


    if (s1 != NULL && s2 != NULL)
    {
        
        // ajout du voisin pour s1
        if (s1->voisins == NULL)
        {
            s1->voisins = (voisin *)malloc(sizeof(voisin));
            s1->voisins->indice = s2->indice;
            s1->voisins->voisin_suivant = NULL;
        }
        else
        {
            voisin *buff = s1->voisins;
            while (buff->voisin_suivant != NULL)
            {
                buff = buff->voisin_suivant;
            }
            buff->voisin_suivant = (voisin *)malloc(sizeof(voisin));
            buff->voisin_suivant->indice = s2->indice;
            buff->voisin_suivant->voisin_suivant = NULL;
        }

        // ajout du voisin pour s2
        if (s2->voisins == NULL)
        {
            s2->voisins = (voisin *)malloc(sizeof(voisin));
            s2->voisins->indice = s1->indice;
            s2->voisins->voisin_suivant = NULL;
        }
        else
        {
            voisin *buff = s2->voisins;
            while (buff->voisin_suivant != NULL)
            {
                buff = buff->voisin_suivant;
            }
            buff->voisin_suivant = (voisin *)malloc(sizeof(voisin));
            buff->voisin_suivant->indice = s1->indice;
            buff->voisin_suivant->voisin_suivant = NULL;
            printf("Ajout de l'arête réussi ! \n");
        }
    }
    else
    {
        printf("Un des indices correspond à un sommet qui n'a pas encore été implémenté \n");
    }
}

graphe *construireGraphe(int N)
{
    int input2 = 0;
    graphe *G = creeGraphe();
    for (int i = 0; i < N; i++)
    {
        printf("Veuillez entrer le numéro du %d sommet à ajouter \n", (i + 1));
        int input;
        scanf("%d", &input);
        creerSommet(G, input);
    }
    printf("Veuillez maintenant entrer les arêtes que vous soubaitez ajouter \n");
    while (input2 != 1)
    {
        printf("Veuillez entrer le numéro du premier sommet pour lequel ajouter l'arête \n");
        int som1;
        scanf("%d", &som1);

        printf("Veuillez entrer le numéro du deuxième sommet pour lequel ajouter l'arrête \n");
        int som2;
        scanf("%d", &som2);

        ajouterArete(G, som1, som2);

        printf("Voulez-vous vous arrêter (1 pour oui) \n");
        scanf("%d", &input2);
    }
    return G;
}

int rechercherDegre(graphe *g)
{
    sommet *buff = g->tete;
    int deg = 0;
    int degSommet;
    while (buff != NULL)
    {
        degSommet = rechercherDegreSommet(buff);
        if (degSommet > deg)
        {
            deg = degSommet;
        }
        buff = buff->suivant;
    }
    return deg;
}

int rechercherDegreSommet(sommet *s)
{
    int deg = 0;
    voisin *buff = s->voisins;
    while (buff != NULL)
    {
        buff = buff->voisin_suivant;
        deg++;
    }
    return deg;
}

void supprimerSommet(graphe *g, int id)
{
    printf("Suppression d'un sommet: %d\n", id);
    if (g->tete == NULL)
    {
        printf("Le graphe est vide.\n");
        return;
    }

    sommet *current = g->tete;
    sommet *previous = NULL;

    // Trouver le sommet à supprimer et maintenir le lien avec le précédent
    while (current != NULL && current->indice != id)
    {
        previous = current;
        current = current->suivant;
    }

    // Si le sommet n'est pas trouvé
    if (current == NULL)
    {
        printf("Le sommet que vous essayez de supprimer n'existe pas.\n");
        return;
    }

    // Supprimer le sommet de la liste
    if (previous == NULL)
    { // Le sommet est la tête
        g->tete = current->suivant;
    }
    else
    {
        previous->suivant = current->suivant;
    }

    // Supprimer le sommet de la liste des voisins des autres sommets
    sommet *s = g->tete;
    while (s != NULL)
    {
        supprimerVoisin(s, id);
        s = s->suivant;
    }

    // Libérer la mémoire
    free(current);
    printf("Sommet %d supprimé.\n", id);
}

void supprimerVoisin(sommet *s, int id)
{
    if (s->voisins == NULL)
        return;

    voisin *current = s->voisins;
    voisin *previous = NULL;

    while (current != NULL && current->indice != id)
    {
        previous = current;
        current = current->voisin_suivant;
    }

    if (current == NULL)
        return; // Voisin non trouvé

    if (previous == NULL)
    { // Le voisin est le premier de la liste
        s->voisins = current->voisin_suivant;
    }
    else
    {
        previous->voisin_suivant = current->voisin_suivant;
    }

    free(current);
}

// Affiche la liste des voisins d'un sommet donné
void printListeVoisins(voisin *tete)
{
    voisin *actuel = tete;
    while (actuel != NULL)
    {
        printf("Voisin avec l'indice: %d\n", actuel->indice);
        actuel = actuel->voisin_suivant;
    }
}

// Affiche tous les sommets du graphe ainsi que leurs voisins
void printGraphe(graphe *g)
{
    if (g == NULL)
    {
        printf("Le graphe est vide.\n");
        return;
    }

    sommet *sommetActuel = g->tete;
    while (sommetActuel != NULL)
    {
        printf("Sommet avec l'indice: %d\n", sommetActuel->indice);
        printf("Voisins de ce sommet:\n");
        printListeVoisins(sommetActuel->voisins);
        sommetActuel = sommetActuel->suivant;
        printf("\n");
    }
}
