﻿#define _CRT_SECURE_NO_WARNINGS
#include "employees.h"
#include "menu.h"
#include <stdio.h>
#include "customers.h"
#include "items.h"
#include "employees.h"

int main()
{
	int choice, ItmToSellID,/* ItmToReturnID,*/ SumOfItems = 0, UpdateChoice,AbleToS/*, AbleToRe,SumToRe,des*/;
	int CustomerID, employeeLevel = 0, /*NewEmployeeLevel,*/ value, Purchase, size, SumToPur;
	int  LastItemID, LastCustomerID;
	char itemName, customerName[15]/*, employeeName, userName, password*/;
	//Customer NewCus;
	CusNode* CusTree[] = { NULL,NULL};
	CusNode* CusForUpdate = NULL;
	//Item NewItem;
	Item ITM;
	ItemNode* ItemTree[] = { NULL,NULL,NULL,NULL };//0-id,1-price,2-modifydate,3-modle
	ItemNode* ItemForUpdate = NULL;
	Employee_node* employeeTree = NULL;
	ItemPur* PurchasedItms[3] = { NULL, NULL, NULL };

	//PurchasedItms[0] = (ItemPur*)malloc(sizeof(ItemPur));
	//PurchasedItms[1] = (ItemPur*)malloc(sizeof(ItemPur));
	//PurchasedItms[2] = (ItemPur*)malloc(sizeof(ItemPur));
	mallocPurchasedItms(&PurchasedItms);

	if (!checkIfEmployeeFileExists(employeeTree))
	{
		employeeTree = createDefaultAdmin();//äëðñúé àú äîùúðä äçãù ùðåöø ìòõ
	}

	else
	{
		load_employee_tree(&employeeTree);
	}

	Employee_node* currentEmployee = NULL;//äçìôúé ñåâ îùúðä 

	while (currentEmployee == NULL)
	{
		currentEmployee = login(&employeeTree);
	}
	
	LastItemID = load_items_tree(&ItemTree);
	LastCustomerID = load_customer_tree(&CusTree, &ItemTree[3]);


	do
	{
		printMenu(currentEmployee->data->level);
		scanf("%d", &choice);

		while ((choice > 3 && currentEmployee->data->level == 3) || (choice > 8 && currentEmployee->data->level > 1))
		{
			printf("\n\n==>Choice is not on the list, maybe you dont have the promission for that choice!");
			printf("\n\n==>Please try again-");
			scanf("%d", &choice);
		}
		switch (choice)
		{
		case 1:
				searceMenu(&ItemTree);
				break;
		case 2:
			addItemMenu(&ItemTree, &LastItemID);
			break;
		case 3:
			addCusMenu(&CusTree, &LastCustomerID);
			break;
		case 4:
			/*printf("\n\n==>Enter The ID of the item you want to sell\n");
			scanf("%d", &ItmToSellID);

			printf("\n\n==>Enter the size of the item you want to sell\n");
			scanf("%d", &size);

			printf("\n\n==>Enter the sum of the item you want to sell\n");
			scanf("%d", &SumToPur);

			AbleToS = AbleToSell(&ItemTree, ItmToSellID, size, SumToPur);

			if (AbleToS)
			{
				ITM = SellByID(&ItemTree, ItmToSellID, size, SumToPur);
				PurchasedItms[SumOfItems]->Itm = ITM;
				PurchasedItms[SumOfItems]->size = size;
				PurchasedItms[SumOfItems]->sum = SumToPur;
				SumOfItems++;

				printf("\n\n==>Fine, if you want to sell another item for this customer, press 1, else press 0\n");
				scanf("%d", &Purchase);
			}

			else
			{
				printf("\n\n==>If you want to try again press 1, else press 0\n");
				scanf("%d", &Purchase);

				if (Purchase == 0)
				{
					break;
				}
			}

				while (Purchase == 1 && SumOfItems <= 2)
				{
					printf("\n\n==>Enter The ID of the item you want to sell\n");
					scanf("%d", &ItmToSellID);

					printf("\n\n==>Enter the size of the item you want to sell\n");
					scanf("%d", &size);

					printf("\n\n==>Enter the sum of the item you want to sell\n");
					scanf("%d", &SumToPur);

					AbleToS = AbleToSell(&ItemTree, ItmToSellID, size, SumToPur);

					if (AbleToS)
					{
						ITM = SellByID(&ItemTree, ItmToSellID, size, SumToPur);
						PurchasedItms[SumOfItems]->Itm = ITM;
						PurchasedItms[SumOfItems]->size = size;
						PurchasedItms[SumOfItems]->sum = SumToPur;
						SumOfItems++;

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


				printf("\n\n==>Enter the ID of the customer who buy that item\n");
				scanf("%d", &CustomerID);
				BuyerUpdate(&CusTree, CustomerID, &PurchasedItms, &ItemTree);
				Purchase = 0;

				printf("\n\n==>Purchase Succeed");*/
			purchaseMenu(&ItemTree,&CusTree,&PurchasedItms);
			break;
		case 5:
			removeItemMenu(&ItemTree);
			break;
		case 6:
			UpdateItem(&ItemTree);
			break;
		case 7:
			updateCusMenu(&CusTree);
			break;

		case 8:

			//des = 1;

			//while (des == 1)
			//{
			//	printf("\n\n==>Enter The ID of the item you want to return\n");
			//	scanf("%d", &ItmToReturnID);

			//	printf("\n\n==>Enter The size of the item you want to return\n");
			//	scanf("%d", &size);

			//	printf("\n\n==>Enter the ID of the customer who want to return that item\n");
			//	scanf("%d", &CustomerID);

			//	printf("\n\n==>Enter the sum of the item you want to return\n");
			//	scanf("%d", &SumToRe);

			//	AbleToRe = AbleToReturn(&CusTree, CustomerID, ItmToReturnID, size, SumToRe);

			//	if (AbleToRe)
			//	{
			//		ItemReturn(&ItemTree, ItmToReturnID, size, SumToRe);

			//		printf("\n\n==>Item return succeed\nIf you want return another Item press 1, else press 0\n");
			//		scanf("%d", &des);

			//	}

			//	else
			//	{
			//		printf("\n\n==>If you want to try again press 1, else press 0\n");
			//		scanf("%d", &des);

			//	}
			//}
			returnItemMenu(&ItemTree,&CusTree);
			break;

		case 9:
			addEnpMenu(&employeeTree);
			break;
		case 10:
			update_employee(employeeTree);
			break;
		default:
			printf("\n\n==> Choice is not on the list.. Try Again..!\n");
			break;
		}

		printf("\n\n==>To continue please press 1, for exit please press 0\n\n");
		scanf("%d", &value);

	} while (value != 0);

	if (value == 0)
	{
		shutDown(&ItemTree, &CusTree, &PurchasedItms, &employeeTree);
		//printf("\n==>Goodbye and have a good day");
		//save_employee_tree(&employeeTree);
		//save_customer_tree(&CusTree);
		//save_items_tree(&ItemTree);

		//freeEmpTree(employeeTree);
		//freeItemTree(ItemTree);
		//freeCusTree(ItemTree);
		//freePurchasedItms(&PurchasedItms);
	}
}