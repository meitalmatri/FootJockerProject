#include "items.h"

ItemNode* search_item(ItemNode** Itemtree, char* name)
{
	if (!(*Itemtree))
		return NULL;
	if (!strcmp((*Itemtree)->itemN.model, name))
		return *Itemtree;
	else if (strcmp(name, (*Itemtree)->itemN.model) < 0)
		return search_item(&(*Itemtree)->left, name);
	else
		return search_item(&(*Itemtree)->right, name);