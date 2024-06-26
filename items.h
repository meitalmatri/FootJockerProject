//�� ��� 308471341
//���� ���� 318573367
//���� ��� ��� 319123378


#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include<conio.h>

typedef struct item{
    int id;
    char model[20];
    char manuf[20];
    int size[11];
    float price;
    int inventory;
    bool InStock;
} Item;

typedef struct itemsPurchased {
    Item Itm;
    int size;
    int sum;
} ItemPur;

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

void UpdateItem(ItemNode** Itemtree);

ItemNode* min_value(ItemNode* Itm, int* height);

ItemNode* max_value(ItemNode* Itm, int* height);

void removeItem(ItemNode** Itemtree, int ID);

//void load_item_tree(ItemNode** tree);

int load_items_tree(ItemNode** ItmTree);

void save_items_tree(ItemNode** ItmTree);

void item_fprint_inorder(ItemNode* ItmTree, FILE* fp);

Item SellByID(ItemNode** ItmTree, int ID, int size, int sumToPur);

int AbleToSell(ItemNode** ItmTree, int ID, int size, int sumToPur);

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

ItemNode* search_model(ItemNode* tree, char* word);

int strstartswith(const char* str, const char* prefix);

ItemNode* search_manuf(ItemNode* tree, char* word);

ItemNode* search_price(ItemNode* tree, float price);

void print_inorderPrice(ItemNode* tree, float min, float max);

void print_inorderdate(ItemNode* tree, char* min, char* max);

void ItemReturn(ItemNode** Itemtree, int ItmToReturnID, int size, int SumToRe);

void print_inorderInStoke(ItemNode* tree);

void freeItemTree(ItemNode* tree);

void print_inordere(ItemNode* tree);

void printSize(ItemNode** Itemtree, int ID);

void sizeZero(Item* itm);

void mallocPurchasedItms(ItemPur** PurchasedItms);

void freePurchasedItms(ItemPur** PurchasedItms);
