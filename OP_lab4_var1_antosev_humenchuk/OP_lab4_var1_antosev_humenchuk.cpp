#include "stdafx.h"
#include "ArrayProcessing.h"
#include "TextFileProcessing.h"
#include <iostream>
#include <queue>

void FillArrayFromFile(FILE *file, char **arr, int rows, int cols);
void MakeTopsArray();
void DijkstrasAlgorithm(int startI, int startJ, int finishI, int finishJ);
void FindPath(int index);
void GetBack(int index, int finishScore);

using namespace std;

int rows;
int cols;
char **map;
int *tops;
std::queue<int> q;
bool *visited;
int finishPointIndex;
int FINISH = 10000;

int main()
{	
	FILE *file = LoadData("map.txt");
	rows = GetTextFileHeight("map.txt");
	cols = GetTextFileWidth("map.txt");
	map = new char*[rows];
	for (int i = 0; i < rows; i++)
	{
		map[i] = new char[cols];
	}
	FillArrayFromFile(file, map, rows, cols);
	ShowDoubleArray(map, rows, cols);
	DijkstrasAlgorithm(4, 1, 1, 6);
	//DijkstrasAlgorithm(12,1,3,6);
	ShowDoubleArray(map, rows, cols);
	system("pause");
    return 0;
}

void FillArrayFromFile(FILE *file, char **arr, int rows, int cols)
{
	char symbol;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			fscanf(file, "%c", &arr[i][j]);
		}
		fscanf(file, "\n");
	}
}

void MakeTopsArray()
{
	tops = new int[rows*cols];
	visited = new bool[rows*cols];
	int k = 0;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (map[i][j] == 'X') tops[k] = -1;
			else tops[k] = 10000;
			visited[k] = false;
			k++;			
		}
	}
}

void DijkstrasAlgorithm(int startI, int startJ, int finishI, int finishJ)
{
	MakeTopsArray();
	if (startI <= 0 || startI >= rows || startJ <= 0 || startJ >= cols)
	{
		std::cout << "Incorrect start point";
	}
	else if (finishI <= 0 || finishI >= rows || finishJ <= 0 || finishJ >= cols)
	{
		std::cout << "Incorrect finish point";
	}
	else
	{
		int startPointIndex = startI*cols + startJ;
		finishPointIndex = finishI*cols + finishJ;
		tops[startPointIndex] = 0;
		tops[finishPointIndex] = -2;
		FindPath(startPointIndex);
		//ShowArray(tops, rows*cols, rows);
		GetBack(finishPointIndex, FINISH - 1);
		for (int i = 0; i = q.size(); i++)
		{
			int p = q.front();
			int indexI = p / rows;
			int indexJ = p % cols;
			map[indexI][indexJ] = 'a' + i;
			q.pop();
		}
	}
}

void FindPath(int index)
{	
	visited[index] = true;
	if ((tops[index - 1] == -2 || tops[index - rows] == -2 || tops[index + 1] == -2 || tops[index + rows] == -2))
	{
		if(tops[index] + 1 <= FINISH)
		FINISH = tops[index] + 1;
	}
	if (tops[index - 1] != -1 && visited[index - 1] == false && tops[index - 1] != -2) //go left
	{
		if (tops[index] + 1 < tops[index - 1]) tops[index - 1] = tops[index] + 1;
		FindPath(index - 1);
		if (tops[index - 1] != tops[index] - 1) visited[index - 1] = false;
	}
	if (tops[index - rows] != -1 && visited[index - rows] == false && tops[index - rows] != -2) //go up
	{		
		if (tops[index] + 1 < tops[index - rows]) tops[index - rows] = tops[index] + 1;
		FindPath(index - rows);
		if (tops[index - rows] != tops[index] - 1) visited[index - rows] = false;
	}
	if (tops[index + 1] != -1 && visited[index + 1] == false && tops[index + 1] != -2) //go right
	{		
		if (tops[index] + 1 < tops[index + 1]) tops[index + 1] = tops[index] + 1;
		FindPath(index + 1);	
		if (tops[index + 1] != tops[index] - 1) visited[index + 1] = false;
	}
	if (tops[index + rows] != -1 && visited[index + rows] == false && tops[index + rows] != -2) //go down
	{
		if (tops[index] + 1 < tops[index + rows]) tops[index + rows] = tops[index] + 1;
		FindPath(index + rows);
		if (tops[index + rows] != tops[index] - 1) visited[index + rows] = false;
	}
}

void GetBack(int index, int finishScore)
{	
	q.push(index);
	if (tops[index] == 0)
	{
		return;
	}
	else
	{		
		if (tops[index - 1] == finishScore) //go left
		{
			GetBack(index - 1, --finishScore);
		}
		else if (tops[index - rows] == finishScore) //go up
		{
			GetBack(index - rows, --finishScore);
		}
		else if (tops[index + 1] == finishScore) //go right
		{
			GetBack(index + 1, --finishScore);
		}
		else if (tops[index + rows] == finishScore) //go down
		{
			GetBack(index + rows, --finishScore);
		}		
	}	
}