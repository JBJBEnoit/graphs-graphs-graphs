#include <iostream>
#include "Graph.hpp"
#include <vector>

using namespace std;

unsigned connected_components(Graph g)
{
	vector<bool> visited(g.numVertices);
	unsigned count = 0;
	for (unsigned i = 0; i < g.numVertices; ++i)
	{
		if (!visited[i])
		{
			++count;
			dfs(g, visited, i);
		}
	}

	return count;
}

unsigned connected_components(Graph g, vector<int>& components)
{
	vector<bool> visited(g.numVertices);
	unsigned count = 0;
	for (unsigned i = 0; i < g.numVertices; ++i)
	{
		if (!visited[i])
		{
			++count;
			dfs_components(g, visited, i, components);
		}
	}

	return count;
}