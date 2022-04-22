#ifndef GRAPH
#define GRAPH

#include <iostream>
#include <vector>
#include <list>

struct adjNode {
	int val = -1;
	int weight = -1;
	std::vector<std::string> data;
};

struct Edge {
	int start_vertex, end_vertex, weight;
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

//prototypes
void dfs(Graph g, std::vector<bool>& visited, int start);
void dfs_components(Graph g, std::vector<bool>& visited, int start, std::vector<int>& components);
unsigned connected_components(Graph g);
unsigned connected_components(Graph g, std::vector<int>& components);

#endif
