#include "menu.h"


void printMenu(unsigned int employeeLevel)
{

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