void printMenu(unsigned int employeeLevel)
{

	printf("\n============> FootJockerMenue <============\n");
	printf("Choose your operation:\n\n");
	printf("1.ITEM SEARCHING \n");
	printf("2.ADD ITEM \n");
	printf("3.ADD CUSTOMER  \n");


	if (employeeLevel == 2)
	{
		printf("4.REMOVE ITEM \n");
		printf("5.UPDATE ITEM \n");
		printf("6.UPDATE CUSTOMER \n");
	}

	if (employeeLevel == 1)
	{
		printf("7.ADD EMPLOYEE \n");
		printf("8.UPDATE EMPLOYEE LEVEL \n");
	}

	printf("Your Choice:");


}
