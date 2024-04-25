#include "Dates.h"

// Function to get the current date in the format dd/mm/yy
char* getCurrentDate() {
	// Get the current time
	time_t now = time(NULL);
	struct tm* local_time = localtime(&now);

	// Buffer to hold the formatted date string
	static char date[9]; // dd/mm/yy + '\0'

	// Format the date string
	strftime(date, sizeof(date), "%d/%m/%y", local_time);

	return date;
}

int dateCmp(char* x, char* y)
{
	if (strcmp(x + 6, y + 6) != 0)
		return(strcmp(x + 6, y + 6));
	if (strcmp(x + 3, y + 3) != 0)
		return(strcmp(x + 3, y + 3));
	return(strcmp(x, y));
}

long int convertToDate(char* date)
{
	int day, month, year;
	sscanf(date, "%d%d%d", &day, &month, &year);

	long int days = year * 365 + day;
	for (int i = 0; i < month - 1; i++) {
		if (i == 3 || i == 5 || i == 8 || i == 10)
			days += 30;
		else if (i == 1) {
			if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
				days += 29;
			else
				days += 28;
		}
		else
			days += 31;
	}
	return days;
}

// Function to check if 14 days have passed between two dates
int check14DaysPassed(char* date1, char* date2)
{
	long int days1 = convertToDate(date1);
	long int days2 = convertToDate(date2);

	// Calculate the difference between the two dates
	long int difference = days2 - days1;

	// Check if the difference is exactly 14 days
	if (difference == 14)
		return 1;
	else
		return 0;
}