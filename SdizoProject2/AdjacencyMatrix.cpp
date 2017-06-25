#include "AdjacencyMatrix.h"
#include <iostream>
#include <vector>
#include "HelpufulStructuresForAlgorithms.h"
using namespace std;
AdjacencyMatrix::~AdjacencyMatrix()
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
		delete[] matrixDirected[i];
		delete[] matrixUndirected[i];
	}

	delete[]matrixDirected;
	delete[]matrixUndirected;
	matrixDirected = nullptr;
	matrixUndirected = nullptr;

}
AdjacencyMatrix::AdjacencyMatrix()
{
}
void AdjacencyMatrix::createMatrixForDirectedGraph()
{
	matrixDirected = new int *[verticles];
	for (int i = 0; i < verticles; i++) {
		matrixDirected[i] = new int[verticles];
	}
	for (int i = 0; i < verticles; i++) {
		for (int j = 0; j < verticles; j++) {
			matrixDirected[i][j] = 999;
		}
	}
	for (int i = 0; i < edges; i++) {
		matrixDirected[directedGraph[i][0]][directedGraph[i][1]] = directedGraph[i][2];
	}
}

void AdjacencyMatrix::createMatrixForUndirectedGraph()
{
	matrixUndirected = new int *[verticles];
	for (int i = 0; i < verticles; i++) {
		matrixUndirected[i] = new int[verticles];
	}
	for (int i = 0; i < verticles; i++) {
		for (int j = 0; j < verticles; j++) {
			matrixUndirected[i][j] = 999;
		}
	}

	for (int i = 0; i < edgeY; i++) {
		matrixUndirected[undirectedGraph[i][0]][undirectedGraph[i][1]] = undirectedGraph[i][2];
		matrixUndirected[undirectedGraph[i][1]][undirectedGraph[i][0]] = undirectedGraph[i][2];
	}
}

void AdjacencyMatrix::printMatrixDirected()
{
	for (int i = 0; i < verticles; i++) {
		for (int j = 0; j < verticles; j++) {
			cout << matrixDirected[i][j] << " ";
		}
		cout << endl;
	}
	
}

void AdjacencyMatrix::printMatrixUndirected()
{
	for (int i = 0; i < verticles; i++) {
		for (int j = 0; j < verticles; j++) {
			cout << matrixUndirected[i][j] << " ";
		}
		cout << endl;
	}
}

void AdjacencyMatrix::PrimAlgorithm(bool printResult)
{
	resultsForMatrix = new int*[verticles - 1]; 
	Edge edge;
	int i, v, z;
	z = 0;
	Heap heap;                  
	bool * visitedVerticles = new bool[verticles];

	for (i = 0; i < verticles; i++)
		visitedVerticles[i] = false;          

	v = 0;
	visitedVerticles[v] = true;          

	for (i = 0; i < verticles-1; i++)  
	{
		for (int j = 0; j < verticles; j++) {
			if (matrixUndirected[v][j] != 999 && matrixUndirected[v][j] < 11 &&
				!visitedVerticles[j]) {
				edge.verticleFrom = v;
				edge.verticleTo = j;
				edge.weight = matrixUndirected[v][j];
				heap.addEdge(edge);
			}
		}

		do
		{
			edge = heap.getTopElement();       
			heap.deleteTop();
		} while (visitedVerticles[edge.verticleTo]);       

		resultsForMatrix[z] = new int[3];
		resultsForMatrix[z][0] = edge.verticleTo;
		resultsForMatrix[z][1] = edge.verticleFrom;
		resultsForMatrix[z][2] = edge.weight;   
		visitedVerticles[edge.verticleTo] = true;   
		v = edge.verticleTo;
		z++;

	}

	if(printResult)
	{
		int MST = 0;
		for (i = 0; i < verticles - 1; i++) {
			cout << "(" << resultsForMatrix[i][0] << "," << resultsForMatrix[i][1] << ")   " << resultsForMatrix[i][2] << endl;
			MST += resultsForMatrix[i][2];
		}
		cout << "MST: " << MST << endl;
	}
	

	delete[] visitedVerticles;
	for(i=0;i<verticles - 1;i++)
	{
		delete resultsForMatrix[i];
	}
	
}


