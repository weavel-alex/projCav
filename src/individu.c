#include "individu.h"

Individu *initialisationIndividu(){
	/**Initialise un individu a NULL*/
	Individu *indiv = NULL;
	indiv = malloc(sizeof(*indiv));
	indiv->prenom = NULL;
	indiv->pere = NULL;
	indiv->mere = NULL;
	return indiv;
}


Individu *copieIndividu(Individu *ind){
	/**Fait une copie de l'individu*/
    Individu *copie = ind;
    return copie;
}

void afficherIndividu(Individu *ind){
	/**Affiche un individu*/
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

int existe(Individu **l, int taille, char *prenom){
	/**Verifie si l'individu existe*/
	for(int i=0;i<taille;i++){
		if(mystrcmp(l[i]->prenom,prenom)==0){
			return 1;
		}
	}
	return 0;
}

void modificationPrenom(char *prenom, char *new_prenom, Individu **l, int taille){
	/**Modifie le prenom d'un individu*/
    for(int i=0;i<taille;i++){
        if(mystrcmp(l[i]->prenom,prenom)==0){
            l[i]->prenom = realloc(l[i]->prenom,sizeof(char)*strlen(new_prenom));
            strcpy(l[i]->prenom,new_prenom);
        }
    }
}
