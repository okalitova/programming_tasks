#ifndef FLOWBFS_H_INCLUDED
#define FLOWBFS_H_INCLUDED

#include <vector>
#include "graph.h"

class FlowBfs {
private:
    std::vector < int > dist;
    std::vector < int > prev;
    FlowGraph graph;
    int start;
public:

    FlowBfs(FlowGraph _graph);

    std::vector < int > getDist();

    std::vector < int > getPrev();

    bool isConnected();

    FlowGraph getLayerNet();
};

#endif // FLOWBFS_H_INCLUDED
