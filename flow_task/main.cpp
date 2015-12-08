#include "graph.h"
#include "maxflowdinic.h"
#include "preflow.h"

int main() {
    std::cout << "describe a graph\n";
    FlowGraph g;
    g.read();
    int flag;
    std::cout << "DinicScaling (0) or PushPreFlow (1)?\n";
    std::cin >> flag;
    if (flag == 0) {
        MaxFlowDinicScaling max_flow(g);
        std::cout << "max flow value: " << max_flow.max_flow_value << "\n";
        std::cout << "edges:\n";
        max_flow.graph.printRealGraph();
    } else {
        MaxFlowPushPreFlow max_flow(g);
        std::cout << "max flow value: " << max_flow.max_flow_value << "\n";
        std::cout << "edges:\n";
        max_flow.graph.printRealGraph();
    }
    return 0;
}
