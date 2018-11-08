#include "fctSimple.h"

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

void viderBuffer(){
	int c;
	do {
		c = getchar();
	} while (c != '\n' && c != EOF);
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

FILE* ouvrirFichier(char* nom, char* option){
	FILE* fichier = NULL;
	fichier = fopen(nom,option);
	return fichier;
}

void fermerFichier(FILE* fichier){
	fclose(fichier);
	fichier=NULL;
}
