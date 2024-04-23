#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "tp3.h"

graphe *creerGraphe()
{
    graphe *g = (graphe *)malloc(sizeof(graphe));
    return g;
}

void creerSommet(graphe *g, int id)
{
    // Vérifier si le sommet existe déjà
    if (rechercherSommet(g, id) != NULL)
    {
        printf("Le sommet que vous essayez d'ajouter existe deja\n");
        return;
    }

    // Créer un nouveau sommet
    sommet *nouveauSommet = (sommet *)malloc(sizeof(sommet));
    if (nouveauSommet == NULL)
    {
        printf("Erreur: Impossible d'allouer de la memoire pour le nouveau sommet\n");
        return;
    }
    nouveauSommet->indice = id;
    nouveauSommet->suivant = NULL;
    nouveauSommet->voisins = NULL; // Initialisation des voisins à NULL

    // Si le graphe est vide, le nouveau sommet devient la tête du graphe
    if (g->tete == NULL || id < g->tete->indice)
    {
        nouveauSommet->suivant = g->tete;
        g->tete = nouveauSommet;
        return;
    }

    // Recherche de l'emplacement où insérer le nouveau sommet dans la liste triée
    sommet *precedent = g->tete;
    while (precedent->suivant != NULL && id > precedent->suivant->indice)
    {
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
        if (rechercherArrete(g, id1, id2) == 1)
        {
            printf("L'arete que vous souhaitez ajouter existe deja.\n");
            return;
        }

        // Ajout du voisin pour s1 de manière ordonnée
        voisin *nouveauVoisin1 = (voisin *)malloc(sizeof(voisin));
        if (nouveauVoisin1 == NULL)
        {
            printf("Erreur: Impossible d'allouer de la memoire pour le nouveau voisin\n");
            return;
        }
        nouveauVoisin1->indice = id2;
        nouveauVoisin1->voisin_suivant = NULL;

        if (s1->voisins == NULL || s1->voisins->indice > id2)
        {
            // Insertion au début
            nouveauVoisin1->voisin_suivant = s1->voisins;
            s1->voisins = nouveauVoisin1;
        }
        else
        {
            // Insertion à la position correcte
            voisin *actuel = s1->voisins;
            while (actuel->voisin_suivant != NULL && actuel->voisin_suivant->indice < id2)
            {
                actuel = actuel->voisin_suivant;
            }
            nouveauVoisin1->voisin_suivant = actuel->voisin_suivant;
            actuel->voisin_suivant = nouveauVoisin1;
        }

        // Ajouter l'arête de manière symétrique si les sommets sont différents
        if (id1 != id2)
        {
            voisin *nouveauVoisin2 = (voisin *)malloc(sizeof(voisin));

            nouveauVoisin2->indice = id1;
            nouveauVoisin2->voisin_suivant = NULL;

            if (s2->voisins == NULL || s2->voisins->indice > id1)
            {
                // Insertion au début
                nouveauVoisin2->voisin_suivant = s2->voisins;
                s2->voisins = nouveauVoisin2;
            }
            else
            {
                // Insertion à la position correcte
                voisin *actuel = s2->voisins;
                while (actuel->voisin_suivant != NULL && actuel->voisin_suivant->indice < id1)
                {
                    actuel = actuel->voisin_suivant;
                }
                nouveauVoisin2->voisin_suivant = actuel->voisin_suivant;
                actuel->voisin_suivant = nouveauVoisin2;
            }
        }
        printf("Ajout de l'arete reussi entre %d et %d.\n", id1, id2);
    }
    else
    {
        printf("Un des indices correspond à un sommet qui n'a pas encore ete implemente.\n");
    }
}

