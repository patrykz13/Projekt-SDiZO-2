#include "AdjacencyList.h"
#include <iostream>
#include <iomanip>      // std::setw
#include "HelpufulStructuresForAlgorithms.h"
#include <vector>

using namespace std;
AdjacencyList::~AdjacencyList()
{

	for (int i = 0; i < edges; i++) {
		delete[] directedGraph[i];
		delete[] undirectedGraph[i];
	}
	delete[]directedGraph;
	delete[]undirectedGraph;
	directedGraph = nullptr;
	undirectedGraph = nullptr;

	for (int i = 0; i < verticles; i++) {
		delete[] listUndirectional[i];
		delete[] ListDirectional[i];
	}
	delete[]listUndirectional;
	delete[]ListDirectional;
	ListDirectional = nullptr;
	listUndirectional = nullptr;
}
AdjacencyList::AdjacencyList()
{
}
void AdjacencyList::createUndirectedAdjacencyList() {
	listUndirectional = new ListElement *[verticles];
	for (int i = 0; i < verticles; i++)
		listUndirectional[i] = nullptr;

	for (int i = 0; i < edgeY; i++) {
		helpList = new ListElement;
		helpList->n = undirectedGraph[i][1];
		helpList->weight = undirectedGraph[i][2];
		helpList->next = listUndirectional[undirectedGraph[i][0]];
		listUndirectional[undirectedGraph[i][0]] = helpList;


		helpList = new ListElement;
		helpList->n = undirectedGraph[i][0];
		helpList->weight = undirectedGraph[i][2];
		helpList->next = listUndirectional[undirectedGraph[i][1]];
		listUndirectional[undirectedGraph[i][1]] = helpList;
	}

}

void AdjacencyList::printUndirectedAdjacencyList() {
	for (int i = 0; i < verticles; i++) {
		cout << "A[" << i << "] =";
		helpList = listUndirectional[i];
		while (helpList) {
			cout << setw(6) << helpList->n << "(" << helpList->weight << ")";
			helpList = helpList->next;
		}
		cout << endl;
	}
}

void AdjacencyList::createDirectedAdjacencyList() {
	ListDirectional = new ListElement *[verticles];
	for (int i = 0; i < verticles; i++)
		ListDirectional[i] = nullptr;

	for (int i = 0; i < edges; i++) {

		helpList = new ListElement;
		helpList->n = directedGraph[i][1];
		helpList->weight = directedGraph[i][2];
		helpList->next = ListDirectional[directedGraph[i][0]];
		ListDirectional[directedGraph[i][0]] = helpList;
	}

}

void AdjacencyList::printDirectedAdjacencyList() {
	for (int i = 0; i < verticles; i++) {
		cout << "A[" << i << "] =";
		helpList = ListDirectional[i];
		while (helpList) {
			cout << setw(6) << helpList->n << "(" << helpList->weight << ")";
			helpList = helpList->next;
		}
		cout << endl;
	}
}

void AdjacencyList::PrimAlgorithm(bool printResult)
{

	resultForList = new int*[verticles - 1];
	Edge edge;
	int i;
	int z = 0;
	Heap heap;
	bool * visitedVerticles = new bool[verticles];

	for (i = 0; i < verticles; i++)
		visitedVerticles[i] = false;

	int v = 0;
	visitedVerticles[v] = true;

	for (i = 0; i < verticles - 1; i++)
	{
		for (helpList=listUndirectional[v]; helpList!=nullptr; helpList=helpList->next) {
			if (helpList->weight != 0 && helpList->weight < 11 && visitedVerticles[helpList->n] == false) {
				edge.verticleFrom = v;
				edge.verticleTo = helpList->n;
				edge.weight = helpList->weight;
				heap.addEdge(edge);
			}
		}

		do
		{
			edge = heap.getTopElement();
			heap.deleteTop();
		} while (visitedVerticles[edge.verticleTo]);

		resultForList[z] = new int[3];
		resultForList[z][0] = edge.verticleTo;
		resultForList[z][1] = edge.verticleFrom;
		resultForList[z][2] = edge.weight;
		visitedVerticles[edge.verticleTo] = true;
		v = edge.verticleTo;
		z++;

	}

	if(printResult)
	{
		int MST = 0;
		for (i = 0; i < verticles - 1; i++) {
			cout << "(" << resultForList[i][0] << "," << resultForList[i][1] << ")   " << resultForList[i][2] << endl;
			MST += resultForList[i][2];
		}
		cout << "MST: " << MST << endl;
	}
	

	for (int i = 0; i<verticles - 1; i++)
	{
		delete resultForList[i];
	}
	delete[]resultForList;
	delete[] visitedVerticles;


}

	

	


