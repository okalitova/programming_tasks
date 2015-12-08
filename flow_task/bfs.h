#ifndef BFS_H_INCLUDED
#define BFS_H_INCLUDED

#include "graph.h"

template <typename TGraph>
class Bfs {
private:
    std::vector < int > dist;
    std::vector < int > prev;
    TGraph graph;
    int start;
public:
    Bfs(TGraph _graph, bool (*isEdge)(typename TGraph::EdgeType*));
    std::vector < int > getDist();

    std::vector < int > getPrev();

    bool isConnected();

    TGraph getLayerNet();
};

#include "bfs.cpp"

#endif // FLOWBFS_H_INCLUDED
