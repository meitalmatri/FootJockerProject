#include "employees.h"
#include "menu.h"
#include <stdio.h>
#include "customers.h"
#include "items.h"
#include "employees.h"
#include "dates.h"
#include<malloc.h>

#define MAX_DATE_LENGTH 20
#define MAX_USERNAME_LENGTH 50
#define MAX_ACTION_LENGTH 100
#define LOG_SIZE 500

typedef struct {
    char date[11];
    char username[20];
    char action[100];
    int success;
} LogEntry;

void printLog(LogEntry** log, int* i, char* username, char* word);
void writeLog(const LogEntry* entry, const char* filename);
void printLogEntry(const LogEntry* entry);
int loging();

