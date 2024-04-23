#include <stdio.h>
#include <stdlib.h>
#include "tp3.h"

// Fonction pour créer un nouveau graphe
graphe *creeGraphe() {
    graphe *g = (graphe *)malloc(sizeof(graphe));
    if (g == NULL) {
        printf("Erreur: Impossible d'allouer de la memoire pour le graphe\n");
        exit(EXIT_FAILURE);
    }
    g->tete = NULL;
    return g;
}

// Fonction pour créer un nouveau sommet dans le graphe
void creerSommet(graphe *g, int id) {
    // Vérifie si le sommet existe déjà dans le graphe
    if (rechercherSommet(g, id) != NULL) {
        printf("Le sommet que vous essayez d'ajouter existe deja\n");
        return;
    }
    // Vérifie si l'identifiant du sommet est positif
    if (id < 0) {
        printf("Le sommet que vous essayez d'ajouter doit etre strictement positif\n");
        return;
    }
    // Alloue de la mémoire pour le nouveau sommet
    sommet *nouveauSommet = (sommet *)malloc(sizeof(sommet));
    if (nouveauSommet == NULL) {
        printf("Erreur: Impossible d'allouer de la memoire pour le nouveau sommet\n");
        exit(EXIT_FAILURE);
    }
    // Initialise les attributs du nouveau sommet
    nouveauSommet->indice = id;
    nouveauSommet->suivant = NULL;
    nouveauSommet->voisins = NULL;
    // Si le graphe est vide ou l'indice est inférieur à l'indice du premier sommet, le nouveau sommet devient la tête du graphe
    if (g->tete == NULL || id < g->tete->indice) {
        nouveauSommet->suivant = g->tete;
        g->tete = nouveauSommet;
        return;
    }
    // Recherche de l'emplacement où insérer le nouveau sommet dans la liste triée par ordre croissant d'indices
    sommet *precedent = g->tete;
    while (precedent->suivant != NULL && id > precedent->suivant->indice) {
        precedent = precedent->suivant;
    }
    // Insère le nouveau sommet après 'precedent'
    nouveauSommet->suivant = precedent->suivant;
    precedent->suivant = nouveauSommet;
}

// Fonction pour rechercher un sommet dans le graphe par son identifiant
sommet *rechercherSommet(graphe *g, int id) {
    sommet *buff = g->tete;
    while (buff != NULL) {
        if (buff->indice == id)
        {
            return buff;
        }
        buff = buff->suivant;
    }
    return NULL;
}

// Fonction pour ajouter une arête entre deux sommets dans le graphe
void ajouterArete(graphe *g, int id1, int id2)
{
    if (id1 == id2)
    {
        printf("Ajout de l'arete impossible. Les deux indices sont les memes.\n");
        return;
    }

    // indice croissant
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
            voisin *nouveauVoisin2 = (voisin *) malloc(sizeof(voisin));

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
        printf("Un des indices correspond a un sommet qui n'a pas encore ete ajoute .\n");
    }
}

// Fonction pour construire un graphe avec N sommets et leurs arêtes
graphe *construireGraphe(int N) {
    graphe *G = creeGraphe();
    for (int i = 0; i < N; i++) {
        int input;
        printf("Veuillez entrer le numero du sommet %d a ajouter\n", (i + 1));
        scanf("%d", &input);
        while (input < 0) {
            printf("Le numero du sommet doit etre positif. Veuillez reessayer :\n");
            scanf("%d", &input);
        }
        creerSommet(G, input );
    }
    int input2 = 0;
    printf("Souhaitez-vous ajouter des aretes ? (1 pour oui, 0 pour non)\n");
    scanf("%d", &input2);
    while (input2 != 0) {
        int som1, som2;
        printf("Veuillez entrer le numero du premier sommet pour lequel ajouter l'arete :\n");
        scanf("%d", &som1);
        printf("Veuillez entrer le numero du deuxieme sommet pour lequel ajouter l'arete :\n");
        scanf("%d", &som2);
        ajouterArete(G, som1, som2);
        printf("Souhaitez-vous encore ajouter des aretes ? (1 pour oui, 0 pour non)\n");
        scanf("%d", &input2);
    }
    return G;
}

// Fonction pour rechercher le degré maximum dans le graphe
int rechercherDegre(graphe *g) {
    sommet *buff = g->tete;
    int deg = 0;
    while (buff != NULL) {
        int degSommet = rechercherDegreSommet(buff);
        if (degSommet > deg) {
            deg = degSommet;
        }
        buff = buff->suivant;
    }
    return deg;
}

// Fonction pour rechercher si une arête existe entre deux sommets dans le graphe
int rechercherArrete(graphe *g, int id1, int id2) {
    sommet *s1 = rechercherSommet(g, id1);
    sommet *s2 = rechercherSommet(g, id2);
    if (s1 == NULL || s2 == NULL)
        return 0;
    voisin *v1 = s1->voisins;
    while (v1 != NULL) {
        if (v1->indice == id2)
            return 1;
        v1 = v1->voisin_suivant;
    }
    return 0;
}

// Fonction pour rechercher le degré d'un sommet dans le graphe
int rechercherDegreSommet(sommet *s) {
    int deg = 0;
    voisin *buff = s->voisins;
    while (buff != NULL) {
        buff = buff->voisin_suivant;
        deg++;
    }
    return deg;
}

