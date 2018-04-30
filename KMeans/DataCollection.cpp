#include "DataCollection.h"
#include <iostream>
using namespace std;

DataCollection::DataCollection()
{
	
}
DataCollection::DataCollection(int* points)
{
	pointCount = points;
	dataPoints = new int*[*pointCount];
	for (int k = 0; k < *points; k++)
	{
		//Enter points manually
		dataPoints[k] = new int[2];
		cout << "Enter data points. " << endl;
		int one;
		int two;
		cout << "Enter point one " << endl;
		cin >> one;
		while (cin.fail())//Error checking for integer input
		{
			cout << "Error. Enter point one " << endl;
			cin.clear();
			cin.ignore(256, '\n');
			cin >> one;
			
		}
		cout << "Enter point two " << endl;
		cin >> two;
		while (cin.fail())//Error checking for integer input
		{
			cout << "Error. Enter point two " << endl;
			cin.clear();
			cin.ignore(256, '\n');
			cin >> two;
			
		}
		dataPoints[k][0] = one;//first coordinate set to one
		dataPoints[k][1] = two;//second coordinate set to two
	}
}

DataCollection::~DataCollection()
{
	
}

//Precondition: Data is entered
DataCollection::PrintData()
{
	for (int i = 0; i < *pointCount; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			cout << dataPoints[i][j] << " ";
		}
		cout << endl;
	}
}
//Postcondition: None

//Precondition: None
int** DataCollection::GetData()
{
	return dataPoints;
}
//Postcondition: use as a double integer pointer

//Precondition: None
int* DataCollection::GetCount()
{
	return pointCount;
}
//Postcondition: use as integer pointer
