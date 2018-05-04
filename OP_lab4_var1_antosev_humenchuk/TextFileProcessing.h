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
	//for (int i = 0; i < size; i++)
	//{
	//	fprintf(file, "%d\n", arr[i]);
	//}
	fclose(file);
}

int GetTextFileHeight(char *filename)
{
	FILE *file;
	file = fopen(filename, "r");
	int rows = 0;
	int symbol = ' ';
	while (symbol != '\n')
	{
		fscanf(file, "%c", &symbol);
		if(symbol != '\n') rows++;
	}
	fclose(file);
	return rows;	
}

int GetTextFileWidth(char *filename)
{
	FILE *file;
	file = fopen(filename, "r");
	int cols = 0;
	int symbol = ' ';
	while (symbol != '\n')
	{
		fscanf(file, "%c", &symbol);
		if (symbol != '\n') cols++;
	}
	fclose(file);
	return cols;
}