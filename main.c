#define _CRT_SECURE_NO_WARNINGS
#include "employees.h"
#include "menu.h"
#include <stdio.h>
#include "customers.h"
#include "items.h"
#include "employees.h"
#include "log.h"
int main()
{
	int choice, value, LastItemID, LastCustomerID, i = 0;
	CusNode* CusTree[] = { NULL,NULL};
	ItemNode* ItemTree[] = { NULL,NULL,NULL,NULL };//0-id,1-price,2-modifydate,3-modle
	ItemPur* PurchasedItms[3] = { NULL, NULL, NULL };
	Employee_node* employeeTree = NULL;
	Employee_node* currentEmployee = NULL;
	LogEntry log[LOG_SIZE];
	mallocPurchasedItms(&PurchasedItms);
    time_t rawtime;
    struct tm* info;
    time(&rawtime);
    info = localtime(&rawtime);
    char date[MAX_DATE_LENGTH];
    strftime(date, sizeof(date), "%Y-%m-%d %H:%M:%S", info);

	if (!checkIfEmployeeFileExists(employeeTree))
	{
		employeeTree = createDefaultAdmin();
	}

	else
	{
		load_employee_tree(&employeeTree);
	}

	currentEmployee = login(&employeeTree);
	if (currentEmployee == NULL)
		return;
	LastItemID = load_items_tree(&ItemTree);
	LastCustomerID = load_customer_tree(&CusTree, &ItemTree[3]);

	
	do
	{
		choice=printMenu(currentEmployee->data->level);
		switch (choice)
		{
		case 1:
			searceMenu(&ItemTree);
			printLog(&log, &i,currentEmployee->data->username, "searching item");
			break;
		case 2:
			addItemMenu(&ItemTree, &LastItemID);
		        printLog(&log, &i,currentEmployee->data->username, "Add Item");
			break;
		case 3:
			addCusMenu(&CusTree, &LastCustomerID);
			printLog(&log, &i,currentEmployee->data->username, "Add Customer");
			break;
		case 4:
			purchaseMenu(&ItemTree,&CusTree,&PurchasedItms);
			printLog(&log, &i,currentEmployee->data->username, "Purchase Item");
			break;
		case 5:
			removeItemMenu(&ItemTree);
			printLog(&log, &i,currentEmployee->data->username, "Remove Item");
			break;
		case 6:
			UpdateItem(&ItemTree);
			printLog(&log, &i,currentEmployee->data->username, "Update Item");
			i++;
			break;
		case 7:
			updateCusMenu(&CusTree);
			printLog(&log, &i,currentEmployee->data->username, "Update Customer");
			break;
		case 8:
			returnItemMenu(&ItemTree,&CusTree);
			printLog(&log, &i,currentEmployee->data->username, "Return Item");
			break;
		case 9:
			addEnpMenu(&employeeTree);
			printLog(&log, &i,currentEmployee->data->username, "Add Employee");
			break;
		case 10:
			update_employee(employeeTree);
			printLog(&log, &i,currentEmployee->data->username, "Update Employee");
			break;
		default:
			printf("\n\n==> Choice is not on the list.. Try Again..!\n");
			break;
		}

		printf("\n\n==>To continue please press 1, for exit please press 0\n\n");
		scanf("%d", &value);
		system("cls");
	} while (value != 0);

	if (value == 0)
	{
		shutDown(&ItemTree, &CusTree, &PurchasedItms, &employeeTree);

		for (int j = 0; j <i; j++) 
		{

				writeLog(&log[j], "logfile.txt");
			
		}
    
	}

}
