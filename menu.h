#pragma once
#define _CRT_SECURE_NO_WARNINGS


#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include "items.h"
#include "customers.h"


void printMenu(unsigned int employeeLevel);
void searceMenu(ItemNode** tree);
void addItemMenu(ItemNode** tree, int* LastItemID);
void addCusMenu(CusNode** tree, int* LastItemID);
void removeItemMenu(ItemNode** tree);


