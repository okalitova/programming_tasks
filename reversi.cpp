#include <iostream>
#include <vector>
#include <math.h>
#include <string>

class Node{
public:
    static const int EMPTY = 0;
    static const int BLACK = 1;
    static const int WHITE = 2;
    std::vector<std::vector<int>> state;
    std::pair <int, int> last_move;
    std::pair <int, int> best_move;
    int f;
    int g;
    int step;
    int start_color;
public:
    Node(std::vector<std::vector<int>> init_state, int init_start_color, int init_step, std::pair<int, int> init_last_move) {
        state.resize(8);
        for (int i = 0; i < 8; ++i) {
            state[i].resize(8);
            for (int j = 0; j < 8; ++j)
                state[i][j] = init_state[i][j];
        }
        start_color = init_start_color;
        step = init_step;
        last_move = init_last_move;
    }
    std::vector<Node> getChilds() {
        std::vector<Node> childs;
        std::vector<std::pair<int, int>> steps = getAvailable();
        for (int k = 0; k < steps.size(); ++k) {
            int i = steps[k].first;
            int j = steps[k].second;
            childs.push_back(movement(i, j));
        }
        return childs;
    }

    bool isTerminal() {
        if (step == 65) return true;
        std::vector<std::pair<int, int>> available1;
        available1 = getAvailable();
        if (available1.size() != 0) return false;
        if (start_color == 1) {
            start_color = 2;
        } else {
            start_color = 1;
        }
        std::vector<std::pair<int, int>> available2;
        available2 = getAvailable();
        if (start_color == 1) {
            start_color = 2;
        } else {
            start_color = 1;
        }
        if (available2.size() != 0) return false;
        else return true;
        //getAvailable();
    }

    int getF() {
        int f = 0;
        for (int i = 0; i < 8; ++i)
            for(int j = 0; j < 8; ++j) {
                int value = 0;
                if (i == 0 && j == 0 || i == 0 && j == 7 || i == 7 && j == 0 || i == 7 && j == 0) {
                    value = std::max(1, 110 - step);
                    if (step > 60) value = 1;
                } else {
                    if (i == 0 && 1 < j && j < 6  || i == 7 && 1 < j && j < 6 || j == 0 && 1 < i && i < 6 || j == 7 && 1 < i && i < 6) {
                        value = std::max(1, 50 - step);
                        if (step > 60) value = 1;
                    } else {
                        if ((i == 0 || i == 7) && (j == 1 || j == 6) || (i == 1 || i == 6) && (j == 0 || j == 1 || j == 6 || j == 7)) {
                            value = std::min(-20 + step, 0);
                            if (step > 60) value = 1;
                        } else value = 1;
                    }
                }
                if (state[i][j] == BLACK) f += value;
                if (state[i][j] == WHITE) f -= value;
            }
        //std:: << "f: " << f << "\n";
        return f;
    }

    Node movement(int i, int j) {
        std::vector<std::vector<int>> new_state;
        new_state.resize(8);
        for (int i = 0; i < 8; ++i) {
            new_state[i].resize(8);
            for (int j = 0; j < 8; ++j)
                new_state[i][j] = state[i][j];
        }
        for (int i_flag = -1; i_flag <= 1; i_flag++)
            for (int j_flag = -1; j_flag <= 1; j_flag++) {
                if (i_flag != 0 || j_flag != 0) {
                    coverDestination(i, j, i_flag, j_flag, start_color, new_state);
                }
            }
        int new_color;
        if (start_color == 1) {
            new_color = 2;
        } else {
            new_color = 1;
        }
        Node node(new_state, new_color, step + 1, std::make_pair(i, j));
        return node;
    }

    std::vector<std::pair<int, int>> getAvailable() {
        std::vector<std::pair<int, int>> steps;
        for (int i = 0; i < 8; ++i)
            for (int j = 0; j < 8; ++j) {
                bool available = false;
                if (state[i][j] == EMPTY) {
                for (int i_flag = -1; i_flag <= 1; i_flag++)
                    for (int j_flag = -1; j_flag <= 1; j_flag++) {
                        if ((i_flag != 0 || j_flag != 0)) {
                            if(checkDestination(i, j, i_flag, j_flag, start_color))
                                available = true;
                            //std::cout << i << " " << j << " " << i_flag << " " << j_flag  << "\n";
                        }
                    }
                }
                if (available) steps.push_back(std::make_pair(i, j));
            }
        return steps;
    }

private:

