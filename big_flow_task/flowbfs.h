#ifndef FLOWBFS_H_INCLUDED
#define FLOWBFS_H_INCLUDED

class FlowBfs {
private:
    std::vector < int > dist;
    std::vector < int > prev;
    FlowGraph graph;
    int start;
public:
    FlowBfs(FlowGraph _graph) : graph(_graph) {
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
                int to = graph.graph[v][i]->to;
                if (dist[to] == -1 && graph.graph[v][i]->cap != 0) {
                    dist[to] = dist[v] + 1;
                    prev[to] = v;
                    q.push(to);
                }
            }
        }
    }

    std::vector < int > getDist() {
        return dist;
    }

    std::vector < int > getPrev() {
        return prev;
    }

    bool isConnected() {
        return dist[graph.t] != -1;
    }

    FlowGraph getLayerNet() {
        FlowGraph layer_net;
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
};

#endif // FLOWBFS_H_INCLUDED
