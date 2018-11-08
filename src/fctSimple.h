#ifndef H_FCTSIMPLE_H
#define H_FCTSIMPLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int mystrcmp(char *s, char *ch);
void viderBuffer();
int estMinuscule(char c);
int estMajuscule(char c);
int estLettre(char c);
FILE* ouvrirFichier(char* nom, char* option);
void fermerFichier(FILE* fichier);

#endif
