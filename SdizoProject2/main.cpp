#include <iostream>
#include "Graph.h"
#include "AdjacencyMatrix.h"
#include "AdjacencyList.h"
#include "Timer.h"
#include <fstream>


using namespace std;

void randomGraph() {
	AdjacencyList list;
	list.createRandomGraph();
	AdjacencyMatrix matrix;
	Timer stopwatch;
	list.readFromFile("plik.txt");
	matrix.readFromFile("plik.txt");
	ofstream myfile;

	list.createUndirectedGraph();
	matrix.createUndirectedGraph();
	matrix.createMatrixForDirectedGraph();
	matrix.createMatrixForUndirectedGraph();
	list.createDirectedAdjacencyList();
	list.createUndirectedAdjacencyList();

	int choice = 0;
	
		do {
			cout << endl;
			cout << "wybierz opcje " << endl;
			cout << "1.  wyswietl graf skierowany w formie macierzowej" << endl;
			cout << "2.  wyswietl graf nieskieroway w formie macierzowej" << endl;
			cout << "3.  wyswietl graf skierowany w formie listowej" << endl;
			cout << "4.  wyswietl graf nieskierowany w formie listowej" << endl;
			cout << "5.  algorytm prima dla grafu nieskierowanego na bazie reprezentacji macierzowej" << endl;
			cout << "6.  algorytm prima dla grafu nieskierowanego na bazie reprezentacji listowej" << endl;
			cout << "7.  algorytm dijkstry dla grafu skierowanego na bazie reprezentacji macierzowej" << endl;
			cout << "8.  algorytm dijkstry dla grafu skierowanego na bazie reprezentacji listowej" << endl;
			cout << "9.  algorytm Kruskala dla grafu nieskierowanego na bazie reprezentacji macierzowej" << endl;
			cout << "10. algorytm Kruskala dla grafu nieskierowanego na bazie reprezentacji listowej" << endl;
			cout << "11. algorytm Bellmana-Forda dla grafu skierowanego na bazie reprezentacji macierzowej" << endl;
			cout << "12. algorytm Bellmana-Forda dla grafu skierowanego na bazie reprezentacji listowej" << endl;
			cout << "13. zrob testy" << endl;
			cout << "0.  koniec" << endl << endl;


			cout << "[0] koniec" << endl << endl;
			cin >> choice;

			switch (choice) {
			case 1:
				matrix.printMatrixDirected();
				break;
			case 2:
				matrix.printMatrixUndirected();
				break;
			case 3:
				list.printDirectedAdjacencyList();
				break;
			case 4:
				list.printUndirectedAdjacencyList();
				break;
			case 5:
				matrix.PrimAlgorithm(true);
				break;
			case 6:
				list.PrimAlgorithm(true);
				break;
			case 7:
				matrix.DijikstraAlgoritm(matrix.getStartVerticle(), true);
				break;
			case 8:
				list.DijikstraAlgoritm(list.getStartVerticle(),true);
				break;
			case 9:
				matrix.KruskalAlgorithm(true);
				break;
			case 10:
				list.KruskalAlgorithm(true);
				break;
			case 11:
				try { matrix.BellmanFordAlgorithm(list.getStartVerticle(), true); }
				catch (const char* msg) {
					cerr << msg;
				}			break;
			case 12:
				try { list.BellmanFordAlgorithm(list.getStartVerticle(), true); }
				catch (const char* msg) {
					cerr << msg;
				}
				break;
			case 13:
				{
				myfile.open("pomiary2.txt", std::ios_base::app);
				stopwatch.start();
				for (int i = 0; i<10; i++)
					matrix.PrimAlgorithm(false);
				stopwatch.stop();
				myfile << stopwatch.measurement/10;
				myfile << " ";
				stopwatch.start();
				for(int i=0;i<10;i++)
				{
					list.PrimAlgorithm(false);
				}
				stopwatch.stop();
				myfile << stopwatch.measurement/10;
				myfile << " ";

				stopwatch.start();
				for (int i = 0; i<10; i++)
					matrix.KruskalAlgorithm(false);
				stopwatch.stop();
				myfile << stopwatch.measurement/10;
				myfile << " ";

				stopwatch.start();
				for (int i = 0; i<10; i++)
					list.KruskalAlgorithm(false);
				stopwatch.stop();
				myfile << stopwatch.measurement/10;
				myfile << " ";

				stopwatch.start();
				for (int i = 0; i<10; i++)
					matrix.DijikstraAlgoritm(matrix.getStartVerticle(),false);
				stopwatch.stop();
				myfile << stopwatch.measurement/10;
				myfile << " ";

				stopwatch.start();
				for (int i = 0; i<10; i++)
					list.DijikstraAlgoritm(matrix.getStartVerticle(), false);
				stopwatch.stop();
				myfile << stopwatch.measurement/10;
				myfile << " ";

				stopwatch.start();
				for (int i = 0; i<10; i++)
					matrix.BellmanFordAlgorithm(matrix.getStartVerticle(), false);
				stopwatch.stop();
				myfile << stopwatch.measurement/10;
				myfile << " ";

				stopwatch.start();
				for (int i = 0; i<10; i++)
					list.BellmanFordAlgorithm(matrix.getStartVerticle(), false);
				stopwatch.stop();
				myfile << stopwatch.measurement/10;
				myfile << " ";

				myfile << endl;



				}
				break;

			default:
				if(choice != 0)	cout << "bledny wybor" << endl;
				break;
			}

		} while (choice != 0);

}

