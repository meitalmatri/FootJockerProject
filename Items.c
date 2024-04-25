#include "items.h"
#include "dates.h"


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
	ItemNode* ItemToADDInV=NULL;

	insertItem(itemTree, NULL, itm);

	ItemToADDInV= searchItem(itemTree, itm.id);

	AddIventory(&ItemToADDInV);

	return;
}

//void insertItem(ItemNode** itemTree, ItemNode* parent, Item itm)
//{
//	ItemNode* temp = NULL;
//	//if tree node is empty, then create a new item and add it as head.
//
//	if (!(*itemTree))
//	{
//		temp = (ItemNode*)malloc(sizeof(ItemNode));
//		//initialize left and right pointers to NULL, this node is currently a leaf
//		temp->left = temp->right = NULL;
//		//initialize father to the one who called me.
//		temp->parent = parent;
//
//		temp->itemN = itm;
//
//		temp->itemID = itm.id;
//
//		*itemTree = temp;
//	}
//	else
//	{
//		if (itm.id < ((*itemTree)->itemID))
//		{
//			//insert into left pointer of tree, sending the pointer, father (himself) and value
//			insertItem(&(*itemTree)->left, *itemTree, itm);
//		}
//
//		else if (itm.id > ((*itemTree)->itemID))
//		{
//			//insert into right pointer of tree, sending the pointer, father (himself) and value
//			insertItem(&(*itemTree)->right, *itemTree, itm);
//		}
//	}
//}

