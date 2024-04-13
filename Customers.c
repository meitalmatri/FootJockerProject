#include "customers.h"

void AddCustomer(CusNode** Custree, Customer cus)
{
	insertCustomer(Custree, NULL, cus);
}

void print_preorder(CusNode* Custree)
{
	if (Custree)
	{
		printf("id: %d fullname: %s %s %d \n", Custree->cus.ID, Custree->cus.fullName, Custree->cus.JoinDate, Custree->cus.SumOfShops);
		print_preorder(Custree->left);
		print_preorder(Custree->right);
	}

}

void print_inorder(CusNode* Custree)
{
	if (Custree)
	{
		print_inorder(Custree->left);
		printf("id: %d fullname: %s %s %d \n", Custree->cus.ID, Custree->cus.fullName, Custree->cus.JoinDate, Custree->cus.SumOfShops);
		print_inorder(Custree->right);
	}

	else
		return;
}

void print_postorder(CusNode* Custree)
{
	if (Custree)
	{
		print_postorder(Custree->left);
		print_postorder(Custree->right);
		printf("id: %d fullname: %s %s %d \n", Custree->cus.ID, Custree->cus.fullName,Custree->cus.JoinDate, Custree->cus.SumOfShops);
	}
}

CusNode* searchCustomer(CusNode** Custree, int ID)
{
	if (!(*Custree))
	{
		return NULL;
	}

	if (ID < (*Custree)->cus.ID)
	{
		searchCustomer(&((*Custree)->left), ID);
	}
	else if (ID > (*Custree)->cus.ID)
	{
		searchCustomer(&((*Custree)->right), ID);
	}
	else if (ID == (*Custree)->cus.ID)
	{
		return *Custree;
	}
}

void UpdateCustomer(CusNode** Custree)
{
	int value;
	char newName[20];
	char newDate[12];
	printf("What would you like to update? \n");
	printf("For name updating press 1 \n");
	printf("For join date updating press 2 \n");
	scanf("%d", &value);

	if (value == 1)
	{
		printf("Enter new name: ");
		scanf("%s", &newName);
		strcpy(((*Custree)->cus.fullName), newName);		
	}

	if (value == 2)
	{
		printf("Enter new date: ");
		scanf("%s", &newDate);
		strcpy(((*Custree)->cus.JoinDate), newDate);
	}

	print_inorder(*Custree);
}

int load_customer_tree(CusNode** Custree)
{
	FILE* fp = NULL;
	Customer cus;
	int LastCusID;

	fp = fopen("customer.txt", "r");
	if (fp == NULL)
	{
		return 0;
	}
	else
	{
		while (!feof(fp))
		{
			fscanf(fp, "%d %s %s %d %s \n", &cus.ID, &cus.fullName, &cus.JoinDate, &cus.SumOfShops, &cus.lastPurchaseDay.Date);
			AddCustomer(Custree, cus);
			LastCusID = cus.ID;
		}
	}
	fclose(fp);

	return LastCusID;
}

void save_customer_tree(CusNode** Custree)
{
	FILE* fp = NULL;
	fp = fopen("customer.txt", "w");
	if (fp == NULL)
		printf("error uploading the file\n");
	else
	{
		cus_fprint_inorder(*Custree, fp);
	}
	fclose(fp);
}

void cus_fprint_inorder(CusNode* Custree, FILE* fp)
{
	if (Custree)
	{
		cus_fprint_inorder(Custree->left, fp);
		fprintf(fp, "%d %s %s %d ", Custree->cus.ID, Custree->cus.fullName, Custree->cus.JoinDate, Custree->cus.SumOfShops);

		if (Custree->cus.SumOfShops > 0)
		{
			fprintf(fp, "%s\n", Custree->cus.lastPurchaseDay.Date);
		}

		else
		{
			fprintf(fp, "NoPurch %\n");
		}

		cus_fprint_inorder(Custree->right, fp);
	}

	else
		return;
}

