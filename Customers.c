#include "customers.h"

void insertCustomer(CusNode** Custree, CusNode* parent, Customer cus)
{
	CusNode* temp = NULL;

	if (!(*Custree))
	{
		temp = (CusNode*)malloc(sizeof(CusNode));
		//initialize left and right pointers to NULL, this node is currently a leaf
		temp->left = temp->right = NULL;
		//initialize father to the one who called me.
		temp->parent = parent;

		temp->cus = cus;

		temp->CusID = cus.ID;

		*Custree = temp;
	}
	else
	{
		if (cus.ID < ((*Custree)->CusID))
		{
			//insert into left pointer of tree, sending the pointer, father (himself) and value
			insertCustomer(&(*Custree)->left, *Custree, cus);
		}

		else if (cus.ID > ((*Custree)->CusID))
		{
			//insert into right pointer of tree, sending the pointer, father (himself) and value
			insertCustomer(&(*Custree)->right, *Custree, cus);
		}
	}
}

void AddCustomer(CusNode** Custree, Customer cus)
{
	insertCustomer(Custree, NULL, cus);
}

void print_preorder(CusNode* Custree)
{
	if (Custree)
	{
		printf("id: %d fullname: %s %s %d \n", Custree->CusID, Custree->cus.fullName, Custree->cus.JoinDate, Custree->cus.SumOfShops);
		print_preorder(Custree->left);
		print_preorder(Custree->right);
	}

}

void print_inorder(CusNode* Custree)
{
	if (Custree)
	{
		print_inorder(Custree->left);
		printf("id: %d fullname: %s %s %d \n", Custree->CusID, Custree->cus.fullName, Custree->cus.JoinDate, Custree->cus.SumOfShops);
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
		printf("id: %d fullname: %s %s %d \n", Custree->CusID, Custree->cus.fullName,Custree->cus.JoinDate, Custree->cus.SumOfShops);
	}
}

CusNode* searchCustomer(CusNode** Custree, int ID)
{
	if (!(*Custree))
	{
		return NULL;
	}

	if (ID < (*Custree)->CusID)
	{
		searchCustomer(&((*Custree)->left), ID);
	}
	else if (ID > (*Custree)->CusID)
	{
		searchCustomer(&((*Custree)->right), ID);
	}
	else if (ID == (*Custree)->CusID)
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
			fscanf(fp, "%d %s %s %d \n", &cus.ID, &cus.fullName, &cus.JoinDate, &cus.SumOfShops);
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
		fprintf(fp, "%d %s %s %d %s\n", Custree->cus.ID, Custree->cus.fullName, Custree->cus.JoinDate, Custree->cus.SumOfShops, &Custree->cus.lastPurchaseDay);
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

