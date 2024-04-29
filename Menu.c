#include "menu.h"
#include"log.h"


int printMenu(unsigned int employeeLevel)
{
	int choice;

	printf("\n============> FootJockerMenue <============\n");
	printf("Choose your operation:\n\n");
	printf("1.ITEM SEARCHING \n");
	printf("2.ADD ITEM \n");
	printf("3.ADD CUSTOMER  \n");

	if (!(employeeLevel > 2))
	{
		printf("4.PURCHASE SCREEN\n");
		printf("5.REMOVE ITEM \n");
		printf("6.UPDATE ITEM \n");
		printf("7.UPDATE CUSTOMER \n");
		printf("8.RETURN ITEM\n");
	}

	if (!(employeeLevel>1))
	{
		printf("9.ADD EMPLOYEE \n");
		printf("10.UPDATE EMPLOYEE LEVEL \n");
	}

	printf("Your Choice:");

	scanf("%d", &choice);

	while ((choice > 3 && employeeLevel == 3) || (choice > 8 && employeeLevel > 1))
	{
		printf("\n\n==>Choice is not on the list, maybe you dont have the promission for that choice!");
		printf("\n\n==>Please try again-");
		scanf("%d", &choice);
	}
	return choice;
}

void searceMenu(ItemNode** tree)
{
	int tempId, value;
	float minpr=0, maxpr=0;
	char minda[11], maxda[11], tempdate[11];
	system("cls");
	do
	{
		printf("\n\n==>please enter by what you would like to do the item serching by:\n");
		printf("     1 id\n     2 date\n     3 date range\n     4 price\n     5 price range\n     6 in stoked\n     0 exit\n");
		scanf("%d", &value);
		system("cls");
		switch (value)
		{
		case 1:
			printf("\n\n==>you chose to search by id\nplease enter id:");
			scanf("%d", &tempId);
			system("cls");
			print_item(searchItemByID(&tree[0], tempId));
			break;
		case 2:
			printf("\n\n==>you chose to search by date\nplease enter a date (dd/mm/yyyy):");
			scanf("%s", tempdate);
			system("cls");
			print_inorderdate(tree[2], tempdate, "00/00/0000");
			break;
		case 3:
			printf("\n\n==>you chose to search by date range\nplease enter the min date (dd/mm/yyyy):\n");
			scanf("%s", minda);
			printf("\n\n==>please enter the max date (dd/mm/yyyy):\n");
			scanf("%s", maxda);
			system("cls");
			print_inorderdate(tree[2], minda, maxda);
			break;
		case 4:
			printf("\n\n==>you chose to search by price\nplease enter a price:\n");
			scanf("%f", &minpr);
			system("cls");
			print_inorderPrice(tree[1], minpr, 0);
			break;
		case 5:
			printf("\n\n==>you chose to search by price range\nplease enter the min price:\n");
			scanf("%f", &minpr);
			printf("\n\n==>please enter the max price:\n");
			scanf("%f", &maxpr);
			system("cls");
			print_inorderPrice(tree[1], minpr, maxpr);
			break;
		case 6:
			printf("\n\n==>you chose to search by price in stoked\n");
			print_inorderInStoke(tree[0]);
			break;
		case 0:
			break;
		}
	}while (value != 0);
}

void addItemMenu(ItemNode** tree, int* LastItemID)
{
	Item NewItem;

	system("cls");
	*LastItemID= *LastItemID+1;
	NewItem.id = *LastItemID;
	NewItem.inventory = NULL;
	printf("\n\n==>Enter the model of the item you to add:");
	scanf("%s", &NewItem.model);
	printf("\n\n==>Enter manufactory date:");
	scanf("%s", &NewItem.manuf);
	printf("\n\n==>Enter price:");
	scanf("%f", &NewItem.price);
	AddItem(tree, NewItem);
}

