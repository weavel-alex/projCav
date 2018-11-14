#include "affichage.h"

void view (List *l, Individu **tab, int taille){
	int i;
	for(i=0;i<taille;i++){
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
					printf("Gd Pere paternel inconnu\n");
				}
			}
			else{
				printf("Pere inconnu\n");
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
					printf("Gd Pere maternel inconnu\n");
				}
			}
			else{
				printf("Mere inconnue\n");
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
					printf("Gd Mere paternelle inconnu\n");
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
					printf("Gd Mere maternelle inconnu\n");
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
				printf("\t%s\n",l[i]->pere->prenom);
				ascendants(l,taille,l[i]->pere->prenom);
			 }
			 if(l[i]->mere != NULL){
				 printf("\t%s\n",l[i]->mere->prenom);
				 ascendants(l,taille,l[i]->mere->prenom);
			 }
		 }
	 }
 }

void enfants (Individu **l, int taille,char *prenom){
	/** donne les noms des enfants de l'individu */
	int i;
	int aP=0;
	for(i=0;i<taille;i++){
		if (l[i]->pere != NULL && mystrcmp(l[i]->pere->prenom,prenom)==0){
			printf("\t%s\n",l[i]->prenom);
			aP=1;
		}
		if (l[i]->mere != NULL && mystrcmp(l[i]->mere->prenom,prenom)==0){
			printf("\t%s\n",l[i]->prenom);
			aP=1;
		}
	}
	/*
	if(!aP)
		printf("%s: Aucun enfant\n",prenom);
	*/
}

void petits_enfant (Individu **l, int taille,char *prenom){
	/** donne les noms des petits enfants de l'individu */
	int i;
	int aP = 0;
	for(i=0;i<taille;i++){
		if (l[i]->pere != NULL){
			if(l[i]->pere->pere != NULL && mystrcmp(prenom,l[i]->pere->pere->prenom)==0){
				printf("\t%s\n",l[i]->prenom);
				aP=1;
			}
			if(l[i]->pere->mere != NULL && mystrcmp(prenom,l[i]->pere->mere->prenom)==0){
				printf("\t%s\n",l[i]->prenom);
				aP=1;
			}
		}
		if (l[i]->mere != NULL && mystrcmp(l[i]->mere->prenom,prenom)==0){
			if(l[i]->mere->pere != NULL && mystrcmp(prenom,l[i]->mere->pere->prenom)==0){
				printf("\t%s\n",l[i]->prenom);
				aP=1;
			}
			if(l[i]->mere->mere != NULL && mystrcmp(prenom,l[i]->mere->mere->prenom)==0){
				printf("\t%s\n",l[i]->prenom);
				aP=1;
			}
		}
	}
	if(!aP)
		printf("Aucun petit enfant\n");
}

void descendants (Individu **l, int taille,char *prenom){
	/** done les noms de tout les descendant de l'individu */
	int i;
	for(i=0;i<taille;i++){
		if (l[i]->pere != NULL && mystrcmp(l[i]->pere->prenom,prenom)==0){
			printf("\t%s\n",l[i]->prenom);
			descendants(l,taille,l[i]->prenom);
		}
		if (l[i]->mere != NULL && mystrcmp(l[i]->mere->prenom,prenom)==0){
			printf("\t%s\n",l[i]->prenom);
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
					printf("\t%s\n",l[i]->mere->prenom);
				} else {
					printf("Partenaire inconnue\n");
				}
			}
		}
	}
	if (s == 'f'){
		for(i=0;i<taille;i++){
			if (l[i]->mere != NULL && mystrcmp(l[i]->mere->prenom,prenom)==0){
				if (l[i]->pere != NULL){
					printf("\t%s\n",l[i]->pere->prenom);
				} else {
					printf("Partenaire inconnu\n");
				}
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
						printf("\t%s\n",l[i]->prenom);
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
						printf("\t%s\n",l[i]->prenom);
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
						printf("\t%s\n",l[i]->prenom);
					}
				}
			}	
			if (cur->pere != NULL){
				if(l[i]->pere != NULL && mystrcmp(l[i]->pere->prenom,cur->pere->prenom)!=0){
					if (cur->mere != NULL && l[i]->mere != NULL && mystrcmp(l[i]->mere->prenom,cur->mere->prenom)==0){
						printf("\t%s\n",l[i]->prenom);
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
						printf("\t%s\n",l[i]->prenom);
					}
				}
			}	
			if (cur->pere != NULL){
				if(l[i]->pere != NULL && mystrcmp(l[i]->pere->prenom,cur->pere->prenom)!=0){
					if (cur->mere != NULL && l[i]->mere != NULL && mystrcmp(l[i]->mere->prenom,cur->mere->prenom)==0){
						printf("\t%s\n",l[i]->prenom);
					}
				}
			}	
		}
	}
}

