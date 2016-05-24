#include <iostream>
#include <thread>
#include <vector>
#include <chrono>

using namespace std;

int a = 0;
int b[1000000];
int c = 0;

vector<thread> threads;

void f(int &x) {
    for (int i = 0; i < 1e9; ++i) {
        x = (x % 123 + 678) % 345;
    }
}

int main() {
    freopen("without_ping_pong.txt", "w", stdout);
    auto start_time = std::chrono::steady_clock::now();
    threads.push_back(thread(f, std::ref(a)));
    threads.push_back(thread(f, std::ref(c)));
    for (int i = 0; i < 2; ++i) {
        threads[i].join();
    }
    auto end_time = std::chrono::steady_clock::now();
    auto elapsed_ns = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
    std::cout << "time: " << elapsed_ns.count() << "\n";
    cout << a << " " << c;
    return 0;
}

