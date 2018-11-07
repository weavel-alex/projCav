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
	List *l = NULL;
	l = malloc(sizeof(*l));
	l->premier = NULL;
	return l;
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

Individu **toutLesIndividus (List *l, int *taille){
	/** stocke l'arbre en memoire */
	int taille_max = 20;
	Individu **tab = malloc(sizeof(*tab)*taille_max);
	ListNode *actuel = l->premier;
	*taille = 0;
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

FILE* ouvrirFichier(char* nom, char* option){
	FILE* fichier = NULL;
	fichier = fopen(nom,option);
	return fichier;
}

void fermerFichier(FILE* fichier){
	fclose(fichier);
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
		ListNode *node = malloc(sizeof(*node));
		Individu *ind = initialisationIndividu();
		ind->prenom = malloc(sizeof(char)*strlen(prenom));
		strcpy(ind->prenom,prenom);
		ind->sexe = sexe;
		node->individu = ind;
		
		l->premier = node;
	} else {
		//Ajout en fin de chaine si pas de parents
		//Verifie que le pere car s'il n'a pas de pere il n'aura pas de mere
		if(prenom_pere == NULL){
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
						printf("Erreur de sexe pour le pere\n");
						printf("Ajout annulé\n");
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
						printf("Erreur de sexe pour la mere\n");
						printf("Ajout annulé\n");
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
				printf("Erreur detecter pendant l'ajout\n");
				return;
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

int estMinuscule(char c){
	return (c >= 'a' && c <= 'z');
}

int estMajuscule(char c){
	return (c >= 'A' && c <= 'Z');
}

int estLettre(char c){
	return estMajuscule(c) || estMinuscule(c);
}

void load (char *nom_fichier, List *l){
	/** charge en memoire l'arbre stocké dans le fichier 'nom_fichier' */
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
			if(estLettre(c)){
				indv[ptr][fin_mot] = c;
				fin_mot++;
				if(fin_mot == taille_mot){
					taille_mot *= 2;
					indv[ptr] = realloc(indv[ptr],(sizeof(char)*taille_mot));
				}
			} else {
				//Si un autre caractere
				if(fin_mot != 0){
					//Ecriture de la fin du mot
					indv[ptr][fin_mot] = '\0';
					if(fin_mot != taille_mot){
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
					new(l,indv[0],indv[1][0],indv[2],indv[3]);
					ptr=0;
					//On realloc pour ne pas avoir de soucis de memoire apres
					for(i=0;i<4;i++){
						indv[i] = NULL;
						indv[i] = realloc(indv[i],(sizeof(char)*taille_mot));
					}
				}
			}
		}
		for(i=0;i<4;i++){
			free(indv[i]);
		}
		free(indv);
		fermerFichier(fichier);
	} else {
		printf("Le fichier %s n'existe pas.\n",nom_fichier);
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
	//Met les autres arg a NULL
	int k;
	for(k=nb_arg+1;k<taille_arg;k++){
		fct[k]=NULL;
	}
	(*new_nb_arg) = nb_arg+1;
	return fct;
}

void interface (List *indiv){
	int *nb_arg = malloc(sizeof(int));
	*nb_arg = 5;
	char *cmd_u = malloc(sizeof(char));
	char **ma_cmd = malloc(sizeof(char*)*(*nb_arg));
	ma_cmd[0] = "NULL";
	while(mystrcmp(ma_cmd[0],"exit")!=0){
		printf(">> ");
		scanf("%s",cmd_u);
		ma_cmd=commande(cmd_u,nb_arg);
		if(mystrcmp(ma_cmd[0], "view") == 0){
			view(indiv);
		} else if (mystrcmp(ma_cmd[0], "exit") == 0){
			printf("Fin de l'application\n");
		} else if((*nb_arg) <= 1){
			printf("Commande invalide\n");
			//Vider le buffer
			int c = 0;
			while (c != '\n' && c != EOF)
			{
				c = getchar();
			}
			//fin vider buffer
		} else {
			if(mystrcmp(ma_cmd[0], "load") == 0){
				load(ma_cmd[1],indiv);
			}
			else if(mystrcmp(ma_cmd[0], "save") == 0){
				save(ma_cmd[1],indiv);
			}
			else if(mystrcmp(ma_cmd[0], "new" ) == 0){
				if((*nb_arg) < 3 || (*nb_arg) == 4){
					printf("Commande non valide, probleme de parametre\n");
				} else {
					new(indiv, ma_cmd[1],ma_cmd[2][0],ma_cmd[3],ma_cmd[4]);
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
	/*
	new(l,"A",'m',NULL,NULL);
	new(l,"B",'f',NULL,NULL);
	new(l,"C",'m',"A","B");
	new(l,"D",'f',NULL,NULL);
	new(l,"E",'f',NULL,NULL);
	new(l,"F",'m',"C","D");
	new(l,"G",'m',"C","D");
	new(l,"H",'m',"C","E");
	view(l);printf("\n");
	*/
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
	
	//interface(l);
	//save("test.txt",l);
	load("test.txt",l);
	view(l);
	return 0;
}
