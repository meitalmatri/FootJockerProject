void printMenu(unsigned int employeeLevel)
{

	printf("\n============> FootJockerMenue <============\n");
	printf("Choose your operation:\n\n");
	printf("1.ITEM SEARCHING \n");
	printf("2.ADD ITEM \n");
	printf("3.ADD CUSTOMER  \n");
	printf("4.PURCHASE SCREEN  \n");


	if (!(employeeLevel > 2))
	{
		printf("5.REMOVE ITEM \n");
		printf("6.UPDATE ITEM \n");
		printf("7.UPDATE CUSTOMER \n");
	}

	if (!(employeeLevel>1))
	{
		printf("8.ADD EMPLOYEE \n");
		printf("9.UPDATE EMPLOYEE LEVEL \n");
	}

	printf("Your Choice:");


}
