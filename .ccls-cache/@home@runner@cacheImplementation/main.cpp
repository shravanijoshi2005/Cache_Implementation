#include <unordered_map>
#include<iostream>
using namespace std;

// Node class for doubly linked list
class Node
{
    public:
    int key;
    int value;
    Node*next;
    Node*prev;

    Node(int key, int value)
    {
        this->key = key;
        this->value = value;
        next = nullptr;
        prev = nullptr;
    }
};

// CREATING HASH TABLE OF LRU CACHE 
class LRUCache {
private:
   unordered_map<int, Node*>cache;
    Node*head;
    Node*tail;
    int capacity;
    int size;

    // Add node just after the head (most recently used position)
    void addNode(Node* newNode) {
        newNode->next = head->next;
        newNode->prev = head;
        head->next->prev = newNode;
        head->next = newNode;
    }

    // Remove an existing node from the list
    void removeNode(Node* node) {
        Node* prevNode = node->prev;
        Node* nextNode = node->next;
        prevNode->next = nextNode;
        nextNode->prev = prevNode;
    }

    // Move the accessed node to the head (most recently used)
    void moveToHead(Node* node) {
        removeNode(node);
        addNode(node);
    }

    // Remove the least recently used node (node just before the tail)
    Node* popTail() {
        Node* lruNode = tail->prev;
        removeNode(lruNode);
        return lruNode;
    }

public:
    // Constructor to initialize LRU Cache with given capacity
    LRUCache(int capacity) {
        this->capacity = capacity;
        size = 0;

        // Initialize dummy head and tail
        head = new Node(0, 0);
        tail = new Node(0, 0);
        head->next = tail;
        tail->prev = head;
    }

    // Get value by key, return -1 if not found
    int get(int key) {
        if (cache.find(key) != cache.end()) {
            Node* node = cache[key];
            moveToHead(node);  // Move the accessed node to the head (MRU)
            return node->value;
        }
        return -1;  // If not found, return -1
    }

    // Put key-value pair into the cache
    void put(int key, int value) {
        if (cache.find(key) != cache.end()) {
            // Update the value of the existing node and move it to the head
            Node* node = cache[key];
            node->value = value;
            moveToHead(node);
        } else {
            // Create a new node
            Node* newNode = new Node(key, value);
            cache[key] = newNode;
            addNode(newNode);
            size++;

            // If cache exceeds capacity, remove the least recently used node
            if (size > capacity) {
                Node* lruNode = popTail();
                cache.erase(lruNode->key);  // Remove from hash map
                delete lruNode;  // Free memory
                size--;
            }
        }
    }

    ~LRUCache() {
        // Free up all dynamically allocated memory (for good practice)
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

// Example usage:
int main() {
    int cap,key,value,ch;
    cout<<"Enter cache capacity\n";
    cin>>cap;
    LRUCache lru(cap);  // Cache capacity is 2

   do { 
       cout<<"CACHE OPERATIONS: \n 1.Put Key-value pair into the cache\n 2.Get value by key\n3. Exit\n";
       cin>>ch;
       switch(ch)
           {
               case 1:
               cout<<"Enter Key, value pairs";
               cin>>key>>value;
               lru.put(key,value);
               cout<<"Key-val pairs inserted successfully\n";

               case 2:
               cout<<"Enter key whos value is to be found:\n";
               cin>>key;
               printf("%d\n", lru.get(key));
               case 3:
               cout<<"Thanks for your co-operation!\n";  
           }
   } while (ch !=3);
    

    return 0;
}
