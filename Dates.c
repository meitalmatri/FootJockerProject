#include "Dates.h"

int dateCmp(char* x, char* y)
{
	if (strcmp(x + 6, y + 6) != 0)
		return(strcmp(x + 6, y + 6));
	if (strcmp(x + 3, y + 3) != 0)
		return(strcmp(x + 3, y + 3));
	return(strcmp(x, y));
}

why are you