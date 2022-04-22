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
			for (adjNode* a : g.adj[cur])
			{
				stack.push(a->val);
			}

			visited[cur] = true;
		}
	}	
}

void dfs_components(Graph g, vector<bool>& visited, int start, vector<int>& components)
{
	stack<int> stack;
	stack.push(start);

	while (!stack.empty())
	{
		int cur = stack.top();
		stack.pop();

		if (!visited[cur])
		{
			for (adjNode* a : g.adj[cur])
			{
				stack.push(a->val);
			}

			visited[cur] = true;
			components[cur] = start;
		}
	}
}

