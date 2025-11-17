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

    friend class List;
};

class List {
private:
    Node* list_head;

public:
    List() : list_head(nullptr) {}

    ~List() {
        while (!empty())
            pop_front();
    }

    bool empty() const {
        return (list_head == nullptr);
    }

    int size() const {
        int count = 0;
        for (Node* ptr = list_head; ptr != nullptr; ptr = ptr->next())
            ++count;
        return count;
    }

    int front() const {
        if (empty()) {
            cerr << "List is empty! Cannot access front element.\n";
            return -1;
        }
        return list_head->retrieve();
    }

    int end() const {
        if (empty()) {
            cerr << "List is empty! Cannot access end element.\n";
            return -1;
        }

        Node* ptr = list_head;
        while (ptr->next() != nullptr)
            ptr = ptr->next();
        return ptr->retrieve();
    }

    Node* head() const {
        return list_head;
    }

    int count(int n) const {
        int node_count = 0;
        for (Node* ptr = head(); ptr != nullptr; ptr = ptr->next()) {
            if (ptr->retrieve() == n)
                ++node_count;
        }
        return node_count;
    }

    void push_front(int n) {
        Node* new_node = new Node(n, list_head);
        list_head = new_node;
    }

    void push_end(int n) {
        Node* new_node = new Node(n, nullptr);

        if (empty()) {
            list_head = new_node;
            return;
        }

        Node* ptr = list_head;
        while (ptr->next() != nullptr)
            ptr = ptr->next();
        ptr->set_next(new_node);
    }

    void push_between(int index, int n) {
        int size_val = size();

        if (index < 0 || index > size_val) {
            cerr << "Invalid index! Must be between 0 and " << size_val << ".\n";
            return;
        }

        if (index == 0) {
            push_front(n);
            return;
        }

        if (index == size_val) {
            push_end(n);
            return;
        }

        Node* ptr = list_head;
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

        int value = list_head->retrieve();
        Node* temp = list_head;
        list_head = list_head->next();
        delete temp;
        return value;
    }

    int pop_end() {
        if (empty()) {
            cerr << "List is empty! Cannot pop end.\n";
            return -1;
        }

        if (list_head->next() == nullptr) {
            int value = list_head->retrieve();
            delete list_head;
            list_head = nullptr;
            return value;
        }

        Node* ptr = list_head;
        while (ptr->next()->next() != nullptr)
            ptr = ptr->next();

        int value = ptr->next()->retrieve();
        delete ptr->next();
        ptr->set_next(nullptr);
        return value;
    }

    int erase(int n) {
        int count_removed = 0;

        while (list_head != nullptr && list_head->retrieve() == n) {
            Node* temp = list_head;
            list_head = list_head->next();
            delete temp;
            ++count_removed;
        }

        Node* ptr = list_head;
        while (ptr != nullptr && ptr->next() != nullptr) {
            if (ptr->next()->retrieve() == n) {
                Node* temp = ptr->next();
                ptr->next_node = ptr->next()->next();
                delete temp;
                ++count_removed;
            } else {
                ptr = ptr->next();
            }
        }

        return count_removed;
    }

    void display() const {
        if (empty()) {
            cout << "List is empty.\n";
            return;
        }

        for (Node* ptr = list_head; ptr != nullptr; ptr = ptr->next())
            cout << ptr->retrieve() << " -> ";
        cout << "nullptr\n";
    }
};

int main() {
    List lst;

    lst.push_front(10);
    lst.push_front(20);
    lst.push_front(30);
    lst.display();

    lst.push_end(40);
    lst.push_end(50);
    lst.display();



    lst.erase(20);
    lst.display();

    lst.display();

    lst.display();



    return 0;
}
