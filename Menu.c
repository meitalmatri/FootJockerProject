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