void AddIventory(ItemNode** ItemNO)
{
	int ID,size,sum;

	ItemNode* ItmToUpdate;

	ItmToUpdate = *ItemNO;

	printf("\n\n==>Which size would you like to add inventory to? \n");
	scanf("%d", &size);

	while (size != -1)
	{
		if (30 < size && size < 41)
		{
			if (ItmToUpdate->itemN.InStock==false)
				ItmToUpdate->itemN.InStock = true;
			printf("\n\n==>How much inventory you would like to add to this size?");
			scanf("%d", &sum);

			if (ItmToUpdate->itemN.size[(size % 30)] >= 0)
				ItmToUpdate->itemN.size[(size % 30)] += sum;

			else
				ItmToUpdate->itemN.size[(size % 30)] = sum;


			if (ItmToUpdate->itemN.inventory ==NULL)
			{
				ItmToUpdate->itemN.inventory = sum;
			}
				

			else
			{
				ItmToUpdate->itemN.inventory += sum;
			}
		}

		else
		{
			printf("\n\n==>The size you've written is not allowed please try again");
		}

		printf("\n\n==>Which more size would you like to add inventory to? if there is no more size to add, press -1 \n");
		scanf("%d", &size);
	}

	*ItemNO = ItmToUpdate;
	printf("\n\n==>Inventory Sucssesful update");

	return;
	
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

//void load_item_tree(ItemNode** tree)
//{
//	FILE* fp = NULL;
//	int id, inventory, size[11];
//	char model[20], manuf[20];
//	float price;
//	bool InStock;
//	Item* temp_Item = (Item*)malloc(sizeof(Item));
//	if (temp_Item != NULL)
//	{
//		fp = fopen("employee.txt", "r");
//		if (fp == NULL)
//			printf("error uploading the file\n");
//		else
//		{
//			while (!feof(fp))
//			{
//			char model[20], manuf[20];
//			fscanf(fp, "%d %s %s %f %d", temp_Item->id, &temp_Item->model, temp_Item->manuf, &temp_Item->price,&temp_Item->inventory);
//			for (int i = 0; i < 11; i++)
//			{
//				fscanf(fp, " %d", &temp_Item->size[i]);
//			}
//			fscanf(fp, "\n");
//
//			AddItem(tree, *temp_Item);
//			}
//		}
//	fclose(fp);
//	}
//	else
//	{
//		printf("error please try agian\n");
//		return;
//	}
//}

int load_items_tree(ItemNode** ItmTree)
{
	FILE* fp = NULL;
	Item itm;
	int LastItmID,size,inv;
	char inStock[15], word[10];

	fp = fopen("Items.txt", "r");
	if (fp == NULL)
	{
		return 0;
	}
	else
	{
		while (!feof(fp))
		{
			fscanf(fp, "%d %s %s  %f %d ", &itm.id, &itm.model, &itm.manuf, &itm.price, &itm.inventory);

			if (itm.inventory> 0)
			{
				itm.InStock == true;

				fscanf(fp, "%s", &word);

				while (strcmp(word, "size") == 0)
				{
					fscanf(fp, "%d %s %d", &size, &word, &inv);
					itm.size[size % 30] = inv;

					fscanf(fp, "%s \n", &word);
				}
			
			}
			else
				itm.InStock == false;

			insertItem(ItmTree, NULL, itm);

			LastItmID = itm.id;
		}
	}

	fclose(fp);

	return LastItmID;
}
	

void save_items_tree(ItemNode** ItmTree)
{
	FILE* fp = NULL;
	fp = fopen("Items.txt", "w");
	if (fp == NULL)
		printf("error uploading the file\n");
	else
	{
		item_fprint_inorder(*ItmTree, fp);
	}
	fclose(fp);
}

void item_fprint_inorder(ItemNode* ItmTree, FILE* fp)
{
	if (ItmTree)
	{
		item_fprint_inorder(ItmTree->left, fp);
		fprintf(fp, "%d %s %s %.0f %d", ItmTree->itemN.id, ItmTree->itemN.model, ItmTree->itemN.manuf, ItmTree->itemN.price, ItmTree->itemN.inventory);

		if (ItmTree->itemN.InStock)
		{

			for (int i=0; i <= 10; i++)
			{
				if (ItmTree->itemN.size[i]>0)
				{
					fprintf(fp, " size %d inv %d ", (i + 30), ItmTree->itemN.size[i]);
				}
			}

			fprintf(fp, "InStock\n");
		}
		else
			fprintf(fp, "NotInStock\n");

		item_fprint_inorder(ItmTree->right, fp);
	}

	else
		return;
}

int SellByID(ItemNode** ItmTree, int ID)
{
	int sum,size, CusID;
	ItemNode* ItmToSell = NULL;
	ItmToSell = searchItem(ItmTree, ID);

	if (ItmToSell->itemN.InStock)
	{
		printf("\n\n==>Enter the size of the item you want to sell\n");
		scanf("%d", &size);

		while (size<31 && size>40)
		{
			printf("This size isn't available, try again\n");
		}

		printf("\n\n==>Enter the sum of the item you want to sell\n");
		scanf("%d", &sum);
		

		if (ItmToSell->itemN.size[size % 30] >= sum)
		{
			ItmToSell->itemN.size[size % 30] -= sum;
			ItmToSell->itemN.inventory -= sum;
			return 1;
		}

		else
		{
			printf("\n\n==>There is not enough inventory for that purchase, try again later");
			return 0;
		}
	}

}


void insertItem(ItemNode** itemTree, ItemNode* parent, Item itm)
{
	ItemNode* temp = NULL;
	//if tree node is empty, then create a new item and add it as head.
	temp = (ItemNode*)malloc(sizeof(ItemNode));
	insertbyid(&itemTree[0], parent, &itm, temp);
	insertbypr(&itemTree[1], parent, &itm, temp);
	insertbymf(&itemTree[2], parent, &itm, temp);
	insertbymd(&itemTree[3], parent, &itm, temp);

}

void insertbyid(ItemNode** tree, ItemNode* parent, Item* itm, ItemNode* temp)
{
	if (!(*tree))
	{
		temp->left = temp->right = NULL;
		temp->parent = parent;
		temp->height = 1;
		temp->itemN = *itm;
		temp->itemID = itm->id;
		*tree = temp;
		return;
	}

	if (itm->id < (*tree)->itemN.id)
	{
		insertbyid(&(*tree)->left, *tree, itm, temp);
	}
	else if (itm->id > (*tree)->itemN.id)
	{
		insertbyid(&(*tree)->right, *tree, itm, temp);
	}
	(*tree)->height = 1 + max(getHeight1((*tree)->left), getHeight1((*tree)->right));
	int bf = getBalanceFactor1(*tree);

	// Left Left Case  
	if (bf > 1 && (itm->id < (*tree)->itemN.id)) {
		(*tree) = rightRotate1(*tree);
		return;
	}
	// Right Right Case  
	if (bf < -1)
	{
		if (!(*tree)->left)
		{
			(*tree) = leftRotate1(*tree);
			return;
		}
		else if (itm->id > (*tree)->itemN.id)
		{
			(*tree) = leftRotate1(*tree);
			return;
		}
	}
	// Left Right Case  
	if (bf > 1 && (itm->id > (*tree)->itemN.id)) {
		(*tree)->left = leftRotate1((*tree)->left);
		(*tree) = rightRotate1(*tree);
		return;
	}
	// Right Left Case  
	if (bf < -1 && (itm->id < (*tree)->itemN.id)) {
		(*tree)->right = rightRotate1((*tree)->right);
		(*tree) = leftRotate1(*tree);
		return;
	}
	return;
}

void insertbypr(ItemNode** tree, ItemNode* parent, Item* itm, ItemNode* temp)
{
	if (!(*tree))
	{
		temp->left_pr = temp->right_pr = NULL;
		temp->parent_pr = parent;
		temp->height_pr = 1;
		temp->itemN = *itm;
		*tree = temp;
		return;
	}

	if (itm->price < (*tree)->itemN.price)
	{
		insertbypr(&(*tree)->left_pr, *tree, itm, temp);
	}
	else if (itm->price > (*tree)->itemN.price)
	{
		insertbypr(&(*tree)->right_pr, *tree, itm, temp);
	}
	else
		if (itm->id < (*tree)->itemN.id)
		{
			insertbypr(&(*tree)->left_pr, *tree, itm, temp);
		}
		else if (itm->id > (*tree)->itemN.id)
		{
			insertbypr(&(*tree)->right_pr, *tree, itm, temp);
		}
	(*tree)->height_pr = 1 + max(getHeightpr((*tree)->left_pr), getHeightpr((*tree)->right_pr));
	int bf = getBalanceFactorpr(*tree);

	// Left Left Case  
	if (bf > 1 && (itm->price < (*tree)->itemN.price)) {
		(*tree) = rightRotatepr(*tree);
		return;
	}
	// Right Right Case  
	if (bf < -1)
	{
		if (!(*tree)->left_pr)
		{
			(*tree) = leftRotatepr(*tree);
			return;
		}
		else if (itm->price > (*tree)->itemN.price)
		{
			(*tree) = leftRotatepr(*tree);
			return;
		}
	}
	// Left Right Case  
	if (bf > 1 && (itm->price > (*tree)->itemN.price)) {
		(*tree)->left_pr = leftRotatepr((*tree)->left_pr);
		(*tree) = rightRotatepr(*tree);
		return;
	}
	// Right Left Case  
	if (bf < -1 && (itm->price < (*tree)->itemN.price)) {
		(*tree)->right_pr = rightRotatepr((*tree)->right_pr);
		(*tree) = leftRotatepr(*tree);
		return;
	}
	return;
}

void insertbymd(ItemNode** tree, ItemNode* parent, Item* itm, ItemNode* temp)
{
	if (!(*tree))
	{
		temp->left_md = temp->right_md = NULL;
		temp->parent_md = parent;
		temp->height_md = 1;
		temp->itemN = *itm;
		*tree = temp;
		return;
	}

	if (strcmp(itm->model , (*tree)->itemN.model)<0)
	{
		insertbymd(&(*tree)->left_md, *tree, itm, temp);
	}
	else if (strcmp(itm->model, (*tree)->itemN.model) > 0)
	{
		insertbymd(&(*tree)->right_md, *tree, itm, temp);
	}
	(*tree)->height_md = 1 + max(getHeight1((*tree)->left_md), getHeight1((*tree)->right_md));
	int bf = getBalanceFactor1(*tree);

	// Left Left Case  
	if (bf > 1 && strcmp(itm->model, (*tree)->itemN.model)<0) 
	{
		(*tree) = rightRotate1(*tree);
		return;
	}
	// Right Right Case  
	if (bf < -1)
	{
		if (!(*tree)->left_md)
		{
			(*tree) = leftRotate1(*tree);
			return;
		}
		else if (strcmp(itm->model, (*tree)->itemN.model) > 0)
		{
			(*tree) = leftRotate1(*tree);
			return;
		}
	}
	// Left Right Case  
	if (bf > 1 && strcmp(itm->model, (*tree)->itemN.model) > 0)
	{
		(*tree)->left_md = leftRotate1((*tree)->left_md);
		(*tree) = rightRotate1(*tree);
		return;
	}
	// Right Left Case  
	if (bf < -1 && strcmp(itm->model, (*tree)->itemN.model )< 0)
	{
		(*tree)->right_md = rightRotate1((*tree)->right_md);
		(*tree) = leftRotate1(*tree);
		return;
	}
	return;
}

void insertbymf(ItemNode** tree, ItemNode* parent, Item* itm, ItemNode* temp)
{
	if (!(*tree))
	{
		temp->left_mf = temp->right_mf = NULL;
		temp->parent_mf = parent;
		temp->height_mf = 1;
		temp->itemN = *itm;
		*tree = temp;
		return;
	}

	if (dateCmp(itm->manuf, (*tree)->itemN.manuf) < 0)
	{
		insertbymf(&(*tree)->left_mf, *tree, itm, temp);
	}
	else if (dateCmp(itm->manuf, (*tree)->itemN.manuf) > 0)
	{
		insertbymf(&(*tree)->right_mf, *tree, itm, temp);
	}
	(*tree)->height_mf = 1 + max(getHeightmf((*tree)->left_mf), getHeightmf((*tree)->right_mf));
	int bf = getBalanceFactormf(*tree);

	// Left Left Case  
	if (bf > 1 && dateCmp(itm->manuf, (*tree)->itemN.manuf) < 0)
	{
		(*tree) = rightRotatemf(*tree);
		return;
	}
	// Right Right Case  
	if (bf < -1)
	{
		if (!(*tree)->left_mf)
		{
			(*tree) = leftRotatemf(*tree);
			return;
		}
		else if (dateCmp(itm->manuf, (*tree)->itemN.manuf) > 0)
		{
			(*tree) = leftRotatemf(*tree);
			return;
		}
	}
	// Left Right Case  
	if (bf > 1 && dateCmp(itm->manuf, (*tree)->itemN.manuf) > 0)
	{
		(*tree)->left_mf = leftRotatemf((*tree)->left_mf);
		(*tree) = rightRotatemf(*tree);
		return;
	}
	// Right Left Case  
	if (bf < -1 && dateCmp(itm->manuf, (*tree)->itemN.manuf) < 0)
	{
		(*tree)->right_mf = rightRotatemf((*tree)->right_mf);
		(*tree) = leftRotatemf(*tree);
		return;
	}
	return;
}

int getHeight1(ItemNode* n) {
	if (n == NULL)
		return 0;
	return n->height;
}

ItemNode* rightRotate1(ItemNode* y) {
	ItemNode* x = y->left;
	ItemNode* T2 = x->right;

	x->right = y;
	y->left = T2;

	x->height = max(getHeight1(x->right), getHeight1(x->left)) + 1;
	y->height = max(getHeight1(y->right), getHeight1(y->left)) + 1;

	return x;
}

ItemNode* leftRotate1(ItemNode* x) {
	ItemNode* y = x->right;
	ItemNode* T2 = y->left;

	y->left = x;
	x->right = T2;

	x->height = max(getHeight1(x->right), getHeight1(x->left)) + 1;
	y->height = max(getHeight1(y->right), getHeight1(y->left)) + 1;

	return y;
}

int getBalanceFactor1(ItemNode* n) {
	if (n == NULL) {
		return 0;
	}
	return getHeight1(n->left) - getHeight1(n->right);
}

void print_preorder1(ItemNode* tree)
{
	if (tree)
	{
		print_item(&tree->itemN);
		printf("\nthe left sun of %d is\n", tree->itemN.id);
		print_preorder1(tree->left_pr);
		printf("\nthe right sun of %d is\n", tree->itemN.id);
		print_preorder1(tree->right_pr);
	}

}

void print_item(Item* user)
{
	printf("id:%d inventory:%d manuf:%s model:%s price:%f\n", user->id, user->inventory, user->manuf,user->model,user->price);
	/*  printf("first name: %s\n", user->firstname);
	  printf("password %s\n", user->password);
	  printf("level: %d\n", user->level);*/
}

/*ItemNode* searchItem(ItemNode** Itemtree, Item itemID)
{
	if (!(*Itemtree))
	{
		return NULL;
	}

	if (itemID.id < (*Itemtree)->itemN.id)
	{
		searchItem(&((*Itemtree)->left), itemID);
	}
	else if (itemID.id > (*Itemtree)->itemN.id)
	{
		searchItem(&((*Itemtree)->right), itemID);
	}
	else if (itemID.id == (*Itemtree)->itemN.id)
	{
		return *Itemtree;
	}
}*/

int getHeightpr(ItemNode* n) {
	if (n == NULL)
		return 0;
	return n->height_pr;
}

ItemNode* rightRotatepr(ItemNode* y) {
	ItemNode* x = y->left_pr;
	ItemNode* T2 = x->right_pr;

	x->right_pr = y;
	y->left_pr = T2;

	x->height_pr = max(getHeightpr(x->right_pr), getHeightpr(x->left_pr)) + 1;
	y->height_pr = max(getHeightpr(y->right_pr), getHeightpr(y->left_pr)) + 1;

	return x;
}

ItemNode* leftRotatepr(ItemNode* x) {
	ItemNode* y = x->right_pr;
	ItemNode* T2 = y->left_pr;

	y->left_pr = x;
	x->right_pr = T2;

	x->height_pr = max(getHeightpr(x->right_pr), getHeightpr(x->left_pr)) + 1;
	y->height_pr = max(getHeightpr(y->right_pr), getHeightpr(y->left_pr)) + 1;

	return y;
}

int getBalanceFactorpr(ItemNode* n) {
	if (n == NULL) {
		return 0;
	}
	return getHeightpr(n->left_pr) - getHeightpr(n->right_pr);
}

int getHeightmf(ItemNode* n) {
	if (n == NULL)
		return 0;
	return n->height_mf;
}

ItemNode* rightRotatemf(ItemNode* y) {
	ItemNode* x = y->left_mf;
	ItemNode* T2 = x->right_mf;

	x->right_mf = y;
	y->left_mf = T2;

	x->height_mf = max(getHeightmf(x->right_mf), getHeightmf(x->left_mf)) + 1;
	y->height_mf = max(getHeightmf(y->right_mf), getHeightmf(y->left_mf)) + 1;

	return x;
}

ItemNode* leftRotatemf(ItemNode* x) {
	ItemNode* y = x->right_mf;
	ItemNode* T2 = y->left_mf;

	y->left_mf = x;
	x->right_mf = T2;

	x->height_mf = max(getHeightmf(x->right_mf), getHeightmf(x->left_mf)) + 1;
	y->height_mf = max(getHeightmf(y->right_mf), getHeightmf(y->left_mf)) + 1;

	return y;
}

int getBalanceFactormf(ItemNode* n) {
	if (n == NULL) {
		return 0;
	}
	return getHeightmf(n->left_mf) - getHeightmf(n->right_mf);
}

int getHeightmd(ItemNode* n) {
	if (n == NULL)
		return 0;
	return n->height_md;
}

ItemNode* rightRotatemd(ItemNode* y) {
	ItemNode* x = y->left_md;
	ItemNode* T2 = x->right_md;

	x->right_md = y;
	y->left_md = T2;

	x->height_md = max(getHeightmd(x->right_md), getHeightmd(x->left_md)) + 1;
	y->height_md = max(getHeightmd(y->right_md), getHeightmd(y->left_md)) + 1;

	return x;
}

ItemNode* leftRotatemd(ItemNode* x) {
	ItemNode* y = x->right_md;
	ItemNode* T2 = y->left_md;

	y->left_md = x;
	x->right_md = T2;

	x->height_md = max(getHeightmd(x->right_md), getHeightmd(x->left_md)) + 1;
	y->height_md = max(getHeightmd(y->right_md), getHeightmd(y->left_md)) + 1;

	return y;
}

int getBalanceFactormd(ItemNode* n) {
	if (n == NULL) {
		return 0;
	}
	return getHeightmd(n->left_md) - getHeightmd(n->right_md);
}

ItemNode* search_model(ItemNode* tree, char* word)
{
	if (!tree)
		return NULL;
	int startwith;
	startwith=strstartswith(tree->itemN.model, word);

	if (startwith == 0)
	{
		char ans=NULL;
		printf("did you mean %s?\npress Y if yes or N if no\n", tree->itemN.model);
		int c;
		while ((c = getchar()) != '\n' && c != EOF) {}
		scanf("%c", &ans);
		if ('Y' == ans)
			return tree;
		search_model(tree->left_md, word);
		search_model(tree->right_md, word);
	}
	else if(startwith < 0)
		search_model(tree->left_md, word);
	else
		search_model(tree->right_md, word);
}

int strstartswith(const char* str, const char* prefix) {
	if (!str || !prefix) {
		return 0;  // Return false if any string is NULL
	}
	size_t len_prefix = strlen(prefix);
	size_t len_str = strlen(str);
	if (len_prefix > len_str) {
		return 0;  // Return false if prefix is longer than str
	}
	return strncmp(str, prefix, len_prefix);  // Compare and return the result
}