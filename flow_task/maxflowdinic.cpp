#include "maxflowdinic.h"
#include "flowbfs.h"
#include "blockflow.h"

MaxFlowDinic::MaxFlowDinic(FlowGraph _flow_graph) : flow_graph(_flow_graph) {
    max_flow_value = 0;
    while (true) {
        FlowBfs flow_bfs(flow_graph);
        if (flow_bfs.isConnected()) {
            BlockFlow block_flow(flow_bfs.getLayerNet());
            max_flow_value += block_flow.max_block_flow;
        } else {
            break;
        }
    }
}

MaxFlowDinicScaling::MaxFlowDinicScaling(FlowGraph _flow_graph) : flow_graph(_flow_graph) {
    max_flow_value = 0;
    max_edge_value = findMaxEdgeValue();
    while (max_edge_value > 0) {
        FlowGraph cur_graph;
        cur_graph = createGraph(max_edge_value);
        MaxFlowDinic max_flow(cur_graph);
        max_flow_value += max_flow.max_flow_value;
        max_edge_value = max_edge_value / 2;
        //flow_graph = block_flow.getGraph;
    }
}

long long MaxFlowDinicScaling::findMaxEdgeValue() {
    long long max_e = 0;
    for (int i = 0; i < flow_graph.n; ++i)
        for (int j = 0; j < flow_graph.graph[i].size(); ++j) {
            max_e = std::max(max_e, flow_graph.graph[i][j]->cap);
        }
    return max_e;
}

FlowGraph MaxFlowDinicScaling::createGraph(long long value) {
    FlowGraph cur_graph;
    cur_graph.n = flow_graph.n;
    cur_graph.s = flow_graph.s;
    cur_graph.t = flow_graph.t;
    cur_graph.graph.resize(cur_graph.n);
    for (int i = 0; i < flow_graph.n; ++i)
        for (int j = 0; j < flow_graph.graph[i].size(); ++j) {
            if (flow_graph.graph[i][j]->cap >= value) {
                cur_graph.graph[i].push_back(flow_graph.graph[i][j]);
            }
        }
    return cur_graph;
}
