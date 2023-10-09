/**************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

***************************/

#include <iostream>

using namespace std;
template<typename T>
class Node {
    public:
    Node<T> *arr[26];
    int prefix_count;
    T value;
    
    
    Node() {}
    Node(const T &value) {
        this -> value = std::move(value);
    }
};

template<typename T>
class Trie {
    private:
    Node<T> *root = new Node<T>();
    public:
    Trie() : root(new Node<T>()) {}
     
    Trie(const Trie& trie_node) : root(new Node<T>()) {
        root = create(trie_node.root);
    }
    
    Trie& operator=(const Trie& rhs) {
        if (&rhs != this) {
           root = create(rhs.root);
        }
        return *this;
    }


    Node<T>* create(Node<T>* srcNode) {
        if (!srcNode) {
            return nullptr;
        }
    
        Node<T>* destNode = new Node<T>(srcNode->value);
        destNode->prefix_count = srcNode->prefix_count;
    
        for (int i = 0; i < 26; i++) {
            destNode-> arr[i] =  create(srcNode-> arr[i]);
        }
    
        return destNode;
    }

    void insert(std::string_view str, const T &value) {
        Node<T> *temp = root;
        for(auto it = str.begin(); it != str.end(); it++) {
            int idx = (int)*it - (int)'a';
            if(temp -> arr[idx] == nullptr) {
                temp -> arr[idx] = new Node(value);
            }
            temp -> prefix_count++;
            temp = temp -> arr[idx];
        }
        temp -> value = std::move(value);
    }
    
    const T &read(std::string_view key) const {
        Node<T> *curr = search_h(key);
        if(curr == nullptr|| curr -> value == T()){
              throw runtime_error("error");
        }
        return curr-> value;
    }
    
    void remove1(string_view key){
        Node<T>* curr = root;
        for(auto it = key.begin() ; it != key.end(); it++) {
            if(curr-> prefix_count ==0) return;
            curr -> prefix_count--;
            int idx = (int)*it - (int)'a';
            if(curr -> arr[idx]==nullptr) return;
            curr = curr -> arr[idx];
        }
        curr-> value = T();
    }
    
    
    bool contains(string_view key) const noexcept{
        Node<T> *curr = search_h(key);
        if(curr == nullptr|| curr -> value == T()){
            return false;
        }
        return true;
    }
    
    int prefixCount(string_view key){
        Node<T>* node = search_h(key);
        if(node==nullptr) return 0;
        else return node -> prefix_count;
    }
    
    Node<T>* search_h(string_view key) const {
    	Node<T> *current = root;
    	for(auto it = key.begin() ; it != key.end(); it++) {
    		int idx = (int)*it - (int)'a';
    		if(current -> arr[idx] == nullptr)
    			return nullptr;	
    		current = current -> arr[idx];
    	}
    	return current;
    }
    
    template <typename... ArgTs>
    auto emplace(string_view key, ArgTs&&... args){
        Node<T> *current = root;
    	current->prefix_count++;
    	
    	for(int i = 0 ; i < key.length(); ++i)
    	{
    		int letter = (int)key[i] - (int)'a';	//extract first character of word
    		if(current->arr[letter] == nullptr)
    			current->arr[letter] = new Node<T>();
    
    		current->arr[letter]->prefix_count++;
    		current = current->arr[letter];		
    	}
    	current->value = T(forward<ArgTs>(args)...);
    	return current->value;
    }
    
};
int main() {
    cout << "Trie datastructure" << endl;
    Trie<string> trie;
    
    trie.insert("abc", "abc");
    trie.insert("abcdef", "abcdef");
    trie.insert("abhgf", "abhgf");
    
    cout << trie.prefixCount("ab") << endl; // 3
    cout << trie.read("abc") << endl; // abc
    // cout << trie.read("abc,c") << endl; // key does not exist
     
    // trie.remove1("abc");
    // cout << trie.read("abc") << endl;
    
    Trie<string> r2 = trie;
    
    cout << r2.read("abcdef") << endl;
    r2.emplace("key", "value", "val2");
    
    cout << r2.read("key");
     

    return 0;
}