void addCusMenu(CusNode** CusTree, int* LastCustomerID)
{
	Customer NewCus;

	system("cls");
	*LastCustomerID = *LastCustomerID + 1;
	NewCus.ID = *LastCustomerID;
	printf("\n\n==>Enter the name of the customer you want to add:\n");
	scanf("%s", &NewCus.fullName);
	strcpy(NewCus.JoinDate, getCurrentDate());
	NewCus.SumOfShops = 0;
	//strcpy(NewCus.lastPurchaseDay->Date, "NoPurch");
	NewCus.lastPurchaseDay = NULL;
	AddCustomer(CusTree, NewCus);
	printf("\n\nthe costumer you added is:\n");
	print_cus(&NewCus);
	//cus_print_preorder(CusTree[0]);

}

void addEnpMenu(Employee_node** tree)
{
	add_new_employee(tree);
	system("cls");
	printf("the employee was secssfully added\n");
}

void removeItemMenu(ItemNode** tree)
{
	int ID;

	system("cls");
	printf(" ==> Enter items in stoke are: \n");
	print_inorderInStoke(tree[0]);
	printf("\n\n ==> Enter the ID of the Item you want to remove : \n");
	scanf("%d", &ID);
	removeItem(tree, ID);
	system("cls");
	printf(" the item secssfuly removed\n\n ==> the items in stoke are: \n");
	print_inorderInStoke(tree[0]);

}

void returnItemMenu(ItemNode** ItemTree, CusNode** CusTree)
{
	int des = 1, ItmToReturnID, size, CustomerID, SumToRe, AbleToRe;

	while (des == 1)
	{
		system("cls");
		printf("\n\n==>Enter The ID of the item you want to return\n");
		scanf("%d", &ItmToReturnID);

		printf("\n\n==>Enter The size of the item you want to return\n");
		scanf("%d", &size);

		printf("\n\n==>Enter the ID of the customer who want to return that item\n");
		scanf("%d", &CustomerID);

		printf("\n\n==>Enter the sum of the item you want to return\n");
		scanf("%d", &SumToRe);

		AbleToRe = AbleToReturn(CusTree, CustomerID, ItmToReturnID, size, SumToRe);

		if (AbleToRe)
		{
			ItemReturn(ItemTree, ItmToReturnID, size, SumToRe);

			printf("\n\n==>Item return succeed\nIf you want return another Item press 1, else press 0\n");
			scanf("%d", &des);

		}

		else
		{
			printf("\n\n==>If you want to try again press 1, else press 0\n");
			scanf("%d", &des);

		}
	}
}

void updateCusMenu(CusNode** CusTree)
{
	int UpdateChoice, CustomerID;
	char customerName[15];
	CusNode* CusForUpdate = NULL;

	system("cls");
	printf("\n\n==>If you want to update customer by name please press 0 for ID press 1\n");
	scanf("%d", &UpdateChoice);

	if (UpdateChoice == 0)
	{
		printf("\n\n==>Enter the name of the customer you to update:");
		scanf("%s", &customerName);
		CusForUpdate = searchCustomerByName(&CusTree[1], &customerName);

		if (CusForUpdate == NULL)
		{
			printf("\n\n==>Name not found, please try again \n");
			printf("\n\n==>Enter the Name of the customer you to update:");
			scanf("%s", &customerName);
			CusForUpdate = searchCustomerByName(&CusTree[1], &customerName);

			if (CusForUpdate == NULL)
			{
				printf("\n\n==>Name not found, please try again later");
				return;
			}
		}

	}

	else
	{
		printf("\n\n==>Enter the ID of the customer you to update:");
		scanf("%d", &CustomerID);
		CusForUpdate = searchCustomerByID(&CusTree[0], CustomerID);

		if (CusForUpdate == NULL)
		{
			printf("\n\n==>ID not found, please try again \n");
			printf("\n\n==>Enter the ID of the customer you to update:");
			scanf("%d", &CustomerID);
			CusForUpdate = searchCustomerByID(&CusTree[0], CustomerID);

			if (CusForUpdate == NULL)
			{
				printf("\n\n==>ID not found, please try again later");
				return;
			}
		}
	}
	system("cls");
	UpdateCustomer(&CusForUpdate);
}

