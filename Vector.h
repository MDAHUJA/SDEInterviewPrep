#pragma once 
#include <iostream>
using namespace std;

template<typename T> 
class Vector {
public: 
    Vector() {
        // allocate 2 elements
        ReAlloc(2);
    }
    ~Vector() {
        Clear();
        delete[] m_Data;
    }
    void pushBack(const T& value) {
        if(m_Size >= m_Capacity) {
            ReAlloc(m_Capacity + (m_Capacity / 2));
        }
        m_Data[m_Size] = value; 
        m_Size++;
    }
    void pushBack(T&& value) {
        if(m_Size >= m_Capacity) {
            ReAlloc(m_Capacity + (m_Capacity / 2));
        }
        m_Data[m_Size] = move(value); 
        m_Size++;
    }
    template<typename... Args>
    T& emplaceBack(Args&&... args) {
        if(m_Size >= m_Capacity) {
            ReAlloc(m_Capacity + m_Capacity / 2);
        }
        m_Data[m_Size] = T(forward<Args>(args)...);
        return m_Data[m_Size++];
    } 
    void popBack() {
        if(m_Size > 0) {
            m_Size--;
            m_Data[m_Size].~T();
        }
    }
    void clear() {
        for(size_t i = 0; i < m_Size; i++) {
            m_Data[i].~T();
        }
        m_Size = 0;
    }
    size_t Size() const { return m_Size; }
    T& operator[](size_t index) {
        return m_Data[index];
    }
    const T& operator[](size_t index) const {
        if(index >= m_Size) {
            //assert
        }
        return m_Data[index];
    }
private: 
    void ReAlloc(size_t newCapacity) {
        // 1. allocate a new block of memory 
        // 2. Copy/move old elements into new block 
        // 3. delete 

        T* newBlock = ::operator new(newCapacity * sizeof(T));

        if(newCapacity < m_Size) {
            m_Size = newCapacity;
        }

        for(size_t i = 0; i < m_Size; i++) {
            newBlock[i] = move(m_Data[i]);
        }

        delete[] m_Data;
        m_Data = newBlock;
        m_Capacity = newCapacity;
    }
private: 
    T* m_Data = nullptr;

    size_t m_Size = 0;
    size_t m_Capacity = 0; 
};