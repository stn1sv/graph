#include <iostream>

class PQueue {
private:
//экземпляр элемента очереди с приоритетом
    struct node {
        int data; //значение элемента
        node* next; //указатель на следующий элемент
    };

    node* head;
    node* tail;
    int length;
public:
    // Конструктор класса
    PQueue() {
        head = nullptr;
        tail = nullptr;
        length = 0;
    }
//добавление элемента(неприоритетное)
    void insert(int data) {
        node* q = new node;
        if (length == 0){
            head = q;
        } else{
            tail->next = q;
        }
        q->data = data;
        q->next = nullptr;
        tail = q;
        length++;
    }

//удаление элемента(приоритетное)
    int Delete(int shortest[]) {
        //пустая очередь
        if (!head) {
            std::cerr << "queue is empty\n";
            exit(1);
        }

        //поиск элемента, с минимальным значением shortest
        int min_shortest = shortest[head->data];
        int min_key = head->data;
        node* curr = head->next;
        node* prev = head;

        while (curr) {
            if (shortest[curr->data] < min_shortest) {
                min_shortest = shortest[curr->data];
                min_key = curr->data;
            }

            curr = curr->next;
        }

        if (head->data == min_key) {
            curr = head->next;
            delete head;
            head = curr;
        } else {
            prev = head;
            curr = head->next;
            while (curr) {
                if (curr->data == min_key) {
                    prev->next = curr->next;
                    delete curr;
                    break;
                }

                prev = curr;
                curr = curr->next;
            }
        }

        length--;
        return min_key;
    }

//Проверка на пустоту
    bool empty(){
        return !head;
    }
};
