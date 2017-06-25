#include "Graph.h"
#include <vector>
#include <ctime>
#include <iostream>
#include <fstream>
#include<string>
using namespace std;
int Graph::getStartVerticle()
{
	return startVerticle;
}
void Graph::createRandomGraph()
{
		int verticles2 = 0;
		float density = 0;

		do {
			cout << "Podaj liczbe wierzcholkow ";
			cin >> verticles2;
		} while (verticles2 < 2);


		this->verticles = verticles2;
		maxWeight = 9;
		minEdges = verticles - 1;								//minimalna ilosc krawedzi dla grafu spojnego
		maxEdges = ((verticles - 1)*verticles) / 2;
		int minDensity = ceil((minEdges / maxEdges) * 100);

		do {
			cout << "Podaj gestosc (minimum " << minDensity << "%) " << endl;
			cin >> density;
		} while (density < minDensity || density >= 100);


		edges = ceil(maxEdges*(density / 100));					//pozadana liczba krawedzi
		int weight;
		result = new int *[2 * edges];

		//kreowanie drzewa
		vector <int> tab;									//vektor pamietajacy czy wierzcholek byl juz odwiedzony
		for (int i = 0; i < verticles; i++)	tab.push_back(i);

		srand(time(NULL));
		int next, previous;
		previous = rand() % verticles;
		tab[previous] = -1;
		for (int i = 1; i < minEdges + 1; i++) {
			while (true) {
				next = rand() % verticles;
				if (tab[next] >= 0)
					break;
			}

			result[i - 1] = new int[3];
			result[i - 1][0] = previous;
			result[i - 1][1] = next;
			weight = (rand() % maxWeight) + 1;
			result[i - 1][2] = weight;
			tab[next] = -1;
			previous = next;
		}
		bool czyJest = false;
		for (int i = minEdges; i < edges; i++) {
			while (true) {
				czyJest = false;
				previous = rand() % verticles;
				next = rand() % verticles;
				for (int j = 0; j < i; j++) {
					if ((result[j][0] == previous && result[j][1] == next) || (result[j][0] == next && result[j][1] == previous) || (next == previous)) {
						czyJest = true;
						break;
					}
				}
				if (czyJest == false) {
					result[i] = new int[3];
					result[i][0] = previous;
					result[i][1] = next;
					weight = rand() % maxWeight + 1;
					result[i][2] = weight;
					break;
				}
			}

		}

		int help;
		for (int i = edges; i < edges * 2; i++) {

			while (true) {
				czyJest = false;
				previous = rand() % verticles;
				next = rand() % verticles;
				for (int j = 0; j < i; j++) {

					if ((result[j][0] == previous && result[j][1] == next) || (next == previous)) {
						czyJest = true;
						break;
					}

				}
				if (czyJest == false) {
					result[i] = new int[3];
					result[i][0] = previous;
					result[i][1] = next;
					weight = rand() % maxWeight + 1;
					result[i][2] = weight;
					break;
				}
			}

		}



		fstream plik("plik.txt", ios::out);				//wpisuje do pliku 
		if (plik.good()) {
			plik << 2 * edges << " " << verticles << " " << result[0][0] << " " << result[verticles - 1][0] << "\n";
			for (int i = 0; i < 2 * edges; i++)	plik << result[i][0] << " " << result[i][1] << " " << result[i][2] << "\n";
			plik.close();
		}

		for(int i=0;i<2 * edges;i++)
		{
			delete result[i];
		}
	}


bool Graph::readFromFile(string filename)
{
	bool success = false;
	

	fstream file(filename, std::ios::in);
	if (file.is_open()) {
		file >> edges;
		file >> verticles;
		file >> startVerticle;
		file >> finishVerticle;
		directedGraph = new int *[edges];
		if (file.fail())
			cout << "blad" << endl;
		else {
			int source, destination, localWeight;
			for (int i = 0; i < edges; i++) {
				file >> source;
				file >> destination;
				file >> localWeight;

				if (file.fail()) {
					throw  "blad";
					break;
				}
				else {
					directedGraph[i] = new int[3];
					directedGraph[i][0] = source;
					directedGraph[i][1] = destination;
					directedGraph[i][2] = localWeight;
				}
			}
		}

		file.close();
		success = true;
	}
	else {
		cout << "blad" << endl;
		success = false;
	}

	return success;
}
void Graph::createDirectedGraph() {				//wczytuje plik na podstawie ktorego utworzy tablice bazowa z danymi dla skierowanego
	fstream file("plik.txt", std::ios::in);
	if (file.is_open()) {
		file >> edges;
		file >> verticles;
		file >> startVerticle;
		file >> finishVerticle;
		directedGraph = new int *[edges];
		if (file.fail())
			cout << "blad" << endl;
		else {
			int source, destination, localWeight;
			for (int i = 0; i < edges; i++) {
				file >> source;
				file >> destination;
				file >> localWeight;

				if (file.fail()) {
					cout << "blad" << endl;
					break;
				}
				else {
					directedGraph[i] = new int[3];
					directedGraph[i][0] = source;
					directedGraph[i][1] = destination;
					directedGraph[i][2] = localWeight;
				}
			}
		}

		file.close();
	}
	else
		cout << "blad" << endl;

}

void Graph::createUndirectedGraph() {			//tablica bez powtorzonych wierzcholkow potrzebna dla operacji na grafie nieskierowanym
	bool *duplicate;
	duplicate = new bool[edges];
	for (int i = 0; i < edges; i++)
		duplicate[i] = false;
	undirectedGraph = new int *[edges];
	for (int i = 0; i < edges; i++)
		undirectedGraph[i] = nullptr;

	for (int i = 0; i < edges; i++) {
		for (int j = 0; j < i; j++) {
			if ((directedGraph[i][0] == directedGraph[j][0] && directedGraph[i][1] == directedGraph[j][1]) || (directedGraph[i][1] == directedGraph[j][0] && directedGraph[i][0] == directedGraph[j][1])) {
				duplicate[i] = false;
				break;
			}
			duplicate[i] = true;
		}
	}

	duplicate[0] = true;
	edgeY = 0;
	for (int i = 0; i < edges; i++) {
		if (duplicate[i] == true) {
			undirectedGraph[edgeY] = new int[3];
			undirectedGraph[edgeY][0] = directedGraph[i][0];
			undirectedGraph[edgeY][1] = directedGraph[i][1];
			undirectedGraph[edgeY][2] = directedGraph[i][2];
			edgeY++;
		}
	}

	delete[] duplicate;
}



Graph::~Graph()
{

}
