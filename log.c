#include "log.h"
#include "employees.h"
#include "menu.h"
#include <stdio.h>
#include "customers.h"
#include "items.h"
#include "employees.h"
#include "dates.h"

void printLogEntry(const LogEntry* entry) {
    printf("%s\t%s\t%s\t%s\n", entry->date, entry->username, entry->action, (entry->success ? "Success" : "Failure"));
}


void writeLog(const LogEntry* entry, int j) {
    FILE* logfile = fopen("log.txt", "a");
    if (logfile == NULL) {
        printf("Error opening log file!\n");
        return;
    }
    for(int i=0;i<j;i++)
    fprintf(logfile,"\n%s %s %s %s\n", entry->date, entry->username, entry->action, (entry->success ? "Success" : "Failure"));

    fclose(logfile);
}

//int loging()
//{
//    LogEntry log[LOG_SIZE];
//
//    time_t rawtime;
//    struct tm* info;
//    time(&rawtime);
//    info = localtime(&rawtime);
//    char date[MAX_DATE_LENGTH];
//    strftime(date, sizeof(date), "%Y-%m-%d %H:%M:%S", info);
//
// 
//    for (int i = 0; i < LOG_SIZE; ++i) {
//        sprintf(log[i].date, "%s", date);
//        sprintf(log[i].username, "User%d", i + 1);
//        sprintf(log[i].action, "Performed action %d", i + 1);
//        log[i].success = i % 2; 
//    }
//
//  
//    for (int j= 0; j< LOG_SIZE;j++) {
//        writeLog(&log[i], "logfile.txt");
//    }
//
// 
//    printf("First 10 log entries:\n");
//    for (int i = 0; i < 10; ++i) {
//        printLogEntry(&log[i]);
//    }
//
//    return 0;
//}


void printLog(LogEntry* log, int* i,char* username ,char* word)
{
    strcpy(log[*i].date, getCurrentDate());
    strcpy(log[*i].username, username);
    strcpy(log[*i].action, word);
    *i = *i + 1;
}