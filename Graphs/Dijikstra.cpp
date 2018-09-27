/*
This program is for dijkestra
It finds the shortest path from 1 to n (can be easily changed)
It also returns the path
*/

#include <iostream>
#include <queue>
#define INF 1e17

using namespace std;

typedef pair<long long, long long> pii;

vector<int> Dijkstra(const vector<vector<pii>> &graph, int src, int dest) {
	int n = graph.size();
	n--;
	vector<long long> dist(n + 1, INF); //cost, vertex
	vector<bool> visited(n + 1, false);
	priority_queue<pii, vector<pii>, greater<pii>> pq; 

	dist[src] = 0;
	for (int i = 1; i <= n; i++) {
		pq.push({dist[i], i});
	}
	
	vector<int> parent(n+1);
	parent[src] = src;

	while(!pq.empty()) {
		pii top = pq.top();
		pq.pop();
		long long current_cost = top.first;
		int current_vertex = top.second;

		if (visited[current_vertex]) {
			continue;
		}

		visited[current_vertex] = true;

		for (auto neighbor: graph[current_vertex]) {
			int neighbor_vertex = neighbor.first;
			long long edge = neighbor.second;

			if (visited[neighbor_vertex]) {
				continue;
			}

			if (dist[current_vertex] + edge < dist[neighbor_vertex]) {
				dist[neighbor_vertex] = current_cost + edge;
				pq.push({dist[neighbor_vertex], neighbor_vertex});

				parent[neighbor_vertex] = current_vertex; 
			}
		}
	}
	if (dist[dest] == INF) {
		return vector<int>();
	}
	long long shorthest_path_cost = dist[dest];

	vector<int> path;

	int child = dest;
	while(child != src) {
		path.push_back(child);
		child = parent[child];
	}
	path.push_back(src);

	return path;
}

int main(void) {
	int n, m;
	scanf("%d %d", &n, &m); //n is the number of vertices (1 based) and m is the number of edges

	vector<vector<pii>> graph(n+1, vector<pii>()); //graph[a][b].first => a vertex that is adjacent to a, second is the cost to get from a to first

	for(int i = 0; i < m; i++) {
		int src, dest, cost; 
		scanf("%d %d %d", &src, &dest, &cost);
		graph[src].push_back({dest, cost});
		graph[dest].push_back({src, cost});
	}

	int src = 1, dest = n; 

	auto path = Dijkstra(graph, src, dest);

	if (path.size() == 0) {
		printf("-1\n");
	}
	else {
		for (int i = path.size()-1; i >= 0; i--) {
			cout << path[i] << " ";
		}
	}


	return 0;
}