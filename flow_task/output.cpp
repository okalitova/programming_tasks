

 // Start of preflow.cpp




 // Start of preflow.h

#define PREFLOW_H_INCLUDED




 // Start of graph.h

#define GRAPH_H_INCLUDED


#include <string>

#include <iostream>

#include <vector>

#define print_graph std::cout

class Edge {
public:
    int from;
    int to;
    Edge();
    Edge(int _from, int _to);
    virtual void read();
};

class FlowEdge : public Edge {
public:
    long long cap;
    long long flow;
    FlowEdge();
    FlowEdge(int _from, int _to, long long _cap = 0);
    void read();
};

class BiEdge : public FlowEdge {
public:
    BiEdge* co_bi_edge;
    BiEdge(int _from = 0, int _to = 0, long long _cap = 0);
    void read();
    void edgeDecrease(long long c);
};

template <typename TEdge>
class Graph {
public:
    typedef TEdge EdgeType;
    int n;
    int s;
    int t;
    std::vector < std::vector < TEdge* > > graph;

    void addEdge(TEdge* t_edge);
    virtual void read() = 0;
};

class FlowGraph : public Graph < BiEdge > {
public:
    std::vector < BiEdge* > real_graph;

    void read();
    void print();
    void printRealGraph();
    static bool isEdge(BiEdge* bi_edge);
};



 // End of graph.h





 // Start of maxflow.h

#define MAXFLOW_H_INCLUDED




 // Start of graph.h



 // End of graph.h



class MaxFlow {
public:
    static const int INF = 1e9;
    FlowGraph graph;
    long long max_flow_value;
public:
    MaxFlow(FlowGraph _graph);
};



 // End of maxflow.h



#include <queue>

class MaxFlowPushPreFlow : public MaxFlow {
private:
    std::vector < int > h;
    std::vector < long long > e;
    std::queue < int > q;
    std::vector < int > current_push;
    std::vector < int > h_count;
public:
    MaxFlowPushPreFlow(FlowGraph _graph);
private:
    void initializePreFlow();
    void relable(int v);
    void push(BiEdge* bi_edge);
    void gap(int gap_h);
    void discharge(int v);
};



 // End of preflow.h



MaxFlowPushPreFlow::MaxFlowPushPreFlow(FlowGraph _graph) : MaxFlow(_graph) {
    max_flow_value = 0;
    initializePreFlow();
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        discharge(v);
    }
    max_flow_value = e[graph.t];
}

void MaxFlowPushPreFlow::initializePreFlow() {
    h.resize(graph.n, 0);
    e.resize(graph.n, 0);
    current_push.resize(graph.n, 0);
    h_count.resize(graph.n * 2 - 1, 0);
    h_count[0] = graph.n - 1;
    h[graph.s] = graph.n;
    for (int i = 0; i < graph.graph[graph.s].size(); ++i) {
        int to = graph.graph[graph.s][i]->to;
        long long cap = graph.graph[graph.s][i]->cap;
        e[to] += cap;
        graph.graph[graph.s][i]->edgeDecrease(cap);
        if (e[to] > 0 && (to != graph.t && to != graph.s))
            q.push(to);
    }
}

 

void MaxFlowPushPreFlow::relable(int v) {
    int h_min = INF;
    for (int i = 0; i < graph.graph[v].size(); ++i) {
        if (graph.graph[v][i]-> cap > 0) {
            h_min = std::min(h_min, h[graph.graph[v][i]->to]);
        }
    }
    if (h_min < 3 * graph.n) {
        h[v] = h_min + 1;
    }
}

void MaxFlowPushPreFlow::push(BiEdge* bi_edge) {
    int from = bi_edge->from;
    int to = bi_edge->to;
    long long c = std::min(e[from], bi_edge->cap);
    bi_edge->edgeDecrease(c);
    e[from] -= c;
    e[to] += c;
    if (e[to] == c && e[to] > 0 && (to != graph.t && to != graph.s))
        q.push(to);
}

void MaxFlowPushPreFlow::gap(int gap_h) {
    if (h_count[gap_h] != 0) return;
    for (int i = 0; i < graph.n; ++i)
        if (i != graph.s && i != graph.t) {
            if(h[i] > gap_h && h[i] < graph.n) {
                h[i] = graph.n + 1;
            }
        }
}

