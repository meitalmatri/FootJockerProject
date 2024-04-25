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
                     * right_mf, * left_mf, * parent_mf, 
                     * right_md, * left_md, * parent_md;

    char ManiDate[9];
    int height, height_pr, height_mf, height_md;

}ItemNode;

ItemNode* searchItemByID(ItemNode** Itemtree, int itemID);

ItemNode* searchItemByName(ItemNode** Itmtree, char* ModelName);

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

void insertbypr(ItemNode** tree, ItemNode* parent, Item* itm, ItemNode* temp);

void insertbymf(ItemNode** tree, ItemNode* parent, Item* itm, ItemNode* temp);

void insertbymd(ItemNode** tree, ItemNode* parent, Item* itm, ItemNode* temp);

int getHeightpr(ItemNode* n);

ItemNode* rightRotatepr(ItemNode* y);

ItemNode* leftRotatepr(ItemNode* x);

int getBalanceFactorpr(ItemNode* n);

int getHeightmf(ItemNode* n);

ItemNode* rightRotatemf(ItemNode* y);

ItemNode* leftRotatemf(ItemNode* x);

int getBalanceFactormf(ItemNode* n);

int getHeightmd(ItemNode* n);

ItemNode* rightRotatemd(ItemNode* y);

ItemNode* leftRotatemd(ItemNode* x);

int getBalanceFactormd(ItemNode* n);