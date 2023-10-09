LRU Cache

#include <iostream>
#include<unordered_map>

using namespace std;
class Node {
    public:
    Node *prev;
    Node *next;
    
    string_view key;
    string_view value;
    
    Node( string_view key,  string_view value) {
        this -> key = key;
        this -> value = value;
    }
};

class LRU {
    public:
    int cap;
    Node *head, *tail;
    unordered_map<string_view, Node*> map;
    
    LRU(int cap) {
        this -> cap= cap;
        head = new Node("-1", "-1");
        tail = new Node("-1", "-1");
        head -> next = tail;
        tail -> prev = head;
    }
    
    void make_latest(string_view key) {
        if(map.find(key) != map.end()) {
            Node *curr = map[key];
            curr -> prev -> next = curr -> next;
            curr -> next -> prev = curr -> prev;
             Node *last = tail -> prev;
             last -> next = curr;
             curr -> prev  = last;
             tail -> prev = curr;
             curr -> next = tail;
        }
        
    }
    
    string_view get_value(string_view key){
        if(map.find(key) == map.end()) {
            return "Key does not exist";
        } else {
            Node *curr = map[key];
            make_latest(key);
            return curr -> value;
        }
    }
    
    void print_latest_value() {
        cout << tail -> prev -> value << endl;
    }
    
    void set_val(string_view key, string_view value) {
        if(map.find(key) != map.end()) {
            Node *curr = map[key];
            curr -> value = value;
            make_latest(key);
        }
        else if(cap > map.size()) {
            Node *nnode = new Node(key, value);
            Node *last = tail -> prev;
            last -> next = nnode;
            nnode -> prev = last;
            nnode -> next = tail;
            tail -> prev  = nnode;
            map[key] = nnode;
            // make_latest(key);
        }else {
            Node *rem = head -> next;
            map.erase(rem -> key);
            rem -> key = key;
            rem -> value = value;
            map[key] = rem;
            make_latest(rem -> key);
            
        }
    }
    
};

int main()
{

    auto r  = LRU(3);
    r.set_val("1", "1");
    r.set_val("2", "2");
    r.set_val("3", "3");
    r.set_val("2","5");
    
    cout << r.get_value("2") << endl; // 2
    r.print_latest_value(); // 2
    r.set_val("4", "4");
    r.print_latest_value(); // 4
    
    cout << r.head -> next -> value; // 3

    return 0;
}
