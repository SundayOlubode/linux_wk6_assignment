#include "manipulator.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define filename "fullnames.txt"

int sort_names()
{
	FILE *file = fopen(filename, "r");
	if (!file)
	{
		printf("Could not open %s\n", filename);
		return 1;
	}

	char **names = NULL;
	size_t count = 0;
	char buffer[100];

	while (fgets(buffer, sizeof(buffer), file))
	{
		names = realloc(names, (count + 1) * sizeof(char *));
		buffer[strcspn(buffer, "\n")] = '\0';
		names[count] = strdup(buffer);
		count++;
	}
	fclose(file);

	for (size_t i = 0; i < count - 1; i++)
	{
		for (size_t j = i + 1; j < count; j++)
		{
			if (strcasecmp(names[i], names[j]) > 0)
			{
				char *temp = names[i];
				names[i] = names[j];
				names[j] = temp;
			}
		}
	}

	for (size_t i = 0; i < count; i++)
	{
		printf("%s\n", names[i]);
		free(names[i]);
	}
	free(names);

	return 0;
}

int count_entries()
{
	FILE *file = fopen(filename, "r");
	if (!file)
	{
		printf("Could not open %s\n", filename);
		return 1;
	}

	int count = 0;
	char buffer[100];
	while (fgets(buffer, sizeof(buffer), file))
	{
		count++;
	}
	fclose(file);
	return count;
}

// int main()
// {
// 	printf("Sorting names:\n");
// 	sort_names();
// 	int entries = count_entries();
// 	printf("\nNumber of entries: %d\n", entries);
// 	return 0;
// }