#ifndef MAXFLOWDINIC_H_INCLUDED
#define MAXFLOWDINIC_H_INCLUDED

#include "graph.h"
#include "maxflow.h"

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

#endif // MAXFLOWDINIC_H_INCLUDED
