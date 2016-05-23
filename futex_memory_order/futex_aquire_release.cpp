//
// Created by nimloth on 13.05.16.
//

#include <iostream>
#include <atomic>
#include <thread>
#include <chrono>
#include <vector>
#include <mutex>

using namespace std;

typedef thread::id tid;

class futex{
private:
    atomic<tid> block;
public:
    futex() {
        tid zero(0);
        block = zero;
    }

    ~futex() {
        tid zero(0);
        block = zero;
    }

    void lock() {
        tid zero(0);
        tid thread_id = this_thread::get_id();
        while(!block.compare_exchange_strong(zero, thread_id, std::memory_order_acquire)) {
            std::this_thread::yield();
            zero = tid(0);
        }
    }

    void unlock() {
        tid zero(0);
        tid thread_id = this_thread::get_id();
        if(!block.compare_exchange_strong(thread_id, zero, memory_order_release)) {
            throw new exception;
        }
    }

    bool try_lock() {
        tid zero(0);
        tid thread_id = this_thread::get_id();
        if(!block.compare_exchange_strong(zero, thread_id)) return false;
        else return true;
    }
};

futex ftx;
mutex mtx;

int sum = 0;
vector<int> sum_thread(20);

void calculateSum(int k, int num) {
    for (int i = 0; i < k; ++i) {
        ftx.lock();
        sum++;
        ftx.unlock();
    }
}

int main() {
    freopen("res_futex_aquire_release.txt", "w", stdout);
    vector<thread> threads;
    int n, k;
    k = 36288000;
    for (int n = 2; n < 10; ++n) {
        sum = 0;
        threads.clear();
        auto start_time = std::chrono::steady_clock::now();
        for (int i = 0; i < n; i++) {
            threads.push_back(thread(calculateSum, k / n, i));
        }
        for (int i = 0; i < n; i++) {
            threads[i].join();
        }
        auto end_time = std::chrono::steady_clock::now();
        auto elapsed_ns = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);

        std::cout << "time: " << n << " " << elapsed_ns.count() << "\n";
        cout << "check correctness:\n";
        cout << "sum = " << sum << "\n";
    }
    return 0;
}