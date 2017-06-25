#pragma once
#include "Graph.h"

class AdjacencyList :public Graph
{

	struct ListElement {
		ListElement *next;
		int n;
		int weight;
	};

	int **resultForList;

	ListElement **listUndirectional;
	ListElement **ListDirectional, *helpList;


public:
	~AdjacencyList();
	AdjacencyList();
	void createUndirectedAdjacencyList();
	void createDirectedAdjacencyList();
	void printUndirectedAdjacencyList();
	void printDirectedAdjacencyList();
	virtual void PrimAlgorithm(bool) override;
	virtual void DijikstraAlgoritm(int, bool) override;
	virtual void BellmanFordAlgorithm(int, bool) override;
	virtual void KruskalAlgorithm(bool) override;

};
