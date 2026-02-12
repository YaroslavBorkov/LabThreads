#pragma once
#include <queue>
#include <mutex>
#include <condition_variable>

template <class T>
class BlockingQueue { //потокобезопасная очередь блокирует поток при попытке 
    //извлечь элемент из пустой очереди и разблокирует его когда элемент становится доступным
public:
    void push(const T& x) {
        std::unique_lock<std::mutex> lock(m);
        q.push(x);
        cv.notify_one();
    }

    void push(T&& x) {
        std::unique_lock<std::mutex> lock(m);
        q.push(std::move(x));
        cv.notify_one();
    }

    T pop() {
        std::unique_lock<std::mutex> lock(m);
        cv.wait(lock, [&]{ return !q.empty(); });
        T x = std::move(q.front());
        q.pop();
        return x;
    }

private:
    std::queue<T> q;
    std::mutex m;
    std::condition_variable cv;
};
