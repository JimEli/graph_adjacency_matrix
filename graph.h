// Adjacency matrix graph.
#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <iostream> // cout
#include <iomanip>  // setfill, setw
#include <limits>   // max
#include <vector>   // adjacency matrix, etc.
#include <queue>    // bfs

// Define ALL_PATHS to print all vs. single path in dijkstra routine.
//#define ALL_PATHS 

template <typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
class Graph
{
private:
	std::size_t numVertices;
	bool directed;

	static std::size_t minDistance(const std::vector<T>& dist, const std::vector<bool>& shortestPathSet, const std::size_t numVertices)
	{
		T min = std::numeric_limits<T>::max();
		std::size_t minIndex = 0;

		for (std::size_t v = 0; v < numVertices; v++)
		{
			if (shortestPathSet[v] == false && dist[v] <= min)
			{
				min = dist[v];
				minIndex = v;
			}
		}

		return minIndex;
	}

	static void printPath(const std::vector<int>& predecessor, const std::size_t n) {
		if (predecessor[n] < 0)
			return;
		printPath(predecessor, predecessor[n]);
		std::cout << n << " ";
	}

	void init(std::size_t n) { am.resize(n, std::vector<T>(n)); }

	void dfs(std::size_t source, std::vector<bool>& visited) const
	{
		visited[source] = true;

		std::cout << source << " ";

		for (std::size_t i = 0; i < numVertices; i++)
			if (am[source][i] >= 0 && (!visited[i]))
				dfs(i, visited);
	}

protected:
	std::vector<std::vector<T>> am;

public:
	Graph() : numVertices(1), directed(false) { init(1); }
	explicit Graph(const std::size_t n) : numVertices(n), directed(false) { init(numVertices); }
	Graph(const std::size_t n, const bool d) : numVertices(n), directed(d) { init(numVertices); }

	std::size_t size() const { return numVertices; }

	void insertEdge(std::size_t u, std::size_t v) { insertEdge(u, v, T{ 1 }); }
	void insertEdge(std::size_t u, std::size_t v, T w)
	{
		if (u > numVertices || v > numVertices)
			throw "Graph::insertEdge vertex out of bounds";
		am[u][v] = w;
		if (!directed)
			am[v][u] = w;
	}

	void removeEdge(std::size_t u, std::size_t v)
	{
		am[u][v] = T{ 0 };
		am[v][u] = T{ 0 };
	}

	T& isEdge(std::size_t u, std::size_t v) const { return am.at(u).at(v); }
	bool isDirected() const { return directed; }

	void dijkstra(const std::size_t source, const std::size_t destination)
	{
		std::vector<T> distance(numVertices, std::numeric_limits<T>::max());
		std::vector<int> predecessor(numVertices, -1);
		std::vector<bool> shortestPathSet(numVertices, false);

		distance[source] = 0;

		for (std::size_t i = 0; i < numVertices - 1; i++)
		{
			std::size_t u = minDistance(distance, shortestPathSet, numVertices);
			shortestPathSet[u] = true;

			for (std::size_t v = 0; v < numVertices; v++)
			{
				if (!shortestPathSet[v] && am[u][v] && distance[u] + am[u][v] < distance[v])
				{
					predecessor[v] = u;
					if (v == destination)
						std::cout << u << " ";
					distance[v] = distance[u] + am[u][v];
				}
			}
		}

		std::cout << "Vertex\tDistance\tPath";
#ifdef ALL_PATHS
		for (std::size_t v = 0; v < numVertices; v++) {
			std::cout << "\n" << source << "->" << v << "\t" << distance[v] << "\t\t" << source << " ";
			printPath(predecessor, v);
		}
#else
		std::cout << "\n" << source << "->" << destination << "\t" << distance[destination] << "\t\t" << source << " ";
		printPath(predecessor, destination);
#endif
		std::cout << std::endl;
	}

	void bfs(std::size_t source) const
	{
		std::vector<bool> visited(numVertices, false);
		std::queue<std::size_t> q; //std::vector<std::size_t> q;
		q.push(source); //q.push_back(source);

		visited[source] = true;

		while (!q.empty())
		{
			std::size_t v = q.front(); //std::size_t v = q[0]; 

			std::cout << v << " ";
			q.pop(); //	q.erase(q.begin());

			for (std::size_t i = 0; i < numVertices; i++)
				if (am[v][i] > 0 && (!visited[i]))
				{
					q.push(i); //q.push_back(i);
					visited[i] = true;
				}
		}
	}

	void dfs(std::size_t source) const
	{
		std::vector<bool> visit(numVertices, false);
		dfs(source, visit);
	}

	friend std::ostream& operator<< (std::ostream& os, const Graph<T>& g)
	{
		for (std::vector<T> row : g.am)
		{
			for (auto i : row)
				os << std::fixed << std::showpoint << std::setprecision(1) << std::setfill(' ') << std::setw(4) << i << " ";
			os << std::endl;
		}
		return os << std::endl;
	}
};

#endif
