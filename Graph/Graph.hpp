#ifndef GRAPH
#define GRAPH

#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <sstream>
#include <cassert>
#include <unordered_set>

// Exception
struct dataGraphMismatch
{
	int numVertices;
	std::vector<std::string> JSON_data;

	dataGraphMismatch(int const numVertices, std::vector<std::string> const& JSON_data) : numVertices(numVertices), JSON_data(JSON_data) {};
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
	adjNode(int const id, int const weight)
	{
		this->id = id;
		this->weight = weight;
	}
};

struct Edge {
	int start_vertex, end_vertex, weight;
	Edge(int const start, int const end, int const weight)
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
	Graph(std::vector<Edge>& edges, unsigned const numVertices)
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
	Undirected_Graph(std::vector<Edge>& edges, unsigned const numVertices)
	{
		this->numVertices = numVertices;
		this->adj = std::vector<std::list<adjNode>>(numVertices);
		this->JSON_data = std::vector<std::string>(numVertices);
		// Add nodes to adjacency list
		buildAdjList(edges);
	}

	Undirected_Graph(std::vector<Edge>& edges, unsigned const numVertices, std::vector<std::string>& JSON_data)
	{
		assert(numVertices == JSON_data.size() && "JSON_data length does not match number of vertices");

		this->numVertices = numVertices;
		this->adj = std::vector<std::list<adjNode>>(numVertices);
		this->JSON_data = JSON_data;
		// Add nodes to adjacency list
		buildAdjList(edges);
	}
};

// A grid is treated as though cells are connected vertices unless the cell contains an 'obstacle'
// There is no directionality in the sense that the same movement rules apply to every cell

static const int MAX_DIMENSIONS = 5;
template<class T, size_t numDims>
class Grid
{
	
	std::vector<unsigned>dimLengths;
	std::vector<std::vector<int>> directions; // vector of directional vectors, one for each dimension
	std::vector<unsigned> coordinates;
	std::vector<T> grid;

	size_t index(std::vector<unsigned> const& coords)
	{
		size_t idx = 0;

		// Calculate index in the linear grid vector
		for (size_t i = 0; i < coords.size(); ++i)
		{
			if (i == 0)
			{
				idx += coords[i];
			}
			else
			{
				size_t factor = 1;

				for (size_t j = 0; j < i; ++j)
				{
					factor *= dimLengths[j];
				}

				idx += coords[i] * factor;
			}
		}

		return idx;
	}

	
public:
	Grid(std::vector<unsigned>dimLengths, std::vector<std::vector<int>> directions)
	{
		size_t gridLen = 1;
		for (unsigned i : dimLengths)
		{
			gridLen *= i;
		}
		std::vector<T> vec(gridLen);
		this->dimLengths.swap(dimLengths);
		this->directions.swap(directions);
		this->grid.swap(vec);
	}

	//Member Functions
	// Returns pointer to a cell
	T* getCell(std::vector<unsigned> const& coords)
	{
		size_t idx = index(coords);

		return &grid[idx];	
	}

	// Finds the path with the fewest moves from a start position to any number of end points
	// Takes obstacles as a set
	void least_path_mv(std::vector<unsigned> const& start, std::unordered_set<std::vector<unsigned>> const& end, 
		std::unordered_set< std::vector<unsigned>> const& obstacles, std::vector<size_t>& path)
	{
		size_t count = 0;

		// Convert obstacles to a set of integers for faster comparison
		// NOTE TODO could possible make this more space efficient by storing obstacles in the grid(presumably they are unreachable, so...)
		std::unordered_set<size_t> obs;
		if (!obstacles.empty())
		{
			for (auto i : obstacles)
			{
				obs.insert(index(i));
			}
		}

		return count;
	}
};

//prototypes
void dfs(Graph g, std::vector<bool>& visited, int start);
void dfs_components(Undirected_Graph g, std::vector<bool>& visited, int start, std::vector<int>& components, int count);
void dfs(Undirected_Graph g, std::vector<bool>& visited, int start);
unsigned connected_components(Undirected_Graph g);
unsigned connected_components(Undirected_Graph g, std::vector<int>& components);


#endif
