#include <iostream>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <unistd.h>

using namespace std;

template <typename T>
class Queue {
public:
    virtual void pop() = 0;
    virtual void push(T item) = 0;
    virtual T front() = 0;
    virtual bool empty() = 0;
};

template<typename T>
class SyncQueue : public Queue<T>{
private:
    queue<T> que;
    mutex mtx;
    std::condition_variable notEmpty;
public:
    void push(T item) {
        unique_lock<mutex> u_lock(mtx);
        que.push(item);
        u_lock.unlock();
        notEmpty.notify_one();
    }

    void pop() {
        unique_lock<mutex> u_lock(mtx);
        notEmpty.wait(u_lock, [this] {return !this->que.empty();});
        que.pop();
    }

    T front() {
        unique_lock<mutex> u_lock(mtx);
        return que.front();
    }

    bool empty() {
        unique_lock<mutex> u_lock(mtx);
        return que.empty();
    }
};

SyncQueue<int> sync_queue;

void pushElem(int num) {
    sync_queue.push(num);
}

void popElem() {
    sync_queue.pop();
}

int main() {
    vector<thread> threads;
    int n, m;
    cin >> n;
    for (int i = 0; i < n; i++) {
        if (i % 2 == 0)
            threads.push_back(thread(pushElem, i));
        else
            threads.push_back(thread(popElem));
    }
    for (int i = 0; i < n; i++) {
        threads[i].join();
    }
    while(!sync_queue.empty()) {
        cout << sync_queue.front() << " ";
        sync_queue.pop();
    }
    return 0;
}