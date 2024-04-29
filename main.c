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
			sprintf(log[i].date, "%s", date);
			sprintf(log[i].username, "currentEmployee.username.date");
			sprintf(log[i].action, "addItemMenu");
			i++1;
			break;
		case 3:
			addCusMenu(&CusTree, &LastCustomerID);
			sprintf(log[i].date, "%s", date);
			sprintf(log[i].username, "currentEmployee.username.date");
			sprintf(log[i].action, "addCusMenu");
			i++1;
			break;
		case 4:
			purchaseMenu(&ItemTree,&CusTree,&PurchasedItms);
			sprintf(log[i].date, "%s", date);
			sprintf(log[i].username, "currentEmployee.username.date");
			sprintf(log[i].action, "purchaseMenu");
			i++1;
			break;
		case 5:
			removeItemMenu(&ItemTree);
			sprintf(log[i].date, "%s", date);
			sprintf(log[i].username, "currentEmployee.username.date");
			sprintf(log[i].action, "removeItemMenu");
			i++1;
			break;
		case 6:
			UpdateItem(&ItemTree);
			sprintf(log[i].date, "%s", date);
			sprintf(log[i].username, "currentEmployee.username.date");
			sprintf(log[i].action, "UpdateItem");
			i++1;
			break;
		case 7:
			updateCusMenu(&CusTree);
			sprintf(log[i].date, "%s", date);
			sprintf(log[i].username, "currentEmployee.username.date");
			sprintf(log[i].action, "updateCusMenu");
			i++1;
			break;
		case 8:
			returnItemMenu(&ItemTree,&CusTree);
			sprintf(log[i].date, "%s", date);
			sprintf(log[i].username, "currentEmployee.username.date");
			sprintf(log[i].action, "returnItemMenu");
			i++1;
			break;
		case 9:
			addEnpMenu(&employeeTree);
			sprintf(log[i].date, "%s", date);
			sprintf(log[i].username, "currentEmployee.username.date");
			sprintf(log[i].action, "addEnpMenu");
			i++1;
			break;
		case 10:
			update_employee(employeeTree);
			sprintf(log[i].date, "%s", date);
			sprintf(log[i].username, "currentEmployee.username.date");
			sprintf(log[i].action, "update_employee");
			i++1;
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
	}
}