// Fonction pour supprimer un sommet du graphe
void supprimerSommet(graphe *g, int id) {
    printf("Suppression d'un sommet: %d\n", id); 
    
    
    if (g->tete == NULL) {
        printf("Le graphe est vide.\n");
        return;
    }
    sommet *current = g->tete;
    sommet *previous = NULL;
    while (current != NULL && current->indice != id) {
        previous = current;
        current = current->suivant;
    }
    if (current == NULL) {
        printf("Le sommet que vous essayez de supprimer n'existe pas.\n");
        return;
    }
    if (previous == NULL) {
        g->tete = current->suivant;
    } else {
        previous->suivant = current->suivant;
    }
    sommet *s = g->tete;
    while (s != NULL) {
        supprimerVoisin(s, id);
        s = s->suivant;
    }
    free(current);
    printf("Sommet %d supprime.\n", id);

}

// Fonction pour supprimer un voisin d'un sommet dans le graphe
void supprimerVoisin(sommet *s, int id) {
    if (s->voisins == NULL)
        return;
    voisin *current = s->voisins;
    voisin *previous = NULL;
    while (current != NULL && current->indice != id) {
        previous = current;
        current = current->voisin_suivant;
    }
    if (current == NULL)
        return;
    if (previous == NULL) {
        s->voisins = current->voisin_suivant;
    } else {
        previous->voisin_suivant = current->voisin_suivant;
    }
    free(current);
}

// Fonction pour afficher la liste des voisins d'un sommet
void printListeVoisins(voisin *tete) {
    voisin *actuel = tete;
    while (actuel != NULL) {
        printf("Voisin avec l'indice: %d\n", actuel->indice);
        actuel = actuel->voisin_suivant;
    }
}

// Fonction pour afficher le graphe avec tous ses sommets et arêtes
void printGraphe(graphe *g) {
    if (g == NULL) {
        printf("Le graphe est vide.\n");
        return;
    }
    sommet *sommetActuel = g->tete;
    while (sommetActuel != NULL) {
        printf("Sommet avec l'indice: %d\n", sommetActuel->indice);
        printf("Voisins de ce sommet:\n");
        printListeVoisins(sommetActuel->voisins);
        sommetActuel = sommetActuel->suivant;
        printf("\n");
    }
}

// Fonction pour fusionner deux sommets du graphe sous un nouvel identifiant
void fusionnerSommet(graphe *g, int idSommet1, int idSommet2) {
    if (idSommet1 == idSommet2) {
        printf("Les deux sommets sont identiques.\n");
        return;
    }
    int newId = idSommet1 < idSommet2 ? idSommet1 : idSommet2;
    int oldId = idSommet1 > idSommet2 ? idSommet1 : idSommet2;
    sommet *newSommet = rechercherSommet(g, newId);
    sommet *oldSommet = rechercherSommet(g, oldId);
    if (newSommet == NULL || oldSommet == NULL) {
        printf("L'un des sommets specifies n'existe pas.\n");
        return;
    }
    voisin *v = oldSommet->voisins;
    while (v != NULL) {
        if (rechercherArrete(g, newId, v->indice) == 0) {
            ajouterArete(g, newId, v->indice );
        }
        v = v->voisin_suivant;
    }
    supprimerSommet(g, oldId);
    printf("Les sommets %d et %d ont ete fusionnes sous l'identifiant %d.\n", idSommet1, idSommet2, newId);
}

int SommetContientBoucle(graphe *g, int Sommet, int *visites, int parent) {

    visites[Sommet] = 1;
    sommet *s = rechercherSommet(g, Sommet);
    voisin *voisins = s->voisins;
    while (voisins != NULL) {
        if (!visites[voisins->indice]) {
            if (SommetContientBoucle(g, voisins->indice, visites, Sommet))
            {
                return 1;
            }

        } else if ((voisins->indice != parent) && (parent != -1)) {
            return 1;
        }
        voisins = voisins->voisin_suivant;
    }
    return 0;
}

// Fonction pour vérifier si le graphe contient une boucle en appelant la fonction pour chaque sommet
int contientBoucle(graphe *g) {
    int nbSommets = 0;
    sommet *s = g->tete;
    while (s != NULL) {
        nbSommets++;
        s = s->suivant;
    }
    int *tab = (int *) malloc(nbSommets * sizeof(int));
    sommet *curr = g->tete;
    int j=0;
    while (curr != NULL) {
        tab[j] = curr->indice;
        j++;
        curr = curr->suivant;;
    }

    int *visites = (int *)malloc(nbSommets * sizeof(int));
    for (int i = 0; i < nbSommets; i++) {
        visites[i] = 0;
    }
    //créer un tab d'ids de sommets
    for (int i = 0; i < nbSommets; i++) {
        if (visites[i] == 0) {
            // DFS à partir de ce sommet pour détecter les boucles
            if (SommetContientBoucle(g, tab[i], visites, -1)) { // tab[i]
                free(visites);
                return 1;
            }
        }
    }

    free(visites);
    return 0;
}

// Fonction pour libérer la mémoire allouée pour le graphe et ses sommets
void libererMemoire(graphe *g) {
    sommet *s = g->tete;
    while (s != NULL) {
        voisin *v = s->voisins;
        while (v != NULL) {
            voisin *temp1 = v;
            v = v->voisin_suivant;
            free(temp1);
        }
        sommet *temp2 = s;
        s = s->suivant;
        free(temp2);
    }
    free(g);
}
