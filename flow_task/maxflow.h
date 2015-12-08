#ifndef MAXFLOW_H_INCLUDED
#define MAXFLOW_H_INCLUDED

#include "graph.h"

class MaxFlow {
public:
    static const int INF = 1e9;
    FlowGraph graph;
    long long max_flow_value;
public:
    MaxFlow(FlowGraph _graph);
};

#endif // MAXFLOW_H_INCLUDED