void BuyerUpdate(CusNode** Custree,int cusID, int* ItemsID, ItemNode** Itmtree)
{
	CusNode* CusToUpdate = NULL;
	ItemNode* ItemPurchased = NULL;
	char* purchaseDay[10];
	int SumOfItems = 0, i=0;

	CusToUpdate = searchCustomer(Custree, cusID);

	while (!CusToUpdate)
	{
		printf("\n\n==>Wrong ID, try again, for exit press 0\n");
		scanf("%d", &cusID);

		if (cusID == 0)
			return;

		CusToUpdate = searchCustomer(Custree, cusID);
	}

	printf("\n\n==>Enter purchase date\n");
	scanf("%s", &purchaseDay);

	strcpy(CusToUpdate->cus.lastPurchaseDay.Date, purchaseDay);

	//if (CusToUpdate->cus.lastPurchaseDay.Date)
	//{
	//	strcpy(CusToUpdate->cus.lastPurchaseDay.previous, CusToUpdate->cus.lastPurchaseDay.Date);
	//	strcpy(CusToUpdate->cus.lastPurchaseDay.Date, purchaseDay);
	//}
	//	

	//else
	//{
	//	
	//}
	//

		while(ItemsID[i] > 0)
		{
			ItemPurchased = searchItem(Itmtree, ItemsID[i]);
			CusToUpdate->cus.lastPurchaseDay.purItems[i] = ItemPurchased->itemN;
			SumOfItems++;

			ItemsID[i] = 0;

			if (i <= 2)
				i++;
		}

	CusToUpdate->cus.SumOfShops=SumOfItems;

	return;
	
}

void CusInsertbyid(CusNode** tree, CusNode* parent, Customer cus)
{
	if (!(*tree))
	{
		CusNode* temp = NULL;
		//if tree node is empty, then create a new item and add it as head.
		temp = (CusNode*)malloc(sizeof(CusNode));
		temp->left = temp->right = NULL;
		temp->parent = parent;
		temp->height = 1;
		temp->cus = cus;
		*tree = temp;

		return;
	}

	if (cus.ID < (*tree)->cus.ID)
	{
		CusInsertbyid(&(*tree)->left, *tree, cus);
	}
	else if (cus.ID > (*tree)->cus.ID)
	{
		CusInsertbyid(&(*tree)->right, *tree, cus);
	}
	(*tree)->height = 1 + max(getHeightCus((*tree)->left), getHeightCus((*tree)->right));
	int bf = getBalanceFactorCus(*tree);

	// Left Left Case  
	if (bf > 1 && (cus.ID < (*tree)->cus.ID)) {
		(*tree) = rightRotateCus(*tree);
		return;
	}
	// Right Right Case  
	if (bf < -1)
	{
		if (!(*tree)->left)
		{
			(*tree) = leftRotateCus(*tree);
			return;
		}
		else if (cus.ID > (*tree)->cus.ID)
		{
			(*tree) = leftRotateCus(*tree);
			return;
		}
	}
	// Left Right Case  
	if (bf > 1 && (cus.ID > (*tree)->cus.ID)) {
		(*tree)->left = leftRotateCus((*tree)->left);
		(*tree) = rightRotateCus(*tree);
		return;
	}
	// Right Left Case  
	if (bf < -1 && (cus.ID < (*tree)->cus.ID)) {
		(*tree)->right = rightRotateCus((*tree)->right);
		(*tree) = leftRotateCus(*tree);
		return;
	}
	return;
}

