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
    Edge();
    Edge(int _from, int _to);
    virtual void read();
};

class FlowEdge : public Edge {
public:
    long long cap;
    long long flow;
    FlowEdge();
    FlowEdge(int _from, int _to, long long _cap = 0);
    void read();
};

class BiEdge : public FlowEdge {
public:
    BiEdge* co_bi_edge;
    BiEdge(int _from = 0, int _to = 0, long long _cap = 0);
    void read();
    void edgeDecrease(long long c);
};

template <typename TEdge>
class Graph {
public:
    typedef TEdge EdgeType;
    int n;
    int s;
    int t;
    std::vector < std::vector < TEdge* > > graph;
    virtual void read() = 0;
    void addEdge(TEdge* t_edge);
};

class FlowGraph : public Graph < BiEdge > {
public:
    void read();
    void print();
    void printRealGraph();
    static bool isEdge(BiEdge* bi_edge);
private:
    std::vector < BiEdge* > real_graph;
};

#endif // GRAPH_H_INCLUDED
