#include <iostream>
using namespace std;

class DNode {
private:
    int value;
    DNode* next_node;
    DNode* prev_node;

public:
    DNode(int val = 0, DNode* next = nullptr, DNode* prev = nullptr)
        : value(val), next_node(next), prev_node(prev) {}

    int retrieve() const { return value; }
    DNode* next() const { return next_node; }
    DNode* prev() const { return prev_node; }
    void set_next(DNode* next) { next_node = next; }
    void set_prev(DNode* prev) { prev_node = prev; }

    friend class DList;
};

class DList {
private:
    DNode* list_head;
    DNode* list_tail;

public:
    DList() : list_head(nullptr), list_tail(nullptr) {}

    ~DList() {
        while (!empty())
            pop_front();
    }

    bool empty() const {
        return (list_head == nullptr);
    }

    int size() const {
        int count = 0;
        for (DNode* ptr = list_head; ptr != nullptr; ptr = ptr->next())
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
        return list_tail->retrieve();
    }

    DNode* head() const {
        return list_head;
    }

    DNode* tail() const {
        return list_tail;
    }

    int count(int n) const {
        int node_count = 0;
        for (DNode* ptr = head(); ptr != nullptr; ptr = ptr->next()) {
            if (ptr->retrieve() == n)
                ++node_count;
        }
        return node_count;
    }

    void push_front(int n) {
        DNode* new_node = new DNode(n, list_head, nullptr);

        if (empty()) {
            list_head = list_tail = new_node;
        } else {
            list_head->set_prev(new_node);
            list_head = new_node;
        }
    }

    void push_end(int n) {
        DNode* new_node = new DNode(n, nullptr, list_tail);

        if (empty()) {
            list_head = list_tail = new_node;
        } else {
            list_tail->set_next(new_node);
            list_tail = new_node;
        }
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

        DNode* ptr = list_head;
        for (int i = 0; i < index - 1; ++i) {
            ptr = ptr->next();
        }
        DNode* new_node = new DNode(n, ptr->next(), ptr);
        ptr->next()->set_prev(new_node);
        ptr->set_next(new_node);
    }

    int pop_front() {
        if (empty()) {
            cerr << "List is empty! Cannot pop front.\n";
            return -1;
        }

        int value = list_head->retrieve();
        DNode* temp = list_head;

        if (list_head == list_tail) {
            list_head = list_tail = nullptr;
        } else {
            list_head = list_head->next();
            list_head->set_prev(nullptr);
        }

        delete temp;
        return value;
    }

    int pop_end() {
        if (empty()) {
            cerr << "List is empty! Cannot pop end.\n";
            return -1;
        }

        int value = list_tail->retrieve();
        DNode* temp = list_tail;

        if (list_head == list_tail) {
            list_head = list_tail = nullptr;
        } else {
            list_tail = list_tail->prev();
            list_tail->set_next(nullptr);
        }

        delete temp;
        return value;
    }

    int erase(int n) {
        int count_removed = 0;
        DNode* ptr = list_head;

        while (ptr != nullptr) {
            DNode* next_node = ptr->next();

            if (ptr->retrieve() == n) {
                if (ptr == list_head) {
                    pop_front();
                }
                else if (ptr == list_tail) {
                    pop_end();
                }
                else {
                    ptr->prev()->set_next(ptr->next());
                    ptr->next()->set_prev(ptr->prev());
                    delete ptr;
                }
                ++count_removed;
            }
            ptr = next_node;
        }
        return count_removed;
    }

    void display() const {
        if (empty()) {
            cout << "List is empty.\n";
            return;
        }

        cout << "nullptr <- ";
        for (DNode* ptr = list_head; ptr != nullptr; ptr = ptr->next()) {
            cout << ptr->retrieve();
            if (ptr->next() != nullptr)
                cout << " <-> ";
        }
        cout << " -> nullptr\n";
    }

    void display_reverse() const {
        if (empty()) {
            cout << "List is empty.\n";
            return;
        }

        cout << "nullptr <- ";
        for (DNode* ptr = list_tail; ptr != nullptr; ptr = ptr->prev()) {
            cout << ptr->retrieve();
            if (ptr->prev() != nullptr)
                cout << " <-> ";
        }
        cout << " -> nullptr\n";
    }
};

int main() {
    DList lst;

    lst.push_front(10);
    lst.push_front(20);
    lst.push_front(30);
    lst.display();

    lst.push_end(40);
    lst.push_end(50);
    lst.display();



    return 0;
}
