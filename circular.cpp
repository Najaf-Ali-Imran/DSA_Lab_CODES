#include <iostream>
using namespace std;

class Node {
private:
    int value;
    Node* next_node;

public:
    Node(int val = 0, Node* next = nullptr)
        : value(val), next_node(next) {}

    int retrieve() const { return value; }
    Node* next() const { return next_node; }
    void set_next(Node* next) { next_node = next; }

    friend class CList;
};

class CList {
private:
    Node* list_tail;

public:
    CList() : list_tail(nullptr) {}

    ~CList() {
        while (!empty())
            pop_front();
    }

    bool empty() const {
        return (list_tail == nullptr);
    }

    Node* head() const {
        if (empty()) return nullptr;
        return list_tail->next();
    }

    Node* tail() const {
        return list_tail;
    }

    int front() const {
        if (empty()) {
            cerr << "List is empty! Cannot access front element.\n";
            return -1;
        }
        return head()->retrieve();
    }

    int end() const {
        if (empty()) {
            cerr << "List is empty! Cannot access end element.\n";
            return -1;
        }
        return tail()->retrieve();
    }

    void push_front(int n) {
        if (empty()) {
            Node* new_node = new Node(n);
            new_node->set_next(new_node);
            list_tail = new_node;
        } else {
            Node* old_head = list_tail->next();
            Node* new_node = new Node(n, old_head);
            list_tail->set_next(new_node);
        }
    }

    void push_end(int n) {
        if (empty()) {
            push_front(n);
        } else {
            Node* old_head = list_tail->next();
            Node* new_node = new Node(n, old_head);
            list_tail->set_next(new_node);
            list_tail = new_node;
        }
    }

    void push_between(int index, int n) {
        if (empty()) {
            cerr << "Cannot insert in empty list! Use push_front first.\n";
            return;
        }

        int size_val = size();
        if (index < 0 || index >= size_val) {
            cerr << "Invalid index! Must be between 0 and " << (size_val - 1) << ".\n";
            return;
        }

        if (index == 0) {
            push_front(n);
            return;
        }

        Node* ptr = head();
        for (int i = 0; i < index - 1; ++i) {
            ptr = ptr->next();
        }
        Node* new_node = new Node(n, ptr->next());
        ptr->set_next(new_node);
    }

    int pop_front() {
        if (empty()) {
            cerr << "List is empty! Cannot pop front.\n";
            return -1;
        }

        Node* old_head = list_tail->next();
        int value = old_head->retrieve();

        if (old_head == list_tail) {
            delete old_head;
            list_tail = nullptr;
        } else {
            list_tail->set_next(old_head->next());
            delete old_head;
        }
        return value;
    }

    int pop_end() {
        if (empty()) {
            cerr << "List is empty! Cannot pop end.\n";
            return -1;
        }

        Node* old_tail = list_tail;
        int value = old_tail->retrieve();

        if (list_tail->next() == list_tail) {
            delete old_tail;
            list_tail = nullptr;
        } else {
            Node* ptr = list_tail->next();
            while (ptr->next() != list_tail) {
                ptr = ptr->next();
            }
            ptr->set_next(list_tail->next());
            list_tail = ptr;
            delete old_tail;
        }
        return value;
    }

    int erase(int index) {
        if (empty()) {
            cerr << "List is empty! Cannot erase.\n";
            return -1;
        }

        int size_val = size();
        if (index < 0 || index >= size_val) {
            cerr << "Invalid index! Must be between 0 and " << (size_val - 1) << ".\n";
            return -1;
        }

        if (index == 0) {
            return pop_front();
        }

        if (index == size_val - 1) {
            return pop_end();
        }

        Node* ptr = head();
        for (int i = 0; i < index - 1; ++i) {
            ptr = ptr->next();
        }

        Node* to_delete = ptr->next();
        int value = to_delete->retrieve();

        ptr->set_next(to_delete->next());
        delete to_delete;

        return value;
    }

    void display() const {
        if (empty()) {
            cout << "List is empty.\n";
            return;
        }

        Node* ptr = head();
        cout << "Head -> ";
        do {
            cout << ptr->retrieve() << " -> ";
            ptr = ptr->next();
        } while (ptr != head());

        cout << "(Back to Head)\n";
        cout << "(Tail is: " << list_tail->retrieve() << ")\n";
    }

    int size() const {
        if (empty()) return 0;

        int count = 0;
        Node* ptr = head();
        do {
            ++count;
            ptr = ptr->next();
        } while (ptr != head());
        
        return count;
    }
};

int main() {
    CList lst;

    lst.push_front(10);
    lst.push_front(20);
    lst.push_front(30);
    lst.display();

    lst.push_end(40);
    lst.push_end(50);
    lst.display();



    return 0;
}
