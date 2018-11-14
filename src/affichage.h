#ifndef H_AFFICHAGE_H
#define H_AFFICHAGE_H

#include "listeCh.h"

//Affichage
void view(List *l, Individu **tab, int taille);
void info(Individu **l, int taille, char *prenom);
void pere(Individu **l, int taille,char *prenom);
void mere(Individu **l, int taille,char *prenom);
void parents(Individu **l, int taille,char *prenom);
void gd_peres(Individu **l, int taille,char *prenom);
void gd_meres(Individu **l, int taille, char *prenom);
void gd_parents(Individu **l, int taille, char *prenom);
void ascendants(Individu **l, int taille,char *prenom);
void enfants(Individu **l, int taille,char *prenom);
void petits_enfant(Individu **l, int taille,char *prenom);
void descendants(Individu **l, int taille,char *prenom);
void partenaires(Individu **l, int taille,char *prenom);
void freres(Individu **l, int taille,char *prenom);
void soeurs(Individu **l, int taille,char *prenom);
void demi_freres(Individu **l, int taille,char *prenom);
void demi_soeurs(Individu **l, int taille,char *prenom);
void oncles(Individu **l, int taille,char *prenom);
void tantes(Individu **l, int taille,char *prenom);
void cousins(Individu **l, int taille,char *prenom);


#endif
