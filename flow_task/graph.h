#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include <string>
#include <iostream>
#include <vector>

#define print_graph std::cout

class Edge {
public:
    int from;
    int to;
    Edge(int _from, int _to);
    Edge();
};

class FlowEdge : public Edge {
public:
    long long cap;
    long long flow;
    FlowEdge(int _from, int _to, long long _cap);
    FlowEdge();
};

class BiEdge : public FlowEdge{
public:
    BiEdge* co_bi_edge;
    BiEdge(int _from, int _to, long long _cap);
    BiEdge(int _from, int _to);
};

template <typename TEdge>
class Graph {
public:
    int n;
    std::vector < std::vector < TEdge* > > graph;

    void addEdge(TEdge* t_edge);
    virtual void read() = 0;
};

class FlowGraph : public Graph < BiEdge > {
public:
    int s, t;
    std::vector < BiEdge* > real_graph;

    void read();
    void print();
    void printRealGraph();
};

#endif // GRAPH_H_INCLUDED
