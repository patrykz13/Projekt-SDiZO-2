#pragma once
#include "Graph.h"

class AdjacencyMatrix:public Graph
{
	int **matrixDirected;
	int **matrixUndirected;
	int **resultsForMatrix;
public:
	~AdjacencyMatrix();
	AdjacencyMatrix();
	void createMatrixForDirectedGraph();
	void createMatrixForUndirectedGraph();
	void printMatrixDirected();
	void printMatrixUndirected();
	bool minDistance(int *dist, bool *sptSet);
	virtual void PrimAlgorithm(bool) override;
	virtual void DijikstraAlgoritm(int, bool) override;
	virtual void BellmanFordAlgorithm(int, bool) override;
	virtual void KruskalAlgorithm(bool) override;

};
