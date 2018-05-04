#pragma once
#include <iostream>

FILE *LoadData(char *filename)
{
	FILE *file;
	file = fopen(filename, "r");
	if (file == NULL)
	{
		printf("Error opening file");
	}
	return file;
}

void SaveData(char *filename, int *arr, int size)
{
	FILE *file;
	file = fopen(filename, "w");
	if (file == NULL)
	{
		printf("Error opening file");
	}
	for (int i = 0; i < size; i++)
	{
		fprintf(file, "%d\n", arr[i]);
	}
	fclose(file);
}