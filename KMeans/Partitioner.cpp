#include "Partitioner.h"
#include "DataCollection.h"
#include <cstdlib>
#include <time.h>
#include <cmath>
#include <iostream>
using namespace std;
//K-Means Algorithm
//1. Initialize the random cluster centers
//2. Assign each data point to closest center
//3. Readjust centers and reassign data points
//4. Repeat until convergence


Partitioner::Partitioner(DataCollection datac)
{
	datacollect = &datac;
	
}

Partitioner::~Partitioner()
{
}

//Precondition: The number of clusters is determined, and
//must be an int
Partitioner::InitializeCenters(int clusters)
{
	srand(time(NULL));
	
	cl = clusters;
	cout << "# of clusters: " << cl << endl;
	randomCenters = new double*[cl];
	for (int i = 0; i < cl; i++)
	{
		randomCenters[i] = new double[2];
		randomCenters[i][0] = (rand() % 2) + (i * 2 + 1);//use i to separate ranges
		randomCenters[i][1] = (rand() % 2) + (i * 2 + 1);
		cout << randomCenters[i][0] << " " << randomCenters[i][1] << endl;
		
	}
	
	clusterAssignments = new int*[cl];
	for (int i = 0; i < cl; i++)
	{
		clusterAssignments[i] = new int[*(datacollect->GetCount())];//initialize all with -1
		int zeroTwo = 0;
		for (int* j = &zeroTwo; *j < *(datacollect->GetCount()); (*j)++)
		{
			clusterAssignments[i][*j] = -1;
		}
		
	}
	
}
//Postcondition: Measure distance afterward
//do not use again in the same run

//Precondition: none
Partitioner::InitializeDistances()
{
	int* size = datacollect->GetCount();
	int zero = 0;
	storedDistances = new double*[cl];
	for(int c = 0; c < cl; c++)
	{
		storedDistances[c] = new double[*size];
		cout << "Array: " << c << endl;
		for (int* d = &zero;*d < *size; ++*d)
		{
			//distances between each coordinate of each point
			//to corresponding coordinate
			storedDistances[c][*d] = 0.0;
		}
	}
	
}
//Postcondition: none

//Precondition: centers are initialized
Partitioner::PrintCenters()
{
	for (int i = 0; i < cl; i++)
	{
		cout << "Center: " << i << endl;
		for (int j = 0; j < 2; j++)
		{
			cout << randomCenters[i][j] << " ";
		}
		cout << "" << endl;
	}
	return 0;
}
//Postcondition: none

//Precondition: data points in data collection object are initialized

// and randomCenters is initialzed
Partitioner::MeasureDistances()
{
	int** dataPoints = datacollect->GetData();
	
	//Store distances//

	for (int h = 0; h < cl; h++)
	{
		
		int distCount = 1;
		int zero = 0;
		int* i;
		for (i = &zero; *i < *(datacollect->GetCount()); (*i)++)
		{
			cout << "Distance: " << h << " axis 1: " << dataPoints[*i][0] - randomCenters[h][0] << " axis 2: " << dataPoints[*i][1] - randomCenters[h][1] << endl;
			//assign value to storedDistances using pythagorean theorem
			double v = pow(dataPoints[*i][0] - randomCenters[h][0], 2.0);
			double vtwo = pow(dataPoints[*i][1] - randomCenters[h][1], 2.0);
			double vthree = v + vtwo;
			double dist = pow(vthree, 0.5);
			cout << distCount << ": " << dist << endl;
			distCount++;
			storedDistances[h][*i] = dist;
			cout << "Distance stored." << endl;
			
		}
		
	}
	
	cout << "Distances Stored!." << endl;
	return 0;
}
//Postcondition: Assign points after

//Precondition: distances are initialized, ideally calculated distances
//and not 0.0
void Partitioner::PrintDistances()
{
	
	for (int i = 0; i < cl; i++)
	{
		int zero = 0;
		cout << "Distances for point " << i << endl;
		for (int* j = &zero; *j < *(datacollect->GetCount()); ++*j)
		{
			cout << storedDistances[i][*j] << endl;
		}
	}
	this->AssignPoints();
}
//Postcondition: distances are printed

