#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "employees.h"
#include<malloc.h>


int checkIfEmployeeFileExists()
{
    FILE* fp = NULL;
    fp = fopen("employee.txt", "r");
	if (fp == NULL)
		return 0;
	else
		fclose(fp);
	return 1;
}

void load_employee_tree(Employee_node** tree)
{
	FILE* fp = NULL;
	char username[20], firstname[10], password[10];
	int level;
	fp = fopen("employee.txt", "r");
	if (fp == NULL)
		printf("error uploading the file\n");
	else
	{
		while (!feof(fp))
		{
			fscanf(fp, "%s %s %s %d\n", username, firstname, password, &level);
			add_employee(tree, username, firstname, password, level);
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
		fprint_inorder( *tree, fp);
	}
	fclose(fp);
}

void fprint_inorder(Employee_node* tree,FILE* fp)
{
	if (tree)
	{
		fprint_inorder(tree->left,fp);
		fprintf(fp, "%s %s %s %d\n", tree->data->username, tree->data->firstname,tree->data->password,tree->data->level);
		fprint_inorder(tree->right,fp);
	}
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
	add_employee(tree, username, firstname, password, level);
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

		temp->data = user;
		*tree = temp;
		return;
	}

	if (strcmp(user->username,(*tree)->data->username)<0)
	{
		insert(&(*tree)->left, *tree, user);
	}
	else if (strcmp(user->username, (*tree)->data->username) > 0)
	{
		 insert(&(*tree)->right, *tree, user);
	}
}

void print_preorder(Employee_node* tree)
{
	if (tree)
	{
		print_employee(tree->data);
		print_preorder(tree->left);
		print_preorder(tree->right);
	}

}

Employee_node* login(Employee_node** tree)
{
	char username_temp[20];
	char password_temp[10];
	Employee_node* temp_emp;
	for (int i = 0; i < 3; i++)
	{
		printf("please enter your user name:\n");
		scanf("%s", username_temp);
		printf("please enter your user password:\n");
		scanf("%s", password_temp);
		temp_emp = search_emp(tree, username_temp);
		if ((temp_emp)&&(!strcmp(temp_emp->data->password, password_temp)))
		{
			printf("login successful\nwelcome %s\n",temp_emp->data->firstname);
			return temp_emp;
		}

		printf("please try again\n");
	}
	printf("login faild please try again later\n");
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

	printf("what username would you like to update?");
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