void purchaseMenu(ItemNode** ItemTree,CusNode** CusTree, ItemPur** PurchasedItms)
{
	int ItmToSellID, size, SumToPur, AbleToS, SumOfItems = 0, Purchase, CustomerID;
	Item ITM;


	system("cls");
	print_inorderInStoke(*ItemTree);
	printf("\n\n==>Enter The ID of the item you want to sell\n");
	scanf("%d", &ItmToSellID);

	printSize(ItemTree, ItmToSellID);
	printf("\n\n==>Enter the size of the item you want to sell\n");
	scanf("%d", &size);

	printf("\n\n==>Enter the sum of the item you want to sell\n");
	scanf("%d", &SumToPur);

	AbleToS = AbleToSell(ItemTree, ItmToSellID, size, SumToPur);

	if (AbleToS)
	{
		ITM = SellByID(ItemTree, ItmToSellID, size, SumToPur);
		PurchasedItms[SumOfItems]->Itm = ITM;
		PurchasedItms[SumOfItems]->size = size;
		PurchasedItms[SumOfItems]->sum = SumToPur;
		SumOfItems++;
		system("cls");
		printf("\n\n==>Fine, if you want to sell another item for this customer, press 1, else press 0\n");
		scanf("%d", &Purchase);
	}

	else
	{
		printf("\n\n==>If you want to try again press 1, else press 0\n");
		scanf("%d", &Purchase);

		if (Purchase == 0)
		{
			return;
		}
	}

	while (Purchase == 1 && SumOfItems <= 2)
	{
		print_inorderInStoke(*ItemTree);
		printf("\n\n==>Enter The ID of the item you want to sell\n");
		scanf("%d", &ItmToSellID);

		printSize(ItemTree, ItmToSellID);
		printf("\n\n==>Enter the size of the item you want to sell\n");
		scanf("%d", &size);

		printf("\n\n==>Enter the sum of the item you want to sell\n");
		scanf("%d", &SumToPur);

		AbleToS = AbleToSell(ItemTree, ItmToSellID, size, SumToPur);

		if (AbleToS)
		{
			ITM = SellByID(ItemTree, ItmToSellID, size, SumToPur);
			PurchasedItms[SumOfItems]->Itm = ITM;
			PurchasedItms[SumOfItems]->size = size;
			PurchasedItms[SumOfItems]->sum = SumToPur;
			SumOfItems++;
			system("cls");
			printf("\n\n==>Fine, if you want to sell another item for this customer, press 1, else press 0\n");
			scanf("%d", &Purchase);
		}

		else
		{
			printf("\n\n==>If you want to try again press 1, else press 0\n");
			scanf("%d", &Purchase);
		}

	}

	while (Purchase == 1 && SumOfItems > 2)
	{
		printf("\n\n==>Error, you've reach the maximum items to sell on that purchase");
		printf("\n\n==>Fine, if you want to sell another item for this customer, press 1, else press 0\n");
		scanf("%d", &Purchase);
	}

	system("cls");
	printf("\n\n==>Enter the ID of the customer who buy that item\n");
	scanf("%d", &CustomerID);
	BuyerUpdate(CusTree, CustomerID, PurchasedItms, ItemTree);
	Purchase = 0;

	printf("\n\n==>Purchase Succeed");


}

void shutDown(ItemNode** ItemTree, CusNode** CusTree, ItemPur** PurchasedItms, Employee_node** employeeTree)
{
	printf("\n==>Goodbye and have a good day");
	save_employee_tree(employeeTree);
	save_customer_tree(CusTree);
	save_items_tree(ItemTree);

	freeEmpTree(*employeeTree);
	freeItemTree(*ItemTree);
	freeCusTree(*ItemTree);
	freePurchasedItms(PurchasedItms);
}