    void coverDestination(int i, int j, int i_flag, int j_flag, int color, std::vector<std::vector<int>> &new_state) {
        int i_cur = i, j_cur = j;
        //first step
        if (0 <= i_cur + i_flag && i_cur + i_flag < 8 && 0 <= j_cur + j_flag && j_cur + j_flag < 8) {
            if (state[i_cur + i_flag][j_cur + j_flag] == color || state[i_cur + i_flag][j_cur + j_flag] == EMPTY) {
                return;
            }
        } else return;
        //
        while(0 <= i_cur && i_cur < 8 && 0 <= j_cur && j_cur < 8) {
            if (0 <= i_cur + i_flag && i_cur + i_flag < 8 && 0 <= j_cur + j_flag && j_cur + j_flag < 8) {
                if (state[i_cur + i_flag][j_cur + j_flag] == EMPTY) {
                    return;
                } else {
                    if (state[i_cur + i_flag][j_cur + j_flag] == color) {
                        i_cur += i_flag;
                        j_cur += j_flag;
                        break;
                    } else {
                        i_cur += i_flag;
                        j_cur += j_flag;
                    }
                }
            } else return;
        }
        while (i != i_cur || j != j_cur) {
            new_state[i][j] = color;
            i += i_flag;
            j += j_flag;
        }
    }

    bool checkDestination(int i, int j, int i_flag, int j_flag, int color) {
        int i_cur = i, j_cur = j;
        //first step
        if (0 <= i_cur + i_flag && i_cur + i_flag < 8 && 0 <= j_cur + j_flag && j_cur + j_flag < 8) {
            if (state[i_cur + i_flag][j_cur + j_flag] == color || state[i_cur + i_flag][j_cur + j_flag] == EMPTY) {
                return false;
            }
        } else return false;
        //
        while(0 <= i_cur && i_cur < 8 && 0 <= j_cur && j_cur < 8) {
            if (0 <= i_cur + i_flag && i_cur + i_flag < 8 && 0 <= j_cur + j_flag && j_cur + j_flag < 8) {
                if (state[i_cur + i_flag][j_cur + j_flag] == EMPTY) {
                    return false;
                } else {
                    if (state[i_cur + i_flag][j_cur + j_flag] == color) {
                        i_cur += i_flag;
                        j_cur += j_flag;
                        return true;
                    } else {
                        i_cur += i_flag;
                        j_cur += j_flag;
                    }
                }
            } else return false;
        }
    }
};

int alphabeta(Node &node, int depth, int alpha, int beta, bool maximizing_player, int &counter) {
    //std::cerr << node.start_color << "\n";
    static const int INF = 1e9;
   // std::cerr << "terminal: " << node.isTerminal() << "\n";
    if (depth == 0) {
        counter++;
      //  std::cerr << "f: " << node.getF() << "\n";
        return node.getF();

    }
    if (node.isTerminal()) {
        counter++;
        return node.getF() * 1000;
    }
    int v;
    std::vector <Node> childs = node.getChilds();
    /*if (depth == 4) {
        std::cerr << node.start_color << "\n";
        std::cerr << "HERE " << childs.size() << "\n";
         for (int k = 0; k < childs.size(); ++k) {
            for (int i = 0; i < 8; ++i) {
                for (int j = 0; j < 8; ++j) {
                    std::cerr << "H" << childs[k].state[j][i] << " ";
                }
                std::cerr << "\n";
            }
            std::cerr << "\n";
        }
    }*/
    if (childs.size() == 0) {
        if (node.start_color == 1) {
            node.start_color = 2;
        } else {
            node.start_color = 1;
        }
        if (maximizing_player)
            maximizing_player = false;
        else
            maximizing_player = true;
    }
    if (maximizing_player) {
        v = -INF;
        for (int i = 0; i < childs.size(); ++i) {
            /*if (node.step == 64 || node.step == 63) {
                std::cerr << "CHILD1\n";
                for (int k = 0; k < 8; ++k) {
                            for (int j = 0; j < 8; ++j) {
                                std::cerr << childs[i].state[j][k] << " ";
                            }
                            std::cerr << "\n";
                }
            }*/
            counter++;
            int ab = alphabeta(childs[i], depth - 1, alpha, beta, false, counter);
            if (v < ab) {
                v = ab;
                node.best_move = childs[i].last_move;
                //if (depth >= 4) std::cerr << "v: " << v << " "<< "depth: " << depth << " best_move " << "\n";
            }
            alpha = std::max(alpha, v);
            if (beta < alpha) break;
        }
    } else {
        //if (depth == 4) std::cerr << "HERE2\n";
        v = INF;
        for (int i = 0; i < childs.size(); ++i) {
            counter++;
            /*if (node.step == 64 || node.step == 63) {
                std::cerr << "CHILD2\n";
                for (int k = 0; k < 8; ++k) {
                            for (int j = 0; j < 8; ++j) {
                                std::cerr << childs[i].state[j][k] << " ";
                            }
                            std::cerr << "\n";
                }
            }*/
            int ab = alphabeta(childs[i], depth - 1, alpha, beta, true, counter);
            if (v > ab) {
                v = ab;
                node.best_move = childs[i].last_move;
            }
            beta = std::min(beta, v);
            if (beta < alpha) break;
        }
    }
    return v;
}

