#include <iostream>
#include "Graph.hpp"
#include <vector>

using namespace std;

int main()
{
	// Need to develop a notation that can be parsed into an adjacency list
	// perhaps something like "0,2,1/1,2,3/3,3,0/" would work (especially since JS likes to use strings for everything)
	//vector<Edge> edges = { Edge(0, 2, 1), Edge(1, 2, 3), Edge(3, 3, 0) };
	vector<Edge> edges;
	Graph::parse_edge_str(edges, "0,2,1/1,2,3/3,3,0/");
	vector<string> JSON_data;
	JSON_data.push_back("blah");
	JSON_data.push_back("foo");

	Graph g(edges, 4, JSON_data);
	
	
}