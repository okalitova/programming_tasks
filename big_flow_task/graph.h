#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#define print_graph std::cout

class Edge {
public:
    int from;
    int to;
    Edge(int _from, int _to) : from(_from), to(_to) {}
    Edge() : from(0), to(0) {}
};

class FlowEdge : public Edge {
public:
    long long cap;
    long long flow;
    FlowEdge(int _from, int _to, long long _cap) : Edge(_from, _to), cap(_cap), flow(0) {}
    FlowEdge() : Edge() , cap(0), flow(0) {}
};

class BiEdge : public FlowEdge{
public:
    BiEdge* co_bi_edge;
    BiEdge(int _from, int _to, long long _cap) : FlowEdge(_from, _to, _cap) {}
    BiEdge(int _from, int _to) : FlowEdge() {}
};

template <typename TEdge>
class Graph {
public:
    int n;
    std::vector < std::vector < TEdge* > > graph;
    void addEdge(TEdge* t_edge) {
        graph[t_edge->from].push_back(t_edge);
    }

    virtual void read(const std::string &file_name) {
        std::ifstream read_graph(file_name.c_str());
        read_graph >> n;
        graph.resize(n);
        while(read_graph) {
            int from, to;
            read_graph >> from >> to;
            TEdge* t_edge = new TEdge(from, to);
            addEdge(t_edge);
        }
        read_graph.close();
    }
};

class FlowGraph : public Graph < BiEdge > {
public:
    int s, t;
    std::vector < BiEdge* > real_graph;
    void read(/*const std::string &file_name*/) {
        //std::ifstream read_graph(file_name.c_str());
        //read_graph >> n >> s >> t;
        //s--; t--;
        int m;
        std::cin >> n >> m;
        graph.resize(n);
        s = 0; t = n - 1;
        int from, to;
        long long cap;
        /*while(read_graph >> from >> to >> cap)*/for(int i = 0; i < m; ++i) {
            std::cin >> from >> to >> cap;
            from--; to--;
            BiEdge* bi_edge = new BiEdge(from, to, cap);
            BiEdge* co_bi_edge = new BiEdge(to, from, 0);
            bi_edge->co_bi_edge = co_bi_edge;
            co_bi_edge->co_bi_edge = bi_edge;
            addEdge(bi_edge);
            addEdge(co_bi_edge);
            real_graph.push_back(bi_edge);
        }
        //read_graph.close();
    }

    void print() {
        //std::ofstream print_graph();
        print_graph << n << "\n";
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < graph[i].size(); j++) {
                print_graph << "from= " << graph[i][j]->from << " to= " << graph[i][j]->to;
                print_graph << " cap= " << graph[i][j]->cap << " flow= " << graph[i][j]->flow << "\n";
            }
    }

    void printRealGraph() {
        for (int i = 0; i < real_graph.size(); i++)
            print_graph << real_graph[i]->flow << "\n";
    }
};

#endif // GRAPH_H_INCLUDED
