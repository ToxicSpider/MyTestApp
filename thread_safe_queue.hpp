#ifndef THREAD_SAFE_QUEUE_HPP
#define THREAD_SAFE_QUEUE_HPP

#include <queue>
#include <mutex>

/*
A thread-safe queue. We want to guarantee full thread safety, 
and since the standard does not provide such a structure, 
it needs to be implemented independently.
*/

template <typename T>
class ThreadSafeQueue {
public:
    void enqueue(const T & item) {
        std::lock_guard<std::mutex> lk(lock_);
        queue_.push(item);
    }

    bool dequeue(T & result) {
        std::lock_guard<std::mutex> lk(lock_);
        if (queue_.empty()) { 
            return false;
        }
        result = queue_.front();
        queue_.pop();
        return true;
    }

private:
    std::queue<T> queue_;
    std::mutex lock_;
};

#endif // THREAD_SAFE_QUEUE_HPP