void AdjacencyMatrix::KruskalAlgorithm(bool printResult)
{
	resultsForMatrix = new int*[verticles - 1];
	Edge edge;
	int i;
	Heap heap;
	DisjointSet set(verticles);
	int z = 0;
	for (i = 0; i < verticles; i++)
		set.make(i);

	for (i = 0; i < verticles; i++)
	{
		for (int j = 0; j < verticles; j++) {
			if (matrixUndirected[i][j] != 999 && matrixUndirected[i][j] < 11) {
				edge.verticleFrom = i;
				edge.verticleTo = j;
				edge.weight = matrixUndirected[i][j];
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
		resultsForMatrix[z] = new int[3];
		resultsForMatrix[z][0] = edge.verticleTo;
		resultsForMatrix[z][1] = edge.verticleFrom;
		resultsForMatrix[z][2] = edge.weight;
		z++;
		set.UnionSets(edge);
	}

	if(printResult)
	{
		int MST = 0;
		for (i = 0; i < verticles - 1; i++) {
			cout << "(" << resultsForMatrix[i][0] << "," << resultsForMatrix[i][1] << ")   " << resultsForMatrix[i][2] << endl;
			MST += resultsForMatrix[i][2];
		}
		cout << "MST: " << MST << endl;
	}

	for (int i = 0; i<verticles - 1; i++)
	{
		delete resultsForMatrix[i];
	}
}

void AdjacencyMatrix::DijikstraAlgoritm(int start, bool printResult)
{
	bool ujemne = false;
	for (int i = 0; i < verticles; i++)
	{
		for (int j = 0; j<verticles; j++)
			if (matrixDirected[i][j]<0)
			{
				cout << "Ujemne wagi algorytm moze nie zadzialac poprawnie!" << endl;;
				ujemne = true;
				break;
			}
		if (ujemne)
		{
			break;
		}

	}
	QueueHeapForDijkstraAlgorithm QueueHeap(verticles, start);
	int * Stack = new int[verticles];
	int stackPointer = 0;

	Verticle* verticlesCostArray = new Verticle[verticles];
	bool* QS = new bool[verticles];

	for (int i = 0; i < verticles; i++) {

		if (i == start)
			verticlesCostArray[i].cost = 0;
		else
			verticlesCostArray[i].cost = INT_MAX;
			verticlesCostArray[i].nr = -1;
		QS[i] = false;
	}

	for (int i = 0; i < verticles; i++) {

		Verticle v = QueueHeap.pop();
		QS[v.nr] = true;

		if (verticlesCostArray[v.nr].nr == -1 && v.nr != start)
			break;

		int n_adj = 0;
		Verticle* adj = new Verticle[n_adj];


			for (int j = 0; j < verticles; j++) {
				if (matrixDirected[v.nr][j] != 999 && matrixDirected[v.nr][j] < 11) {
					Verticle* buf = new Verticle[n_adj + 1];
					memcpy(buf, adj, n_adj * sizeof(Verticle));
					buf[n_adj].nr = j;
					buf[n_adj].cost = matrixDirected[v.nr][j];

					delete[] adj;
					adj = buf;
					n_adj++;

				}
			}

		

		for (int ad = 0; ad < n_adj; ad++) {
			if (QS[adj[ad].nr] == true)
				continue;
			if (verticlesCostArray[adj[ad].nr].cost > adj[ad].cost + verticlesCostArray[v.nr].cost) {

				verticlesCostArray[adj[ad].nr].cost = adj[ad].cost + verticlesCostArray[v.nr].cost;
				verticlesCostArray[adj[ad].nr].nr = v.nr;

				QueueHeap.changeCost(adj[ad].nr, verticlesCostArray[adj[ad].nr].cost);
			}
		}

	}

	if(printResult)
	{
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
		
	
		delete[]Stack;
		delete[]verticlesCostArray;
}

void AdjacencyMatrix::BellmanFordAlgorithm(int startVerticle, bool printResult)
{

	int x, j, i;
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
	
	for (x = 1; x < verticles; x++)
	{
		for (i = 0; i < verticles; i++)
		{
			for (j = 0; j < verticles; j++) {
				if (matrixDirected[i][j] != 999 && matrixDirected[i][j] < 11) {

					if (cost[j] > cost[i] + matrixDirected[i][j])
					{
						cost[j] = cost[i] + matrixDirected[i][j];
						path[j] = i;
					}

				}
			}
		}
	}

	for (i = 0; i < verticles; i++)
	{
		for (j = 0; j < verticles; j++) {
			if ((cost[j] > cost[i] + matrixDirected[i][j])&&matrixDirected[i][j] != 999) {
				throw " Znaleziono scie¿kê o ujemnym cyklu - STOP";
			}
		}

	}


	if(printResult)
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


