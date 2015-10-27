#ifndef PREFLOW_H_INCLUDED
#define PREFLOW_H_INCLUDED

#include "graph.h"
#include <queue>

class MaxFlowPushPreFlow {
public:
    FlowGraph graph;
    long long max_flow_value;
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
    void edgeDecrease(BiEdge* bi_edge, long long c);
    void relable(int v);
    void push(BiEdge* bi_edge);
    void gap(int gap_h);
    void discharge(int v);
};

#endif // PREFLOW_H_INCLUDED
