#include <iostream>
#include <vector>
#include <mutex>
#include <condition_variable>

using namespace std;

template <typename T>
class CircularBuffer {
public:
    explicit CircularBuffer(size_t size) : buffer_(size), size_(size), write_index_(0), read_index_(0) {}

    void Push(const T& item) {
        unique_lock<mutex> lock(mutex_);
        not_full_.wait(lock, [this] { return !IsFull(); });
        buffer_[write_index_] = item;
        write_index_ = (write_index_ + 1) % size_;
        not_empty_.notify_all();
    }

    T Pop() {
        unique_lock<mutex> lock(mutex_);
        not_empty_.wait(lock, [this] { return !IsEmpty(); });
        T item = buffer_[read_index_];
        read_index_ = (read_index_ + 1) % size_;
        not_full_.notify_all();
        return item;
    }

private:
    bool IsFull() const {
        return ((write_index_ + 1) % size_) == read_index_;
    }

    bool IsEmpty() const {
        return write_index_ == read_index_;
    }

    vector<T> buffer_;
    size_t size_;
    size_t write_index_;
    size_t read_index_;
    mutex mutex_;
    condition_variable not_full_;
    condition_variable not_empty_;
};

int main() {
    CircularBuffer<int> buffer(5);

    thread producer([&buffer]() {
        for (int i = 1; i <= 10; ++i) {
            buffer.Push(i);
            this_thread::sleep_for(chrono::milliseconds(100));
        }
    });

    thread consumer([&buffer]() {
        for (int i = 1; i <= 10; ++i) {
            int item = buffer.Pop();
            cout << "Consumed: " << item << endl;
            this_thread::sleep_for(chrono::milliseconds(200));
        }
    });

    producer.join();
    consumer.join();

    return 0;
}
