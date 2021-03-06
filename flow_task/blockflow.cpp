#include "blockflow.h"
#include "maxflow.h"

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
