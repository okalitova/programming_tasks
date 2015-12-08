#ifndef PREFLOW_H_INCLUDED
#define PREFLOW_H_INCLUDED

#include "graph.h"
#include "maxflow.h"
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

#endif // PREFLOW_H_INCLUDED
