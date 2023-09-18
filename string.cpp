#include <iostream>
#include <cstring>
#include <stdexcept>

class MyString {
private:
    char* str;

public:
    MyString() : str(nullptr) {}

    MyString(const char* val) {
        if (val == nullptr) {
            str = nullptr;
        }
        else {
            str = new char[std::strlen(val) + 1];
            std::strcpy(str, val);
        }
    }

    MyString(const MyString& source) : str(nullptr) {
        if (source.str != nullptr) {
            str = new char[std::strlen(source.str) + 1];
            std::strcpy(str, source.str);
        }
    }

    MyString(MyString&& source) : str(source.str) {
        source.str = nullptr;
    }

    ~MyString() {
        delete[] str;
    }

    MyString& operator=(const MyString& rhs) {
        if (this == &rhs) {
            return *this;
        }
        delete[] str;
        str = nullptr;
        if (rhs.str != nullptr) {
            str = new char[std::strlen(rhs.str) + 1];
            std::strcpy(str, rhs.str);
        }
        return *this;
    }

    void pop_back() {
        if (str == nullptr) {
            return;
        }
        int length = std::strlen(str);
        if (length > 0) {
            char* buff = new char[length];
            for (int i = 0; i < length - 1; i++) {
                buff[i] = str[i];
            }
            buff[length - 1] = '\0';
            *this = MyString{ buff };
            delete[] buff;
        }
    }

    void push_back(char a) {
        int length = (str != nullptr) ? std::strlen(str) : 0;
        char* buff = new char[length + 2];
        if (str != nullptr) {
            std::strcpy(buff, str);
        }
        buff[length] = a;
        buff[length + 1] = '\0';
        *this = MyString{ buff };
        delete[] buff;
    }

    int get_length() const {
        return (str != nullptr) ? std::strlen(str) : 0;
    }

    // void copy(char s[], int len, int pos) const {
    //     if (str == nullptr) {
    //         s[0] = '\0';
    //         return;
    //     }
    //     int length = std::strlen(str);
    //     if (pos < 0 || pos >= length) {
    //         s[0] = '\0';
    //         return;
    //     }
    //     int copyLength = std::min(len, length - pos);
    //     std::strncpy(s, str + pos, copyLength);
    //     s[copyLength] = '\0';
    // }

    // void swap(MyString& rhs) {
    //     std::swap(str, rhs.str);
    // }

    friend std::ostream& operator<<(std::ostream& os, const MyString& obj);
    friend std::istream& operator>>(std::istream& is, MyString& obj);
    friend MyString operator+(const MyString& lhs, const MyString& rhs);
};

std::ostream& operator<<(std::ostream& os, const MyString& obj) {
    if (obj.str != nullptr) {
        os << obj.str;
    }
    return os;
}

std::istream& operator>>(std::istream& is, MyString& obj) {
    char buff[1000];
    is >> buff;
    obj = MyString(buff);
    return is;
}

MyString operator+(const MyString& lhs, const MyString& rhs) {
    int length = (lhs.str != nullptr ? std::strlen(lhs.str) : 0) + (rhs.str != nullptr ? std::strlen(rhs.str) : 0);
    char* buff = new char[length + 1];
    if (lhs.str != nullptr) {
        std::strcpy(buff, lhs.str);
    }
    if (rhs.str != nullptr) {
        std::strcat(buff, rhs.str);
    }
    MyString temp{ buff };
    delete[] buff;
    return temp;
}

int main() {
    MyString a;
    const char* temp = "Hello";
    MyString b{ temp };
    MyString c{ a };
    const char* temp1 = "World";
    MyString d{ MyString{ temp1 } };
    b.pop_back();
    b.push_back('o');
    std::cout << "Length of b: " << b.get_length() << std::endl;
    char arr[80];
    b.copy(arr, 3, 0);
    std::cout << "arr is: " << arr << std::endl;
    d.swap(b);
    std::cout << "d: " << d << " b: " << b << std::endl;
    d = b + d;
    std::cout << "string d: " << d << std::endl;
    return 0;
}
