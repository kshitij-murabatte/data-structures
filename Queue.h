/*

    * Author - Kshitij Murabatte

*/

#include <iostream>

// a namespace to keep internal structure hidden
namespace secret
{
    // class that stores queue elements in a segmented form
    // to provide similar performance with better space efficency
    class Box
    {
        /*
        * front -> index of front of the current queue
        * back -> index of back of queue
        * _size -> fixed size of individual queue
        * filled -> number of filled elements
        * *arr -> the queue
        */

    public:
        int front, back;
        int const _size = 16;
        int filled;
        int *arr;

        // constructor allocates memory to queue
        Box()
        {
            arr = new int[_size];
            front = back = 0;
            filled = 0;
        }
        // deleting dynamically allocated queue
        ~Box()
        {
            delete[] arr;
        }

        // returning front element of queue
        int Front()
        {
            return arr[front];
        }

        // pushing element at back of queue and increasing number of filled
        void Push(int a)
        {
            ++filled;
            arr[back++];
        }

        // popping from front of queue and reducing number of filled
        void Pop()
        {
            --filled;
            ++front;
        }

        // function to return current size of queue
        int Size()
        {
            return filled;
        }
    };

    /*
    * Blueprint of a linked list node
    * Refer the architecture for better understanding
    */
    class List
    {
    public:
        Box *_queue;
        List *left, *right;

        List()
        {
            _queue = new Box();
            left = right = nullptr;
        }
        ~List()
        {
            // recursively deleting list and queue that it contains
            delete _queue;
            delete right;
        }
    };
}

// main class with which a programmer will intract
class Queue
{
    // private variables to maintian the linked list
private:
    int size;
    secret::List *head, *tail;

public:
    // when a object is created the is no memory allocated dynamically
    Queue()
    {
        size = 0;
        head = tail = 0;
    }
    ~Queue()
    {
        delete head;
    }

    // pusing into the queue
    void push(int a)
    {
        if (!head)
        {
            // if the size of queue is 0 trying to make a new node
            // otherwise informing the programmer of failed operation
            try
            {
                head = tail = new secret::List();
            }
            catch (const std::exception &e)
            {
                std::cerr << e.what() << '\n';
            }
        }

        // increasing the size of queue
        ++size;

        // inserting new element in current node only if it is not
        // completely filled
        if (tail->_queue->filled < tail->_queue->_size)
        {
            tail->_queue->Push(a);
            return;
        }

        // if the tail node is filled
        // try to allocate memory for a new node
        secret::List *temp;

        try
        {
            temp = new secret::List();
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }

        // setting the new node as tail
        tail->right = temp;
        temp->left = tail;
        tail = temp;

        // pushing new element to end of queue
        tail->_queue->Push(a);
    }

    // popping from the queue
    void pop()
    {
        // condition to handle when there are no elements in queue
        try
        {
            if (!head)
                throw -1;
        }
        catch (const int error)
        {
            std::cerr << "\nQueue is empty!";
        }

        // if the current node is the only node in the list
        if (head->right == nullptr)
        {
            // if the node has only 1 remaining element
            // delete this node to free memory
            if (head->_queue->filled == 1)
            {
                --size;
                delete head;
                return;
            }

            // otherwise calling Box->Pop() method on current node queue
            head->_queue->Pop();
            
            // reducing the size of queue
            --size;

            return;
        }

        // when list has more than 1 nodes
        // and current list only has 1 element left
        if (head->_queue->filled == 1)
        {
            // taking a temporary pointer
            secret::List *temp = head->right;

            // detaching the head node (because recursive nature of destructor)
            head->right = nullptr;
            temp->left = nullptr;

            // free the memory
            delete head;

            // reducing size of queue
            head = temp;
            --size;
            return;
        }

        // popping if none of above conditions satisfy
        head->_queue->Pop();
        --size;
    }

    // function to return front of queue
    int front()
    {
        // exception when trying to get front from a empty queue
        try
        {
            if (!head)
                throw -1;
        }
        catch (const int error)
        {
            std::cerr << "\nQueue is empty!";
            return -1;
        }

        // returning from of queue
        return head->_queue->Front();
    }

    // tells whether queue is empty or not
    bool isEmpty()
    {
        return size == 0;
    }
};


/*
#include <iostream>

namespace secret
{
    class Box
    {
    public:
        int front, back;
        int const _size = 4;
        int filled;
        int *arr;

        Box()
        {
            arr = new int[_size];
            front = back = 0;
            filled = 0;
        }
        ~Box()
        {
            delete[] arr;
        }

        int Front()
        {
            return arr[front];
        }
        void Push(int a)
        {
            ++filled;
            arr[back++] = a;
        }
        void Pop()
        {
            --filled;
            ++front;
        }
    };

    class List
    {
    public:
        Box *_queue;
        List *left, *right;

        List()
        {
            _queue = new Box();
            left = right = nullptr;
        }
        ~List()
        {
            delete _queue;
            delete right;
        }
    };
}

class Queue
{
private:
    int size;
    secret::List *head, *tail;

public:
    Queue()
    {
        size = 0;
        head = tail = 0;
    }
    ~Queue()
    {
        delete head;
    }
    void push(int a)
    {
        if (!head)
        {
            head = tail = new secret::List();
        }

        ++size;

        if (tail->_queue->filled < tail->_queue->_size)
        {
            tail->_queue->Push(a);
            return;
        }

        secret::List *temp;

        try
        {
            temp = new secret::List();
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }

        tail->right = temp;
        temp->left = tail;
        tail = temp;

        tail->_queue->Push(a);
    }
    void pop()
    {
        try
        {
            if (!head)
                throw -1;
        }
        catch (const int error)
        {
            std::cerr << "\nQueue is empty!";
        }

        if (head->right == nullptr)
        {
            if (head->_queue->filled == 1)
            {
                --size;
                delete head;
                return;
            }
            head->_queue->Pop();
            --size;
            return;
        }

        if (head->_queue->filled == 1)
        {
            secret::List *temp = head->right;
            head->right = nullptr;
            delete head;

            head = temp;
            --size;
            return;
        }

        head->_queue->Pop();
        --size;
    }
    int front()
    {
        try
        {
            if (!head)
                throw -1;
        }
        catch (const int error)
        {
            std::cerr << "\nQueue is empty!";
            return -1;
        }
        return head->_queue->Front();
    }
};
*/