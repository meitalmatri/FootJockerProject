#define _CRT_SECURE_NO_WARNINGS
#include "employees.h"
#include<malloc.h>


int checkIfEmployeeFileExists(Employee_node* tree)
{
    FILE* fp = NULL;
    fp = fopen("employee.txt", "r");
	if (fp == NULL)
	{
		return 0;
	}
	else
	{
		fclose(fp);
	}
	return 1;
}

void load_employee_tree(Employee_node** tree)
{
	FILE* fp = NULL;
	char* username[20], firstname[10], password[10];
	int level;
	fp = fopen("employee.txt", "r");
	if (fp == NULL)
		printf("error uploading the file\n");
	else
	{
		while (!feof(fp))
		{
			fscanf(fp, "%s %s %s %d\n", &username, &firstname, &password, &level);
			add_employee(tree, &username, &firstname, &password, level);
		}
	}
	fclose(fp);
}

void save_employee_tree(Employee_node** tree)
{
	FILE* fp = NULL;
	fp = fopen("employee.txt", "w");
	if (fp == NULL)
		printf("error uploading the file\n");
	else
	{
		employee_fprint_inorder(*tree, fp);
	}
	fclose(fp);
}

void employee_fprint_inorder(Employee_node* tree,FILE* fp)
{
	if (tree)
	{
		employee_fprint_inorder(tree->left, fp);
		fprintf(fp, "%s %s %s %d\n", tree->data->username, tree->data->firstname, tree->data->password, tree->data->level);
		employee_fprint_inorder(tree->right, fp);
	}

	else
		return;
}

Employee_node* createDefaultAdmin() 
{
	Employee_node* root = NULL;
    Employee* new_manager = (Employee*)malloc(sizeof(Employee));
    if (new_manager != NULL) {
        strcpy(new_manager->username, "admin");
        strcpy(new_manager->firstname, "manager");
        strcpy(new_manager->password, "12345678");
        new_manager->level = 1;
    }
	else
	{
		printf("error please try agian\n");
		return NULL;
	}
	insert(&root, NULL, new_manager);
    return root;
}

void add_new_employee(Employee_node** tree)
{
	char username[20],firstname[10],password[10];
	int level=0;
	printf("hello\nyou are know creating new employee\nplease enter a username:\n");
	scanf("%s",username);
	printf("please enter a firstname:\n");
	scanf("%s",firstname);
	printf("please enter a password:\n");
	scanf("%s",password);
	printf("please enter levle:\n");
	scanf("%d",&level);
	add_employee(tree, &username, &firstname, &password, level);
}

void add_employee(Employee_node** tree,char* username,char* firstname,char* password, int level)
{
	Employee* new_employee = (Employee*)malloc(sizeof(Employee));
	if (new_employee != NULL)
	{
		strcpy(new_employee->username ,username);
		strcpy(new_employee->firstname, firstname);
		strcpy(new_employee->password, password);
		new_employee->level = level;
	}
	else
	{
		printf("error please try agian\n");
		return ;
	}
	insert(tree, NULL, new_employee);
}

void print_employee(Employee* user)
{
    printf("username:%s first name: %s password %s level: %d\n", user->username, user->firstname, user->password, user->level);
  /*  printf("first name: %s\n", user->firstname);
    printf("password %s\n", user->password);
    printf("level: %d\n", user->level);*/
}