void oncles (Individu **l, int taille,char *prenom){
	/** donne les noms de tout les oncles de l'individu */
	int i;
	for(i=0;i<taille;i++){
		if (mystrcmp(prenom,l[i]->prenom)==0){
			if(l[i]->pere != NULL){
				freres(l,taille,l[i]->pere->prenom);
			}
			else{
				printf("Pere inconnu");
			}
			if(l[i]->mere != NULL){
				freres(l,taille,l[i]->mere->prenom);
			}
			else{
				printf("Mere inconnue");
			}
		}
	}
}

void tantes (Individu **l, int taille,char *prenom){
	/** donne les noms de toutes les tantes de l'individu */
	int i;
	for(i=0;i<taille;i++){
		if (mystrcmp(prenom,l[i]->prenom)==0){
			if(l[i]->pere != NULL){
				soeurs(l,taille,l[i]->pere->prenom);
			}
			else{
				printf("Pere inconnu");
			}
			if(l[i]->mere != NULL){
				soeurs(l,taille,l[i]->mere->prenom);
			}
			else{
				printf("Mere inconnue");
			}
		}
	}
}

void cousins (Individu **l, int taille,char *prenom){
	/** donne les nom des tout les cousins de l'individu */
	//coté paternel
	int i,j;
	Individu *cur;
	for (i=0;i<taille;i++){
		if (mystrcmp(l[i]->prenom,prenom)==0){
			if (l[i]->pere != NULL){
				for(j=0;j<taille;j++){
					if(mystrcmp(l[j]->prenom,l[i]->pere->prenom)==0){
						cur = l[j];
					}
				}
			}
			else{
				printf("pere inconnu\n");
			}
		}
	}
	
	if(cur->pere != NULL){
		for(i=0;i<taille;i++){
			if(l[i]->pere != NULL && mystrcmp(l[i]->prenom,cur->prenom)!=0 && mystrcmp(l[i]->pere->prenom,cur->pere->prenom)==0) {
				enfants(l,taille,l[i]->prenom);
			}
		}
	}
	else{
		printf("oncles et tantes paternels inconnus\n");
	}
	
	//coté maternel
	for (i=0;i<taille;i++){
		if (mystrcmp(l[i]->prenom,prenom)==0){
			if (l[i]->mere != NULL){
				for(j=0;j<taille;j++){
					if(mystrcmp(l[j]->prenom,l[i]->mere->prenom)==0){
						cur = l[j];
					}
				}
			}
			else{
				printf("mere inconnue\n");
			}
		}
	}
	
	if(cur->mere != NULL){
		for(i=0;i<taille;i++){
			if(l[i]->mere != NULL && mystrcmp(l[i]->prenom,cur->prenom)!=0 && mystrcmp(l[i]->mere->prenom,cur->mere->prenom)==0) {
				enfants(l,taille,l[i]->prenom);
			}
		}
	}
	else{
		printf("oncles et tantes maternels inconnus\n");
	}
}
