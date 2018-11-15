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
	free(actuel);
	return tab;
}

void MAJToutLesIndividus(List *l, Individu ***tab, int *taille){
	/**Met a jour le tableau de tout les individus de l'arbre*/
	*(tab) = NULL;
	*(tab) = toutLesIndividus(l,taille);
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

void save (char *nom_fichier,List *l, Individu **tab, int taille){
	/** sauvegarde l'arbre en memoire dans le fichier 'nom_fichier' */
	FILE* fichierD = fopen(nom_fichier,"a");
	if(fichierD != NULL){
		remove(nom_fichier);
	}
	FILE *fichier = ouvrirFichier(nom_fichier,"a");
	if(fichier != NULL){
		int i;
		for(i=taille-1;i>=0;i--){
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
					//On cree l'individu et ses parents s'ils n'existent pas
					if(indv[2] != NULL && !existe(tab,nbInd,indv[2])){
						new(l,indv[2],'m',NULL,NULL,tab,nbInd);
						tab = toutLesIndividus(l,&nbInd);
					}
					if(indv[3] != NULL && !existe(tab,nbInd,indv[3])){
						new(l,indv[3],'f',NULL,NULL,tab,nbInd);
						tab = toutLesIndividus(l,&nbInd);
					}
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
	int taille_cmd = strlen(cmd);
	char **fct = malloc(sizeof(char*)*taille_arg);
	for(i=0;i<taille_arg;i++){
		fct[i] = (char *)malloc(sizeof(char)*taille_mot);
	}
	for(i=0;i<taille_cmd;i++){
		if(cmd[i] != ' '){
			if(estLettre(cmd[i]) || (j != 0 && (cmd[i] == '-' || cmd[i] == '.'))){
				//Nom composé avec un - ou pour les fichiers
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
			if(cmd[i] == ')' || i == taille_cmd){
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
	/**Gestion de l'interface utilisateur*/
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
			view(indiv,listIndiv,taille);
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
			save(ma_cmd[1],indiv,listIndiv,taille);
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
				}
				viderBuffer();
			}
		} else if (mystrcmp(ma_cmd[0],"info")==0){
			info(listIndiv,taille,ma_cmd[1]);
			viderBuffer();
		} else if (mystrcmp(ma_cmd[0],"mere")==0){
			mere(listIndiv,taille,ma_cmd[1]);
			viderBuffer();
		} else if (mystrcmp(ma_cmd[0],"pere")==0){
			pere(listIndiv,taille,ma_cmd[1]);
			viderBuffer();
		} else if (mystrcmp(ma_cmd[0],"parents")==0){
			parents(listIndiv,taille,ma_cmd[1]);
			viderBuffer();
		} else if (mystrcmp(ma_cmd[0],"gdperes")==0){
			gd_peres(listIndiv,taille,ma_cmd[1]);
			viderBuffer();	
		} else if (mystrcmp(ma_cmd[0],"gdmeres")==0){
			gd_meres(listIndiv,taille,ma_cmd[1]);
			viderBuffer();	
		} else if (mystrcmp(ma_cmd[0],"gdparents")==0){
			gd_parents(listIndiv,taille,ma_cmd[1]);
			viderBuffer();
		} else if (mystrcmp(ma_cmd[0],"ascendants")==0){
			ascendants(listIndiv,taille,ma_cmd[1]);
			viderBuffer();
		} else if (mystrcmp(ma_cmd[0],"enfants")==0){
			enfants(listIndiv,taille,ma_cmd[1]);
			viderBuffer();
		} else if (mystrcmp(ma_cmd[0],"petitenfants")==0){
			petits_enfant(listIndiv,taille,ma_cmd[1]);
			viderBuffer();
		} else if (mystrcmp(ma_cmd[0],"descendants")==0){
			descendants(listIndiv,taille,ma_cmd[1]);
			viderBuffer();
		} else if (mystrcmp(ma_cmd[0],"partenaires")==0){
			partenaires(listIndiv,taille,ma_cmd[1]);
			viderBuffer();
		} else if (mystrcmp(ma_cmd[0],"freres")==0){
			freres(listIndiv,taille,ma_cmd[1]);
			viderBuffer();
		} else if (mystrcmp(ma_cmd[0],"soeurs")==0){
			soeurs(listIndiv,taille,ma_cmd[1]);
			viderBuffer();
		} else if (mystrcmp(ma_cmd[0],"oncles")==0){
			oncles(listIndiv,taille,ma_cmd[1]);
			viderBuffer();
		} else if (mystrcmp(ma_cmd[0],"tantes")==0){
			tantes(listIndiv,taille,ma_cmd[1]);
			viderBuffer();
		} else if (mystrcmp(ma_cmd[0],"demisoeurs")==0){
			demi_soeurs(listIndiv,taille,ma_cmd[1]);
			viderBuffer();
		} else if (mystrcmp(ma_cmd[0],"demifreres")==0){
			demi_freres(listIndiv,taille,ma_cmd[1]);
			viderBuffer();	
		} else if (mystrcmp(ma_cmd[0],"cousins")==0){
			cousins(listIndiv,taille,ma_cmd[1]);
			viderBuffer();
		} else {
			if(mystrcmp(ma_cmd[0], "exit") != 0)
				printf("Aucune option reconnue\n");
		}
	}
	int i;
	for(i=0;i<(*nb_arg);i++){
		free(ma_cmd[i]);
	}
	free(ma_cmd);
	free(cmd_u);
	free(nb_arg);
}

int main(void){
	List *l = nouvelleListe();
	Individu **indv = malloc(sizeof(*indv));
	int taille = 0;
	interface(l,indv,taille);
	int i;
	for(i=taille-1;i>=0;i++){
		free(indv[i]);
	}
	free(indv);
	return 0;
}
