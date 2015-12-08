#include "maxflowdinic.h"
#include "blockflow.h"
#include "bfs.h"
#include "graph.h"
#include "maxflow.h"

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
