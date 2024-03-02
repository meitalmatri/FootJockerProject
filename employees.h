#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct employee {
    char username[20];
    char firstname[10];
    char password[10];
    unsigned int level; // 1 - admin, 2 - employee, 3 - practicioner
} Employee;

typedef struct bin_tree {
    Employee* data;
    struct bin_tree* right, * left, * parent;
}Employee_node;

int checkIfEmployeeFileExists();
Employee_node* createDefaultAdmin();
void print_employee(Employee* user);
Employee_node* login(Employee_node** tree);
void print_preorder(Employee_node* tree);
void insert(Employee_node** tree, Employee_node* parent, Employee* user);
void add_new_employee(Employee_node** tree);
void load_employee_tree(Employee_node** tree);
void fprint_inorder(Employee_node* tree, FILE* fp);
void save_employee_tree(Employee_node** tree);
void add_employee(Employee_node** tree, char* username, char* firstname, char* password, int level);
Employee_node* search_emp(Employee_node** tree, char* username);
void update_employee(Employee_node* tree);

