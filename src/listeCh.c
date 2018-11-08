#include "listeCh.h"

List *nouvelleListe(){
	List *l = NULL;
	l = malloc(sizeof(*l));
	l->premier = NULL;
	return l;
}

void viderListe(List **l){
	/**Vide la liste et libere la memoire*/
	List *newList = nouvelleListe();
	(*l) = newList;
	/*//Recupere tout les elements
	int taille_max = 20;
	int i = 0;
	Individu **tab = malloc(sizeof(*tab)*taille_max);
	ListNode *actuel = l->premier;
	//Recupere les individus dans la liste chainee
	while(actuel != NULL){
		tab[i] = malloc(sizeof(Individu));
		tab[i] = actuel->individu;
		i++;
		if(taille_max == i){
			taille_max *= 2;
			*tab = realloc(*tab,sizeof(*tab)*taille_max);
		}
		actuel = actuel->next;
	}
	int j,k,estDoublon=0;
	for(j=0;j<i;j++){
		if(tab[j]->pere != NULL){
			//Verif que l'individu n'est pas deja dans le tableau
			for(k=0;k<i;k++){
				if(k!=j && mystrcmp(tab[k]->prenom,tab[j]->pere->prenom) == 0){
					estDoublon=1;
					break;
				}
			}
			//S'il ne l'est pas, on l'ajoute
			if(!estDoublon){
				tab[i] = malloc(sizeof(Individu));
				tab[i] = tab[j]->pere;
				i++;
				if(taille_max == i){
					taille_max *= 2;
					*tab = realloc(*tab,sizeof(*tab)*taille_max);
				}
			} else {
				estDoublon = 0;
			}
		}
		if(tab[j]->mere != NULL){
			//Verif que l'individu n'est pas deja dans le tableau
			for(k=0;k<i;k++){
				if(k!=j && mystrcmp(tab[k]->prenom,tab[j]->mere->prenom) == 0){
					estDoublon=1;
					break;
				}
			}
			//S'il ne l'est pas, on l'ajoute
			if(!estDoublon){
				tab[i] = malloc(sizeof(Individu));
				tab[i] = tab[j]->mere;
				i++;
				if(taille_max == i){
					taille_max *= 2;
					*tab = realloc(*tab,sizeof(*tab)*taille_max);
				}
			} else {
				estDoublon = 0;
			}
		}
	}
	*tab = realloc(*tab,sizeof(*tab)*i);
	for(j=i-1;j>0;j--){
		free(tab[j]);
	}
	l->premier=NULL;
	l=nouvelleListe();*/
}
