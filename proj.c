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

typedef struct S_ListNode{
	Individu *individu;
	struct S_ListNode *next;
} ListNode;

typedef struct{
	ListNode *premier;
} List;

int mystrcmp(char *s, char *ch){
	/**compare deux chaines de caracteres en ignorant la casse */
	int taille1 = strlen(s);
	int taille2 = strlen(ch);
	int taille = (taille1 > taille2 ? taille1 : taille2);
	int i;
	for(i = 0; i < taille; i++){
		if((s[i] >= 'A' && s[i] <= 'Z' ? s[i]-'A'+'a' : s[i]) > (ch[i] >= 'A' && ch[i] <= 'Z' ? ch[i]-'A'+'a' : ch[i])){
			return 1;
		} else if ((s[i] >= 'A' && s[i] <= 'Z' ? s[i]-'A'+'a' : s[i]) < (ch[i] >= 'A' && ch[i] <= 'Z' ? ch[i]-'A'+'a' : ch[i])){
			return -1;
		}
	}
	return 0;
}

////////////////////////////////////////////////////////////////////////
//  				COMMANDES GESTION ARBRE							  //
////////////////////////////////////////////////////////////////////////

Individu *initialisationIndividu(){
	Individu *indiv = NULL;
	indiv = malloc(sizeof(*indiv));
	indiv->prenom = NULL;
	indiv->pere = NULL;
	indiv->mere = NULL;
	return indiv;
}

List *nouvelleListe(){
	List *l = malloc(sizeof(*l));
	l->premier = NULL;
	return l;
}

void load (char *nom_fichier){
	/** charge en memoire l'arbre stocké dans le fichier 'nom_fichier' */
}

void save (char *nom_fichier){
	/** sauvegarde l'arbre en memoire dans le fichier 'nom_fichier' */
}

void afficherIndividu(Individu *ind){
	if(ind->prenom != NULL){
		printf("%s:%c,",ind->prenom,ind->sexe);
		if(ind->pere == NULL){
			printf(",\n");
		} else {
			printf("%s,%s\n",ind->pere->prenom,ind->mere->prenom);
		}
	}
}

Individu *copieIndividu(Individu *ind){
	Individu *copie = initialisationIndividu();
	copie->prenom = NULL;
	copie->prenom = malloc(sizeof(char)*strlen(ind->prenom));
	strcpy(copie->prenom,ind->prenom);
	copie->sexe = ind->sexe;
	copie->pere = ind->pere;
	copie->mere = ind->mere;
	return copie;
}

Individu **toutLesIndividus (List *l, int *taille){
	/** affiche l'arbre en memoire, meme format que la sauvegarde */
	int taille_max = 20;
	Individu **tab = malloc(sizeof(*tab)*taille_max);
	ListNode *actuel = l->premier;
	*taille = 0;
	//Recupere les individus dans la liste chainee
	while(actuel != NULL){
		//printf("%d:%s\n",i,actuel->individu->prenom);
		tab[(*taille)] = NULL;
		tab[(*taille)] = malloc(sizeof(Individu));
		tab[(*taille)] = copieIndividu(actuel->individu);
		(*taille)++;
		if(taille_max == (*taille)){
			taille_max *= 2;
			*tab = realloc(*tab,sizeof(*tab)*taille_max);
		}
		actuel = actuel->next;
	}
	int j,k,estDoublon=0;
	for(j=0;j<(*taille);j++){
		if(tab[j]->pere != NULL){
			//Verif que l'individu n'est pas deja dans le tableau
			for(k=0;k<(*taille);k++){
				if(k!=j && mystrcmp(tab[k]->prenom,tab[j]->pere->prenom) == 0){
					estDoublon=1;
					break;
				}
			}
			//S'il ne l'est pas, on l'ajoute
			if(!estDoublon){
				tab[(*taille)] = NULL;
				tab[(*taille)] = malloc(sizeof(Individu));
				tab[(*taille)] = copieIndividu(tab[j]->pere);
				(*taille)++;
				if(taille_max == (*taille)){
					taille_max *= 2;
					*tab = realloc(*tab,sizeof(*tab)*taille_max);
				}
			} else {
				estDoublon = 0;
			}
		}
		if(tab[j]->mere != NULL){
			//Verif que l'individu n'est pas deja dans le tableau
			for(k=0;k<(*taille);k++){
				if(k!=j && mystrcmp(tab[k]->prenom,tab[j]->mere->prenom) == 0){
					estDoublon=1;
					break;
				}
			}
			//S'il ne l'est pas, on l'ajoute
			if(!estDoublon){
				tab[(*taille)] = NULL;
				tab[(*taille)] = malloc(sizeof(Individu));
				tab[(*taille)] = copieIndividu(tab[j]->mere);
				(*taille)++;
				if(taille_max == (*taille)){
					taille_max *= 2;
					*tab = realloc(*tab,sizeof(*tab)*taille_max);
				}
			} else {
				estDoublon = 0;
			}
		}
	}
	return tab;
}

