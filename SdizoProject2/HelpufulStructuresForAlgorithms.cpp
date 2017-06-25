#include "HelpufulStructuresForAlgorithms.h"
#include <iostream>
#include <ctime>
#include<string>
#include<fstream>
#include <vector>
#include <random>
using namespace std;
Heap::Heap()
{
	srand(time(nullptr));
	heapArray = new Edge[0];
	size = 0;
}
Heap::~Heap()
{
	delete[]heapArray;
	heapArray = nullptr;

}
	
Edge Heap::getTopElement()
{
	return heapArray[0];
}



void Heap::addEdge(Edge e)
{
	

	Edge * tmp = new Edge[size+1];
	for (int i = 0; i < size; i++)
	{
		tmp[i] = heapArray[i];
	}
	delete[] heapArray;
	heapArray = tmp;

	int i, j;
	i = size++;
	j = (i - 1) / 2; //indeks rodzica

	while (i > 0 && heapArray[j].weight> e.weight) //warunek kopca 
	{
		heapArray[i] = heapArray[j];
		i = j;
		j = (i - 1) / 2;

	}

	heapArray[i] = e;
}

int Heap::getSize()
{
	return size;
}


void Heap::deleteTop()
{
	int i, j;
	Edge e;
	
	if (size == 0)
	{
		std::string exception = "Kopiec jest pusty";
		throw exception;
	}

	if (size--)
	{
		e = heapArray[size];

		i = 0;
		j = 1;

		while (j < size) //idziemy w dol kopca
		{
			if (j + 1 < size && heapArray[j + 1].weight < heapArray[j].weight) j++; //szukamy wiekszego syna
			if (e.weight <= heapArray[j].weight) break;
			heapArray[i] = heapArray[j]; //przenosimy wiekszego syna do ojca
			i = j; // skok na indeks wiekszego syna
			j = 2 * j + 1; //indeks lewego syna
		}

		heapArray[i] = e;
	}
	// alokcja nowej tablicy
	Edge * tmp = new Edge[size];
	for (int i = 0; i < size; i++)
	{
		tmp[i] = heapArray[i];
	}
	delete[] heapArray;
	heapArray = tmp;
}



DisjointSet::DisjointSet(int n)
{
	Z = new DisjointSetNode[n];
}


DisjointSet::~DisjointSet()
{
	delete[] Z;
}


void DisjointSet::make(int verticle)
{
	Z[verticle].parent = verticle;
	Z[verticle].rank = 0;
}


int DisjointSet::find(int verticle)
{
	if (Z[verticle].parent != verticle) Z[verticle].parent = find(Z[verticle].parent);
	return Z[verticle].parent;
}

void DisjointSet::UnionSets(Edge element)
{

	int rootA = find(element.verticleFrom); 
	int rootB = find(element.verticleTo);
	if (rootA != rootB)
	{
		if (Z[rootA].rank > Z[rootB].rank)
			Z[rootB].parent = rootA;
		else
		{
			Z[rootA].parent = rootB;
			if (Z[rootA].rank == Z[rootB].rank) Z[rootB].rank++;
		}
	}
}



QueueHeapForDijkstraAlgorithm::QueueHeapForDijkstraAlgorithm(int _size, int start)
{
	this->size = _size;
	queue = new Verticle[size];

	for (int i = 0; i < size; i++) {
		queue[i].nr = i;
		queue[i].cost = INT_MAX;
	}
	this->changeCost(start, 0);
}

QueueHeapForDijkstraAlgorithm::~QueueHeapForDijkstraAlgorithm()
{
	delete[] queue;
}

Verticle QueueHeapForDijkstraAlgorithm::pop()
{
	Verticle ret = queue[0];

	this->size--;

	Verticle* buf = new Verticle[this->size];
	memcpy(buf, queue + 1, size * sizeof(Verticle));

	delete[] queue;

	queue = buf;

	heap_fix_down();
	return ret;
}

void QueueHeapForDijkstraAlgorithm::heap_fix_down()
{
	int i = 0;
	int j = 1;

	while (j < size) {
		if (j + 1 < this->size && queue[j].cost > queue[j + 1].cost)
			j++;

		if (queue[i].cost <= queue[j].cost)
			return;

		Verticle buf = queue[j];
		queue[j] = queue[i];
		queue[i] = buf;
		i = j;
		j = 2 * i + 1;
	}
	return;
}

void QueueHeapForDijkstraAlgorithm::heap_fix_up(int index)
{
	int i = index;
	int parent = (i - 1) / 2;

	while (queue[parent].cost > queue[i].cost && i != 0) {

		Verticle buf = queue[i];
		queue[i] = queue[parent];
		queue[parent] = buf;
		i = parent;
		parent = (i - 1) / 2;
	}
}

void QueueHeapForDijkstraAlgorithm::changeCost(int v_nr, int cost)
{
	int idx;
	for (int i = 0; i < this->size; i++) {
		if (queue[i].nr == v_nr) {
			idx = i;
			queue[i].cost = cost;
			break;
		}
	}
	heap_fix_up(idx);
}
