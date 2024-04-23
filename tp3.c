#include <stdio.h>
#include <stdlib.h>
#include "tp4.h"

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
void creerSommet(graphe *g, int id ,int aff) {
    // Vérifie si le sommet existe déjà dans le graphe
    if (rechercherSommet(g, id) != NULL) {
        if(aff)
            printf("Le sommet que vous essayez d'ajouter existe deja\n");
        return;
    }
    // Vérifie si l'identifiant du sommet est positif
    if (id < 0) {
        if (aff)
            printf("Le sommet que vous essayez d'ajouter doit etre strictement positif\n");
        return;
    }
    // Alloue de la mémoire pour le nouveau sommet
    sommet *nouveauSommet = (sommet *)malloc(sizeof(sommet));
    if (nouveauSommet == NULL) {
        if(aff)
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
        if (buff->indice == id) {
            return buff;
        }
        buff = buff->suivant;
    }
    return NULL;
}

// Fonction pour ajouter une arête entre deux sommets dans le graphe
void ajouterArete(graphe *g, int id1, int id2 , int aff)
{
    // indice croissant
    sommet *s1 = rechercherSommet(g, id1);
    sommet *s2 = rechercherSommet(g, id2);

    if (s1 != NULL && s2 != NULL)
    {
        if (rechercherArrete(g, id1, id2) == 1)
        {
            if (aff)
                printf("L'arrête que vous souhaitez ajouter existe déjà.\n");
            return;
        }

        // Ajout du voisin pour s1 de manière ordonnée
        voisin *nouveauVoisin1 = (voisin *)malloc(sizeof(voisin));
        if (nouveauVoisin1 == NULL)
        {
            if(aff)
                printf("Erreur: Impossible d'allouer de la mémoire pour le nouveau voisin\n");
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
        if (aff)
            printf("Ajout de l'arête réussi entre %d et %d.\n", id1, id2);
    }
    else
    {
        if(aff)
            printf("Un des indices correspond a un sommet qui n'a pas encore ete ajouté .\n");
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
        creerSommet(G, input , 1);
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
        ajouterArete(G, som1, som2 , 1);
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
void supprimerSommet(graphe *g, int id , int aff) {
    if (aff){
        printf("Suppression d'un sommet: %d\n", id); 
    }
    
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
        if (aff){
            printf("Le sommet que vous essayez de supprimer n'existe pas.\n");
        }
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
    if (aff){
        printf("Sommet %d supprime.\n", id);
    }

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
            ajouterArete(g, newId, v->indice , 1);
        }
        v = v->voisin_suivant;
    }
    supprimerSommet(g, oldId , 1);
    printf("Les sommets %d et %d ont ete fusionnes sous l'identifiant %d.\n", idSommet1, idSommet2, newId);
}

// Fonction pour vérifier si le graphe contient une boucle
int contientBoucle(graphe g) {
    // Création d'une copie du graphe pour les manipulations
    graphe* nouveau_graphe = creeGraphe();
    // Copie de tous les sommets du graphe d'origine vers la nouvelle copie
    sommet* sommet_a_dupli = g.tete;
    while (sommet_a_dupli != NULL) {
        creerSommet(nouveau_graphe, sommet_a_dupli->indice , 0);
        sommet_a_dupli = sommet_a_dupli->suivant;
    }
    // Copie de toutes les arêtes du graphe d'origine vers la nouvelle copie
    sommet_a_dupli = g.tete;
    while (sommet_a_dupli != NULL) {
        voisin* voisin_a_dupli = sommet_a_dupli->voisins;
        while (voisin_a_dupli != NULL) {
            ajouterArete(nouveau_graphe, sommet_a_dupli->indice, voisin_a_dupli->indice , 0);
            voisin_a_dupli = voisin_a_dupli->voisin_suivant;
        }
        sommet_a_dupli = sommet_a_dupli->suivant;
    }
    // Recherche de boucles dans la nouvelle copie du graphe
    
    sommet* sommet_test = nouveau_graphe->tete;
    while (sommet_test != NULL) {
        voisin* voisin_test = sommet_test->voisins;
        int compteur_voisin = 0;
        while (voisin_test != NULL) {
            compteur_voisin++;
            voisin_test = voisin_test->voisin_suivant;
        }
        // Supprime le sommet s'il a un voisin ou 0 voisins
        if (compteur_voisin  < 2 ) {
            supprimerSommet(nouveau_graphe, sommet_test->indice , 0);
            sommet_test = nouveau_graphe->tete; // Retourne au début pour vérifier si un autre sommet doit être supprimé
        } else {
            sommet_test = sommet_test->suivant; // Passe au sommet suivant
        }
    }
    // Vérifie si le graphe contient encore des sommets
    sommet_test = nouveau_graphe->tete ;
    if (sommet_test != NULL){
        libererMemoire(nouveau_graphe) ; 
        return 1; // Le graphe contient une boucle
    }else{
         return 0; // Le graphe ne contient pas de boucle
    }
       
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