void view (List *l){
	int *taille = malloc(sizeof(int));
	Individu **tab = toutLesIndividus(l, taille);
	int j;
	for(j=0;j<(*taille);j++){
		afficherIndividu(tab[j]);
	}
}

void new (List *l, char *prenom, char sexe, char *prenom_pere, char *prenom_mere){
	/** ajouter un individu dans l'arbre */
	if(l->premier == NULL){
		ListNode *node = NULL;
		node = malloc(sizeof(*node));
		Individu *ind = initialisationIndividu();
		ind->prenom = NULL;
		ind->prenom = malloc(sizeof(char)*strlen(prenom));
		strcpy(ind->prenom,prenom);
		ind->sexe = sexe;
		node->individu = ind;
		
		l->premier = node;
	} else {
		//Ajout en fin de chaine si pas de parents
		if(prenom_pere == NULL){
			ListNode *actuel = l->premier;
			while(actuel->next != NULL){
				actuel = actuel->next;
			}
			ListNode *node = NULL;
			node = malloc(sizeof(*node));
			Individu *ind = initialisationIndividu();
			ind->prenom = NULL;
			ind->prenom = malloc(sizeof(char)*strlen(prenom));
			strcpy(ind->prenom,prenom);
			ind->sexe = sexe;
			node->individu = ind;
			
			actuel->next = node;
		} else {
			int estSeul = 0;
			Individu *papa = NULL;
			Individu *mama = NULL;
			ListNode *actuel = l->premier;
			ListNode *prec = actuel;
			while(actuel != NULL){
				if(mystrcmp(actuel->individu->prenom,prenom_pere) == 0){
					if(actuel->individu->sexe != 'm'){
						printf("Erreur de sexe pour le pere\n");
						exit(1);
					}
					papa = actuel->individu;
					if(prec == actuel){
						//Si on doit enlever le tete
						if(l->premier->next == NULL){
							//Pour ne pas perdre le liste chainee
							estSeul = 1;
						} else {
							//Si pls noeud on remplace la tete
							l->premier = l->premier->next;
							actuel = l->premier;
							prec = actuel;
						}
					} else {
						//On enleve normalement le noeud
						prec->next = actuel->next;
						actuel = prec;
					}
				}
				if(mystrcmp(actuel->individu->prenom,prenom_mere) == 0){
					if(actuel->individu->sexe != 'f'){
						printf("Erreur de sexe pour la mere\n");
						exit(1);
					}
					mama = actuel->individu;
					if(prec == actuel){
						if(l->premier->next == NULL){
							estSeul = 1;
						} else {
							l->premier = l->premier->next;
							actuel = l->premier;
							prec = actuel;
						}
					} else {
						prec->next = actuel->next;
						actuel = prec;
					}
				}
				prec = actuel;
				actuel = actuel->next;
			}
			//Si le parent rechercher n'est pas dans la liste chainée racine
			//On parcours les parents pour le trouver
			if(papa == NULL || mama == NULL){
				int *nbInd = malloc(sizeof(int));
				Individu **tab = toutLesIndividus(l,nbInd);
				int i;
				for(i=0;i<(*nbInd);i++){
					if(papa == NULL){
						if(mystrcmp(prenom_pere,tab[i]->prenom) == 0){
							papa = tab[i];
						}
					}
					if(mama == NULL){
						if(mystrcmp(prenom_mere,tab[i]->prenom) == 0){
							mama = tab[i];
						}
					}
				}
			}
			if(papa == NULL){
				printf("Aucun individu trouvé pour %s\n",prenom_pere);
			}
			if(mama == NULL){
				printf("Aucun individu trouvé pour %s\n",prenom_mere);
			}
			//On ajoute notre nouveau noeud a liste
			ListNode *node = NULL;
			node = malloc(sizeof(*node));
			Individu *ind = initialisationIndividu();
			ind->prenom = NULL;
			ind->prenom = malloc(sizeof(char)*strlen(prenom));
			strcpy(ind->prenom,prenom);
			ind->sexe = sexe;
			ind->pere = papa;
			
			ind->mere = mama;
			node->individu = ind;
			
			node->next = actuel;
			prec->next = node;
			
			if(estSeul){
				//On supprime le tete de la liste principal
				l->premier = l->premier->next;
				actuel = l->premier;
			}
		}
	}	
}




