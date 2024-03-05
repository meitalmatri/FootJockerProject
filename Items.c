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
	AddIventory(itemTree, itm.id);
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

void AddIventory(ItemNode** Itemtree, int itmID)
{
	int ID,size,sum;

	ItemNode* ItmToUpdate;

	if (itmID == NULL)
	{
		printf("Which item would you like to add inventory to? \n");

		scanf("%d", &ID);

		ItmToUpdate = searchItem(Itemtree, ID);
	}

	else

		ItmToUpdate = searchItem(Itemtree, itmID);

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

	printf("Inventory Sucssesful update");
	
}

void UpdateItem(ItemNode** Itemtree, int itmID)
{
	int ID, size, choose, NewPrice;
	char NewModel[20],ManuFactoryDate[20];

	ItemNode* ItmToUpdate;

	if (itmID == NULL)
	{
		printf("Which item would you like to add inventory to? \n");

		scanf("%d", &ID);

		ItmToUpdate = searchItem(Itemtree, ID);
	}

	else

		ItmToUpdate = searchItem(Itemtree, itmID);

	printf("What would you like to like on this item? \n");
	printf("If you like to update the model press 1 \n");
	printf("If you like to update the price press 2 \n");
	printf("If you like to update the manufactory date press 3 \n");
	scanf("%d", &choose);

	do 
	{
		switch (choose)
		{
		case 1:
			printf("Enter new model: \n");
			scanf("%s", &NewModel[20]);
			strcpy(NewModel, ItmToUpdate->itemN.model);

		case 2:
			printf("Enter new price");
			scanf("%s", &NewPrice);
			ItmToUpdate->itemN.price = NewPrice;

		case 3:
			printf("Enter new manufactory date");
			scanf("%s", &ManuFactoryDate);
			strcpy(ManuFactoryDate, ItmToUpdate->itemN.manuf);
		}
		
	} while (choose != -1);

	printf("Inventory Sucssesful update");

}

void removeItem(ItemNode** Itemtree)
{
	int ItmID;
	ItemNode* ItmNode;

	printf("Enter the ID of The item you want to remove");
	scanf("%d", &ItmID);

	ItmNode = searchItem(Itemtree, ItmID);

	if (ItmNode)
	{
		free(ItmNode);
	}
}