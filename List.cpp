#include <iostream>

class List {
private:
    struct node {
        int data;
        node *next;
    };

    node *head;
    int length;
public:
    List() {
        head = nullptr;
        length = 0;
    }

    void push_front(int data) {
        node* q = new node;
        node* current = head;
        head = q;
        q->next = current;
        q->data = data;
        length++;
    }

    void print() {
        node* current = head;
        while (current != nullptr) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << "\n";
    }
};