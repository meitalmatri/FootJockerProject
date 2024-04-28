#pragma once
#define _CRT_SECURE_NO_WARNINGS


#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include "items.h"
#include "customers.h"


int printMenu(unsigned int employeeLevel);
void searceMenu(ItemNode** tree);
void addItemMenu(ItemNode** tree, int* LastItemID);
void addCusMenu(CusNode** tree, int* LastItemID);
void addEnpMenu(Employee_node** tree);
void removeItemMenu(ItemNode** tree);
void returnItemMenu(ItemNode** ItemTree, CusNode** CusTree);
void updateCusMenu(CusNode** CusTree);
void purchaseMenu(ItemNode** ItemTree, CusNode** CusTree, ItemPur** PurchasedItms);
void shutDown(ItemNode** ItemTree, CusNode** CusTree, ItemPur** PurchasedItms, Employee_node** employeeTree);



