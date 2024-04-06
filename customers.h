#pragma once
#include "Dates.h"
#define _CRT_SECURE_NO_WARNINGS
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include "items.h"

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

    int CusID;

    struct customer_tree* right, * left, * parent;

}CusNode;

void insertCustomer(CusNode** Custree, CusNode* parent, Customer cus);
void AddCustomer(CusNode** Custree, Customer cus);
void print_preorder(CusNode* Custree);
void print_inorder(CusNode* Custree);
void print_postorder(CusNode* Custree);
void deltree(CusNode* Custree);
CusNode* searchCustomer(CusNode** Custree, int CusID);
void UpdateCustomer(CusNode** Custree);
void save_customer_tree(CusNode** Custree);
int load_customer_tree(CusNode** Custree);
void cus_fprint_inorder(CusNode* Custree, FILE* fp);
void BuyerUpdate(CusNode** Custree, int cusID);

