#include "customers.h"

void insertCustomer(CusNode** Custree, CusNode* parent, Customer cus)
{
	CusNode* temp = NULL;
	//if tree node is empty, then create a new item and add it as head.

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

void deltree(CusNode* Custree)
{
	if (Custree)
	{
		deltree(Custree->left);
		deltree(Custree->right);
		free(Custree);
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
	char newDate[10];
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

