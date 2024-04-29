#include "employees.h"
#include "menu.h"
#include <stdio.h>
#include "customers.h"
#include "items.h"
#include "employees.h"
#include "dates.h"



#define MAX_DATE_LENGTH 20
#define MAX_USERNAME_LENGTH 50
#define MAX_ACTION_LENGTH 100
#define LOG_SIZE 500

typedef struct {
    char date[MAX_DATE_LENGTH];
    char username[MAX_USERNAME_LENGTH];
    char action[MAX_ACTION_LENGTH];
    int success; 
} LogEntry;


void printLogEntry(const LogEntry* entry) {
    printf("%s\t%s\t%s\t%s\n", entry->date, entry->username, entry->action, (entry->success ? "Success" : "Failure"));
}


void writeLog(const LogEntry* entry, const char* filename) {
    FILE* logfile = fopen(filename, "a");
    if (logfile == NULL) {
        printf("Error opening log file!\n");
        return;
    }

    fprintf(logfile, "%s\t%s\t%s\t%s\n", entry->date, entry->username, entry->action, (entry->success ? "Success" : "Failure"));

    fclose(logfile);
}

int loging()

    LogEntry log[LOG_SIZE];

    time_t rawtime;
    struct tm* info;
    time(&rawtime);
    info = localtime(&rawtime);
    char date[MAX_DATE_LENGTH];
    strftime(date, sizeof(date), "%Y-%m-%d %H:%M:%S", info);

 
    for (int i = 0; i < LOG_SIZE; ++i) {
        sprintf(log[i].date, "%s", date);
        sprintf(log[i].username, "User%d", i + 1);
        sprintf(log[i].action, "Performed action %d", i + 1);
        log[i].success = i % 2; 
    }

  
    for (int j= 0; j< LOG_SIZE;j++) {
        writeLog(&log[i], "logfile.txt");
    }

 
    printf("First 10 log entries:\n");
    for (int i = 0; i < 10; ++i) {
        printLogEntry(&log[i]);
    }

    return 0;
}
