#ifndef GRAPH
#define GRAPH

#include <iostream>
#include <vector>
#include <list>

struct adjNode {
	int val = -1; // This will hold an index of 0 to numVertices - 1
	int weight = -1;
	std::vector<std::string> JSON_data_string; // This is used for any data to be tracked by the vertex
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
	
	// Insert Node into Adjacency List
	adjNode* addAdjNode(int val, int weight)
	{
		adjNode* node = new adjNode;
		node->val = val;
		node->weight = weight;
		return node;
	}
	
public:
	unsigned numVertices; // number of vertices in graph
	std::vector<std::list<adjNode*>> adj; //array of pointers for adjacency list
	
	// Constructor
	Graph(std::vector<Edge>& edges, unsigned numVertices)
	{
		this->numVertices = numVertices;
		this->adj = std::vector<std::list<adjNode*>>(numVertices);
		// Add nodes to adjacency list
		for (const auto& e : edges)
		{
			int start = e.start_vertex;
			int end = e.end_vertex;
			int weight = e.weight;
			adjNode* newNode = addAdjNode(end, weight);
			adj[start].push_front(newNode);
		}
	}
	
	//Destructor
	~Graph()
	{
		for (unsigned i = 0; i < numVertices; ++i)
		{
			for (auto it = adj[i].begin(); it != adj[i].end(); ++i)
			{
				delete* it;
			}
		}
	}
};

class Undirected_Graph
{
	adjNode* addAdjNode(int val, int weight)
	{
		adjNode* node = new adjNode;
		node->val = val;
		node->weight = weight;
		return node;
	}

public:
	unsigned numVertices; // number of vertices in graph
	std::vector<std::list<adjNode*>> adj; //array of pointers for adjacency list

	Undirected_Graph(std::vector<Edge>& edges, unsigned numVertices)
	{
		this->numVertices = numVertices;
		this->adj = std::vector<std::list<adjNode*>>(numVertices);
		// Add nodes to adjacency list
		for (const auto& e : edges)
		{
			int start = e.start_vertex;
			int end = e.end_vertex;
			int weight = e.weight;
			adjNode* newNode = addAdjNode(end, weight);
			adj[start].push_front(newNode);
			adjNode* newNode2 = addAdjNode(start, weight);
			adj[end].push_front(newNode2);
		}
	}
};

//prototypes
void dfs(Graph g, std::vector<bool>& visited, int start);
void dfs_components(Undirected_Graph g, std::vector<bool>& visited, int start, std::vector<int>& components);
void dfs(Undirected_Graph g, std::vector<bool>& visited, int start);
unsigned connected_components(Undirected_Graph g);
unsigned connected_components(Undirected_Graph g, std::vector<int>& components);

#endif
