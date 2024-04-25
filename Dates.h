#pragma once
#include "items.h"
#include <time.h>

typedef struct purchaseday
{
    char* Date[10];
    struct purchaseday* previous;
    struct purchaseday* next;
    ItemPur purItems[3];
} PurchaseDay;

char* getCurrentDate();

int dateCmp(char* x, char* y);

long int convertToDate(char* date);

int check14DaysPassed(char* date1, char* date2);