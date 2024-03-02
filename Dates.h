#pragma once
#include "items.h"

typedef struct purchaseday
{
    char Date[8];
    struct Purchaseday* previous;
    struct Purchaseday* next;
    Item purItems[3];

} PurchaseDay;

int dateCmp(char* x, char* y);
