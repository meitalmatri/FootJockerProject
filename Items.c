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

ItemNode* min_value(ItemNode* Itm, int* height)
{
	*height = 0;

	/* loop down to find the leftmost leaf */
	while (Itm->left != NULL)
	{
		Itm = Itm->left;
		(*height)++;
	}

	return Itm;
}

ItemNode* max_value(ItemNode* Itm, int* height)
{
	*height = 0;

	/* loop down to find the rightmost leaf */
	while (Itm->right != NULL)
	{
		Itm = Itm->right;
		(*height)++;
	}

	return Itm;
}

ItemNode* removeItem(ItemNode** Itemtree, int ID)
{
	int ItmID;
	ItemNode* ItmNode;

	if(ID==NULL)
	{ 
	printf("Enter the ID of The item you want to remove");
	scanf("%d", &ItmID);
	}

	ItmNode = searchItem(Itemtree, ItmID);

		if (!ItmNode)
			return NULL;

	/*	if (data < root->data)
			root->left = delete_node(root->left, data);
		else if (data > root->data)
			root->right = delete_node(root->right, data);
		else
		{*/
			ItemNode* cursor = NULL;

			if ((ItmNode->left) && (ItmNode->right)) //2 children
			{
				int left, right;
				ItemNode* parent = NULL;
				ItemNode* cursorLeft = min_value(ItmNode->right, &left);
				ItemNode* cursorRight = max_value(ItmNode->left, &right);

				cursor = (left > right) ? cursorLeft : cursorRight;
				parent = cursor->parent;
				ItmNode->itemID = cursor->itemID;

				if (parent->left == cursor)
					parent->left = removeItem(Itemtree, cursor->itemID);
				else
					parent->right = removeItem(Itemtree, cursor->itemID);
			}

			else
			{
				if (ItmNode->left)	//only left child
				{
					cursor = ItmNode->left;
					cursor->parent = ItmNode->parent;
				}
				else if (ItmNode->right) //only right child
				{
					cursor = ItmNode->right;
					cursor->parent = ItmNode->parent;
				}
				free(ItmNode);
				ItmNode = cursor;
			}
			return(ItmNode);
}

void load_item_tree(ItemNode** tree)
{
	FILE* fp = NULL;
	int id, inventory, size[11];
	char model[20], manuf[20];
	float price;
	bool InStock;
	Item* temp_Item = (Item*)malloc(sizeof(Item));
	if (temp_Item != NULL)
	{
		fp = fopen("employee.txt", "r");
		if (fp == NULL)
			printf("error uploading the file\n");
		else
		{
			while (!feof(fp))
			{
			char model[20], manuf[20];
			fscanf(fp, "%d %s %s %f %d", temp_Item->id, &temp_Item->model, temp_Item->manuf, &temp_Item->price,&temp_Item->inventory);
			for (int i = 0; i < 11; i++)
			{
				fscanf(fp, " %d", &temp_Item->size[i]);
			}
			fscanf(fp, "\n");

			AddItem(tree, *temp_Item);
			}
		}
	fclose(fp);
	}
	else
	{
		printf("error please try agian\n");
		return;
	}
}
