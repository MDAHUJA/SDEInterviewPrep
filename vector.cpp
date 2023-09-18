#include <iostream>
#include <stdexcept> // For exception handling

template<typename T> 
class Vector {
private:
    T* arr;
    int size;
    int capacity; 

public: 
    Vector() : arr(nullptr), size(0), capacity(0) {}

    Vector(int num) : arr(nullptr), size(0), capacity(0) {
        allocateMemory(num);
    }

    ~Vector() {
        delete[] arr;
    }

    // Member functions (defined outside the class)
    void pushBack(const T& element);
    void popBack();
    void clear();
    int getSize() const;
    int getCapacity() const;
    void printVector() const;
    T& operator[](int index);
    const T& operator[](int index) const;
    void reserve(int newCapacity);

private:
    // Helper function to allocate memory
    void allocateMemory(int num);
    void copyFrom(const Vector& other);
    void swap(Vector& first, Vector& second) noexcept;
};

// Member function definitions (defined outside the class)
template<typename T>
void Vector<T>::pushBack(const T& element) {
    if (size == capacity) {
        reserve(capacity + 5);
    }
    arr[size] = element;
    size++; 
}

template<typename T>
void Vector<T>::popBack() {
    if (size == 0) {
        throw std::underflow_error("Can't pop from an empty vector");
    }
    size--;
}

template<typename T>
void Vector<T>::clear() {
    delete[] arr;
    arr = nullptr;
    size = 0;
    capacity = 0;
}

template<typename T>
int Vector<T>::getSize() const {
    return size;
}

template<typename T>
int Vector<T>::getCapacity() const {
    return capacity;
}

template<typename T>
void Vector<T>::printVector() const {
    for (int i = 0; i < size; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

template<typename T>
T& Vector<T>::operator[](int index) {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Index out of range");
    }
    return arr[index];
}

template<typename T>
const T& Vector<T>::operator[](int index) const {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Index out of range");
    }
    return arr[index];
}

template<typename T>
void Vector<T>::reserve(int newCapacity) {
    if (newCapacity <= capacity) {
        return; // No need to shrink
    }
    T* temp = new T[newCapacity];
    for (int i = 0; i < size; i++) {
        temp[i] = arr[i];
    }
    delete[] arr;
    arr = temp;
    capacity = newCapacity;
}

template<typename T>
void Vector<T>::allocateMemory(int num) {
    if (num <= 0) {
        throw std::invalid_argument("Invalid vector size");
    }
    arr = new T[num];
    size = num;
    capacity = num;
}

// template<typename T>
// void Vector<T>::copyFrom(const Vector& other) {
//     allocateMemory(other.size);
//     for (int i = 0; i < size; i++) {
//         arr[i] = other.arr[i];
//     }
// }

// template<typename T>
// void Vector<T>::swap(Vector& first, Vector& second) noexcept {
//     using std::swap;
//     swap(first.arr, second.arr);
//     swap(first.size, second.size);
//     swap(first.capacity, second.capacity);
// }

int main() {
    return 0;
}
