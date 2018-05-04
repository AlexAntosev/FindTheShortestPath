#include "stdafx.h"
#include "ArrayProcessing.h"
#include "TextFileProcessing.h"
#include <iostream>
#include <queue>

void RequestStartAndFinishPoints(int & startI, int & startJ, int & finishI, int & finishJ);
void CoordinatesRequest(int & firtsPoint, int & secondPoint);
void CreateMapMatrix();
void CountRowsAndColomnsForMapMatrix();
void FillMatrixFromFile(char *filename);
void MakeTopsArray();
void MakeVisitedTopsArray();
void DijkstrasAlgorithm(int startI, int startJ, int finishI, int finishJ);
void FindPath(int index);
void GetBackToStartPoint(int index, int finishScore);
void DrawPath();

using namespace std;

int rows;
int cols;
char **map;
int *tops;
int topsCount;
queue<int> q;
bool *visited;
int finishPointScore = 10000;

int main()
{	
	int startI, startJ, finishI, finishJ;		
	CreateMapMatrix();
	ShowMatrix(map, rows, cols);
	RequestStartAndFinishPoints(startI, startJ, finishI, finishJ);
	DijkstrasAlgorithm(startI, startJ, finishI, finishJ);
	ShowMatrix(map, rows, cols);
	system("pause");
    return 0;
}

void RequestStartAndFinishPoints(int & startI, int & startJ, int & finishI, int & finishJ)
{
	cout << "Enter the coordinates of the start point";
	CoordinatesRequest(startI, startJ);
	cout << "Enter the coordinates of the finish point";
	CoordinatesRequest(finishI, finishJ);
}

void CoordinatesRequest(int & firtsPoint, int & secondPoint)
{
	cout << endl << "X:";
	cin >> firtsPoint;
	cout << endl << "Y:";
	cin >> secondPoint;
}

void CreateMapMatrix()
{
	CountRowsAndColomnsForMapMatrix();
	map = new char*[rows];
	for (int i = 0; i < rows; i++)
	{
		map[i] = new char[cols];
	}
	FillMatrixFromFile("map.txt");
}

void CountRowsAndColomnsForMapMatrix()
{
	rows = GetTextFileHeight("map.txt");
	cols = GetTextFileWidth("map.txt");	
}

void FillMatrixFromFile(char *filename)
{
	FILE *file = LoadData(filename);
	char symbol;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			fscanf(file, "%c", &map[i][j]);
		}
		fscanf(file, "\n");
	}
}

void MakeTopsArray()
{
	tops = new int[topsCount];	
	int k;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			k = i * rows + j;
			if (map[i][j] == 'X') tops[k] = -1;
			else tops[k] = 10000;			
		}
	}
}

void MakeVisitedTopsArray()
{
	visited = new bool[topsCount];
	for (int i = 0; i < topsCount; i++)
	{
		visited[i] = false;
	}
}

void DijkstrasAlgorithm(int startI, int startJ, int finishI, int finishJ)
{
	topsCount = rows*cols;
	MakeTopsArray();
	MakeVisitedTopsArray();
	if (startI <= 0 || startI >= rows || startJ <= 0 || startJ >= cols)
	{
		std::cout << "Incorrect start point" << endl;
	}
	else if (finishI <= 0 || finishI >= rows || finishJ <= 0 || finishJ >= cols)
	{
		std::cout << "Incorrect finish point" << endl;
	}
	else
	{
		int startPointIndex = startI*cols + startJ;
		int finishPointIndex = finishI*cols + finishJ;
		tops[startPointIndex] = 0;
		tops[finishPointIndex] = -2;
		FindPath(startPointIndex);
		GetBackToStartPoint(finishPointIndex, finishPointScore - 1);
		DrawPath();
	}
}

void DrawPath()
{
	int queueSize = q.size();
	for (int i = 0; i < queueSize; i++)
	{
		int p = q.front();
		int indexI = p / rows;
		int indexJ = p % cols;
		map[indexI][indexJ] = 'a' + i;
		q.pop();
	}
}

void FindPath(int index)
{	
	visited[index] = true;
	if ((tops[index - 1] == -2 || tops[index - rows] == -2 || tops[index + 1] == -2 || tops[index + rows] == -2))
	{
		if(tops[index] + 1 <= finishPointScore) finishPointScore = tops[index] + 1;
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

void GetBackToStartPoint(int index, int finishScore)
{	
	if (tops[index] == 0)
	{
		q.push(index);
		return;
	}
	else
	{		
		if (tops[index - 1] == finishScore) //go left
		{
			GetBackToStartPoint(index - 1, --finishScore);
		}
		else if (tops[index - rows] == finishScore) //go up
		{
			GetBackToStartPoint(index - rows, --finishScore);
		}
		else if (tops[index + 1] == finishScore) //go right
		{
			GetBackToStartPoint(index + 1, --finishScore);
		}
		else if (tops[index + rows] == finishScore) //go down
		{
			GetBackToStartPoint(index + rows, --finishScore);
		}		
	}	
	q.push(index);
}