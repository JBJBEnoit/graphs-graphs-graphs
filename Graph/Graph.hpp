#ifndef GRAPH
#define GRAPH

#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <sstream>
#include <cassert>

// Exception
struct dataGraphMismatch
{
	int numVertices;
	std::vector<std::string> JSON_data;

	dataGraphMismatch(int numVertices, std::vector<std::string> const& JSON_data) : numVertices(numVertices), JSON_data(JSON_data) {};
	void msg()
	{
		std::cerr << "JSON_data length=" << JSON_data.size() << " is different than number of vertices=" << numVertices << std::endl;
		std::cerr << "JSON_data dump: " << std::endl;

		for (std::string s : JSON_data)
		{
			std::cerr << s << std::endl;
		}
	}
};

struct adjNode {
	int id = -1; // This will hold an index of 0 to numVertices - 1
	int weight = -1;
	adjNode(int id, int weight)
	{
		this->id = id;
		this->weight = weight;
	}
};

struct Edge {
	int start_vertex, end_vertex, weight;
	Edge(int start, int end, int weight)
	{
		this->start_vertex = start;
		this->end_vertex = end;
		this->weight = weight;
	}
};

class Graph {

	void buildAdjList(std::vector<Edge>& edges)
	{
		for (const auto& e : edges)
		{
			int start = e.start_vertex;
			int end = e.end_vertex;
			int weight = e.weight;
			adjNode newNode(end, weight);
			adj[start].push_front(newNode);
		}
	}
	
public:
	unsigned numVertices; // number of vertices in graph
	std::vector<std::list<adjNode>> adj; //array of pointers for adjacency list
	std::vector<std::string> JSON_data; // This is used for any data to be tracked by the vertices
	
	// Constructors
	Graph(std::vector<Edge>& edges, unsigned numVertices)
	{
		this->numVertices = numVertices;
		this->adj = std::vector<std::list<adjNode>>(numVertices);
		this->JSON_data = std::vector<std::string>(numVertices);
		// Add nodes to adjacency list
		buildAdjList(edges);
	}

	Graph(std::vector<Edge>& edges, unsigned numVertices, std::vector<std::string>& JSON_data)
	{
		/*if (JSON_data.size() != numVertices)
		{
			throw(dataGraphMismatch(numVertices, JSON_data));
		}*/

		assert(numVertices == JSON_data.size() && "JSON_data length does not match number of vertices");

		this->numVertices = numVertices;
		this->adj = std::vector<std::list<adjNode>>(numVertices);
		this->JSON_data = JSON_data;
		// Add nodes to adjacency list
		buildAdjList(edges);
	}

	// Static method for parsing edge string from format "int(from)/int(to)/int(weight)/..."
	// to vector<Edge>
	static void parse_edge_str(std::vector<Edge>& vec, std::string edge_str)
	{
		std::istringstream slash_strm(edge_str);
		std::string cur;

		while (getline(slash_strm, cur, '/'))
		{
			std::istringstream comma_strm(cur);
			int start;
			int end;
			int weight;
			char comma;
			comma_strm >> start >> comma >> end >> comma >> weight;
			Edge newEdge(start, end, weight);
			vec.push_back(newEdge);
		}
	}
};

class Undirected_Graph
{
	void buildAdjList(std::vector<Edge>& edges)
	{
		for (const auto& e : edges)
		{
			int start = e.start_vertex;
			int end = e.end_vertex;
			int weight = e.weight;
			adjNode newNode(end, weight);
			adj[start].push_front(newNode);
			adjNode newNode2(start, weight);
			adj[end].push_front(newNode2);
		}
	}

public:
	unsigned numVertices; // number of vertices in graph
	std::vector<std::list<adjNode>> adj; //array of pointers for adjacency list
	std::vector<std::string> JSON_data; // This is used for any data to be tracked by the vertices

	// Constructors
	Undirected_Graph(std::vector<Edge>& edges, unsigned numVertices)
	{
		this->numVertices = numVertices;
		this->adj = std::vector<std::list<adjNode>>(numVertices);
		this->JSON_data = std::vector<std::string>(numVertices);
		// Add nodes to adjacency list
		buildAdjList(edges);
	}

	Undirected_Graph(std::vector<Edge>& edges, unsigned numVertices, std::vector<std::string>& JSON_data)
	{
		assert(numVertices == JSON_data.size() && "JSON_data length does not match number of vertices");

		this->numVertices = numVertices;
		this->adj = std::vector<std::list<adjNode>>(numVertices);
		this->JSON_data = JSON_data;
		// Add nodes to adjacency list
		buildAdjList(edges);
	}
};

//prototypes
void dfs(Graph g, std::vector<bool>& visited, int start);
void dfs_components(Undirected_Graph g, std::vector<bool>& visited, int start, std::vector<int>& components);
void dfs(Undirected_Graph g, std::vector<bool>& visited, int start);
unsigned connected_components(Undirected_Graph g);
unsigned connected_components(Undirected_Graph g, std::vector<int>& components);

#endif
