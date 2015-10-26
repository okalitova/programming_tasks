#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
#include <cstdio>
#include <queue>
#include <cmath>
#include "graph.h"
#include "preflow.h"

int main(/*int argc, char** argv*/) {
    //std::string file_name(argv[2]);
    FlowGraph g;
    g.read(/*file_name*/);
    MaxFlowPushPreFlow max_flow(g);
    std::cout << max_flow.max_flow_value << "\n";
    max_flow.graph.printRealGraph();
    return 0;
}
