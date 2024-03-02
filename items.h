#pragma once

#include <stdbool.h>

typedef struct item{
    int id;
    char model[20];
    char manuf[20];
    int size[11];
    float price;
    int inventory;

} Item;

node* search(node tree, int val)
{
	if (!(tree))
	{
		return tree;
	}

	if (val < (tree)->id)
	{
		search(&((tree)->left), val);
	}
	else if (val > (tree)->id)
	{
		search(&((tree)->right), val);
	}
	else if (val == (tree)->id)
	{
		return tree;
	}

}
