#ifndef H_MAIN_H
#define H_MAIN_H

#include "listeCh.h"

//Tableau de tout les individus
Individu **toutLesIndividus(List *l, int *taille);
void MAJToutLesIndividus(List *l, Individu ***tab, int *taille);

//Tableau de tout les individus
Individu toutLesIndividus(List *l, int *taille);
void MAJToutLesIndividus(List *l, Individu *tab, int *taille);

//Modification du prenom d'un individu
void modificationPrenom(char *prenom, char *new_prenom, Individu **l, int taille);

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

//Interface utilisateur
char **commande(char *cmd, int *new_nb_arg);
void interface(List *indiv, Individu **listIndiv, int taille);
#endif
