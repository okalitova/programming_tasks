#include "graph.h"

#define print_graph std::cout

Edge::Edge(int _from, int _to) : from(_from), to(_to) {}
Edge::Edge() : from(0), to(0) {}

FlowEdge::FlowEdge(int _from, int _to, long long _cap) : Edge(_from, _to), cap(_cap), flow(0) {}
FlowEdge::FlowEdge() : Edge() , cap(0), flow(0) {}

BiEdge::BiEdge(int _from, int _to, long long _cap) : FlowEdge(_from, _to, _cap) {}
BiEdge::BiEdge(int _from, int _to) : FlowEdge() {}

template <typename TEdge>
void Graph<TEdge>::addEdge(TEdge* t_edge) {
    graph[t_edge->from].push_back(t_edge);
}

void FlowGraph::read() {
    int m;
    std::cin >> n >> m;
    graph.resize(n);
    s = 0; t = n - 1;
    int from, to;
    long long cap;
    for(int i = 0; i < m; ++i) {
        std::cin >> from >> to >> cap;
        from--; to--;
        BiEdge* bi_edge = new BiEdge(from, to, cap);
        BiEdge* co_bi_edge = new BiEdge(to, from, 0);
        bi_edge->co_bi_edge = co_bi_edge;
        co_bi_edge->co_bi_edge = bi_edge;
        addEdge(bi_edge);
        addEdge(co_bi_edge);
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
