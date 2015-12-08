#include <queue>

#ifdef BFS_H_INCLUDED

template <typename TGraph>
Bfs <TGraph> ::Bfs(TGraph _graph, bool (*isEdge)(typename TGraph::EdgeType*)) : graph(_graph) {
    int start = graph.s;
    dist.resize(graph.n, -1);
    prev.resize(graph.n, -1);
    dist[start] = 0;
    prev[start] = start;
    std::queue <int> q;
    q.push(start);
    while(!q.empty()) {
        int v = q.front();
        q.pop();
        for (int i = 0; i < graph.graph[v].size(); ++i) {
            if (isEdge(graph.graph[v][i])) {
                int to = graph.graph[v][i]->to;
                if (dist[to] == -1) {
                    dist[to] = dist[v] + 1;
                    prev[to] = v;
                    q.push(to);
                }
            }
        }
    }
}

template <typename TGraph>
std::vector <int> Bfs<TGraph> ::getDist() {
    return dist;
}

template <typename TGraph>
std::vector <int> Bfs<TGraph> ::getPrev() {
    return prev;
}

template <typename TGraph>
bool Bfs<TGraph> ::isConnected() {
    return dist[graph.t] != -1;
}

template <typename TGraph>
TGraph Bfs<TGraph> ::getLayerNet() {
    TGraph layer_net;
    layer_net.n = graph.n;
    layer_net.s = graph.s;
    layer_net.t = graph.t;
    layer_net.graph.resize(layer_net.n);
    for (int i = 0; i < graph.n; i++)
        for (int j = 0; j < graph.graph[i].size(); j++) {
            if (dist[graph.graph[i][j]->from] + 1 == dist[graph.graph[i][j]->to]) {
                layer_net.addEdge(graph.graph[i][j]);
            }
        }
    return layer_net;
}
#endif
