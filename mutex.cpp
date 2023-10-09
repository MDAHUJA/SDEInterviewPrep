/**************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

***************************/

#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <shared_mutex> 

using namespace std;

template<typename T>
class threadsafe_queue {
    public:
    
    void enqueue(T data) {
        std::unique_lock<std::shared_mutex> lock(s_m);
        queue.push(data);
    }
    
    T deque() {
     std::unique_lock<std::shared_mutex> lock(s_m);
     T f = queue.front();
     queue.pop();
     return f;
    }
    
    T front() {
        std::shared_lock<std::shared_mutex> lock(s_m);
        return queue.front();
    }
    
    T size() {
        std::shared_lock<std::shared_mutex> lock(s_m);
        return queue.size();
    }
    
    private:
    std::queue<T> queue;
    mutable std::shared_mutex s_m;
};

 threadsafe_queue<int> q;
 void enqueue(int a) {
     q.enqueue(a);
 }
 
 
 void pop() {
     q.deque();
 }

int main()
{
    std::thread t1(enqueue, 1);   
    std::thread t2(enqueue, 2); 
    std::thread t3(pop);
    
    t1.join(); // Make sure to join the threads
    t2.join();
    t3.join();
    
    cout << "size" << q.size() << endl;
    cout << "front" << q.front() << endl;

    

    return 0;
}
