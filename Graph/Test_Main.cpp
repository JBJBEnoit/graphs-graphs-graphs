#include <iostream>
#include "Graph.hpp"
#include <vector>
#include "boost\multi_array.hpp"

using namespace std;

int main()
{
	// Need to develop a notation that can be parsed into an adjacency list
	// perhaps something like "0,2,1/1,2,3/3,3,0/" would work (especially since JS likes to use strings for everything)
	//vector<Edge> edges = { Edge(0, 2, 1), Edge(1, 2, 3), Edge(3, 3, 0) };
	vector<Edge> edges;
	Graph::parse_edge_str(edges, "0,2,1/1,2,3/3,3,0/");
	vector<string> JSON_data;
	JSON_data.push_back(R"({ "name":"blah", "height":"1" })"); //NOTE: figure out a way this JSON can be generated by a function from user-defined object attributes
	JSON_data.push_back(R"({ "name":"foo", "height":"2" })");
	JSON_data.push_back(R"({ "name":"dracula", "height": "3")");
	JSON_data.push_back(R"({ "name":"bigfoot", "height": "17")");
	vector<vector<int>> dir = { {0, 0, -1, 1}, {-1, 1, 0, 0} };
	vector<unsigned> lens = { 2, 4, 7 };
	
	Grid<char, 4> myGrid({ 3, 2, 3, 3 }, { {1,-1,0,0},{0,0,1,-1} });
	*myGrid.getCell({ 1,1,2, 0}) = 'a';
	cout << *myGrid.getCell({ 1, 1, 2, 0 }) << endl;
}