#include "graph.h"

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
