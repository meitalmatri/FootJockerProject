#define _CRT_SECURE_NO_WARNINGS
#include "employees.h"
#include "menu.h"
#include <stdio.h>
#include "customers.h"
#include "items.h"
#include "employees.h"

int main()
{

	//char* currentDate = getCurrentDate();

	//// Print the current date
	//printf("Current date: %s\n", currentDate);

	//return 0;

	int choice, ItmToSellID, ItmToReturnID, AbleToPurchase, SumOfItems = 0, UpdateChoice;
	int CustomerID, employeeLevel = 0, NewEmployeeLevel, value, Purchase;
	int  LastItemID, LastCustomerID;
	int* PurchaedID[3];
	char itemName, customerName, employeeName, userName, password,temp_Date[10];
	Customer NewCus;
	CusNode* CusTree[]= {NULL,NULL,NULL};
	CusNode* CusForUpdate = NULL;
	Item NewItem;
	ItemNode* ItemTree[] = {NULL,NULL,NULL,NULL };//0-id,1-price,2-modifydate,3-modle
	ItemNode* ItemForUpdate = NULL, *temp;
	Employee_node* employeeTree = NULL;


	if (!checkIfEmployeeFileExists(employeeTree))
	{
		employeeTree = createDefaultAdmin();//הכנסתי את המשתנה החדש שנוצר לעץ
	}

	else
	{
		load_employee_tree(&employeeTree);
	}

	Employee_node* currentEmployee = NULL;//החלפתי סוג משתנה 

	while (currentEmployee == NULL)
	{
		currentEmployee = login(&employeeTree);
	}

	//printMenu(currentEmployee->data->level);
	//scanf("%d", &choice);

	LastItemID = load_items_tree(&ItemTree);
	LastCustomerID = load_customer_tree(&CusTree,&ItemTree);

	printf("what manuf date are you searching for?\n");
	scanf("%s", temp_Date);
	temp = search_manuf(ItemTree[2], temp_Date);
	if (temp == NULL)
		printf("not found\n");
	else
	{
		printf("the manuf date you searching for is %s\n",temp->itemN.manuf);
	}
	

	////printf("id\n");
	////print_preorder1(ItemTree[0]);
	////printf("price\n");
	////print_preorder1(ItemTree[1]);
	////printf("modify\n");
	////print_preorder1(ItemTree[2]);
	////printf("modle\n");
	////print_preorder1(ItemTree[3]);


	//while ((choice > 4 && currentEmployee->data->level == 3) || (choice > 7 && currentEmployee->data->level > 1))
	//{
	//	printf("\n\n==>Choice is not on the list, maybe you dont have the promission for that choice!");
	//	printf("\n\n==>Please try again-");
	//	scanf("%d", &choice);
	//}


	//do
	//{
	//	switch (choice)
	//	{
	//		/*case 1:
	//			printf("\n\n==>Enter the item ID you want to search:");
	//			scanf("%d", &value);
	//			break;*/
	//	case 2:
	//		LastItemID++;
	//		NewItem.id = LastItemID;
	//		NewItem.inventory = NULL;
	//		printf("\n\n==>Enter the model of the item you to add:");
	//		scanf("%s", &NewItem.model);
	//		printf("\n\n==>Enter manufactory date:");
	//		scanf("%s", &NewItem.manuf);
	//		printf("\n\n==>Enter price:");
	//		scanf("%f", &NewItem.price);
	//		AddItem(&ItemTree, NewItem);
	//		break;
	//	case 3:
	//		LastCustomerID++;
	//		NewCus.ID = LastCustomerID;
	//		printf("\n\n==>Enter the name of the customer you to add:");
	//		scanf("%s", &NewCus.fullName);
	//		strcpy(NewCus.JoinDate,getCurrentDate());
	//		NewCus.SumOfShops = 0;
	//		//strcpy(NewCus.lastPurchaseDay->Date, "NoPurch");
	//		NewCus.lastPurchaseDay = NULL;
	//		AddCustomer(&CusTree, NewCus);
	//		printf("\n\n");
	//		cus_print_preorder(CusTree[2]);
	//		break;
	//	case 4:
	//		printf("\n\n==>Enter The ID of the item you want to sell\n");
	//		scanf("%d", &ItmToSellID);
	//		AbleToPurchase = SellByID(&ItemTree, ItmToSellID);

	//		if (AbleToPurchase)
	//		{
	//			printf("\n\n==>Enter the ID of the customer who buy that item\n");
	//			scanf("%d", &CustomerID);
	//		}

	//		printf("\n\n==>Fine, if you want to sell another item for this customer, press 1, else press 0\n");
	//		scanf("%d", &Purchase);
	//		PurchaedID[SumOfItems] = ItmToSellID;
	//		SumOfItems++;

	//		while (Purchase == 1 && SumOfItems <= 2)
	//		{
	//			printf("\n\n==>Enter The ID of the item you want to sell\n");
	//			scanf("%d", &ItmToSellID);
	//			AbleToPurchase = SellByID(&ItemTree, ItmToSellID);

	//			if (AbleToPurchase)
	//			{
	//				PurchaedID[SumOfItems] = ItmToSellID;

	//				printf("\n\n==>Fine, if you want to sell another item for this customer, press 1, else press 0\n");
	//				scanf("%d", &Purchase);

	//				SumOfItems++;
	//			}

	//		}

	//		while (Purchase == 1 && SumOfItems > 2)
	//		{
	//			printf("\n\n==>Error, you've reach the maximum items to sell on that purchase");
	//			printf("\n\n==>Fine, if you want to sell another item for this customer, press 1, else press 0\n");
	//			scanf("%d", &Purchase);
	//		}

	//		BuyerUpdate(&CusTree, CustomerID, &PurchaedID, &ItemTree);
	//		Purchase = 0;

	//		printf("\n\n==>Purchase Succeed");


	//		break;
	//	case 5:
	//		removeItem(&ItemTree, NULL);
	//		break;
	//		/*case 6:
	//			printf("\n\n==>Enter the item you to update:");
	//			scanf("%s", &itemName);
	//			UpdateItem(itemName);
	//			break;*/
	//	case 7:
	//		printf("\n\n==>If you want to update customer by name please press 0 for ID press 1\n");
	//		scanf("%d", &UpdateChoice);

	//		if (UpdateChoice == 0)
	//		{
	//			printf("\n\n==>Enter the name of the customer you to update:");
	//			scanf("%s", &customerName);
	//			CusForUpdate = searchCustomerByName(&CusTree[1], &customerName);

	//			if (CusForUpdate == NULL)
	//			{
	//				printf("\n\n==>Name not found, please try again \n");
	//				printf("\n\n==>Enter the Name of the customer you to update:");
	//				scanf("%s", &customerName);
	//				CusForUpdate = searchCustomerByName(&CusTree[1], &customerName);

	//				if (CusForUpdate == NULL)
	//				{
	//					printf("\n\n==>Name not found, please try again later");
	//					break;
	//				}
	//			}

	//		}

	//		else
	//		{
	//			printf("\n\n==>Enter the ID of the customer you to update:");
	//			scanf("%d", &CustomerID);
	//			CusForUpdate = searchCustomerByID(&CusTree[0], CustomerID);

	//			if (CusForUpdate == NULL)
	//			{
	//				printf("\n\n==>ID not found, please try again \n");
	//				printf("\n\n==>Enter the ID of the customer you to update:");
	//				scanf("%d", &CustomerID);
	//				CusForUpdate = searchCustomerByID(&CusTree[0], CustomerID);

	//				if (CusForUpdate == NULL)
	//				{
	//					printf("\n\n==>ID not found, please try again later");
	//					break;
	//				}
	//			}
	//		}

	//		UpdateCustomer(&CusForUpdate);
	//		break;

	//	case 8:

	//		printf("\n\n==>Enter The ID of the item you want to return\n");
	//		scanf("%d", &ItmToReturnID);
	//		AbleToPurchase = SellByID(&ItemTree, ItmToSellID);

	//		if (AbleToPurchase)
	//		{
	//			printf("\n\n==>Enter the ID of the customer who buy that item\n");
	//			scanf("%d", &CustomerID);
	//		}

	//		printf("\n\n==>Fine, if you want to sell another item for this customer, press 1, else press 0\n");
	//		scanf("%d", &Purchase);
	//		PurchaedID[SumOfItems] = ItmToSellID;
	//		SumOfItems++;

	//		while (Purchase == 1 && SumOfItems <= 2)
	//		{
	//			printf("\n\n==>Enter The ID of the item you want to sell\n");
	//			scanf("%d", &ItmToSellID);
	//			AbleToPurchase = SellByID(&ItemTree, ItmToSellID);

	//			if (AbleToPurchase)
	//			{
	//				PurchaedID[SumOfItems] = ItmToSellID;

	//				printf("\n\n==>Fine, if you want to sell another item for this customer, press 1, else press 0\n");
	//				scanf("%d", &Purchase);

	//				SumOfItems++;
	//			}

	//		}

	//		while (Purchase == 1 && SumOfItems > 2)
	//		{
	//			printf("\n\n==>Error, you've reach the maximum items to sell on that purchase");
	//			printf("\n\n==>Fine, if you want to sell another item for this customer, press 1, else press 0\n");
	//			scanf("%d", &Purchase);
	//		}

	//		BuyerUpdate(&CusTree, CustomerID, &PurchaedID, &ItemTree);
	//		Purchase = 0;

	//		printf("\n\n==>Purchase Succeed");

	//		break;
	//	case 9:
	//		printf("\n\n==>Enter the name of the employee you want to add:");
	//		scanf("%s", &employeeName);
	//		printf("\n\n==>Enter the username of the employee you want to add:");
	//		scanf("%s", &userName);
	//		printf("\n\n==>Enter the password of the employee you want to add:");
	//		scanf("%s", &password);
	//		printf("\n\n==>Enter the level of the employee you want to add:");
	//		scanf("%d", &NewEmployeeLevel);
	//		add_employee(&employeeTree, &userName, &employeeName, &password, NewEmployeeLevel);
	//		break;
	//	case 10:
	//		update_employee(employeeTree);
	//		break;
	//	default:
	//		printf("\n\n==> Choice is not on the list.. Try Again..!\n");
	//		break;
	//	}

	//	printf("\n\n==>To continue please press 1, for exit please press 0\n\n");
	//	scanf("%d", &value);

	//	if (value == 1)
	//	{
	//		printMenu(currentEmployee->data->level);
	//		scanf("%d", &choice);

	//		while ((choice > 4 && currentEmployee->data->level == 3) || (choice > 7 && currentEmployee->data->level > 1))
	//		{
	//			printf("\n\n==>Choice is not on the list, maybe you dont have the promission for that choice!");
	//			printf("\n\n==>Please try again-");
	//			scanf("%d", &choice);
	//		}
	//	}

	//} while (value != 0);

	//if (value == 0)
	//{
		printf("\n==>Goodbye and have a good day");
		save_employee_tree(&employeeTree);
		save_customer_tree(&CusTree);
		save_items_tree(&ItemTree);
	}

//}