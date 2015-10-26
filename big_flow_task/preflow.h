#ifndef PREFLOW_H_INCLUDED
#define PREFLOW_H_INCLUDED

class MaxFlowPushPreFlow {
public:
    FlowGraph graph;
    long long max_flow_value;
    std::vector < int > h;
    std::vector < long long > e;
    std::queue < int > q;
    std::vector < int > current_push;
    std::vector < int > h_count;

    MaxFlowPushPreFlow(FlowGraph _graph) : graph(_graph) {
        max_flow_value = 0;
        initializePreFlow();
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            if (v == graph.t || v == graph.s) continue;
            discharge(v);
        }
        max_flow_value = e[graph.t];
    }

    void initializePreFlow() {
        h.resize(graph.n, 0);
        e.resize(graph.n, 0);
        current_push.resize(graph.n, 0);
        h_count.resize(graph.n * 2 + 1, 0);
        h_count[0] = graph.n - 1;
        h[graph.s] = graph.n;
        for (int i = 0; i < graph.graph[graph.s].size(); ++i) {
            int to = graph.graph[graph.s][i]->to;
            long long cap = graph.graph[graph.s][i]->cap;
            e[to] += cap;
            edgeDecrease(graph.graph[graph.s][i], cap);
            if (e[to] > 0)
                q.push(to);
        }
    }

    void edgeDecrease(BiEdge* bi_edge, long long c) {
        bi_edge->cap -= c;
        bi_edge->flow += c;
        bi_edge->co_bi_edge->cap -= -c;
        bi_edge->co_bi_edge->flow += -c;
    }

    void relable(int v) {
        int h_min = 3 * graph.n;
        for (int i = 0; i < graph.graph[v].size(); ++i) {
            if (graph.graph[v][i]-> cap > 0) {
                h_min = std::min(h_min, h[graph.graph[v][i]->to]);
            }
        }
        if (h_min < 3 * graph.n) {
            h[v] = h_min + 1;
        }
    }

    void push(BiEdge* bi_edge) {
        int from = bi_edge->from;
        int to = bi_edge->to;
        long long c = std::min(e[from], bi_edge->cap);
        edgeDecrease(bi_edge, c);
        e[from] -= c;
        e[to] += c;
        if (e[to] == c && e[to] > 0)
            q.push(to);
    }

    void gap(int gap_h) {
        if (h_count[gap_h] != 0) return;
        for (int i = 0; i < graph.n; ++i)
            if (i != graph.s && i != graph.t) {
                if(h[i] > gap_h && h[i] < graph.n) {
                    h[i] = graph.n;
                }
            }
    }

    void discharge(int v) {
        int old_h = h[v];
        int cur = current_push[v];
        while (e[v] > 0) {
            if (cur == graph.graph[v].size()) {
                cur = 0;
                relable(v);
            } else {
                if (h[v] == h[graph.graph[v][cur]->to] + 1 && graph.graph[v][cur]->cap > 0) {
                    push(graph.graph[v][cur]);
                } else {
                    ++cur;
                }
            }
        }
        current_push[v] = cur;
        h_count[old_h] -= 1;
        h_count[h[v]] += 1;
        if (old_h < graph.n && h_count[old_h] == 0) gap(old_h);
    }
};

#endif // PREFLOW_H_INCLUDED
