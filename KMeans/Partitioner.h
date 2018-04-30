#ifndef PARTITIONER_H
#define PARTITIONER_H
#include "DataCollection.h"

//K-Means Algorithm
class Partitioner
{
public:
	Partitioner(DataCollection datac);
	~Partitioner();
	
	int InitializeCenters(int clusters);//Centers are randomly selected
	int InitializeDistances();
	int PrintCenters();//show center coordinates
	int MeasureDistances();//measure the distances from each data point to each center
	void PrintDistances();
	void AssignPoints();//assign the data points to correct cluster
	int FindMinimum(double vals[]);
	void PrintClusterAssignments();//shows the cluster assignments
	int ReadjustCenters();
	
private:
	double** randomCenters;
	double** storedDistances;
	DataCollection* datacollect;
	int** clusterAssignments;
	int cl;
};

#endif // PARTITIONER_H
