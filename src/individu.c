#include "individu.h"

Individu *initialisationIndividu(){
	Individu *indiv = NULL;
	indiv = malloc(sizeof(*indiv));
	indiv->prenom = NULL;
	indiv->pere = NULL;
	indiv->mere = NULL;
	return indiv;
}

Individu *copieIndividu(Individu *ind){
	Individu *copie = initialisationIndividu();
	copie->prenom = malloc(sizeof(char)*strlen(ind->prenom));
	strcpy(copie->prenom,ind->prenom);
	copie->sexe = ind->sexe;
	copie->pere = ind->pere;
	copie->mere = ind->mere;
	return copie;
}

Individu *copieIndividu(Individu *ind){
    Individu *copie = ind;
    return copie;
}

void afficherIndividu(Individu *ind){
	if(ind == NULL){
		printf("NULL\n");
	} else if(ind->prenom != NULL){
		printf("%s:%c,",ind->prenom,ind->sexe);
		if(ind->pere == NULL){
			printf(",");
		} else {
			printf("%s,",ind->pere->prenom);
		}
		if(ind->mere == NULL){
			printf("\n");
		} else {
			printf("%s\n",ind->mere->prenom);
		}
	}
}