int main() {
    /*
    1 1 1 2 1 1 0 1
    1 1 1 2 1 1 1 1
    1 1 1 1 1 1 1 2
    2 2 2 2 1 2 1 1
    2 1 1 1 2 2 1 2
    1 1 1 1 2 2 1 2
    1 1 2 1 1 2 1 2
    2 1 1 1 2 1 1 2
    */
    std::vector<std::vector<int>> init_state;
    init_state.resize(8);
    for (int i = 0; i < 8; ++i)
        init_state[i].resize(8);
    init_state[3][3] = Node::WHITE;
    init_state[3][4] = Node::BLACK;
    init_state[4][3] = Node::BLACK;
    init_state[4][4] = Node::WHITE;
    /*for (int i = 0; i < 8; ++i)
        for (int j = 0; j < 8; ++j)
            std::cin >> init_state[i][j];*/
    Node node(init_state, 1, 5, std::make_pair(0, 0));
    /*std::vector<Node> test = node.getChilds();
    for (int k = 0; k < test.size(); ++k) {
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                std::cout << test[k].state[i][j] << " ";
            }
            std::cout << "\n";
        }
        std::cout << test[k].last_move.first << " " << test[k].last_move.second << "\n";
    }*/
    std::string s;
    std::cin >> s;
    std::cin >> s;
    bool maximizing;
    if (s == "black") {
        maximizing = true;
    } else {
        maximizing = false;
    }
    //std::cerr << maximizing << "\n";
    while(std::cin >> s) {
       // std::cerr << node.start_color << "\n";
        if (s == "move") {
            if (maximizing)
                node.start_color = 2;
            else
                node.start_color = 1;
            int i;
            char c;
            std::cin >> c >> i;
            i--;
            int j = c - 'a';
            //std::cerr << node.start_color << "\n";
            node = node.movement(i, j);
           // std::cerr << node.start_color << "\n";
        } else {
            if (s == "turn") {
                int depth = 2;
                while(depth < 9) {
                  //  std::cerr << "depth: " << depth << "\n";
                    if (maximizing)
                        node.start_color = 1;
                    else
                        node.start_color = 2;
                    int counter = 0;
                    alphabeta(node, depth, -1e9, 1e9, maximizing, counter);
                    std::cerr << "depth: " << depth << "\n";
                    depth++;
                    if (counter > 10000) break;
                }
                //std::cerr << "depth: " << depth << "\n";
                std::cout << "move " << (char)('a' + node.best_move.second) <<  " " << node.best_move.first + 1 << "\n";
                node = node.movement(node.best_move.first, node.best_move.second);
            } else {
                if (s == "win" || s == "lose" || s == "draw")
                    return 0;
            }
        }
        /*for (int i = 0; i < 8; ++i) {
                for (int j = 0; j < 8; ++j) {
                    std::cerr << node.state[j][i] << " ";
                }
                std::cerr << "\n";
            }
            std::cerr << "\n";
        std::vector<Node> childs = node.getChilds();
        for (int k = 0; k < childs.size(); ++k) {
            for (int i = 0; i < 8; ++i) {
                for (int j = 0; j < 8; ++j) {
                    std::cerr << childs[k].state[j][i] << " ";
                }
                std::cerr << "\n";
            }
            std::cerr << "\n";
        }*/
    }
}
