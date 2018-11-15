#ifndef H_MAIN_H
#define H_MAIN_H

#include "affichage.h"

//Tableau de tout les individus
Individu **toutLesIndividus(List *l, int *taille);
void MAJToutLesIndividus(List *l, Individu ***tab, int *taille);

//Nouvel individu dans la liste
void new(List *l, char *prenom, char sexe, char *prenom_pere, char *prenom_mere, Individu **tab, int nbInd);

//Utilisation fichier
void save(char *nom_fichier,List *l, Individu **tab, int taille);
void load(char *nom_fichier, List *l);
	
//Interface utilisateur
char **commande(char *cmd, int *new_nb_arg);
void interface(List *indiv, Individu **listIndiv, int taille);

int main(void);
#endif
