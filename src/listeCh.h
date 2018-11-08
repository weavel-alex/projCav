#ifndef H_LISTECH_H
#define H_LISTECH_H

#include "individu.h"

typedef struct S_ListNode{
	Individu *individu;
	struct S_ListNode *next;
} ListNode;

typedef struct{
	ListNode *premier;
} List;

List *nouvelleListe();
void viderListe(List **l);

#endif
