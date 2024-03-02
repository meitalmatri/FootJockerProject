#pragma once

#include <stdbool.h>

typedef struct item
{
        int id;
        char model[20];
        char manuf[20];
        int size[11];
        float price;
        int inventory;
} Item;