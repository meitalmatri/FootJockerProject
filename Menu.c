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
			print_item(searchItemByID(&tree[0], tempId));
			break;
		case 2:
			printf("\n\n==>you chose to search by date\nplease enter a date (dd/mm/yyyy):");
			scanf("%s", tempdate);
			print_inorderdate(tree[2], tempdate, "00/00/0000");
			break;
		case 3:
			printf("\n\n==>you chose to search by date range\nplease enter the min date (dd/mm/yyyy):\n");
			scanf("%s", minda);
			printf("\n\n==>please enter the max date (dd/mm/yyyy):\n");
			scanf("%s", maxda);
			print_inorderdate(tree[2], minda, maxda);
			break;
		case 4:
			printf("\n\n==>you chose to search by price\nplease enter a price:\n");
			scanf("%f", &minpr);
			print_inorderPrice(tree[1], minpr, 0);
			break;
		case 5:
			printf("\n\n==>you chose to search by price range\nplease enter the min price:\n");
			scanf("%f", &minpr);
			printf("\n\n==>please enter the max price:\n");
			scanf("%f", &maxpr);
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