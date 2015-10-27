#ifndef BLOCKFLOW_H_INCLUDED
#define BLOCKFLOW_H_INCLUDED

#include <vector>
#include "graph.h"

class BlockFlow {
private:
    std::vector < int > cur_edge;
    FlowGraph graph;
public:
    long long max_block_flow;
public:
    BlockFlow(FlowGraph _graph);
private:
    bool dfs(int v);

    long long pathMin(int v);

    void pathDecrease(int v, long long c);

    void edgeDecrease(BiEdge* bi_edge, long long c);
};

#endif // BLOCKFLOW_H_INCLUDED
