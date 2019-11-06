#include "graph.h"

int main() 
{
	Graph<int> g(9, false);
/*
	// Demo matrix representation.
	am = { {
		// 0   1   2   3   4   5   6   7   8
		{  0,  4,  0,  0,  0,  0,  0,  8,  0 }, // 0
		{  4,  0,  8,  0,  0,  0,  0, 11,  0 }, // 1
		{  0,  8,  0,  7,  0,  4,  0,  0,  2 }, // 2
		{  0,  0,  7,  0,  9, 14,  0,  0,  0 }, // 3
		{  0,  0,  0,  9,  0, 10,  0,  0,  0 }, // 4
		{  0,  0,  4, 14, 10,  0,  2,  0,  0 }, // 5
		{  0,  0,  0,  0,  0,  2,  0,  1,  6 }, // 6
		{  8, 11,  0,  0,  0,  0,  1,  0,  7 }, // 7
		{  0,  0,  2,  0,  0,  0,  6,  7,  0 }  // 8
	}  };
*/
	g.insertEdge(0, 1, 4);
	g.insertEdge(0, 7, 8);
	g.insertEdge(1, 2, 8);
	g.insertEdge(1, 7, 11);
	g.insertEdge(2, 3, 7);
	g.insertEdge(2, 5, 4);
	g.insertEdge(2, 8, 2);
	g.insertEdge(3, 4, 9);
	g.insertEdge(3, 5, 14);
	g.insertEdge(4, 5, 10);
	g.insertEdge(5, 6, 2);
	g.insertEdge(6, 7, 1);
	g.insertEdge(6, 8, 6);
	g.insertEdge(7, 8, 7);

	g.dijkstra(3, 7);

	std::cout << "bfs: ";
	g.bfs(3);
	std::cout << std::endl;

	std::cout << "dfs: ";
	g.dfs(3);
	std::cout << std::endl;

	std::cout << g;
}