//Precondition: clusterAssignments have to be initialized, ideally
//includes assignments and not just initialzed with -1
void Partitioner::AssignPoints()
{
	
	
	int minimum;
	int zero = 0;
	int counts[cl];
	//current index of each cluster
	for (int c = 0; c < cl; c++)
	{
		counts[c] = 0;
	}
	for (int i = 0; i < cl; i++)
	{
		
		for (int* j = &zero; *j < *(datacollect->GetCount()); ++(*j))
		{
			double pointDistances[cl];// add center count - 1
			for (int c = 0; c < cl; c++)
			{
				pointDistances[c] = storedDistances[i + c][*j];
			}
			minimum = this->FindMinimum(pointDistances); //minimum will be 0th, 1st,...nth cluster//
			//*j is the data point//
			//clusterAssignments[minimum]
			clusterAssignments[minimum][counts[minimum]] = *j;
			counts[minimum] = counts[minimum] + 1;
			//rest have to be set back to -1//
			
		}
		zero = 0;
		for (int* j = &zero; *j < *(datacollect->GetCount()); ++(*j))
		{
			for (int k = 0; k < cl; k++)
			{
				if(*j >= counts[k])
				{
					//The rest of the row is set to -1
					//to show there is no assignment
					clusterAssignments[k][*(j)] = -1;
				}
			}
			
		}
	}
	
	
		
	
	
}
//Postcondition: Use before adjusting centers

//function to find minimum distance
//Precondition: an array of doubles must be inputted
int Partitioner::FindMinimum(double vals[])
{
	int minimum = 0;
	for (int i = 1; i < cl; i++)
	{
		if(vals[i] < vals[minimum])
		{
			minimum = i;
		}
	}
	return minimum;
}
//Postcondition: used as an integer index, ***returns index of minimum not minimum value***

//Precondition: clusterAssignments are initialized
void Partitioner::PrintClusterAssignments()
{
	
	cout << "Cluster assignments: " << endl;
	for (int a = 0; a < cl; a++)
	{
		int zero = 0;
		for (int* b = &zero; *b < *(datacollect->GetCount()); (*b)++)
		{
			int assign = clusterAssignments[a][*b];
			if (assign != -1)
			{
				cout << assign << " ";
			}
			
		}
		cout << "" << endl;
	}
}
//Postcondition: cluster assignments are printed

//take average of points to reposition clusters//

//Precondition: Must have centers iniialized, used after data points are assigned
int Partitioner::ReadjustCenters()
{
	int** dataPoints = datacollect->GetData();
	int staysSame = 0;//number of centers that stay the same
	for (int a = 0; a < cl; a++)
	{
		int zero = 0;
		double sumOne = 0;//used to average first coordinate
		double sumTwo = 0;//used to average second coordinate
		double dataCount = 0; // points assigned to the cluster
		for (int* b = &zero; *b < *(datacollect->GetCount()); (*b)++)
		{
			int assign = clusterAssignments[a][*b];
			//assign is point out of 9
			if(assign == -1)
			{
				break;
			}
			dataCount += 1;
			double pointLocationOne = dataPoints[assign][0];//location
			double pointLocationTwo = dataPoints[assign][1];//location
			sumOne += pointLocationOne;
			sumTwo += pointLocationTwo;
		}
		cout << "Data count: " << dataCount << endl;
		if ((sumOne / dataCount) == randomCenters[a][0] && (sumTwo / dataCount) == randomCenters[a][1])
		{
			if(dataCount > 0)
			{
				staysSame += 1;
			}
			
		}
		if(dataCount > 0)
		{
			randomCenters[a][0] = (double)(sumOne / dataCount);
			randomCenters[a][1] = (double)(sumTwo / dataCount);
		}
		else
		{
			//if the cluster is empty I decided to make a new random center//
			randomCenters[a][0] = (rand() % 10) + 1;
			randomCenters[a][1] = (rand() % 10) + 1;
		}
		
		
		
		cout << "New cluster pos: " << randomCenters[a][0] << ", " << randomCenters[a][1] << endl;
		dataCount = 0;
	}
	return staysSame;
}
//Postcondition: Use as an int to count centers that stayed the same