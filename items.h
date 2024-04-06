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
void AddIventory(ItemNode** Itemtree);
void UpdateItem(ItemNode** Itemtree, int itmID);
ItemNode* min_value(ItemNode* Itm, int* height);
ItemNode* max_value(ItemNode* Itm, int* height);
ItemNode* removeItem(ItemNode** Itemtree, int ID);
//void load_item_tree(ItemNode** tree);
int load_items_tree(ItemNode** ItmTree);
void save_item_tree(ItemNode** ItmTree);
void item_fprint_inorder(ItemNode* ItmTree, FILE* fp);
int SellByID(ItemNode** ItmTree, int ID);

