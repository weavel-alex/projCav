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

#endif
