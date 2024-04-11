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

void supprimerSommet(graphe *g, int id);

void supprimerVoisin(sommet *s, int id);

int rechercherDegreSommet(sommet *s);

void printListeVoisins(voisin *tete);

void printGraphe(graphe *g);

#endif // TP4_H
