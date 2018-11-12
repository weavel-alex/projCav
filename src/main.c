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
	//Si la liste est vide
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
			//Verif dans la liste chainée si les parents existe
			while(actuel != NULL){
				estModifiee = 0;
				if(prenom_pere != NULL){
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
				}
				if(prenom_mere != NULL){
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
				}
				//Verifie si la modification concerne la mere dans ce cas on ne passe pas au suivant car on l'a deja fais
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
				int i;
				for(i=0;i<nbInd;i++){
					if(papa == NULL && prenom_pere != NULL){
						if(mystrcmp(prenom_pere,tab[i]->prenom) == 0){
							papa = tab[i];
						}
					}
					if(mama == NULL && prenom_mere != NULL){
						if(mystrcmp(prenom_mere,tab[i]->prenom) == 0){
							mama = tab[i];
						}
					}
				}
			}
			//On ajoute notre nouveau noeud a liste
			ListNode *node = malloc(sizeof(*node));
			Individu *ind = initialisationIndividu();
			ind->prenom = malloc(sizeof(char)*strlen(prenom));
			strcpy(ind->prenom,prenom);
			ind->sexe = sexe;
			if(papa == NULL && prenom_pere != NULL){
				printf("new : Aucun individu trouvé pour %s\n",prenom_pere);
				ind->pere = NULL;
			} else {
				ind->pere = papa;
			}
			if(mama == NULL && prenom_mere != NULL){
				printf("new : Aucun individu trouvé pour %s\n",prenom_mere);
				ind->mere = NULL;
			} else {
				ind->mere = mama;
			}
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
			if(tab[i]->pere != NULL && tab[i]->mere != NULL){
				fprintf(fichier,"%s:%c,%s,%s\n",tab[i]->prenom,tab[i]->sexe,tab[i]->pere->prenom,tab[i]->mere->prenom);
			} else {
				if(tab[i]->pere == NULL && tab[i]->mere != NULL){
					fprintf(fichier,"%s:%c,,%s\n",tab[i]->prenom,tab[i]->sexe,tab[i]->mere->prenom);
				} else if(tab[i]->pere != NULL && tab[i]->mere == NULL){
					fprintf(fichier,"%s:%c,%s,\n",tab[i]->prenom,tab[i]->sexe,tab[i]->pere->prenom);
				} else {
					fprintf(fichier,"%s:%c,,\n",tab[i]->prenom,tab[i]->sexe);
				}
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
			//Creation du mot -> si une lettre ou un nom compose avec '-' par exemple j-c
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
}

void descendants (Individu **l, int taille,char *prenom){
	/** done les noms de tout les descendant de l'individu */
		
}

void partenaires (Individu **l, int taille,char *prenom){
	/**donne les noms de tout les partenaires de l'individu 
	 * (-> partenaires si enfant en commun) */
}

void freres (Individu **l, int taille,char *prenom){
	/** donne les noms de tout les freres de l'individu */
}

void soeurs (Individu **l, int taille,char *prenom){
	/** donne les noms de toutes les soeurs de l'individu */
}

void demi_freres (Individu **l, int taille,char *prenom){
	/** donne les noms de tout les demi-freres de l'individu */
}

void demi_soeurs (Individu **l, int taille,char *prenom){
	/** donne les noms de toutes les demi-soeurs de l'individu */
}

void oncles (Individu **l, int taille,char *prenom){
	/** donne les noms de tout les oncles de l'individu */
}

void tantes (Individu **l, int taille,char *prenom){
	/** donne les noms de toutes les tantes de l'individu */
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
			if(estLettre(cmd[i]) || (j != 0 && cmd[i] == '-')){
				fct[nb_arg][j] = cmd[i];
				j++;
				if(j == taille_mot){
					taille_mot *= 2;
					fct[nb_arg] = (char *)realloc(fct[nb_arg],sizeof(char)*taille_mot);
				}
			}
			if(cmd[i] == '(' || cmd[i] == ','){
				//Si on met null en arg
				if(mystrcmp(fct[nb_arg],"null") == 0){
					fct[nb_arg] = NULL;
				}
				else if(j != 0){
					//Si on a au moins une lettre
					fct[nb_arg][j] = '\0';
					if(j < taille_mot){
						fct[nb_arg] = (char *)realloc(fct[nb_arg],sizeof(char)*j);
					}
				} else {
					//Si vide ex: new(a,f,,m) -> arg pere = NULL du coup
					fct[nb_arg] = NULL;
				}
				nb_arg++;j=0;
			}
			if(cmd[i] == ')'){
				if(mystrcmp(fct[nb_arg],"null") == 0){
					fct[nb_arg] = NULL;
				}
				else if(j != 0){
					fct[nb_arg][j] = '\0';
					if(j < taille_mot){
						fct[nb_arg] = (char *)realloc(fct[nb_arg],sizeof(char)*j);
					}
				} else {
					fct[nb_arg] = NULL;
				}
				break;
			}
		}
	}
	//Dans le cas ou on rentre juste le nom pour les fct sans para comme view et exit
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
		} else if(ma_cmd[1] == NULL){
			printf("Prenom non valide\n");
			viderBuffer();
		} else if(mystrcmp(ma_cmd[0], "new" ) == 0){
			if((*nb_arg) < 3){
				printf("Commande non valide, probleme de parametre\n");
				viderBuffer();
			} else {
				if(ma_cmd[3] != NULL && !existe(listIndiv,taille,ma_cmd[3])){
					//Si le pere n'existe pas encore
					new(indiv,ma_cmd[3],'m',NULL,NULL,listIndiv,taille);
					MAJToutLesIndividus(indiv,&listIndiv,&taille);
				}
				if(ma_cmd[4] != NULL && !existe(listIndiv,taille,ma_cmd[4])){
					//Si la mere n'existe pas encore
					new(indiv,ma_cmd[4],'f',NULL,NULL,listIndiv,taille);
					MAJToutLesIndividus(indiv,&listIndiv,&taille);
				}
				if(!existe(listIndiv,taille,ma_cmd[1])){
					//Si l'individu n'existe pas
					new(indiv, ma_cmd[1],ma_cmd[2][0],ma_cmd[3],ma_cmd[4],listIndiv,taille);
					MAJToutLesIndividus(indiv,&listIndiv,&taille);
				} else {
					printf("Individu deja existant.\n");
					viderBuffer();
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
