#pragma once
#include<iostream>

void ShowArray(int *arr, int size, int rows)
{
	for (int i = 0; i < size; i++)
	{
		std::cout << arr[i] << "\t";
		if (i % rows == rows - 1 && i > 0) std::cout << std::endl;
	}
	std::cout << std::endl;
}

void ShowMatrix(char **arr, int rows, int cols)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			std::cout << arr[i][j];
		}
		std::cout << std::endl;
	}	
}