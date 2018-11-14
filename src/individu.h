#ifndef H_INDIVIDU_H
#define H_INDIVIDU_H

#include "fctSimple.h"

struct _Individu {
	char *prenom;
	char sexe;
	struct _Individu *pere;
	struct _Individu *mere;
};
typedef struct _Individu Individu;

Individu *initialisationIndividu();
Individu *copieIndividu(Individu *ind);
void afficherIndividu(Individu *ind);

//Vérification
int existe(Individu **l, int taille, char *prenom);

//Modification du prenom d'un individu
void modificationPrenom(char *prenom, char *new_prenom, Individu **l, int taille);

#endif
