#include <iostream>
using namespace std;
#include "DataCollection.h"
#include "Partitioner.h"

//Implementation of the K-Means algorithm//



void Run()
{
	int clu;
	//User enter both # of clusters and # of data Points
	cout << "Enter number of clusters." << endl;
	cin >> clu;
	int dP;
	cout << "Enter number of data points." << endl;
	cin >> dP;
	int* numbOfClusters = &clu; //number of clusters
	
	int* dataPoints = &dP; // number of data points
	
	
	DataCollection* dc = new DataCollection(dataPoints);
	Partitioner* p = new Partitioner(*dc);
	
	cout << "Print Data." << endl;
	dc->PrintData();
	cout << "Initialize Centers" << endl;
	p->InitializeCenters(clu);
	cout << "Print Centers." << endl;
	p->InitializeDistances();
	p->PrintCenters();
	cout << "Measure Distances."  << endl;
	int testConvergence = 0;
	//Repeat until the same cluster centers occur
	while(testConvergence != clu)
	{
		p->MeasureDistances();
		p->PrintDistances();
		p->PrintClusterAssignments();
		testConvergence = p->ReadjustCenters();
	}
	cout << "Finished." << endl;
}


int main()
{
	Run();
	return 0;
}