void MaxFlowPushPreFlow::discharge(int v) {
    int old_h = h[v];
    int cur = current_push[v];
    while (e[v] > 0) {
        if (cur == graph.graph[v].size()) {
            cur = 0;
            relable(v);
        } else {
            if (h[v] == h[graph.graph[v][cur]->to] + 1 && graph.graph[v][cur]->cap > 0) {
                push(graph.graph[v][cur]);
            } else {
                ++cur;
            }
        }
    }
    current_push[v] = cur;
    h_count[old_h] -= 1;
    h_count[h[v]] += 1;
    if (old_h < graph.n && h_count[old_h] == 0) gap(old_h);
}





 // End of preflow.cpp



 // Start of blockflow.cpp




 // Start of blockflow.h

#define BLOCKFLOW_H_INCLUDED




 // Start of graph.h



 // End of graph.h



class BlockFlow {
private:
    std::vector < int > cur_edge;
    FlowGraph graph;
public:
    long long max_block_flow;
public:
    BlockFlow(FlowGraph _graph);
private:
    bool dfs(int v);

    long long pathMin(int v);

    void pathDecrease(int v, long long c);

     };



 // End of blockflow.h





 // Start of maxflow.h



 // End of maxflow.h



BlockFlow::BlockFlow(FlowGraph _graph) : graph(_graph) {
    max_block_flow = 0;
    cur_edge.resize(graph.n, 0);
    while (dfs(graph.s)) {
        long long min_path_cap = pathMin(graph.s);
        max_block_flow += min_path_cap;
        pathDecrease(graph.s, min_path_cap);
    }
}
bool BlockFlow::dfs(int v) {
    if (v == graph.t) {
        return true;
    }
    int cur_e = cur_edge[v];
    if (cur_e >= graph.graph[v].size()) return false;
    BiEdge* bi_edge = graph.graph[v][cur_e];
    int is_t_reached = dfs(bi_edge->to);
    if (!is_t_reached || bi_edge->cap == 0) {
        cur_edge[v]++;
        return dfs(v);
    } else {
        return true;
    }
}

long long BlockFlow::pathMin(int v) {
    if (v == graph.t) return 1e9;
    int cur_e = cur_edge[v];
    BiEdge* bi_edge = graph.graph[v][cur_e];
    int to = graph.graph[v][cur_e]->to;
    return std::min(bi_edge->cap, pathMin(to));
}

void BlockFlow::pathDecrease(int v, long long c) {
    if (v == graph.t) return;
    int cur_e = cur_edge[v];
    BiEdge* bi_edge = graph.graph[v][cur_e];
    int to = graph.graph[v][cur_e]->to;
    bi_edge->edgeDecrease(c);
    pathDecrease(to, c);
}

 


 // End of blockflow.cpp



 // Start of flowbfs.cpp


#include <queue>



 // End of flowbfs.cpp



 // Start of maxflowdinic.cpp




 // Start of maxflowdinic.h

#define MAXFLOWDINIC_H_INCLUDED




 // Start of graph.h



 // End of graph.h





 // Start of flowbfs.h

#define FLOWBFS_H_INCLUDED




 // Start of graph.h



 // End of graph.h



template <typename TGraph>
class Bfs {
private:
    std::vector < int > dist;
    std::vector < int > prev;
    TGraph graph;
    int start;
public:
    Bfs(TGraph _graph, bool (*isEdge)(typename TGraph::EdgeType*));
    std::vector < int > getDist();

    std::vector < int > getPrev();

    bool isConnected();

    TGraph getLayerNet();
};




 // Start of flowbfs.cpp


#include <queue>


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


 // End of flowbfs.cpp





 // End of flowbfs.h





 // Start of maxflow.h



 // End of maxflow.h



class MaxFlowDinic : public MaxFlow {
public:
    MaxFlowDinic(FlowGraph _graph);
};

class MaxFlowDinicScaling : public MaxFlow {
private:
    long long max_edge_value;
public:
    MaxFlowDinicScaling(FlowGraph _graph);
private:
    long long findMaxEdgeValue();

    FlowGraph createGraph(long long value);
};



 // End of maxflowdinic.h





 // Start of blockflow.h



 // End of blockflow.h





 // Start of flowbfs.h



 // End of flowbfs.h





 // Start of graph.h



 // End of graph.h





 // Start of maxflow.h



 // End of maxflow.h



MaxFlowDinic::MaxFlowDinic(FlowGraph _graph) : MaxFlow(_graph) {
    max_flow_value = 0;
    while (true) {
        Bfs <FlowGraph> bfs(graph, FlowGraph::isEdge);
        if (bfs.isConnected()) {
            BlockFlow block_flow(bfs.getLayerNet());
            max_flow_value += block_flow.max_block_flow;
        } else {
            break;
        }
    }
}

