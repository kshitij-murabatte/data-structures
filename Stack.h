/*

    * Author - Kshitij Murabatte

*/

#include <iostream>

namespace list
{
    template <typename T>
    class LinkedList
    {
    public:
        T data;
        LinkedList *next;

        LinkedList(T input)
        {
            data = input;
            next = nullptr;
        }
        ~LinkedList()
        {
            delete next;
        }
        void Push(LinkedList<T> *&head, const T &value)
        {
            LinkedList<T> *temp = nullptr;

            try
            {
                temp = new LinkedList<T>(value);
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
                std::exit(2);
            }

            if (head == nullptr)
            {
                head = temp;
            }

            temp->next = head;
            head = temp;
        }
        void Pop(LinkedList<T> *&head)
        {
            LinkedList<T> *temp = head;

            head = head->next;
            temp->next = nullptr;

            delete temp;
        }
        T Top()
        {
            if (this == nullptr)
            {
                std::cout << "Stack is empty!\n";
                std::exit(2);
            }
            return this->data;
        }
    };
}

template <typename T>
class Stack
{
private:
    // private head of linked list
    list::LinkedList<T> *stk;
    int _size;

public:
    Stack()
    {
        _size = 0;
        stk = nullptr;
    }
    ~Stack()
    {
        delete stk;
    }

    // Push an element into the stack
    void push(const T input)
    {
        stk->Push(stk, input);
        ++_size;
    }

    // Pop an element from the stack
    void pop()
    {
        if (stk == nullptr)
        {
            std::cout << "Stack is empty!\n";
            std::exit(2);
        }
        stk->Pop(stk);
        --_size;
    }

    // Returns element at top of the stack if present
    T top()
    {
        return stk->Top();
    }

    // Returns true if the stack is empty, false otherwise
    bool isEmpty()
    {
        return _size == 0;
    }

    // Returns size of the stack
    int size()
    {
        return _size;
    }
};