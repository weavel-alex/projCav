#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct _Individu {
	char *prenom;
	char sexe;
	struct _Individu *pere;
	struct _Individu *mere;
};
typedef struct _Individu Individu;

struct S_ListNode{
	Individu *individu;
	struct S_ListNode *next;
}; typedef struct S_ListNode ListNode;

typedef struct{
	ListNode *premier;
} List;

struct _FileIndiv{
	Individu **file;
	int tmax;
	int nbelemt;
}; typedef struct _FileIndiv FileIndiv;


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

FileIndiv initFile(){
	FileIndiv res;
	res.tmax = 10;
	res.nbelemt = 0;
	res.file = malloc(10*sizeof(Individu));
	return res;
}

void enfile (FileIndiv *f, Individu *i){
	f->nbelemt++;
	if (f->nbelemt > f->tmax){
		f->tmax = 2*(f->tmax);
		f->file = realloc(f->file,f->tmax*sizeof(Individu));
	}
	f->file[f->nbelemt-1]=i;
}


Individu *defile(FileIndiv *f){
	Individu *res = f->file[0];
	for (int i=0;i<f->nbelemt-1;i++){
		f->file[i] = f->file[i+1];
	}
	f->nbelemt--;
	return res;
}

Individu *initialisationIndividu(){
	Individu *indiv = malloc(sizeof(*indiv));
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

////////////////////////////////////////////////////////////////////////
//  				COMMANDES GESTION ARBRE							  //
////////////////////////////////////////////////////////////////////////


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

void view (List l){
	/** affiche l'arbre en memoire, meme format que la sauvegarde */
	FileIndiv f = initFile();
	
	ListNode *cur = l.premier;
	while(cur->next!=NULL){
		enfile(&f,cur->individu);
		cur = cur->next;
	}
	while (f.nbelemt > 0){
		FileIndiv newval = initFile();
		for (int i=0; i<f.nbelemt;i++){
			afficherIndividu(f.file[i]);
			if (f.file[i]->pere != NULL){
				enfile(&newval, f.file[i]->pere);
			}
			if (f.file[i]->mere != NULL){
				enfile(&newval, f.file[i]->mere);
			}
		}
		while(f.nbelemt>0){
			defile(&f);
		}
		for (int i=0;i<newval.nbelemt;i++){
			enfile(&f,defile(&newval));
		}
	}	
}

void new (List *l, char *prenom, char sexe, char *prenom_pere, char *prenom_mere){
	/** ajouter un individu dans l'arbre */
	if(l->premier == NULL){
		ListNode *node = malloc(sizeof(*node));
		node->next = NULL;
		Individu *ind = initialisationIndividu();
		ind->prenom = prenom;
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
			ListNode *node = malloc(sizeof(*node));
			node->next = NULL;
			Individu *ind = initialisationIndividu();
			ind->prenom = prenom;
			ind->sexe = sexe;
			node->individu = ind;
			
			actuel->next = node;
		} else {
			Individu *papa;
			Individu *mama;
			ListNode *actuel = l->premier;
			ListNode *prec = actuel;
			while(actuel != NULL){
				if(mystrcmp(actuel->individu->prenom,prenom_pere) == 0){
					papa = actuel->individu;
					if(prec == actuel){
						l->premier = l->premier->next;
						actuel = l->premier;
						prec = actuel;
					} else {
						prec->next = actuel->next;
						actuel = prec;
					}
				}
				if(mystrcmp(actuel->individu->prenom,prenom_mere) == 0){
					mama = actuel->individu;
					if(prec == actuel){
						l->premier = l->premier->next;
						actuel = l->premier;
						prec = actuel;
					} else {
						prec->next = actuel->next;
						actuel = prec;
					}
				}
				prec = actuel;
				actuel = actuel->next;
			}
			ListNode *node = malloc(sizeof(*node));
			node->next = NULL;
			Individu *ind = initialisationIndividu();
			ind->prenom = prenom;
			ind->sexe = sexe;
			ind->pere = papa;
			ind->mere = mama;
			node->individu = ind;
			
			node->next = actuel;
			prec->next = node;
		}
	}
}


List *load (char *nom_fichier){
	/** charge en memoire l'arbre stoqué dans le fichier 'nom_fichier' */
	
	FILE *fichier = fopen(nom_fichier,"r");
	
	List *res = nouvelleListe(); //init la liste chaine qui sert de memoire
	int fini=0;
	char c;
	do{
	//parcour integral du fichier	
		int done = 0;
		while (!done && c != EOF){
			//parcour de la ligne

			char *nom = malloc(sizeof(char)*2);
			char *nom_pere = malloc(sizeof(char)*2);
			char *nom_mere = malloc(sizeof(char)*2);
			char sexe;

			int end = 0;
			
			
			while (c!=':' && c != EOF){
				//copie du deuxieme parametre
				/**/
				nom[end]=c;
				end++;
				nom=realloc(nom,(sizeof(char)*end+1));
				c = fgetc(fichier);
			}
			nom[end] = '\0';
			
			end = 0;
			
			
			while (c!=',' && c != EOF){
				sexe = c;
				c = fgetc(fichier);
			}
			end=0;
			c = fgetc(fichier);
			while (c!=',' && c != EOF){
				//copie du troisieme parametre
				/**/
				
				nom_pere[end]=c;
				end++;
				nom_pere=realloc(nom_pere,(sizeof(char)*end+1));
				c = fgetc(fichier);
				if (strlen(nom_pere)==0){nom_pere = NULL;};
			}
			nom_pere[end] = '\0';
			
			end = 0;
			while (c!='\n' && c != EOF){
				//copie du dernier
				/**/
				
		if (c == EOF){
			c = fgetc(fichier);
		}
				c = fgetc(fichier);
				if (c != ','){
					nom_mere[end]=c;
					end++;
					nom_mere=realloc(nom_mere,(sizeof(char)*end+1));
				}
				if (strlen(nom_mere)==0){nom_mere = NULL;};
			}
			nom_mere[end] = '\0';
			end = 0;
			//printf("%s %c %s %s\n",nom,sexe,nom_pere, nom_mere);
			new(res,nom,sexe,nom_pere,nom_mere);
			done=1;
		}
		if (c != EOF){
			c = fgetc(fichier);
		}
		
	}while (c != EOF);
	fclose(fichier);
	//view(res);
	return res;
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
			//view(indiv);
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
				new(indiv, ma_cmd[1],ma_cmd[2][0],ma_cmd[3],ma_cmd[4]);
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
	
	char *fi = "pok.txt";
	List *meme = load(fi);
	
	
	
	List *l = nouvelleListe();
	new(l,"Test",'f',NULL,NULL);
	new(l,"Test2",'m',NULL,NULL);
	new(l,"Test3",'f',"Test2","Test");
	new(l,"Test4",'m',NULL,NULL);
	new(l,"Test5",'m',NULL,NULL);
	
	view(*l);
	
	
	/*
	view(l);printf("\n");
	new(l,"Parent",'m',"Test5","Test");
	view(l);printf("\n");
	new(l,"Parent2",'m',"Test2","Test4");
	view(l);printf("\n");
	new(l,"GP",'m',"Parent","Parent2");
	* 
	view(l);printf("\n");
	*/
	
	
	//interface(indiv);
	return 0;
}