////////////////////////////////////////////////////////////////////////
//  		COMMANDES D'INFO ET RECHERCHES DANS L'ARBRE				  //
////////////////////////////////////////////////////////////////////////

void info(char *prenom){
	/** affiche prenom sexe pere mere de l'individu */
	return;
}

void pere(char *prenom){
	/** donne le nom du pere de l'Individu */
	return;
}

void mere(char *prenom){
	/** donne le nom de la mere de l'Individu prenom */
	return;
} 

void parents (char *prenom){
	/** donne les noms des parents de l'Individu */
	return;
}

////////////////////


void gd_peres(char *prenom){
	/** donne les nom des grand-peres de l'Individu */
	return;
}

void gd_meres(char *prenom){
	/** donne les noms des grand-meres de l'Individu */
	return;
} 

void gd_parents (char *prenom){
	/** donne les noms des grans-parents de l'Individu */
	return;
}


void ascendants (char *prenom){
	/**donne les noms de tout les ascendant de l'individu 
	 * (parents, gd-parents, arriere gd-parents etc) */
	 return;
}

////////////////////


void enfants (char *prenom){
	/** donne les noms des enfants de l'individu */
	return;
}

void petits_enfant (char *prenom){
	/** donne les noms des petits enfants de l'individu */
	return;
}

void descendants (char *prenom){
	/** done les noms de tout les descendant de l'individu */
	return;
}

////////////////////

void partenaires (char *prenom){
	/**donne les noms de tout les partenaires de l'individu 
	 * (-> partenaires si enfant en commun) */
	 return;
}

////////////////////

void freres (char *prenom){
	/** donne les noms de tout les freres de l'individu */
	return;
}

void soeurs (char *prenom){
	/** donne les noms de toutes les soeurs de l'individu */
	return;
}

void demi_freres (char *prenom){
	/** donne les noms de tout les demi-freres de l'individu */
	return;
}

void demi_soeurs (char *prenom){
	/** donne les noms de toutes les demi-soeurs de l'individu */
	return;
}

void oncles (char *prenom){
	/** donne les noms de tout les oncles de l'individu */
	return;
}

void tantes (char *prenom){
	/** donne les noms de toutes les tantes de l'individu */
	return;
}

void cousins (char *prenom){
	/** donne les nom des tout les cousins de l'individu */
	return;
}

////////////////////////////////////////////////////////////////////////
//  					GESTION DES COMMANDES						  //
////////////////////////////////////////////////////////////////////////

char **commande(char *cmd, int *new_nb_arg){
	/** Retourne un tableau de string avec en premier le nom de la fonction demande par l'utilisateur
		puis les arguments*/
	int i,nb_arg=0,j=0,taille_mot=10,taille_arg=5;
	
	char **fct = malloc(sizeof(char*)*taille_arg);
	for(i=0;i<taille_arg;i++){
		fct[i] = (char *)malloc(sizeof(char)*taille_mot);
	}
	for(i=0;i<strlen(cmd);i++){
		if(cmd[i] != ' '){
			if(cmd[i] == '(' || cmd[i] == ','){
				i++;
				fct[nb_arg][j] = '\0';
				if(j+1 < taille_mot){
					fct[nb_arg] = (char *)realloc(fct[nb_arg],sizeof(char)*j);
				}
				nb_arg++;j=0;
			}
			if(cmd[i] == ')'){
				fct[nb_arg][j] = '\0';
				if(j+1 < taille_mot){
					fct[nb_arg] = (char *)realloc(fct[nb_arg],sizeof(char)*j);
				}
				break;
			}
			fct[nb_arg][j] = cmd[i];
			j++;
			if(j+1 == taille_mot){
				taille_mot *= 2;
				fct[nb_arg] = (char *)realloc(fct[nb_arg],sizeof(char)*taille_mot);
			}
		}
	}
	if(nb_arg+1 < taille_arg){
		fct = realloc(fct,sizeof(char*)*(nb_arg+1));
		(*new_nb_arg) = nb_arg+1;
	}
	return fct;
}