MaxFlowDinicScaling::MaxFlowDinicScaling(FlowGraph _graph) : MaxFlow(_graph) {
    max_flow_value = 0;
    max_edge_value = findMaxEdgeValue();
    while (max_edge_value > 0) {
        FlowGraph cur_graph;
        cur_graph = createGraph(max_edge_value);
        MaxFlowDinic max_flow(cur_graph);
        max_flow_value += max_flow.max_flow_value;
        max_edge_value = max_edge_value / 2;
    }
}

long long MaxFlowDinicScaling::findMaxEdgeValue() {
    long long max_e = 0;
    for (int i = 0; i < graph.n; ++i)
        for (int j = 0; j < graph.graph[i].size(); ++j) {
            max_e = std::max(max_e, graph.graph[i][j]->cap);
        }
    return max_e;
}

FlowGraph MaxFlowDinicScaling::createGraph(long long value) {
    FlowGraph cur_graph;
    cur_graph.n = graph.n;
    cur_graph.s = graph.s;
    cur_graph.t = graph.t;
    cur_graph.graph.resize(cur_graph.n);
    for (int i = 0; i < graph.n; ++i)
        for (int j = 0; j < graph.graph[i].size(); ++j) {
            if (graph.graph[i][j]->cap >= value) {
                cur_graph.graph[i].push_back(graph.graph[i][j]);
            }
        }
    return cur_graph;
}


 // End of maxflowdinic.cpp



 // Start of graph.cpp




 // Start of graph.h



 // End of graph.h



#define print_graph std::cout

Edge::Edge() : from(0), to(0) {}
Edge::Edge(int _from, int _to) : from(_from), to(_to) {}
void Edge::read() {
    std::cin >> from >> to;
    from--; to--;
}

FlowEdge::FlowEdge() : Edge() , cap(0), flow(0) {}
FlowEdge::FlowEdge(int _from, int _to, long long _cap) : Edge(_from, _to), cap(_cap), flow(0) {}
void FlowEdge::read() {
    std::cin >> from >> to >> cap;
    from--; to--;
}

BiEdge::BiEdge(int _from, int _to, long long _cap) : FlowEdge(_from, _to, _cap) {}
void BiEdge::read() {
    std::cin >> from >> to >> cap;
    from--; to--;
    co_bi_edge = new BiEdge(to, from, 0);
    co_bi_edge->co_bi_edge = this;
}

void BiEdge::edgeDecrease(long long c) {
    cap -= c;
    flow += c;
    co_bi_edge->cap -= -c;
    co_bi_edge->flow += -c;
}

template <typename TEdge>
void Graph<TEdge>::addEdge(TEdge* t_edge) {
    graph[t_edge->from].push_back(t_edge);
}

void FlowGraph::read() {
    int m;
    std::cin >> n >> m;
    graph.resize(n);
    s = 0; t = n - 1;
    for(int i = 0; i < m; ++i) {
        BiEdge* bi_edge = new BiEdge();
        bi_edge->read();
        addEdge(bi_edge);
        addEdge(bi_edge->co_bi_edge);
        real_graph.push_back(bi_edge);
    }
}

void FlowGraph::print() {
    print_graph << n << "\n";
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < graph[i].size(); j++) {
            print_graph << "from= " << graph[i][j]->from << " to= " << graph[i][j]->to;
            print_graph << " cap= " << graph[i][j]->cap << " flow= " << graph[i][j]->flow << "\n";
        }
}

void FlowGraph::printRealGraph() {
    for (int i = 0; i < real_graph.size(); i++)
        print_graph << real_graph[i]->flow << "\n";
}

bool FlowGraph::isEdge(BiEdge* bi_edge) {
    if (bi_edge->cap > 0) {
        return true;
    } else {
        return false;
    }
}


 // End of graph.cpp



 // Start of maxflow.cpp




 // Start of maxflow.h



 // End of maxflow.h



MaxFlow::MaxFlow(FlowGraph _graph) {
    graph = _graph;
}


 // End of maxflow.cpp



 // Start of main.cpp




 // Start of graph.h



 // End of graph.h





 // Start of flowbfs.h



 // End of flowbfs.h





 // Start of blockflow.h



 // End of blockflow.h





 // Start of maxflowdinic.h



 // End of maxflowdinic.h





 // Start of preflow.h



 // End of preflow.h



int main() {
         FlowGraph g;
    g.read();
                            MaxFlowDinicScaling max_flow(g);
                 std::cout << max_flow.max_flow_value << "\n";
                          max_flow.graph.printRealGraph();
     
    return 0;
}


 // End of main.cpp