void insert(Employee_node** tree, Employee_node* parent, Employee* user)
{
	Employee_node* temp = NULL;
	if (!(*tree))
	{
		temp = (Employee_node*)malloc(sizeof(Employee_node));
		temp->left = temp->right = NULL;
		temp->parent = parent;
		temp->height = 1;
		temp->data = user;
		*tree = temp;
		return;
	}

	if (strcmp(user->username, (*tree)->data->username) < 0)
	{
		insert(&(*tree)->left, *tree, user);
	}
	else if (strcmp(user->username, (*tree)->data->username) > 0)
	{
		insert(&(*tree)->right, *tree, user);
	}
	(*tree)->height = 1 + max(getHeight((*tree)->left), getHeight((*tree)->right));
	int bf = getBalanceFactor(*tree);

	// Left Left Case  
	if (bf > 1 && strcmp(user->username, (*tree)->left->data->username) < 0) {
		(*tree) = rightRotate(*tree);
		return;
	}
	// Right Right Case  
	if (bf < -1)
	{
		if (!(*tree)->left)
		{
			(*tree) = leftRotate(*tree);
			return;
		}
		else if (strcmp(user->username, (*tree)->left->data->username) > 0)
		{
			(*tree) = leftRotate(*tree);
			return;
		}
	}
	// Left Right Case  
	if (bf > 1 && strcmp(user->username, (*tree)->left->data->username) > 0) {
		(*tree)->left = leftRotate((*tree)->left);
		(*tree) = rightRotate(*tree);
		return;
	}
	// Right Left Case  
	if (bf < -1 && strcmp(user->username, (*tree)->left->data->username) < 0) {
		(*tree)->right = rightRotate((*tree)->right);
		(*tree) = leftRotate(*tree);
		return;
	}
	return;
}

//void print_preorder(Employee_node* tree)
//{
//	if (tree)
//	{
//		print_employee(tree->data);
//		printf("\nthe left sun of %s is\n", tree->data);
//		print_preorder(tree->left);
//		printf("\nthe right sun of %s is\n", tree->data);
//		print_preorder(tree->right);
//	}
//
//}

Employee_node* login(Employee_node** tree)
{
	char username_temp[20];
	char password_temp[10];
	Employee_node* temp_emp;
	for (int i = 0; i < 3; i++)
	{
		printf("==>please enter your user name:\n");
		scanf("%s", username_temp);
		printf("\n==>please enter your user password:\n");
		scanf("%s", password_temp);
		temp_emp = search_emp(tree, username_temp);
		if ((temp_emp) && (!strcmp(temp_emp->data->password, password_temp)))
		{
			printf("==>login successful\nwelcome %s\n", temp_emp->data->firstname);
			return temp_emp;
		}

		if(i<2)
		printf("\n==>please try again\n\n");
	}
	printf("\n==>login failed please try again later\n");

	return NULL;

}

Employee_node* search_emp(Employee_node** tree, char* username)
{
	if (!(*tree))
		return NULL;
	if (!strcmp((*tree)->data->username, username))
		return *tree;
	else if (strcmp(username,(*tree)->data->username) < 0)
		return search_emp(&(*tree)->left, username);
	else
		return search_emp(&(*tree)->right, username);
}

void update_employee(Employee_node* tree)
{
	Employee_node* temp_emp = NULL;
	int temp = 0;
	char update_user[20];

	printf("what username would you like to update?\n");
	scanf("%s", update_user);
	temp_emp = search_emp(&tree, update_user);
	if (temp_emp)
	{
		do
		{
			printf("what data whould you like to update?\n1 - password\n2 - first name\n3 - level\npress any other number to exit\n");
			scanf("%d", &temp);
			switch (temp) {
			case 1:
				printf("what is the new password?\n");
				scanf("%s", temp_emp->data->password);
					break;
			case 2:
				printf("what is the new first name?\n");
				scanf("%s", temp_emp->data->firstname);
				break;
			case 3:
				printf("what is the new level?\n");
				scanf("%d", &temp_emp->data->level);
				break;
			}
		
		} 
		while ((temp < 4) && (temp > 0));
	}
	else
		printf("error username did not found\n");
}

int getHeight(Employee_node* n) {
	if (n == NULL)
		return 0;
	return n->height;
}

Employee_node* rightRotate(Employee_node* y) {
	 Employee_node* x = y->left;
	 Employee_node* T2 = x->right;

	x->right = y;
	y->left = T2;

	x->height = max(getHeight(x->right), getHeight(x->left)) + 1;
	y->height = max(getHeight(y->right), getHeight(y->left)) + 1;

	return x;
}

Employee_node* leftRotate(Employee_node* x) {
	Employee_node* y = x->right;
	Employee_node* T2 = y->left;

	y->left = x;
	x->right = T2;

	x->height = max(getHeight(x->right), getHeight(x->left)) + 1;
	y->height = max(getHeight(y->right), getHeight(y->left)) + 1;

	return y;
}

int getBalanceFactor(Employee_node* n) {
	if (n == NULL) {
		return 0;
	}
	return getHeight(n->left) - getHeight(n->right);
}