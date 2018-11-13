#include "main.h"

Individu **toutLesIndividus (List *l, int *taille){
	/** stocke l'arbre en memoire */
	int taille_max = 20;
	*taille = 0;
	Individu **tab = malloc(sizeof(*tab)*taille_max);
	ListNode *actuel = l->premier;
	//Recupere les individus dans la liste chainee
	while(actuel != NULL){
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

void MAJToutLesIndividus(List *l, Individu ***tab, int *taille){
	*(tab) = NULL;
	*(tab) = toutLesIndividus(l,taille);
}

void mofif(){
	//A FAIRE SI PAS LA FLEMME
}

int existe(Individu **l, int taille, char *prenom){
	for(int i=0;i<taille;i++){
		if(mystrcmp(l[i]->prenom,prenom)==0){
			return 1;
		}
	}
	return 0;
}

void new (List *l, char *prenom, char sexe, char *prenom_pere, char *prenom_mere, Individu **tab, int nbInd){
	/** ajouter un individu dans l'arbre */
	if(sexe != 'f' && sexe != 'm'){
		printf("new : Sexe ne correspond pas\n");
		return;
	}
	if(l->premier == NULL){
		ListNode *node = malloc(sizeof(*node));
		Individu *ind = initialisationIndividu();
		ind->prenom = malloc(sizeof(char)*strlen(prenom));
		strcpy(ind->prenom,prenom);
		ind->sexe = sexe;
		node->individu = ind;
		node->next = NULL;
		
		l->premier = node;
	} else {
		//Ajout en fin de chaine si pas de parents
		//Verifie que le pere car s'il n'a pas de pere il n'aura pas de mere
		if(prenom_pere == NULL && prenom_mere == NULL){
			ListNode *actuel = l->premier;
			while(actuel->next != NULL){
				actuel = actuel->next;
			}
			ListNode *node = malloc(sizeof(*node));
			Individu *ind = initialisationIndividu();
			ind->prenom = malloc(sizeof(char)*strlen(prenom));
			strcpy(ind->prenom,prenom);
			ind->sexe = sexe;
			node->individu = ind;
			node->next = NULL;
			
			actuel->next = node;
		} else {
			int erreur = 0;
			int estModifiee;
			int estSeul = 0;
			Individu *papa = NULL;
			Individu *mama = NULL;
			ListNode *actuel = l->premier;
			ListNode *prec = actuel;
			//Verif dans la liste chainée
			while(actuel != NULL){
				estModifiee = 0;
				if(mystrcmp(actuel->individu->prenom,prenom_pere) == 0){
					if(actuel->individu->sexe != 'm' && !erreur){
						printf("new : Erreur de sexe pour le pere\n");
						printf("new : Ajout annulé\n");
						erreur = 1;
					}
					if(!erreur){
						papa = actuel->individu;
						if(prec == actuel){
							//Si on doit enlever le tete
							if(l->premier->next == NULL){
								//Si un seul element dans la liste chainée, pour ne pas perdre le liste chainee
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
				}
				if(mystrcmp(actuel->individu->prenom,prenom_mere) == 0){
					if(actuel->individu->sexe != 'f' && !erreur){
						printf("new : Erreur de sexe pour la mere\n");
						printf("new : Ajout annulé\n");
						erreur = 1;
					}
					if(!erreur){
						mama = actuel->individu;
						if(prec == actuel){
							if(l->premier->next == NULL){
								estSeul = 1;
							} else {
								l->premier = l->premier->next;
								actuel = l->premier;
								prec = actuel;
								estModifiee = 1;
							}
						} else {
							prec->next = actuel->next;
							actuel = prec;
							estModifiee = 1;
						}
					}
				}
				if(!estModifiee){
					prec = actuel;
					actuel = actuel->next;
				}
			}
			if(erreur){
				printf("new : Erreur detecter pendant l'ajout\n");
				return;
			}
			//Si le parent rechercher n'est pas dans la liste chainée racine
			//On parcours les parents pour le trouver
			if(papa == NULL || mama == NULL){
				//int *nbInd = malloc(sizeof(int));
				//Individu **tab = toutLesIndividus(l,nbInd);
				int i;
				for(i=0;i<nbInd;i++){
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
				printf("new : Aucun individu trouvé pour %s\n",prenom_pere);
			}
			if(mama == NULL){
				printf("new : Aucun individu trouvé pour %s\n",prenom_mere);
			}
			//On ajoute notre nouveau noeud a liste
			ListNode *node = malloc(sizeof(*node));
			Individu *ind = initialisationIndividu();
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

void save (char *nom_fichier,List *l){
	/** sauvegarde l'arbre en memoire dans le fichier 'nom_fichier' */
	FILE* fichierD = fopen(nom_fichier,"a");
	if(fichierD != NULL){
		remove(nom_fichier);
	}
	FILE *fichier = ouvrirFichier(nom_fichier,"a");
	if(fichier != NULL){
		int *taille = malloc(sizeof(int));
		Individu **tab = toutLesIndividus(l, taille);
		int i;
		for(i=(*taille)-1;i>=0;i--){
			if(tab[i]->pere != NULL){
				fprintf(fichier,"%s:%c,%s,%s\n",tab[i]->prenom,tab[i]->sexe,tab[i]->pere->prenom,tab[i]->mere->prenom);
			} else {
				fprintf(fichier,"%s:%c,,\n",tab[i]->prenom,tab[i]->sexe);
			}
		}
		fermerFichier(fichier);
	}
}

void load (char *nom_fichier, List *l){
	/** charge en memoire l'arbre stocké dans le fichier 'nom_fichier' */
	int nbInd;
	Individu **tab = malloc(sizeof(*tab));
	tab = toutLesIndividus(l,&nbInd);
	
	FILE *fichier = ouvrirFichier(nom_fichier,"r");
	if(fichier != NULL){
		int c = 0, taille_mot = 20, ptr = 0, fin_mot = 0;
		char **indv = malloc(sizeof(char*)*4);
		int i;
		for(i=0;i<4;i++){
			indv[i] = (char *)malloc(sizeof(char)*taille_mot);
		}
		for(c = fgetc(fichier); !feof(fichier); c = fgetc(fichier)){
			//Creation du mot
			if(estLettre(c) || c == '-'){
				indv[ptr][fin_mot] = c;
				fin_mot++;
				if(fin_mot+1 == taille_mot){
					taille_mot *= 2;
					indv[ptr] = realloc(indv[ptr],(sizeof(char)*taille_mot));
				}
			} else {
				//Si un autre caractere
				if(fin_mot != 0){
					//Ecriture de la fin du mot
					indv[ptr][fin_mot] = '\0';
					if(fin_mot+1 != taille_mot){
						indv[ptr] = realloc(indv[ptr],(sizeof(char)*fin_mot));
						taille_mot = 20;
					}
				} else {
					//Si on a rien alors NULL pour les parents
					indv[ptr] = NULL;
				}				
				ptr++;fin_mot = 0;
				if(ptr == 4){
					//On cree l'individu
					new(l,indv[0],indv[1][0],indv[2],indv[3],tab,nbInd);
					tab = toutLesIndividus(l,&nbInd);
					ptr=0;taille_mot=20;
					//On realloc pour ne pas avoir de soucis de memoire apres
					for(i=0;i<4;i++){
						indv[i] = NULL;
						indv[i] = realloc(indv[i],(sizeof(char)*taille_mot));
					}
				}
			}
		}
		fermerFichier(fichier);
		for(i=0;i<4;i++){
			free(indv[i]);
		}
		free(indv);
	} else {
		printf("Le fichier %s n'existe pas.\n",nom_fichier);
	}
}

void view (List *l){
	int *taille = malloc(sizeof(int));
	Individu **tab = toutLesIndividus(l, taille);
	int i;
	for(i=0;i<(*taille);i++){
		afficherIndividu(tab[i]);
	}
}

void info(Individu **l, int taille, char *prenom){
	/** affiche prenom sexe pere mere de l'individu */
	int i;
	for(i=0;i<taille;i++){
		if(mystrcmp(l[i]->prenom,prenom)==0){
			afficherIndividu(l[i]);
			return;
		}
	}
	printf("Individu inconnu\n");
}

void pere(Individu **l, int taille,char *prenom){
	/** donne le nom du pere de l'Individu */
	int i;
	for(i=0;i<taille;i++){
		if(mystrcmp(l[i]->prenom,prenom)==0){
			if(l[i]->pere != NULL){
				printf("Pere : %s\n",l[i]->pere->prenom);
				return;
			}
		}
	}
	printf("Pere inconnu\n");
}

void mere(Individu **l, int taille,char *prenom){
	/** donne le nom de la mere de l'Individu prenom */
	int i;
	for(i=0;i<taille;i++){
		if(mystrcmp(l[i]->prenom,prenom)==0){
			if(l[i]->mere != NULL){
				printf("Mere : %s\n",l[i]->mere->prenom);
				return;
			}
		}
	}
	printf("Mere inconnu\n");
} 

void parents (Individu **l, int taille,char *prenom){
	/** donne les noms des parents de l'Individu */
	pere(l,taille,prenom);
	mere(l,taille,prenom);
}

void gd_peres(Individu **l, int taille,char *prenom){
	/** donne les nom des grand-peres de l'Individu */
	int i;
	for(i=0;i<taille;i++){
		if(mystrcmp(l[i]->prenom,prenom)==0){
			if(l[i]->pere != NULL){
				if(l[i]->pere->pere != NULL){
					printf("Gd Pere paternel : %s\n",l[i]->pere->pere->prenom);
					break;
				}
				else{
					printf("grand pere paternel inconnu\n");
				}
			}
			else{
				printf("pere inconnu\n");
			}
		}
	}
	for(i=0;i<taille;i++){
		if(mystrcmp(l[i]->prenom,prenom)==0){
			if(l[i]->mere != NULL){
				if(l[i]->mere->pere != NULL){
					printf("Gd Pere maternel : %s\n",l[i]->mere->pere->prenom);
					return;
				}
				else{
					printf("grand pere maternel inconnu\n");
				}
			}
			else{
				printf("mere inconnue\n");
			}
		}
	}
}

void gd_meres(Individu **l, int taille, char *prenom){
	/** donne les noms des grand-meres de l'Individu */
	int i;
	for(i=0;i<taille;i++){
		if(mystrcmp(l[i]->prenom,prenom)==0){
			if(l[i]->pere != NULL){
				if(l[i]->pere->mere != NULL){
					printf("Gd Mere paternelle : %s\n",l[i]->pere->mere->prenom);
					break;
				}
				else{
					printf("grand mere paternelle inconnu\n");
				}
			}
		}
	}
	for(i=0;i<taille;i++){
		if(mystrcmp(l[i]->prenom,prenom)==0){
			if(l[i]->mere != NULL){
				if(l[i]->mere->mere != NULL){
					printf("Gd Mere maternelle : %s\n",l[i]->mere->mere->prenom);
					return;
				}
				else{
					printf("grand mere maternelle inconnu\n");
				}
			}
		}
	}
} 

void gd_parents (Individu **l, int taille, char *prenom){
	/** donne les noms des grans-parents de l'Individu */
	gd_peres(l,taille,prenom);
	gd_meres(l,taille,prenom);
}

void ascendants (Individu **l, int taille,char *prenom){
	/**donne les noms de tout les ascendant de l'individu 
	 * (parents, gd-parents, arriere gd-parents etc) */
	 int i;
	 for(i=0;i<taille;i++){
		 if (mystrcmp(l[i]->prenom,prenom) == 0){
			 if (l[i]->pere != NULL){
				printf("%s \n",l[i]->pere->prenom);
				ascendants(l,taille,l[i]->pere->prenom);
			 }
			 if(l[i]->mere != NULL){
				 printf("%s \n",l[i]->mere->prenom);
				 ascendants(l,taille,l[i]->mere->prenom);
			 }
		 }
	 }
 }

void enfants (Individu **l, int taille,char *prenom){
	/** donne les noms des enfants de l'individu */
	int i;
	for(i=0;i<taille;i++){
		if (l[i]->pere != NULL && mystrcmp(l[i]->pere->prenom,prenom)==0){
			printf("%s \n",l[i]->prenom);
		}
		if (l[i]->mere != NULL && mystrcmp(l[i]->mere->prenom,prenom)==0){
			printf("%s \n",l[i]->prenom);
		}
	}
}

void petits_enfant (Individu **l, int taille,char *prenom){
	/** donne les noms des petits enfants de l'individu */
	int i,j;
	
	for(i=0;i<taille;i++){
		if (l[i]->pere != NULL){
			if(l[i]->pere->pere != NULL && mystrcmp(prenom,l[i]->pere->pere->prenom)==0){
				printf("%s \n",l[i]->prenom);
			}
			if(l[i]->pere->mere != NULL && mystrcmp(prenom,l[i]->pere->mere->prenom)==0){
				printf("%s \n",l[i]->prenom);
			}
		}
		if (l[i]->mere != NULL && mystrcmp(l[i]->mere->prenom,prenom)==0){
			if(l[i]->mere->pere != NULL && mystrcmp(prenom,l[i]->mere->pere->prenom)==0){
				printf("%s \n",l[i]->prenom);
			}
			if(l[i]->mere->mere != NULL && mystrcmp(prenom,l[i]->mere->mere->prenom)==0){
				printf("%s \n",l[i]->prenom);
			}
		}
	}
}

void descendants (Individu **l, int taille,char *prenom){
	/** done les noms de tout les descendant de l'individu */
	int i;
	for(i=0;i<taille;i++){
		if (l[i]->pere != NULL && mystrcmp(l[i]->pere->prenom,prenom)==0){
			printf("%s \n",l[i]->prenom);
			descendants(l,taille,l[i]->prenom);
		}
		if (l[i]->mere != NULL && mystrcmp(l[i]->mere->prenom,prenom)==0){
			printf("%s \n",l[i]->prenom);
			descendants(l,taille,l[i]->prenom);
		}
	}
}
		

void partenaires (Individu **l, int taille,char *prenom){
	/**donne les noms de tout les partenaires de l'individu 
	 * (-> partenaires si enfant en commun) */
	 int i;
	 char s;
	
	for(i=0;i<taille;i++){
		if (mystrcmp(l[i]->prenom,prenom)==0){
			s=l[i]->sexe;
		}
	}
	
	if (s == 'm'){
		for(i=0;i<taille;i++){
			if (l[i]->pere != NULL && mystrcmp(l[i]->pere->prenom,prenom)==0){
				if (l[i]->mere != NULL){
					printf("%s \n",l[i]->mere->prenom);
				}
				else{printf("une partenaire inconnue\n");}
			}
		}
	}
	
	if (s == 'f'){
		for(i=0;i<taille;i++){
			if (l[i]->mere != NULL && mystrcmp(l[i]->mere->prenom,prenom)==0){
				if (l[i]->pere != NULL){
					printf("%s \n",l[i]->pere->prenom);
				}
				else{printf("un partenaire inconnue\n");}
			}
		}
	}
}

void freres (Individu **l, int taille,char *prenom){
	/** donne les noms de tout les freres de l'individu */
	int i=0;
	Individu *cur;
	for(i=0;i<taille;i++){
		if (mystrcmp(prenom,l[i]->prenom)==0){
			cur=l[i];
		}
	}
	for(i=0;i<taille;i++){
		if (l[i]->sexe == 'm' && mystrcmp(l[i]->prenom,cur->prenom)!=0){
			if (cur->pere != NULL){
				if(l[i]->pere != NULL && mystrcmp(l[i]->pere->prenom,cur->pere->prenom)==0){
					if (cur->mere != NULL && l[i]->mere != NULL && mystrcmp(l[i]->mere->prenom,cur->mere->prenom)==0){
						printf("%s \n",l[i]->prenom);
					}
				}
			}	
		}
	}
}

void soeurs (Individu **l, int taille,char *prenom){
	/** donne les noms de toutes les soeurs de l'individu */
	int i=0;
	Individu *cur;
	for(i=0;i<taille;i++){
		if (mystrcmp(prenom,l[i]->prenom)==0){
			cur=l[i];
		}
	}
	for(i=0;i<taille;i++){
		if (l[i]->sexe == 'f' && mystrcmp(l[i]->prenom,cur->prenom)!=0){
			if (cur->pere != NULL){
				if(l[i]->pere != NULL && mystrcmp(l[i]->pere->prenom,cur->pere->prenom)==0){
					if (cur->mere != NULL && l[i]->mere != NULL && mystrcmp(l[i]->mere->prenom,cur->mere->prenom)==0){
						printf("%s \n",l[i]->prenom);
					}
				}
			}	
		}
	}
}

void demi_freres (Individu **l, int taille,char *prenom){
	/** donne les noms de tout les demi-freres de l'individu */
	int i=0;
	Individu *cur;
	for(i=0;i<taille;i++){
		if (mystrcmp(prenom,l[i]->prenom)==0){
			cur=l[i];
		}
	}
	for(i=0;i<taille;i++){
		if (l[i]->sexe == 'm' && mystrcmp(l[i]->prenom,cur->prenom)!=0){
			if (cur->pere != NULL){
				if(l[i]->pere != NULL && mystrcmp(l[i]->pere->prenom,cur->pere->prenom)==0){
					if (cur->mere != NULL && l[i]->mere != NULL && mystrcmp(l[i]->mere->prenom,cur->mere->prenom)!=0){
						printf("%s \n",l[i]->prenom);
					}
				}
			}	
			if (cur->pere != NULL){
				if(l[i]->pere != NULL && mystrcmp(l[i]->pere->prenom,cur->pere->prenom)!=0){
					if (cur->mere != NULL && l[i]->mere != NULL && mystrcmp(l[i]->mere->prenom,cur->mere->prenom)==0){
						printf("%s \n",l[i]->prenom);
					}
				}
			}	
		}
	}
}

void demi_soeurs (Individu **l, int taille,char *prenom){
	/** donne les noms de toutes les demi-soeurs de l'individu */
	int i=0;
	Individu *cur;
	for(i=0;i<taille;i++){
		if (mystrcmp(prenom,l[i]->prenom)==0){
			cur=l[i];
		}
	}
	for(i=0;i<taille;i++){
		if (l[i]->sexe == 'f' && mystrcmp(l[i]->prenom,cur->prenom)!=0){
			if (cur->pere != NULL){
				if(l[i]->pere != NULL && mystrcmp(l[i]->pere->prenom,cur->pere->prenom)==0){
					if (cur->mere != NULL && l[i]->mere != NULL && mystrcmp(l[i]->mere->prenom,cur->mere->prenom)!=0){
						printf("%s \n",l[i]->prenom);
					}
				}
			}	
			if (cur->pere != NULL){
				if(l[i]->pere != NULL && mystrcmp(l[i]->pere->prenom,cur->pere->prenom)!=0){
					if (cur->mere != NULL && l[i]->mere != NULL && mystrcmp(l[i]->mere->prenom,cur->mere->prenom)==0){
						printf("%s \n",l[i]->prenom);
					}
				}
			}	
		}
	}
}

void oncles (Individu **l, int taille,char *prenom){
	/** donne les noms de tout les oncles de l'individu */
	int i=0;
	Individu *cur;
	for(i=0;i<taille;i++){
		if (mystrcmp(prenom,l[i]->prenom)==0){
			if(l[i]->pere != NULL){
				freres(l,taille,l[i]->pere->prenom);
			}
			else{
				printf("pere inconnu");
			}
			if(l[i]->mere != NULL){
				freres(l,taille,l[i]->mere->prenom);
			}
			else{
				printf("mere inconnue");
			}
		}
	}
}

void tantes (Individu **l, int taille,char *prenom){
	/** donne les noms de toutes les tantes de l'individu */
		int i=0;
	Individu *cur;
	for(i=0;i<taille;i++){
		if (mystrcmp(prenom,l[i]->prenom)==0){
			if(l[i]->pere != NULL){
				soeurs(l,taille,l[i]->pere->prenom);
			}
			else{
				printf("pere inconnu");
			}
			if(l[i]->mere != NULL){
				soeurs(l,taille,l[i]->mere->prenom);
			}
			else{
				printf("mere inconnue");
			}
		}
	}
}

void cousins (Individu **l, int taille,char *prenom){
	/** donne les nom des tout les cousins de l'individu */
}

////////////////////////////////////////////////////////////////////////
//  					GESTION DES COMMANDES						  //
////////////////////////////////////////////////////////////////////////

char **commande(char *cmd, int *new_nb_arg){
	/** Retourne un tableau de string avec en premier le nom de la fonction demande par l'utilisateur
		puis les arguments*/
		//i -> nombre de carac total en para
		//nb_arg -> nombre d'argument qu'on renvoi non null au final
		//j -> nombre de carac dans le mot en construction
		//taille_mot -> la taille du mot en cours de contruction
		//taille_arg -> le nombre d'argument de base, ici 5 car au max 5 args
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
	if(nb_arg == 0){
		fct[nb_arg][j] = '\0';
		if(j+1 < taille_mot){
			fct[nb_arg] = (char *)realloc(fct[nb_arg],sizeof(char)*j);
		}
	}
	//Met les autres arg a NULL
	int k;
	for(k=nb_arg+1;k<taille_arg;k++){
		fct[k]=NULL;
	}
	(*new_nb_arg) = nb_arg+1;
	return fct;
}

void interface (List *indiv, Individu **listIndiv, int taille){
	int i;
	int *nb_arg = malloc(sizeof(int));
	*nb_arg = 5;
	char *cmd_u = malloc(sizeof(char));
	char **ma_cmd = malloc(sizeof(char*)*(*nb_arg));
	ma_cmd[0] = malloc(sizeof(char));
	ma_cmd[0] = "";
	while(mystrcmp(ma_cmd[0],"exit")!=0){
		printf(">> ");
		scanf("%s",cmd_u);
		ma_cmd=commande(cmd_u,nb_arg);
		
		if(mystrcmp(ma_cmd[0], "view") == 0){
			view(indiv);
			viderBuffer();
		} else if (mystrcmp(ma_cmd[0], "exit") == 0){
			printf("Fin de l'application\n");
			viderBuffer();
		} else if((*nb_arg) <= 1){
			printf("Commande invalide, problemes dans les parametres.\n");
			viderBuffer();
		} else if(mystrcmp(ma_cmd[0], "load") == 0){
			viderListe(&indiv);
			load(ma_cmd[1],indiv);
			viderBuffer();
			MAJToutLesIndividus(indiv,&listIndiv,&taille);
		} else if(mystrcmp(ma_cmd[0], "save") == 0){
			save(ma_cmd[1],indiv);
		} else if(mystrcmp(ma_cmd[0], "new" ) == 0){
			if((*nb_arg) < 3){
				printf("Commande non valide, probleme de parametre\n");
			} else {
				if(ma_cmd[3] != NULL && !existe(listIndiv,taille,ma_cmd[3])){
					new(indiv,ma_cmd[3],'m',NULL,NULL,listIndiv,taille);
					MAJToutLesIndividus(indiv,&listIndiv,&taille);
				}
				if(ma_cmd[4] != NULL && !existe(listIndiv,taille,ma_cmd[4])){
					new(indiv,ma_cmd[4],'f',NULL,NULL,listIndiv,taille);
					MAJToutLesIndividus(indiv,&listIndiv,&taille);
				}
				if(!existe(listIndiv,taille,ma_cmd[1])){
					new(indiv, ma_cmd[1],ma_cmd[2][0],ma_cmd[3],ma_cmd[4],listIndiv,taille);
					MAJToutLesIndividus(indiv,&listIndiv,&taille);
				} else {
					printf("Existe deja\n");
				}
			}
		}else if (mystrcmp(ma_cmd[0],"info")==0){
			info(listIndiv,taille,ma_cmd[1]);
			viderBuffer();
		}else if (mystrcmp(ma_cmd[0],"mere")==0){
			mere(listIndiv,taille,ma_cmd[1]);
			viderBuffer();
		}else if (mystrcmp(ma_cmd[0],"pere")==0){
			pere(listIndiv,taille,ma_cmd[1]);
			viderBuffer();
		}else if (mystrcmp(ma_cmd[0],"parents")==0){
			parents(listIndiv,taille,ma_cmd[1]);
			viderBuffer();
		}else if (mystrcmp(ma_cmd[0],"gdperes")==0){
			gd_peres(listIndiv,taille,ma_cmd[1]);
			viderBuffer();	
		}else if (mystrcmp(ma_cmd[0],"gdmeres")==0){
			gd_meres(listIndiv,taille,ma_cmd[1]);
			viderBuffer();	
		}else if (mystrcmp(ma_cmd[0],"gdparents")==0){
			gd_parents(listIndiv,taille,ma_cmd[1]);
			viderBuffer();
		}else if (mystrcmp(ma_cmd[0],"ascendants")==0){
			ascendants(listIndiv,taille,ma_cmd[1]);
			viderBuffer();
		}else if (mystrcmp(ma_cmd[0],"enfants")==0){
			enfants(listIndiv,taille,ma_cmd[1]);
			viderBuffer();
		}else if (mystrcmp(ma_cmd[0],"petit_enfants")==0){
			petits_enfant(listIndiv,taille,ma_cmd[1]);
			viderBuffer();
		}else if (mystrcmp(ma_cmd[0],"descendants")==0){
			descendants(listIndiv,taille,ma_cmd[1]);
			viderBuffer();
		}else if (mystrcmp(ma_cmd[0],"partenaires")==0){
			partenaires(listIndiv,taille,ma_cmd[1]);
			viderBuffer();
		}else if (mystrcmp(ma_cmd[0],"freres")==0){
			freres(listIndiv,taille,ma_cmd[1]);
			viderBuffer();
		}else if (mystrcmp(ma_cmd[0],"soeurs")==0){
			soeurs(listIndiv,taille,ma_cmd[1]);
			viderBuffer();
		}else if (mystrcmp(ma_cmd[0],"oncles")==0){
			oncles(listIndiv,taille,ma_cmd[1]);
			viderBuffer();
		}else if (mystrcmp(ma_cmd[0],"tantes")==0){
			tantes(listIndiv,taille,ma_cmd[1]);
			viderBuffer();
		}else if (mystrcmp(ma_cmd[0],"demi_soeurs")==0){
			demi_soeurs(listIndiv,taille,ma_cmd[1]);
			viderBuffer();
		}else if (mystrcmp(ma_cmd[0],"demi_freres")==0){
			demi_freres(listIndiv,taille,ma_cmd[1]);
			viderBuffer();
			
		} else {
			if(mystrcmp(ma_cmd[0], "exit") != 0)
				printf("Aucune option reconnue\n");
		}
	}
}

/*else if(mystrcmp(ma_cmd[0], "info") == 0){
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
		}*/


int main(void){
	List *l = nouvelleListe();
	Individu **indv = malloc(sizeof(*indv));
	int taille;
	interface(l,indv,taille);
	
	/*new(l,"A",'m',NULL,NULL,indv,taille);MAJToutLesIndividus(l,&indv,&taille);
	new(l,"B",'f',NULL,NULL,indv,taille);MAJToutLesIndividus(l,&indv,&taille);
	new(l,"C",'m',"A","B",indv,taille);MAJToutLesIndividus(l,&indv,&taille);
	new(l,"D",'f',NULL,NULL,indv,taille);MAJToutLesIndividus(l,&indv,&taille);
	new(l,"E",'f',NULL,NULL,indv,taille);MAJToutLesIndividus(l,&indv,&taille);
	new(l,"F",'m',"C","D",indv,taille);MAJToutLesIndividus(l,&indv,&taille);
	new(l,"G",'m',"C","D",indv,taille);MAJToutLesIndividus(l,&indv,&taille);
	new(l,"H",'m',"C","E",indv,taille);MAJToutLesIndividus(l,&indv,&taille);
	new(l,"Z",'m',NULL,NULL,indv,taille);MAJToutLesIndividus(l,&indv,&taille);
	new(l,"W",'f',NULL,NULL,indv,taille);MAJToutLesIndividus(l,&indv,&taille);
	new(l,"Y",'f',"Z","W",indv,taille);MAJToutLesIndividus(l,&indv,&taille);
	view(l);printf("\n");
	
	viderListe(&l);
	MAJToutLesIndividus(l,&indv,&taille);

	load("test.txt",l);
	MAJToutLesIndividus(l,&indv,&taille);
	
	new(l,"z",'m',NULL,NULL,indv,taille);MAJToutLesIndividus(l,&indv,&taille);
	view(l);printf("\n");
	*/
	/*int w;
	for(w=0;w<taille;w++){
		afficherIndividu(indv[w]);
	}
	
	ListNode *actuel = l->premier;
	while(actuel->next != NULL){
		actuel = actuel->next;
	}
	ListNode *node = malloc(sizeof(*node));
	Individu *ind = initialisationIndividu();
	ind->prenom = malloc(sizeof(char)*strlen("z"));
	strcpy(ind->prenom,"z");
	ind->sexe = 'f';
	node->individu = ind;
	node->next = actuel->next;
	
	actuel->next = node;
	
	printf("-\n");
	actuel = l->premier;
	while(actuel != NULL){
		afficherIndividu(actuel->individu);
		actuel = actuel->next;
	}*/
	
	
	//view(l);printf("\n");
	
	//new(l,"Y",'f',NULL,NULL,indv,taille);MAJToutLesIndividus(l,&indv,&taille);
	//view(l);printf("\n");
	
	
	//view(l);printf("\n");
	
	/*char **ma_cmd;
	char c[19] = "new(bru,f,tre,pro)";
	int *t = malloc(sizeof(int));*t=5;
	ma_cmd=commande(c,t);
	int i;
	for(i=0;i<5;i++){
		if(ma_cmd[i] == NULL)
			printf("NULL\n");
		else	
			printf("%s\n",ma_cmd[i]);
	}*/
	
	/*
	new(l,"A",'m',NULL,NULL);
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

	//save("test.txt",l);
	//load("test.txt",l);
	//view(l);
	return 0;
}