void interface (List *indiv){
	int *nb_arg = malloc(sizeof(int));
	*nb_arg = 5;
	char *cmd_u = malloc(sizeof(char)*10);
	char **ma_cmd = malloc(sizeof(char*)*(*nb_arg));
	ma_cmd[0] = "NULL";
	while(mystrcmp(ma_cmd[0],"exit")!=0){
		scanf("%s",cmd_u);
		ma_cmd=commande(cmd_u,nb_arg);
		
		if(mystrcmp(ma_cmd[0], "view") == 0){
			view(indiv);
		} else if (mystrcmp(ma_cmd[0], "exit") == 0){
			printf("Fin de l'application\n");
		} else if((*nb_arg) <= 1){
			printf("Pas assez d'arguments\n");
		} else {
			if(mystrcmp(ma_cmd[0], "load") == 0){
				load(ma_cmd[1]);
			}
			else if(mystrcmp(ma_cmd[0], "save") == 0){
				save(ma_cmd[1]);
			}
			else if(mystrcmp(ma_cmd[0], "new" ) == 0){
				if((*nb_arg) == 5){
					new(indiv, ma_cmd[1],ma_cmd[2][0],ma_cmd[3],ma_cmd[4]);
				}
				if((*nb_arg) == 2){
					new(indiv, ma_cmd[1],ma_cmd[2][0],NULL,NULL);
				} else {
					printf("Commande non valide, probleme de parametre\n");
				}
			}
			else if(mystrcmp(ma_cmd[0], "info") == 0){
				info(ma_cmd[1]);
			}
			else if(mystrcmp(ma_cmd[0], "mere") == 0){
				mere(ma_cmd[1]);
			}
			else if(mystrcmp(ma_cmd[0], "pere") == 0){
				pere(ma_cmd[1]);
			}
			else if(mystrcmp(ma_cmd[0], "parents") == 0){
				parents(ma_cmd[1]);
			}
			else if(mystrcmp(ma_cmd[0], "gdmeres") == 0){
				gd_meres(ma_cmd[1]);
			}
			else if(mystrcmp(ma_cmd[0], "gdperes") == 0){
				gd_peres(ma_cmd[1]);
			}
			else if(mystrcmp(ma_cmd[0], "gdparents") == 0){
				gd_parents(ma_cmd[1]);
			}
			else if(mystrcmp(ma_cmd[0], "ascendants") == 0){
				ascendants(ma_cmd[1]);
			}
			else if(mystrcmp(ma_cmd[0], "enfants") == 0){
				enfants(ma_cmd[1]);
			}
			else if(mystrcmp(ma_cmd[0], "petitsenfants") == 0){
				petits_enfant(ma_cmd[1]);
			}
			else if(mystrcmp(ma_cmd[0], "descendants") == 0){
				descendants(ma_cmd[1]);
			}
			else if(mystrcmp(ma_cmd[0], "partenaires") == 0){
				partenaires(ma_cmd[1]);
			}
			else if(mystrcmp(ma_cmd[0], "freres") == 0){
				freres(ma_cmd[1]);
			}
			else if(mystrcmp(ma_cmd[0], "soeurs") == 0){
				soeurs(ma_cmd[1]);
			}
			else if(mystrcmp(ma_cmd[0], "demifreres") == 0){
				demi_freres(ma_cmd[1]);
			}
			else if(mystrcmp(ma_cmd[0], "demisoeurs") == 0){
				demi_soeurs(ma_cmd[1]);
			}
			else if(mystrcmp(ma_cmd[0], "oncles") == 0){
				oncles(ma_cmd[1]);
			}
			else if(mystrcmp(ma_cmd[0], "tantes") == 0){
				tantes(ma_cmd[1]);
			}
			else if(mystrcmp(ma_cmd[0], "cousins") == 0){
				cousins(ma_cmd[1]);
			}
			else{
				if(mystrcmp(ma_cmd[0], "exit") != 0)
					printf("Aucune option reconnue\n");
			}
		}
	}
}


int main(void){
	List *l = nouvelleListe();
	/*new(l,"A",'m',NULL,NULL);
	view(l);printf("\n");
	new(l,"B",'f',NULL,NULL);
	view(l);printf("\n");
	new(l,"C",'m',"A","B");
	view(l);printf("\n");
	new(l,"D",'f',"A","B");
	view(l);printf("\n");
	new(l,"E",'f',"C","D");
	view(l);printf("\n");
	*/
	
	new(l,"A",'m',NULL,NULL);
	//view(l);printf("\n");
	new(l,"B",'f',NULL,NULL);
	//view(l);printf("\n");
	new(l,"C",'m',"A","B");
	//view(l);printf("\n");
	new(l,"D",'f',NULL,NULL);
	//view(l);printf("\n");
	new(l,"E",'f',NULL,NULL);
	//view(l);printf("\n");
	new(l,"F",'m',"C","D");
	//view(l);printf("\n");
	new(l,"G",'m',"C","D");
	//view(l);printf("\n");
	new(l,"H",'m',"C","E");
	view(l);printf("\n");
	
	//interface(indiv);
	return 0;
}
