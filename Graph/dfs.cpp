#include <iostream>
#include "Graph.hpp"
#include <stack>

using namespace std;

void dfs(Graph g, vector<bool>& visited, int start)
{
	stack<int> stack;
	stack.push(start);

	while (!stack.empty())
	{
		int cur = stack.top();
		stack.pop();
		
		if (!visited[cur])
		{
			for (adjNode a : g.adj[cur])
			{
				stack.push(a.id);
			}

			visited[cur] = true;
		}
	}	
}

void dfs(Undirected_Graph g, vector<bool>& visited, int start)
{
	stack<int> stack;
	stack.push(start);

	while (!stack.empty())
	{
		int cur = stack.top();
		stack.pop();

		if (!visited[cur])
		{
			for (adjNode a : g.adj[cur])
			{
				stack.push(a.id);
			}

			visited[cur] = true;
		}
	}
}

void dfs_components(Undirected_Graph g, vector<bool>& visited, int start, vector<int>& components, int count)
{
	stack<int> stack;
	stack.push(start);

	while (!stack.empty())
	{
		int cur = stack.top();
		stack.pop();

		if (!visited[cur])
		{
			for (adjNode a : g.adj[cur])
			{
				stack.push(a.id);
			}

			visited[cur] = true;
			components[cur] = count;
		}	
	}
}

