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
	free((*l));
	(*l) = newList;
}
