#ifndef TP4_H
#define TP4_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct sommet
{
    int indice;
    struct sommet *suivant;
    struct voisin *voisins;
} sommet;

typedef struct voisin
{
    int indice;
    struct voisin *voisin_suivant;
} voisin;

typedef struct graphe
{

    struct sommet *tete;
} graphe;

graphe *creeGraphe();

void creerSommet(graphe *g, int id);

sommet *rechercherSommet(graphe *g, int id);

void ajouterArete(graphe *g, int id1, int id2);

graphe *construireGraphe(int N);

int rechercherDegre(graphe *g);



/**
 * Vérifie l'existence d'une arête entre deux sommets dans un graphe.
 *
 * Cette fonction parcourt les arêtes du graphe pour déterminer si une arête
 * spécifique entre les sommets `id1` et `id2` existe déjà. Elle est utilisée
 * pour éviter l'ajout de doublons d'arêtes dans le graphe.
 *
 * @param g Un pointeur vers le graphe dans lequel rechercher l'arête.
 * @param id1 L'identifiant du premier sommet de l'arête.
 * @param id2 L'identifiant du deuxième sommet de l'arête.
 *
 * @return int Retourne 1 si l'arête existe déjà entre les sommets `id1` et `id2`.
 *             Retourne 0 si l'arête n'existe pas.
 */
int rechercherArrete(graphe *g, int id1, int id2);

void supprimerSommet(graphe *g, int id);

void supprimerVoisin(sommet *s, int id);

int rechercherDegreSommet(sommet *s);

void printListeVoisins(voisin *tete);

void printGraphe(graphe *g);

#endif // TP4_H
