//דן ענף 308471341
//מיטל מטרי 318573367
//יוהד רמי לוי 319123378


#include "items.h"
#include "dates.h"


ItemNode* searchItemByID(ItemNode** Itemtree, int itemID)
{
	if (!(*Itemtree))
	{
		return NULL;
	}

	if (itemID < (*Itemtree)->itemID)
	{
		searchItemByID(&((*Itemtree)->left), itemID);
	}
	else if (itemID > (*Itemtree)->itemID)
	{
		searchItemByID(&((*Itemtree)->right), itemID);
	}
	else if (itemID == (*Itemtree)->itemID)
	{
		return *Itemtree;
	}
}

ItemNode* searchItemByName(ItemNode** Itmtree, char* ModelName)
{
	if (!(*Itmtree))
	{
		return NULL;
	}

	if (strcmp((*Itmtree)->itemN.model, ModelName) > 0)
	{
		searchItemByName(&((*Itmtree)->left_md), ModelName);
	}
	else if (strcmp((*Itmtree)->itemN.model, ModelName) < 0)
	{
		searchItemByName(&((*Itmtree)->right_md), ModelName);
	}
	else if (strcmp((*Itmtree)->itemN.model, ModelName) == 0)
	{
		return *Itmtree;
	}
}

void ItemReturn(ItemNode** Itemtree, int ItmToReturnID, int size, int SumToRe)
{
	ItemNode* ItmToUpdate;

	ItmToUpdate = searchItemByID(Itemtree, ItmToReturnID);

	if (ItmToUpdate->itemN.size[size % 30] > 0)
	{
		ItmToUpdate->itemN.size[size % 30] += SumToRe;
	}

	else
	{
		ItmToUpdate->itemN.size[size % 30] = SumToRe;
	}

	ItmToUpdate->itemN.inventory += SumToRe;

	if (!ItmToUpdate->itemN.InStock)
	{
		ItmToUpdate->itemN.InStock == true;
	}
}

void AddItem(ItemNode** itemTree, Item itm)
{
	ItemNode* ItemToADDInV=NULL;

	insertItem(itemTree, NULL, itm);

	ItemToADDInV= searchItemByID(itemTree, itm.id);

	AddIventory(&ItemToADDInV);

	return;
}

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
			printf("\n==>How much inventory you would like to add to this size?\n");
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
			printf("\n==>The size you've written is not allowed please try again");
		}

		printf("\n\n==>Which more size would you like to add inventory to? if there is no more size to add, press -1 \n");
		scanf("%d", &size);
	}

	*ItemNO = ItmToUpdate;
	printf("\n\n==>Inventory Sucssesful update");

	return;
	
}

