#ifndef MAXFLOWDINIC_H_INCLUDED
#define MAXFLOWDINIC_H_INCLUDED

#include "graph.h"

class MaxFlowDinic {
public:
    long long max_flow_value;
    FlowGraph flow_graph;
public:
    MaxFlowDinic(FlowGraph _flow_graph);
};

class MaxFlowDinicScaling {
public:
    long long max_flow_value;
    FlowGraph flow_graph;
private:
    long long max_edge_value;
public:
    MaxFlowDinicScaling(FlowGraph _flow_graph);
private:
    long long findMaxEdgeValue();

    FlowGraph createGraph(long long value);
};

#endif // MAXFLOWDINIC_H_INCLUDED
