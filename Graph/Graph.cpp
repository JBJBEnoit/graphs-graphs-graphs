#include <iostream>
#include "Graph.hpp"
#include <vector>

using namespace std;

int main()
{
	vector<Edge> edges = { Edge(0, 2, 1), Edge(1, 2, 3), Edge(3, 3, 0) };

	Undirected_Graph g(edges, 4);

	cout << connected_components(g);
}