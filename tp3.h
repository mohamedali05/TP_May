#ifndef TP3_H
#define TP3_H

#include <stdio.h>
#include <stdlib.h>


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

/** 
* @param aff 1 pour l'affichage 0 pour pas d'affichage
*/
void creerSommet(graphe *g, int id , int aff);

sommet *rechercherSommet(graphe *g, int id);

/** 
* @param aff 1 pour l'affichage 0 pour pas d'affichage
*/
void ajouterArete(graphe *g, int id1, int  , int aff);

graphe *construireGraphe(int N);

int rechercherDegre(graphe *g);



/**
 * Verifie l'existence d'une arete entre deux sommets dans un graphe.
 *
 * Cette fonction parcourt les aretes du graphe pour determiner si une arete
 * specifique entre les sommets `id1` et `id2` existe deja. Elle est utilisee
 * pour eviter l'ajout de doublons d'aretes dans le graphe.
 *
 * @param g Un pointeur vers le graphe dans lequel rechercher l'arete.
 * @param id1 L'identifiant du premier sommet de l'arete.
 * @param id2 L'identifiant du deuxieme sommet de l'arete.
 *
 * @return int Retourne 1 si l'arete existe deja entre les sommets `id1` et `id2`.
 *             Retourne 0 si l'arete n'existe pas.
 */
int rechercherArrete(graphe *g, int id1, int id2);


/** 
* @param aff 1 pour l'affichage 0 pour pas d'affichage
*/
void supprimerSommet(graphe *g, int id , int aff);

void supprimerVoisin(sommet *s, int id);

int rechercherDegreSommet(sommet *s);

void printListeVoisins(voisin *tete);

void printGraphe(graphe *g);

void libererMemoire(graphe *g);

/**
 * Vérifie si un graphe contient une boucle.
 *
 * Cette fonction recherche les boucles dans un graphe en supprimant récursivement les sommets qui n'ont qu'un voisin.
 * Une boucle est une séquence de sommets et d'arêtes où le premier et le dernier sommet sont identiques.
 * Cette fonction ne fonctionne pas dans le cas où une arête boucle sur le même sommet (par exemple, une arête partant et revenant au même sommet).
 *
 * @param g Le graphe à analyser.
 * @return 1 si le graphe contient une boucle, 0 sinon.
 */
int contientBoucle(graphe g);

void fusionnerSommet(graphe *g, int idSommet1, int idSommet2);

#endif // TP3_H
