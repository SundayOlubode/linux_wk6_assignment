#include "manipulator.h"
#include <stdio.h>

int main()
{
	const char *filename = "names.txt";

	printf("Sorting names:\n\n");
	sort_names(filename);

	int entries = count_entries(filename);
	printf("\nNumber of entries: %d\n", entries);

	return 0;
}
