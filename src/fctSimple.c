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
	/**Vide le buffer*/
	int c;
	do {
		c = getchar();
	} while (c != '\n' && c != EOF);
}

int estMinuscule(char c){
	/**Renvoi vrai si le caractere est minuscule*/
	return (c >= 'a' && c <= 'z');
}

int estMajuscule(char c){
	/**Renvoi vrai si le caractere est majuscule*/
	return (c >= 'A' && c <= 'Z');
}

int estLettre(char c){
	/**Renvoi vrai si le caractere est une lettre*/
	return estMajuscule(c) || estMinuscule(c);
}

FILE* ouvrirFichier(char* nom, char* option){
	/**Ouvre un fichier et le renvoi*/
	FILE* fichier = NULL;
	fichier = fopen(nom,option);
	return fichier;
}

void fermerFichier(FILE* fichier){
	/**Ferme le fichier*/
	fclose(fichier);
	fichier=NULL;
}