void CusInsertbyName(CusNode** tree, CusNode* parent, Customer cus)
{

	if (!(*tree))
	{
		CusNode* temp = NULL;
		//if tree node is empty, then create a new item and add it as head.
		temp = (CusNode*)malloc(sizeof(CusNode));
		temp->left = temp->right = NULL;
		temp->parent = parent;
		temp->height = 1;
		temp->cus = cus;
		*tree = temp;

		return;
	}

	if (strcmp(cus.fullName , (*tree)->cus.fullName)<0)
	{
		CusInsertbyName(&(*tree)->left, *tree, cus);
	}
	else if (strcmp(cus.fullName, (*tree)->cus.fullName) > 0)
	{
		CusInsertbyName(&(*tree)->right, *tree, cus);
	}
	(*tree)->height = 1 + max(getHeightCus((*tree)->left), getHeightCus((*tree)->right));

	int bf = getBalanceFactorCus(*tree);

	// Left Left Case  
	if (bf > 1 && (strcmp(cus.fullName, (*tree)->cus.fullName) < 0)) {
		(*tree) = rightRotateCus(*tree);
		return;
	}
	// Right Right Case  
	if (bf < -1)
	{
		if (!(*tree)->left)
		{
			(*tree) = leftRotateCus(*tree);
			return;
		}
		else if (cus.ID > (*tree)->cus.ID)
		{
			(*tree) = leftRotateCus(*tree);
			return;
		}
	}
	// Left Right Case  
	if (bf > 1 && (cus.ID > (*tree)->cus.ID)) {
		(*tree)->left = leftRotateCus((*tree)->left);
		(*tree) = rightRotateCus(*tree);
		return;
	}
	// Right Left Case  
	if (bf < -1 && (cus.ID < (*tree)->cus.ID)) {
		(*tree)->right = rightRotateCus((*tree)->right);
		(*tree) = leftRotateCus(*tree);
		return;
	}
	return;
}

void cus_print_preorder(CusNode* tree)
{
	if (tree)
	{
		print_cus(&tree->cus);
		if (tree->left)
		{
			printf("\nthe left sun of %s is\n", tree->cus.fullName);
			cus_print_preorder(tree->left);
		}

		if (tree->right)
		{
			printf("\nthe right sun of %s is\n", tree->cus.fullName);
			cus_print_preorder(tree->right);
		}
	}

}

void insertCustomer(CusNode** cusTree, CusNode* parent, Customer cus)
{
	CusInsertbyid(&cusTree[0], parent, cus);

	CusInsertbyName(&cusTree[1], parent, cus);
}

void print_cus(Customer* cus)
{
	printf("id: %d \nFull Name: %s \nJoin Date: %s \nSum Of Shops: %d \n", cus->ID, cus->fullName , cus->JoinDate, cus->SumOfShops);

	if (cus->SumOfShops > 0)
	{
		printf("Last Purchase Day : % s\n", cus->lastPurchaseDay.Date);
	}
	/*  printf("first name: %s\n", user->firstname);
	  printf("password %s\n", user->password);
	  printf("level: %d\n", user->level);*/

	/* int ID;
	char fullName[20];
	char JoinDate[10];
	int SumOfShops;
	PurchaseDay lastPurchaseDay; */

}

int getHeightCus(CusNode* custree) {
	if (custree == NULL)
		return 0;
	return custree->height;
}

CusNode* rightRotateCus(CusNode* custree) {
	CusNode* x = custree->left;
	CusNode* T2 = x->right;

	x->right = custree;
	custree->left = T2;

	x->height = max(getHeightCus(x->right), getHeightCus(x->left)) + 1;
	custree->height = max(getHeightCus(custree->right), getHeightCus(custree->left)) + 1;

	return x;
}

CusNode* leftRotateCus(CusNode* custree) {
	CusNode* y = custree->right;
	CusNode* T2 = y->left;

	y->left = custree;
	custree->right = T2;

	custree->height = max(getHeightCus(custree->right), getHeightCus(custree->left)) + 1;
	y->height = max(getHeightCus(y->right), getHeightCus(y->left)) + 1;

	return y;
}

int getBalanceFactorCus(CusNode* custree) {
	if (custree == NULL) {
		return 0;
	}
	return getHeightCus(custree->left) - getHeightCus(custree->right);
}