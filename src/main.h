#ifndef H_MAIN_H
#define H_MAIN_H

#include "listeCh.h"

//Tableau de tout les individus
Individu **toutLesIndividus(List *l, int *taille);
void MAJToutLesIndividus(List *l, Individu ***tab, int *taille);

//Vérification
int existe(Individu **l, int taille, char *prenom);

//Nouvel individu dans la liste
void new(List *l, char *prenom, char sexe, char *prenom_pere, char *prenom_mere, Individu **tab, int nbInd);

//Utilisation fichier
void save(char *nom_fichier,List *l);
void load(char *nom_fichier, List *l);
	
//Affichage
void view(List *l);
void info(Individu **l, int taille, char *prenom);
void pere(Individu **l, int taille,char *prenom);
void mere(Individu **l, int taille,char *prenom);
void parents(Individu **l, int taille,char *prenom);
void gd_peres(Individu **l, int taille,char *prenom);
void gd_meres(Individu **l, int taille, char *prenom);
void gd_parents(Individu **l, int taille, char *prenom);
void ascendants(char *prenom);
void enfants(char *prenom);
void petits_enfant(char *prenom);
void descendants(char *prenom);
void partenaires(char *prenom);
void freres(char *prenom);
void soeurs(char *prenom);
void demi_freres(char *prenom);
void demi_soeurs(char *prenom);
void oncles(char *prenom);
void tantes(char *prenom);
void cousins(char *prenom);

//Interface utilisateur
char **commande(char *cmd, int *new_nb_arg);
void interface(List *indiv, Individu **listIndiv, int taille);
#endif