void UpdateItem(ItemNode** Itemtree)
{
	int ID, size, choose, NewPrice;
	char NewModel[20],ManuFactoryDate[20];

	ItemNode* ItmToUpdate;
	system("cls");
	print_inordere(*Itemtree);
	printf("\n\n==>please enter the item ID you want to change \n");
	scanf("%d", &ID);
	ItmToUpdate = searchItemByID(Itemtree, ID);

	while (!ItmToUpdate)
	{
		system("cls");
		print_inordere(*Itemtree);
		printf("\n\n==>ID not found, please try again\n");
		printf("\n\n==>Enter ID to update\n");
		scanf("%d", &ID);
		ItmToUpdate = searchItemByID(Itemtree, ID);
	}

		do
		{
			system("cls");
			print_item(&ItmToUpdate->itemN);

			printf("\n\n What would you like to update on this item? \n");
			printf("\n\n==>If you like to update the price press 1 \n");
			printf("\n\n==>If you like to update the manufactory date press 2 \n");
			printf("\n\n==>If you like to update the inventory press 3 \n");
			scanf("%d", &choose);

			switch (choose)
			{
			case 1:
				printf("Enter new price\n");
				scanf("%d", &NewPrice);
				ItmToUpdate->itemN.price = NewPrice;
				break;

			case 2:
				printf("Enter new manufactory date\n");
				scanf("%s", ManuFactoryDate);
				strcpy(ItmToUpdate->itemN.manuf, ManuFactoryDate);
				break;

			case 3:
				system("cls");
				AddIventory(&ItmToUpdate);
				break;
			}
			printf("\n\n==>To continue update please press 1, for exit please press 0\n\n");
			scanf("%d", &choose);
		} while (choose != 0);

		system("cls");
		printf("Inventory Sucssesful update\n");
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

int load_items_tree(ItemNode** ItmTree)
{
	FILE* fp = NULL;
	Item itm;
	int LastItmID,size,inv;
	char inStock[15], word[12];

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
			sizeZero(&itm);
			if (itm.inventory> 0)
			{
				itm.InStock = true;

				fscanf(fp, "%s", &word);

				while (strcmp(word, "size") == 0)
				{
					fscanf(fp, "%d %s %d", &size, &word, &inv);
					itm.size[size % 30] = inv;

					fscanf(fp, "%s \n", &word);
				}
			
			}
			else
			{
				itm.InStock = false;
				fscanf(fp, "%s \n", &word);
			}

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
		fprintf(fp, "%d %s %s %.0f %d ", ItmTree->itemN.id, ItmTree->itemN.model, ItmTree->itemN.manuf, ItmTree->itemN.price, ItmTree->itemN.inventory);

		if (ItmTree->itemN.InStock)
		{

			for (int i=0; i <= 10; i++)
			{
				if (ItmTree->itemN.size[i]>0)
				{
					fprintf(fp, "size %d inv %d ", (i + 30), ItmTree->itemN.size[i]);
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

Item SellByID(ItemNode** ItmTree, int ID, int size, int sumToPur)
{
	ItemNode* ItmToSell = NULL;
	ItmToSell = searchItemByID(ItmTree, ID);
	ItmToSell->itemN.size[size % 30] -= sumToPur;
	ItmToSell->itemN.inventory -= sumToPur;
	if (ItmToSell->itemN.inventory == 0)
	{
		ItmToSell->itemN.InStock = false;
	}
	return ItmToSell->itemN;
	
}

int AbleToSell(ItemNode** ItmTree, int ID, int size, int sumToPur)
{
	ItemNode* ItmToSell = NULL;
	ItmToSell = searchItemByID(ItmTree, ID);

	if (ItmToSell->itemN.InStock)
	{
		if (size < 31 && size>40)
		{
			printf("\n\n==>This size isn't available,please try again later\n");

			return 0;
		}

		if (ItmToSell->itemN.size[size % 30] >= sumToPur)
		{
			return 1;
		}

		else
		{

			printf("\n\n==>This size isn't available,please try again later\n");

			return 0;
		}
	}

	else
	{

		printf("This Item isn't available,please try again later\n");
		//printf("\n\n==>There is not enough inventory for that purchase");

		return 0;
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
	if(user!=NULL)
	printf("id:%d inventory:%d manuf:%s model:%s price:%.2f\n", user->id, user->inventory, user->manuf,user->model,user->price);
	/*  printf("first name: %s\n", user->firstname);
	  printf("password %s\n", user->password);
	  printf("level: %d\n", user->level);*/
}

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
		print_item(tree);
		printf("did you mean these item?\npress Y if yes or N if no\n");
		int c;
		while ((c = getchar()) != '\n' && c != EOF) {}
		scanf("%c", &ans);
		if ('Y' == ans || 'y' == ans)
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

ItemNode* search_manuf(ItemNode* tree, char* date)
{
	if (!tree)
		return NULL;
	int searchDate;
	searchDate = dateCmp(date,tree->itemN.manuf);

	if (searchDate == 0)
	{
		char ans = NULL;
		print_item(tree);
		printf("did you mean these item?\npress Y if yes or N if no\n");
		int c;
		while ((c = getchar()) != '\n' && c != EOF) {}
		scanf("%c", &ans);
		if ('Y' == ans || 'y' == ans)
			return tree;
		search_manuf(tree->left_mf, date);
		search_manuf(tree->right_mf, date);
	}
	else if (searchDate < 0)
		search_manuf(tree->left_mf, date);
	else
		search_manuf(tree->right_mf, date);
}

ItemNode* search_price(ItemNode* tree, float price)
{
	if (!tree)
		return NULL;
	float cmpPrice;
	cmpPrice = (tree->itemN.price) - price;

	if (cmpPrice == 0)
	{
		char ans = NULL;
		print_item(tree);
		printf("did you mean these item?\npress Y if yes or N if no\n");
		int c;
		while ((c = getchar()) != '\n' && c != EOF) {}
		scanf("%c", &ans);
		if ('Y' == ans || 'y' == ans)
			return tree;
		search_price(tree->left_pr, price);
		search_price(tree->right_pr, price);
	}
	else if (cmpPrice > 0)
		search_price(tree->left_pr, price);
	else
		search_price(tree->right_pr, price);
}

void print_inorderPrice(ItemNode* tree,float min,float max)
{
	if (tree)
	{	
		print_inorderPrice(tree->left_pr,min,max);
		if (((tree->itemN.price > min) && (tree->itemN.price < max)) || (min == tree->itemN.price))
			print_item(&tree->itemN);
		print_inorderPrice(tree->right_pr, min, max);
	}

}

void print_inorderdate(ItemNode* tree, char* min,char* max)
{
	if (tree)
	{
		print_inorderdate(tree->left_mf, min, max);
		if (((dateCmp(tree->itemN.manuf, min) > 0) && (dateCmp(tree->itemN.manuf, max) < 0)) || ((0 == dateCmp(min, tree->itemN.manuf)) && (0 == dateCmp(max, "00/00/0000"))))
			print_item(&tree->itemN);
		print_inorderdate(tree->right_mf, min, max);
	}

}

void print_inorderInStoke(ItemNode* tree)
{
	if (tree)
	{
		print_inorderInStoke(tree->left);
		if (tree->itemN.InStock)
			print_item(&tree->itemN);
		print_inorderInStoke(tree->right);
	}

}

void print_inordere(ItemNode* tree)
{
	if (tree)
	{
		print_inordere(tree->left);
		print_item(&tree->itemN);
		print_inordere(tree->right);
	}

}

void removeItem(ItemNode** Itemtree, int ID)
{
	ItemNode* itemremov; 
	itemremov = searchItemByID(Itemtree, ID);

	while (!itemremov)
	{
		printf("\n\n==>ID not found, please try again\n");
		printf("\n\n==>Enter ID to remove\n");
		scanf("%d", &ID);
		itemremov = searchItemByID(Itemtree, ID);
	}

	itemremov->itemN.InStock = false;
	itemremov->itemN.inventory = 0;
	for (int i = 0; i < 11; i++)
		itemremov->itemN.size[i] = 0;
}

void freeItemTree(ItemNode* tree)
{
	if (tree)
		return;
	freeItemTree(tree->left);
	freeItemTree(tree->right);
	free(tree);
}

void printSize(ItemNode** Itemtree, int ID)
{
	ItemNode* temp;
	temp = searchItemByID(Itemtree, ID);
	printf("\nsize:inventory\n");
	for (int i = 0; i < 11; i++)
	{
		if (temp->itemN.size[i] != 0)
			printf("%d:%d  ", i + 30, temp->itemN.size[i]);
	}
}

void sizeZero(Item* itm)
{
	for (int i = 0; i < 11; i++)
		itm->size[i] = 0;
}

void mallocPurchasedItms(ItemPur** PurchasedItms)
{
	PurchasedItms[0] = (ItemPur*)malloc(sizeof(ItemPur));
	PurchasedItms[1] = (ItemPur*)malloc(sizeof(ItemPur));
	PurchasedItms[2] = (ItemPur*)malloc(sizeof(ItemPur));
}

void freePurchasedItms(ItemPur** PurchasedItms)
{
	free(PurchasedItms[0]);
	free(PurchasedItms[1]);
	free(PurchasedItms[2]);
}