#define _CRT_SECURE_NO_WARNINGS
#include "employees.h"
#include "menu.h"
#include <stdio.h>
#include "customers.h"

int main() 
{
    //if (!checkIfEmployeeFileExists()) {
    //    createDefaultAdmin();
    //}

   /* Employee currentEmployee = login();*/
    //if (currentEmployee.level == 0) {
    //    printf("Login failed. Try again later..\n");
    //    return 0;
    //}

    //
    //return 0;

  
    //Customer* cus1 = (Customer*)malloc(sizeof(Customer));
	int choice;
	int value,CustomerID;
	int LastCustomerID = 0, LastItemID=0;
	char itemName, customerName, employeeName;
	Customer NewCus;
	CusNode* CusTree = NULL;
	CusNode* CusForUpdate = NULL;
	Item NewItem;
	ItemNode* ItemTree = NULL;
	ItemNode* ItemForUpdate = NULL;


	//do
	//{
	//	printMenu(currentEmployee.level);
	//	scanf("%d", &choice);
	//	printf("\n\n==>To exit press 'q': ");
	//	if ((currentEmployee.level == 3 && choice > 3) || (currentEmployee.level == 2 && choice > 7))
	//	{
	//		printf("This option is not avalible for you");
	//	}



		//switch (choice)
		//{
		//case 1:
		/*	printf("\n\n==>Enter the item ID you want to search:");
			scanf("%d", &value);
			break;*/
		//case 2:
			LastItemID++;
		    NewItem.id = LastItemID;
		    printf("\n\n==>Enter the model of the item you to add:");
		    scanf("%s", &NewItem.model);
		    printf("\n\n==>Enter manufactory date:");
		    scanf("%s", &NewItem.manuf);
			printf("\n\n==>Enter price:");
			scanf("%d", &NewItem.price);
	        AddItem(&ItemTree, NewItem);
    	    print_inorder(ItemTree);
		//	break;
		/*case 3:*/
	printf("For start press 0 ");
	scanf("%d", &value);
	while (value == 0)
	{
		LastCustomerID++;
		NewCus.ID = LastCustomerID;
		printf("\n\n==>Enter the full name of the customer you to add:");
		scanf("%s", &NewCus.fullName);
		printf("\n\n==>Enter current date:");
		scanf("%s", &NewCus.JoinDate);
		NewCus.SumOfShops = 0;
		NewCus.lastPurchaseDay = NULL;
		AddCustomer(&CusTree, NewCus);
		print_inorder(CusTree);
		/*	break;*/
		//case 4:
		//	printf("\n\n==>Enter the item you to remove:");
		//	scanf("%s", &itemName);
		//	RemoveItem(itemName);
		//	break;
		//case 5:
		//	printf("\n\n==>Enter the item you to update:");
		//	scanf("%s", &itemName);
		//	UpdateItem(itemName);
		//	break;
		//case 6:
			printf("\n\n==>Enter the ID of the customer you to update:");
			scanf("%d", &CustomerID);
			CusForUpdate=searchCustomer(&CusTree, CustomerID);
			while (CusForUpdate == NULL)
			{
				printf("ID not found, please try again \n");
				printf("\n\n==>Enter the ID of the customer you to update:");
				scanf("%d", &CustomerID);
				CusForUpdate = searchCustomer(&CusTree, CustomerID);
			}

			UpdateCustomer(&CusForUpdate);
		//	break;
		//case 7:
		//	printf("\n\n==>Enter the name of the worker you to add:");
		//	scanf("%s", &employeeName);
		//	UAddEmployee(employeeName);
		//	break;
		//case 8:
		//	printf("\n\n==>Enter the name of the workwr you to update:");
		//	scanf("%s", &employeeName);
		//	UpdatEmployeeLevel(employeeName);
		//	break;
		//default:
		//	printf("\n\n==> Choice is not on the list.. Try Again..!\n");
		//	break;
	/*	}
	} while (getch() != 'q');
*/

		printf("\n to continue press 0 ");
		scanf("%d", &value);
	}


}