
#include <string>

class Graph 
{
protected:
	const int MAXINT = 2147483647;
	int maxWeight, minEdges;
	double maxEdges;
	int **result;
	int verticles;
	int edges;
	int startVerticle;
	int finishVerticle;
	int **directedGraph;
	int **undirectedGraph;
	int edgeY;

public:
	int getStartVerticle();
	void createRandomGraph();
	bool readFromFile(std::string);
	void createDirectedGraph();
	void createUndirectedGraph();
	virtual void PrimAlgorithm(bool) = 0;
	virtual void DijikstraAlgoritm(int,bool) = 0;
	virtual void BellmanFordAlgorithm(int,bool) = 0;
	virtual void KruskalAlgorithm(bool) = 0;
	virtual ~Graph();

};

#pragma once
