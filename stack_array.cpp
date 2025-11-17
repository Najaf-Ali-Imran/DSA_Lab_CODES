#include <iostream>
using namespace std;

class StackArray {
private:
    static const int MAX_SIZE = 100;
    int arr[MAX_SIZE];
    int stack_top;

public:
    StackArray() : stack_top(-1) {}

    bool empty() const {
        return (stack_top == -1);
    }

    bool full() const {
        return (stack_top == MAX_SIZE - 1);
    }

    int size() const {
        return stack_top + 1;
    }

    int peek() const {
        if (empty()) {
            cerr << "Stack is empty! Cannot peek.\n";
            return -1;
        }
        return arr[stack_top];
    }

    void push(int n) {
        if (full()) {
            cerr << "Stack is full! Cannot push " << n << ".\n";
            return;
        }
        arr[++stack_top] = n;
        cout << "Pushed " << n << " onto the stack.\n";
    }

    int pop() {
        if (empty()) {
            cerr << "Stack is empty! Cannot pop.\n";
            return -1;
        }
        return arr[stack_top--];
    }

    void display() const {
        if (empty()) {
            cout << "Stack is empty.\n";
            return;
        }

        cout << "Stack (top to bottom):\n";
        cout << "TOP\n";
        cout << " |\n";
        for (int i = stack_top; i >= 0; --i) {
            cout << " " << arr[i] << "\n";
            if (i > 0)
                cout << " |\n";
        }
        cout << "BOTTOM\n";
    }

    void clear() {
        stack_top = -1;
        cout << "Stack cleared.\n";
    }

    int capacity() const {
        return MAX_SIZE;
    }
};

int main() {
    StackArray stk;

    stk.push(50);
    cout << "\n";

    stk.display();
    stk.clear();


    return 0;
}