void AdjacencyList::DijikstraAlgoritm(int start, bool printResult)
{

	QueueHeapForDijkstraAlgorithm QueueHeap(verticles, start);
	bool ujemne = false;
	if (printResult)
	{

		for (int i = 0; i < verticles-1; i++)
		{
			for (helpList = ListDirectional[i]; helpList!=nullptr; helpList = helpList->next)
				if (helpList->weight<0)
				{
					cout << "Ujemne wagi algorytm moze nie zadzialac poprawnie!" << endl;;
					ujemne = true;
					break;
				}
			if(ujemne)
			{
				break;
			}
				
		}

	}

	Verticle* verticlesCostArray = new Verticle[verticles];
	bool* visitedVerticle = new bool[verticles];

	for (int i = 0; i < verticles; i++) {

		if (i == start)
			verticlesCostArray[i].cost = 0;
		else
			verticlesCostArray[i].cost = INT_MAX;
			verticlesCostArray[i].nr = -1;
		visitedVerticle[i] = false;
	}

	for (int i = 0; i < verticles; i++) {

		Verticle v = QueueHeap.pop();
		visitedVerticle[v.nr] = true;


		if (verticlesCostArray[v.nr].nr == -1 && v.nr != start)
			break;


		int n_adj = 0;
		Verticle* adj = new Verticle[n_adj];

		ListElement* ptr = ListDirectional[v.nr];

		while (ptr != nullptr) {
			Verticle* buf = new Verticle[n_adj + 1];
			memcpy(buf, adj, n_adj * sizeof(Verticle));
			buf[n_adj].nr = ptr->n;
			buf[n_adj].cost = ptr->weight;

			delete[] adj;
			adj = buf;
			n_adj++;

			ptr = ptr->next;
		}

		for (int ad = 0; ad < n_adj; ad++) {
			if (visitedVerticle[adj[ad].nr] == true)
				continue;
			if (verticlesCostArray[adj[ad].nr].cost > adj[ad].cost + verticlesCostArray[v.nr].cost) {

				verticlesCostArray[adj[ad].nr].cost = adj[ad].cost + verticlesCostArray[v.nr].cost;
				verticlesCostArray[adj[ad].nr].nr = v.nr;

				QueueHeap.changeCost(adj[ad].nr, verticlesCostArray[adj[ad].nr].cost);
			}
		}

	}

	if (printResult)
	{
		int * Stack = new int[verticles];
		int stackPointer = 0;
		cout << "Startowy " << startVerticle << endl;
		cout << "End    Dist    Path" << endl;
		for (int i = 0; i < verticles; i++) {
			cout << i << ": ";
			for (int j = i; j > -1; j = verticlesCostArray[j].nr) Stack[stackPointer++] = j;
			cout << "   | " << verticlesCostArray[i].cost << " |   ";
			while (stackPointer) cout << Stack[--stackPointer] << " ";
			cout << endl;
		}
	}

		
	

		

}
			
	


	

void AdjacencyList::BellmanFordAlgorithm(int startVerticle, bool printResult)
{
	int z, j, i;
	long long * cost = new long long[verticles];
	int * path = new int[verticles];
	int * Stack = new int[verticles];
	int stackPointer = 0;
	for (i = 0; i < verticles; i++)
	{
		cost[i] = MAXINT;
		path[i] = -1;
	}
	cost[startVerticle] = 0;
	for (i = 0; i < verticles-1; i++)
	{
		for (z = 0; z < verticles; z++) 
			for (helpList = ListDirectional[z]; helpList!=nullptr; helpList = helpList->next) 
				if (cost[helpList->n] > cost[z] + helpList->weight)
				{
					cost[helpList->n] = cost[z] + helpList->weight; 
					path[helpList->n] = z;
				}
	}


	for (i = 0; i < verticles; i++)
	{
		for (helpList = ListDirectional[i]; helpList!=nullptr; helpList = helpList->next)
		{
			if (cost[helpList->n] > cost[i] + helpList->weight) throw " Znaleziono scie¿kê o ujemnym cyklu - STOP";

		}

	}




	
	if (printResult)
	{
		cout << "Startowy " << startVerticle << endl;
		cout << "End    Dist    Path" << endl;
		for (i = 0; i < verticles; i++) {
			cout << i << ": ";
			for (j = i; j > -1; j = path[j]) Stack[stackPointer++] = j;
			cout << "   | " << cost[i] << " |   ";
			while (stackPointer) cout << Stack[--stackPointer] << " ";
			cout << endl;
		}
	}


	


	delete[] cost;
	delete[] path;
	delete[] Stack;
	
}

void AdjacencyList::KruskalAlgorithm(bool printResult)
{
	resultForList = new int*[verticles - 1];
	Edge edge;
	int i;
	Heap  heap;
	DisjointSet set(verticles);
	int z = 0;
	for (i = 0; i < verticles; i++)
		set.make(i); 

	for (i = 0; i < verticles ; i++)
	{
		for (helpList = listUndirectional[i]; helpList != nullptr; helpList = helpList->next) {
			if (helpList->weight != 0 && helpList->weight < 11 ) {

				edge.verticleFrom = i;
				edge.verticleTo = helpList->n;
				edge.weight = helpList->weight;
				heap.addEdge(edge);
			}
		}
	}

	for (i = 0; i < verticles - 1; i++)
	{
		do
		{
			edge = heap.getTopElement();
			heap.deleteTop();
		} while (set.find(edge.verticleFrom) == set.find(edge.verticleTo));
		resultForList[z] = new int[3];
		resultForList[z][0] = edge.verticleTo;
		resultForList[z][1] = edge.verticleFrom;
		resultForList[z][2] = edge.weight;
		z++;
		set.UnionSets(edge);
	}

	if(printResult)
	{
		int MST = 0;
		for (i = 0; i < verticles - 1; i++) {
			cout << "(" << resultForList[i][0] << "," << resultForList[i][1] << ")   " << resultForList[i][2] << endl;
			MST += resultForList[i][2];
		}
		cout << "MST: " << MST << endl;


	}

	for (i = 0; i<verticles - 1; i++)
	{
		delete resultForList[i];
	}
	delete[]resultForList;

	

}
