#ifndef DATACOLLECTION_H
#define DATACOLLECTION_H

class DataCollection
{
public:
	DataCollection();
	DataCollection(int* points);
	~DataCollection();
	int PrintData();
	int** GetData();
	int* GetCount();

private:
	int** dataPoints;
	int* pointCount;
};

#endif // DATACOLLECTION_H
