#pragma once
#include "Dates.h"
#define _CRT_SECURE_NO_WARNINGS
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include "items.h"
#include "employees.h"


typedef struct cus 
{
    int ID;
    char fullName[20];
    char JoinDate[10];
    int SumOfShops; 
    PurchaseDay* lastPurchaseDay;
    
} Customer;

typedef struct customers_tree
{
    Customer cus;

    struct customer_tree* right, * left, * parent,
        * right_name, * left_name, * parent_name;

    char ManiDate[9];

    int height, height_pr, height_na, height_md;

}CusNode;

void insertCustomer(CusNode** Custree, CusNode* parent, Customer cus);
void AddCustomer(CusNode** Custree, Customer cus);
int AbleToReturn(CusNode** CusTree, int CusID, int ItemID, int ItemSize,int ItemSum);
void print_preorder(CusNode* Custree);
void print_inorder(CusNode* Custree);
void print_postorder(CusNode* Custree);
void deltree(CusNode* Custree);
CusNode* searchCustomerByID(CusNode** Custree, int CusID);
CusNode* searchCustomerByName(CusNode** Custree, char* FullName);
void UpdateCustomer(CusNode** Custree);
void save_customer_tree(CusNode** Custree);
int load_customer_tree(CusNode** Custree,ItemNode** ItmTree);
void cus_fprint_inorder(CusNode* Custree, FILE* fp);
void BuyerUpdate(CusNode** Custree, int cusID, ItemPur* PurchasedItems[], ItemNode** Itmtree);
void CusInsertbyid(CusNode** tree, CusNode* parent, Customer cus);
void CusInsertbyName(CusNode** tree, CusNode* parent, Customer cus);
void CusInsertbyDate(CusNode** tree, CusNode* parent, Customer cus);
void cus_print_preorder(CusNode* tree);
void print_cus(Customer* cus);
CusNode* rightRotateCus(CusNode* y);
CusNode* leftRotateCus(CusNode* x);
int getBalanceFactorCus(CusNode* n);
int getHeightCus(CusNode* n);



