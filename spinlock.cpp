/**************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

***************************/

#include <iostream>
#include<atomic>
#include<queue>
#include<thread>
using namespace std;

template<typename T>
class threadsafe_queue {
    private:
    std::queue<T> q;
    
    int readerCount = 0;
    
    using Lock = std::atomic<bool>;
    Lock readerLock;
    Lock writerLock;
    
    public:
    void push(T &value) {
        acquire(writerLock);
        q.push(value);
        release(writerLock);
    }
    
    void pop() {
        acquire(writerLock);
        q.pop();
        release(writerLock);
    }
    
    T front() {
        acquire(readerLock);
        readerCount++;
        if(readerCount == 1) {
            acquire(writerLock);
        }
        release(readerLock);
        T data = q.front();
        acquire(readerLock);
        readerCount--;
        if(readerCount == 0) {
            release(writerLock);
        }
        release(readerLock);
        return data;
    }
    
    T size() {
        return q.size();
    }
    
   void acquire(Lock &lock) {
        while (lock.exchange(true, std::memory_order_acquire)) {
            
        }
    }

    void release(Lock &lock) {
        lock.store(false, std::memory_order_release);
    }
    
};
