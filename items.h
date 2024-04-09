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

    struct items_tree* right, * left, * parent, 
                     * right_pr, * left_pr, * parent_pr, 
                     * right_na, * left_na, * parent_na, 
                     * right_md, * left_md, * parent_md;

    char ManiDate[9];
    int height, height_pr, height_na, height_md;

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

int getHeight1(ItemNode* n);

ItemNode* rightRotate1(ItemNode* y);

ItemNode* leftRotate1(ItemNode* x);

int getBalanceFactor1(ItemNode* n);

void insertbyid(ItemNode** tree, ItemNode* parent, Item* itm, ItemNode* temp);

void print_item(Item* user);

void print_preorder1(ItemNode* tree);

