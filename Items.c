#include "items.h"


ItemNode* searchItem(ItemNode** Itemtree, int itemID)
{
	if (!(*Itemtree))
	{
		return NULL;
	}

	if (itemID < (*Itemtree)->itemID)
	{
		searchItem(&((*Itemtree)->left), itemID);
	}
	else if (itemID > (*Itemtree)->itemID)
	{
		searchItem(&((*Itemtree)->right), itemID);
	}
	else if (itemID == (*Itemtree)->itemID)
	{
		return *Itemtree;
	}
}

void AddItem(ItemNode** itemTree, Item itm)
{
	insertItem(itemTree, NULL, itm);
	AddIventory(itemTree, itm);
}

void insertItem(ItemNode** itemTree, ItemNode* parent, Item itm)
{
	ItemNode* temp = NULL;
	//if tree node is empty, then create a new item and add it as head.

	if (!(*itemTree))
	{
		temp = (ItemNode*)malloc(sizeof(ItemNode));
		//initialize left and right pointers to NULL, this node is currently a leaf
		temp->left = temp->right = NULL;
		//initialize father to the one who called me.
		temp->parent = parent;

		temp->itemN = itm;

		temp->itemID = itm.id;

		*itemTree = temp;
	}
	else
	{
		if (itm.id < ((*itemTree)->itemID))
		{
			//insert into left pointer of tree, sending the pointer, father (himself) and value
			insertItem(&(*itemTree)->left, *itemTree, itm);
		}

		else if (itm.id > ((*itemTree)->itemID))
		{
			//insert into right pointer of tree, sending the pointer, father (himself) and value
			insertCustomer(&(*itemTree)->right, *itemTree, itm);
		}
	}
}

void AddIventory(ItemNode** Itemtree, ItemNode* itm)
{
	int ID,size,sum;
	printf("Which item would you like to add inventory to? \n");

	scanf("%d", &ID);

	ItemNode* ItmToUpdate = searchItem(Itemtree, ID);

	printf("Which size would you like to add inventory to? \n");
	scanf("%d", &size);

	while (size != -1)
	{
		if (30 < size < 41)
		{
			if (!ItmToUpdate->itemN.InStock)
				ItmToUpdate->itemN.InStock = true;
			printf("How much inventory you would like to add to this size?");
			scanf("%d", &sum);
			ItmToUpdate->itemN.size[(size % 30) + 1] += sum;
			ItmToUpdate->itemN.inventory+=sum;
		}

		else
		{
			printf("The size you've written is not allowed please try again");
		}

		printf("Which more size would you like to add inventory to? if there is no more size to add, press -1 \n");
		scanf("%d", &size);
	}

	
}