void readGraph() {
	bool success;

	string filename;
	AdjacencyList list;
	AdjacencyMatrix matrix;
	

	do {
		cout << "Podaj nazwe pliku z koncowka .txt " << endl;
		cin >> filename;
		success = list.readFromFile(filename);
		matrix.readFromFile(filename);

	} while (success != true);

	list.createUndirectedGraph();	
	matrix.createUndirectedGraph();
	matrix.createMatrixForDirectedGraph();
	matrix.createMatrixForUndirectedGraph();
	list.createDirectedAdjacencyList();
	list.createUndirectedAdjacencyList();

	int choice = 0;
	do {
		cout << endl;
		cout << "wybierz opcje: " << endl;
		cout << "1.  wyswietl graf skierowany w formie macierzowej" << endl;
		cout << "2.  wyswietl graf nieskieroway w formie macierzowej" << endl;
		cout << "3.  wyswietl graf skierowany w formie listowej" << endl;
		cout << "4.  wyswietl graf nieskierowany w formie listowej" << endl;
		cout << "5.  algorytm prima dla grafu nieskierowanego na bazie reprezentacji macierzowej" << endl;
		cout << "6.  algorytm prima dla grafu nieskierowanego na bazie reprezentacji listowej" << endl;
		cout << "7.  algorytm dijkstry dla grafu skierowanego na bazie reprezentacji macierzowej" << endl;
		cout << "8.  algorytm dijkstry dla grafu skierowanego na bazie reprezentacji listowej" << endl;
		cout << "9.  algorytm Kruskala dla grafu nieskierowanego na bazie reprezentacji macierzowej" << endl;
		cout << "10. algorytm Kruskala dla grafu nieskierowanego na bazie reprezentacji listowej" << endl;
		cout << "11. algorytm Bellmana-Forda dla grafu skierowanego na bazie reprezentacji macierzowej" << endl;
		cout << "12. algorytm Bellmana-Forda dla grafu skierowanego na bazie reprezentacji listowej" << endl;
		cout << "0.  koniec" << endl << endl;
		cin >> choice;

		switch (choice) {
		case 1:
			matrix.printMatrixDirected();
			break;
		case 2:
			matrix.printMatrixUndirected();
			break;
		case 3:
			list.printDirectedAdjacencyList();
			break;
		case 4:
			list.printUndirectedAdjacencyList();
			break;
		case 5:
			matrix.PrimAlgorithm(true);
			break;
		case 6:
			list.PrimAlgorithm(true);
			break;
		case 7:
			matrix.DijikstraAlgoritm(matrix.getStartVerticle(), true);
			break;
		case 8:
			try
			{
				list.DijikstraAlgoritm(list.getStartVerticle(), true);

			}
			catch (const char* msg) {
				cerr << msg;
			}
			break;
		case 9:
			matrix.KruskalAlgorithm(true);
			break;
		case 10:
			list.KruskalAlgorithm(true);
			break;
		case 11:
			try { matrix.BellmanFordAlgorithm(list.getStartVerticle(), true); }
			catch (const char* msg) {
				cerr << msg;
			}			break;
		case 12:
			try { list.BellmanFordAlgorithm(list.getStartVerticle(), true); }
			catch (const char* msg) {
				cerr << msg;
			}
			break;

		default:
			if (choice != 0) cout << "bledny wybor" << endl;
			break;
		}

	} while (choice != 0);


}


int main() {
	cout << "Patryk Zdral" << endl;
	int randomOrFile = 0;

	do {
		cout << "wybierz sposob wygenerowania grafu " << endl;
		cout << "1. losowo" << endl;
		cout << "2. z pliku" << endl;
		cout << "3. wyjscie" << endl << endl;
		cin >> randomOrFile;

		switch (randomOrFile) {
		case 1:
			randomGraph();

			break;

		case 2:
			readGraph();
			break;
		case 3:
			break;
		default:
			cout << "bledny wybor" << endl;
			break;
		}
	} while (randomOrFile != 3);


	return 0;
}