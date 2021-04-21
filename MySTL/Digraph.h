#pragma once
#include "LinkedList.h"

/**
* 邻接表存图
* 从0到N-1
*/
template<int N>
class Digraph {
public:
	struct Edge {
		int to;
		int w;
		Edge(int to, int w) : to(to), w(w) {}
	};

	LinkedList<Edge> edges[N];

	void add(int from, int to, int weight = 1);

	/**
	* @return true if sort succeeded(no circle)
	*/
	bool topo_sort(LinkedList<int>& result);

	void shortest_path(int source, int dist[N]);
};

template<int N>
void Digraph<N>::add(int from, int to, int weight) {
	edges[from].push_last(Edge(to, weight));
}

template<int N>
bool Digraph<N>::topo_sort(LinkedList<int>& result) {
	result.clear();
	int degree[N]{ 0 };
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < edges[i].size(); j++) {
			degree[edges[i][j].to]++;
		}
	}

	LinkedList<int> queue;
	for (int i = 0; i < N; i++) {
		if (degree[i] == 0 
			// && degree[i].size() > 0
			) {
			queue.push_last(i);
		}
	}
	while (!queue.empty()) {
		int i = queue.pop_first();
		result.push_last(i);
		for (int j = 0; j < edges[i].size(); j++) {
			int to = edges[i][j].to;
			if (--degree[to] == 0) {
				queue.push_last(to);
			}
		}
	}
	return result.size() == N;
}

template<int N>
void Digraph<N>::shortest_path(int source, int dist[N]) {
	// Dijkstra
	bool visited[N]{ false };
	for (int i = 0; i < N; i++) dist[i] = 0x7fffffff;
	for (int to = 0; to < edges[source].size(); to++) {
		Edge e = edges[source][to];
		dist[e.to] = e.w;
	}
	visited[source] = true;
	dist[source] = 0;

	int min_node = source;
	for (int i = 0; i < N; i++) {
		int min_dist = 0x7fffffff;
		// 搜索离顶点最近且没有被访问过的边
		for (int j = 0; j < edges[min_node].size(); j++) {
			Edge e = edges[min_node][j];
			if (!visited[e.to] && dist[e.to] < min_dist) {
				min_node = e.to;
				min_dist = dist[e.to];
			}
		}
		visited[min_node] = true;
		// 松弛离顶点最近的顶点能到达的所有的点
		for (int j = 0; j < edges[min_node].size(); j++) {
			Edge e = edges[min_node][j];
			if (!visited[e.to] && min_dist + e.w < dist[e.to]) {
				dist[e.to] = min_dist + e.w;
			}
		}
	}

}