graphe *construireGraphe(int N)
{
    int input2 = 0;
    graphe *G = creerGraphe();
    for (int i = 0; i < N; i++)
    {
        printf("Veuillez entrer le numero du  sommet %d a ajouter \n", (i + 1));
        int input;
        scanf("%d", &input);
        creerSommet(G, input);
    }
    printf("Souhaitez vous ajouter des aretes (0 pour oui , 1 pour non )\n");
    scanf("%d", &input2);
    while (input2 != 1)
    {
        printf("Veuillez entrer le numero du premier sommet pour lequel ajouter l'arete \n");
        int som1;
        scanf("%d", &som1);

        printf("Veuillez entrer le numero du deuxieme sommet pour lequel ajouter l'arete \n");
        int som2;
        scanf("%d", &som2);

        ajouterArete(G, som1, som2);

        printf("Voulez-vous vous arreter (1 pour oui , 0 pour non ) \n");
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

int rechercherArrete(graphe *g, int id1, int id2)
{
    sommet *s1 = rechercherSommet(g, id1);
    sommet *s2 = rechercherSommet(g, id2);

    if (s1 == NULL || s2 == NULL)
    {
        return 0;
    }
    voisin *v1 = s1->voisins;
    while (v1 != NULL)
    {
        if (v1->indice == id2)
        {
            return 1;
        }
        v1 = v1->voisin_suivant;
    }
    return 0;
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
    printf("Sommet %d a ete supprime.\n", id);
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
/*
int contientBoucle(graphe g) {
    // Création d'une nouvelle copie du graphe pour manipulations
    graphe* nouveau_graphe = creeGraphe();

    // Copie de tous les sommets du graphe d'origine vers la nouvelle copie
    sommet* sommet_a_dupli = g.tete;
    while (sommet_a_dupli != NULL) {
        creerSommet(nouveau_graphe, sommet_a_dupli->indice);
        sommet_a_dupli = sommet_a_dupli->suivant;
    }

    // Copie de toutes les arêtes du graphe d'origine vers la nouvelle copie
    sommet_a_dupli = g.tete;
    while (sommet_a_dupli != NULL) {
        voisin* voisin_a_dupli = sommet_a_dupli->voisins;
        while (voisin_a_dupli != NULL) {
            ajouterArete(nouveau_graphe, sommet_a_dupli->indice, voisin_a_dupli->indice);
            voisin_a_dupli = voisin_a_dupli->voisin_suivant;
        }
        sommet_a_dupli = sommet_a_dupli->suivant;
    }

    // Recherche de boucle dans la nouvelle copie du graphe
    sommet* sommet_test = nouveau_graphe->tete;
    while (sommet_test != NULL) {
        voisin* voisin_test = sommet_test->voisins;
        int compteur_voisin = 0;
        while (voisin_test != NULL) {
            compteur_voisin++;
            voisin_test = voisin_test->voisin_suivant;
        }
        // Supprimer le sommet s'il n'a qu'un seul voisin
        if (compteur_voisin == 1 || voisin_test == NULL) {
            supprimerSommet(nouveau_graphe, sommet_test->indice);
            sommet_test = nouveau_graphe->tete; // Retourner au début pour vérifier si un autre sommet doit être supprimé
        } else {
            sommet_test = sommet_test->suivant; // Passer au sommet suivant
        }
    }


    // Vérification de la présence de sommets restants (s'il reste des sommets, cela signifie qu'il y a une boucle)
    sommet_test = nouveau_graphe->tete;
    if (sommet_test != NULL)
        return 1; // Le graphe contient une boucle
    else
        return 0; // Le graphe ne contient pas de boucle
}
*/

int contientBoucle(graphe g) {
    bool *visited = calloc(g->n, sizeof(bool));
    int *parent = calloc(g->n, sizeof(int));

    for (int v = 0; v < g->n; v++) {
        if (!visited[v]) {
            if (isCyclicUtil(g, v, visited, parent, -1)) {
                free(visited);
                free(parent);
                return 1;
            }
        }
    }

    free(visited);
    free(parent);
    return 0;
}

bool isCyclicUtil(graphe g, int v, bool *visited, int *parent, int parent_index) {
    visited[v] = true;
    parent[v] = parent_index;

    struct sommet *current = g->liste_sommets;
    while (current != NULL) {
        struct voisin *neighbor = current->liste_voisins;
        while (neighbor != NULL) {
            if (!visited[neighbor->voisin]) {
                if (isCyclicUtil(g, neighbor->voisin, visited, parent, v)) {
                    return true;
                }
            } else if (parent[neighbor->voisin] != v) {
                return true;
            }
            neighbor = neighbor->suivant;
        }
        current = current->suivant;
    }

    return false;
}

void fusionnerSommet(graphe *g, int idSommet1, int idSommet2)
{
    if (idSommet1 == idSommet2)
    {
        printf("Les deux sommets sont identiques.\n");
        return;
    }

    int newId = idSommet1 < idSommet2 ? idSommet1 : idSommet2;
    int oldId = idSommet1 > idSommet2 ? idSommet1 : idSommet2;

    sommet *newSommet = rechercherSommet(g, newId);
    sommet *oldSommet = rechercherSommet(g, oldId);

    if (newSommet == NULL || oldSommet == NULL)
    {
        printf("L'un des sommets specifies n'existe pas.\n");
        return;
    }

    // Transférer les voisins de oldSommet à newSommet
    voisin *v = oldSommet->voisins;
    while (v != NULL)
    {
        if (rechercherArrete(g, newId, v->indice) == 0)
        {
            ajouterArete(g, newId, v->indice);
        }
        v = v->voisin_suivant;
    }

    // Supprimer l'ancien sommet
    supprimerSommet(g, oldId);
    printf("Les sommets %d et %d ont ete fusionnes sous l'identifiant %d.\n", idSommet1, idSommet2, newId);
}

void libererMemoire(graphe *g) {
    sommet *s = g->tete;
    while (s != NULL) {
        voisin *v = s->voisins;
        while (v != NULL) {
            voisin *temp = v;
            v = v->voisin_suivant;
            free(temp);
        }
        sommet *temp = s;
        s = s->suivant;
        free(temp);
    }
    free(g);
}
