#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<stdbool.h>

typedef struct item{
    int id;
    char model[20];
    char manuf[20];
    int size[11];
    float price;
    int inventory;
    bool InStock;
} Item;

typedef struct items_tree
{
    Item itemN;

    int itemID;

    struct items_tree* right, * left, * parent;

    char ManiDate[9];

}ItemNode;

ItemNode* searchItem(ItemNode** Itemtree, int itemID);

void AddItem(ItemNode** Itemtree, Item itm);

void insertItem(ItemNode** ItemTree, ItemNode* parent, Item itm);

void AddIventory(ItemNode** Itemtree, int ID);

