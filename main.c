#define _CRT_SECURE_NO_WARNINGS
#include "employees.h"
#include "menu.h"
#include <stdio.h>
#include "customers.h"
#include "items.h"
#include "employees.h"

int main() 
{
	int choice;
	int CustomerID,employeeLevel=0, NewEmployeeLevel, value;
	int  LastItemID=0, LastCustomerID;
	char itemName, customerName, employeeName, userName, password;
	Customer NewCus;
	CusNode* CusTree = NULL;
	CusNode* CusForUpdate = NULL;
	Item NewItem;
	ItemNode* ItemTree = NULL;
	ItemNode* ItemForUpdate = NULL;
	Employee_node* employeeTree = NULL;

	if (!checkIfEmployeeFileExists(employeeTree)) 
	{
		employeeTree = createDefaultAdmin();//������ �� ������ ���� ����� ���
	}

	else
	{
		load_employee_tree(&employeeTree);
	}

	Employee_node* currentEmployee=NULL;//������ ��� ����� 

	while (currentEmployee==NULL)
	{
		currentEmployee = login(&employeeTree);
	}

	printMenu(currentEmployee->data->level);
	scanf("%d", &choice);

	LastCustomerID = load_customer_tree(&CusTree);


	while ((choice > 3 && currentEmployee->data->level == 3) || (choice > 6 && currentEmployee->data->level > 1))
	{
		printf("\n\n==>Choice is not on the list, maybe you dont have the promission for that choice!");
		printf("\n\n==>Please try again-");
		scanf("%d", &choice);
	}

	do
	{
		switch (choice)
		{
		/*case 1:
			printf("\n\n==>Enter the item ID you want to search:");
			scanf("%d", &value);
			break;*/
		case 2:
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
			break;
		case 3:
		    LastCustomerID++;
		    NewCus.ID = LastCustomerID;
		    printf("\n\n==>Enter the name of the customer you to add:");
		    scanf("%s", &NewCus.fullName);
		    printf("\n\n==>Enter current date:");
		    scanf("%s", &NewCus.JoinDate);
		    NewCus.SumOfShops = 0;
		    NewCus.lastPurchaseDay = NULL;
		    AddCustomer(&CusTree, NewCus);
		    print_inorder(CusTree);
		    break;
		case 4:
		    removeItem(&ItemTree, NULL);
			break;
		/*case 5:
			printf("\n\n==>Enter the item you to update:");
			scanf("%s", &itemName);
			UpdateItem(itemName);
			break;*/
		case 6:
			printf("\n\n==>Enter the ID of the customer you to update:");
			scanf("%d", &CustomerID);
			CusForUpdate=searchCustomer(&CusTree, CustomerID);
			if (CusForUpdate == NULL)
			{
				printf("ID not found, please try again \n");
				printf("\n\n==>Enter the ID of the customer you to update:");
				scanf("%d", &CustomerID);
				CusForUpdate = searchCustomer(&CusTree, CustomerID);

				if (CusForUpdate == NULL)
				{
					printf("ID not found, please try again later");
					break;
				}
			}

			UpdateCustomer(&CusForUpdate);
			break;
		case 7:
			printf("\n\n==>Enter the name of the employee you want to add:");
			scanf("%s", &employeeName);
			printf("\n\n==>Enter the username of the employee you want to add:");
			scanf("%s", &userName);
			printf("\n\n==>Enter the password of the employee you want to add:");
			scanf("%s", &password);
			printf("\n\n==>Enter the level of the employee you want to add:");
			scanf("%d", &NewEmployeeLevel);
			add_employee(&employeeTree, &userName, &employeeName, &password, NewEmployeeLevel);
			break;
		case 8:
			update_employee(employeeTree);
			break;
		default:
			printf("\n\n==> Choice is not on the list.. Try Again..!\n");
			break;
		}

		printf("\n\n==>To continue please press 1, for exit please press 0\n\n");
		scanf("%d", &value);

		if (value == 1)
		{
			printMenu(currentEmployee->data->level);
			scanf("%d", &choice);

			while ((choice > 3 && currentEmployee->data->level == 3) || (choice > 6 && currentEmployee->data->level > 1))
			{
				printf("\n\n==>Choice is not on the list, maybe you dont have the promission for that choice!");
				printf("\n\n==>Please try again-");
				scanf("%d", &choice);
			}
		}
		
	} while (value != 0);

	if (value == 0)
	{
		printf("\n==>Goodbye and have a good day");
		save_employee_tree(&employeeTree);
		save_customer_tree(&CusTree);
	}
}