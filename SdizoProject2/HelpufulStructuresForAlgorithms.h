

struct Edge
{
	int verticleFrom, verticleTo, weight;
};

class Heap
{

private:
	Edge *heapArray;
	int size;

public:
	Heap();
	~Heap();
	Edge getTopElement();
	void addEdge(Edge value);
	void deleteTop();
	int getSize();
	
};


struct DisjointSetNode
{
	int parent, rank;
};

class DisjointSet
{
private:
	DisjointSetNode * Z;
public:
	DisjointSet(int n);
	~DisjointSet();
	void make(int v);
	int find(int v);
	void UnionSets(Edge e);
};




struct Verticle {
	int nr;
	int cost;
};

class QueueHeapForDijkstraAlgorithm
{

public:
	int size;
	Verticle* queue;

	QueueHeapForDijkstraAlgorithm(int _size, int start);
	~QueueHeapForDijkstraAlgorithm();

	Verticle pop();
	void heap_fix_down();
	void heap_fix_up(int index);
	void changeCost(int v_nr, int cost);
};
