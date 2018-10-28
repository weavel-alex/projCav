#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct _Individu {
	char *prenom;
	char sexe;
	struct _Individu *pere;
	struct _Individu *mere;
};
typedef struct _Individu Individu;

int mystrcmp (char *c1, char *c2){
	/**compare deux chaines de caracteres en ignorant la casse */
	int t1 = strlen(c1);
	int t2 = strlen(c2);
	
	if (t1 != t2){
		return 0;
	}
	
	for (int i=0;i<t1;i++){
		if (c1[i] != c2[i]){
			if(c1[i]-('A'-'a')!=c2[i] && c1[i] != c2[i]-('A'-'a')){
				return 0;
			}
		}
	}
	return 1;
}

////////////////////////////////////////////////////////////////////////
//  				COMMANDES GESTION ARBRE							  //
////////////////////////////////////////////////////////////////////////

void load (char *nom_fichier){
	/** charge en memoire l'arbre stoqué dans le fichier 'nom_fichier' */
}

void save (char *nom_fichier){
	/** sauvegarde l'arbre en memoire dans le fichier 'nom_fichier' */
}

void view (void){
	/** affiche l'arbre en memoire, meme format que la sauvegarde */
}

void new (char *prenom, char sexe, char *prenom_pere, char *prenom_mere){
	/** ajouter un individu dans l'arbre */
}




////////////////////////////////////////////////////////////////////////
//  		COMMANDES D'INFO ET RECHERCHES DANS L'ARBRE				  //
////////////////////////////////////////////////////////////////////////

void info(char *prenom){
	/** affiche prenom sexe pere mere de l'individu */
}

void pere(char *prenom){
	/** donne le nom du pere de l'Individu */
} 

void mere(char *prenom){
	/** donne le nom de la mere de l'Individu prenom */
} 

void parents (char *prenom){
	/** donne les noms des parents de l'Individu */
}

////////////////////


void gd_peres(char *prenom){
	/** donne les nom des grand-peres de l'Individu */
} 

void gd_meres(char *prenom){
	/** donne les noms des grand-meres de l'Individu */
} 

void gd_parents (char *prenom){
	/** donne les noms des grans-parents de l'Individu */
}


void ascendants (char *prenom){
	/**donne les noms de tout les ascendant de l'individu 
	 * (parents, gd-parents, arriere gd-parents etc) */
}

////////////////////


void enfants (char *prenom){
	/** donne les noms des enfants de l'individu */
}

void petits_enfant (char *prenom){
	/** donne les noms des petits enfants de l'individu */
}

void descendants (char *prenom){
	/** done les noms de tout les descendant de l'individu */
}

////////////////////

void partenaires (char *prenom){
	/**donne les noms de tout les partenaires de l'individu 
	 * (-> partenaires si enfant en commun) */
}

////////////////////

void freres (char *prenom){
	/** donne les noms de tout les freres de l'individu */
}

void soeurs (char *prenom){
	/** donne les noms de toutes les soeurs de l'individu */
}

void demi_freres (char *prenom){
	/** donne les noms de tout les demi-freres de l'individu */
}

void demi_soeurs (char *prenom){
	/** donne les noms de toutes les demi-soeurs de l'individu */
}

void oncles (char *prenom){
	/** donne les noms de tout les oncles de l'individu */
}

void tantes (char *prenom){
	/** donne les noms de toutes les tantes de l'individu */
}

void cousins (char *prenom){
	/** donne les nom des tout les cousins de l'individu */
}

////////////////////////////////////////////////////////////////////////
//  					GESTION DES COMMANDES						  //
////////////////////////////////////////////////////////////////////////

void interface (){
	quit = 0;
	while(!quit){
		char *commande;
		char *nom;
		printf(">>");
		scanf("%s",commande);
		
		switch commande{
			////
		}
	}
}


int main(void){
	printf("%d\n",mystrcmp(c1,c2));
	return 0;
}
