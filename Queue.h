/*

    * Author - Kshitij Murabatte

*/

#include <iostream>

// a namespace to keep internal structure hidden

namespace secret
{
    // class that stores queue elements in a segmented form
    // to provide similar performance with better space efficency
    template <typename T>
    class Box
    {
        /*
        * front -> index of front of the current queue
        * back -> index of back of queue
        * _size -> fixed size of individual queue
        * *arr -> the queue
        */

    public:
        int front, back;
        int const _size = 64;
        T *arr;

        // constructor allocates memory to queue
        Box()
        {
            arr = new T[_size];
            front = back = 0;
        }
        // deleting dynamically allocated queue
        ~Box()
        {
            delete[] arr;
        }

        // returning front element of queue
        T Front()
        {
            return arr[front];
        }

        // pushing element at back of queue and increasing number of filled
        void Push(const T &a)
        {
            arr[back++] = a;
        }

        // popping from front of queue and reducing number of filled
        void Pop()
        {
            ++front;
        }

        // function to return current size of queue
    };

    /*
    * Blueprint of a linked list node
    * Refer the architecture for better understanding
    */
    template <typename T>
    class List
    {
    public:
        Box<T> *_queue;
        List<T> *left, *right;

        List()
        {
            _queue = new Box<T>();
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

// Standard FIFO data structure
template <typename T>
class Queue
{
    // private variables to maintian the linked list
private:
    int _size;
    secret::List<T> *head, *tail;

public:
    // when a object is created there is no memory allocated dynamically
    Queue()
    {
        _size = 0;
        head = tail = 0;
    }
    ~Queue()
    {
        delete head;
    }

    // pushing into the queue
    void push(const T a)
    {
        if (!head)
        {
            // if the size of queue is 0, trying to make a new node
            // otherwise informing the programmer of failed operation
            try
            {
                head = tail = new secret::List<T>();
            }
            catch (const std::exception &e)
            {
                std::cerr << e.what() << '\n';
                std::exit(2);
            }
        }

        // increasing the size of queue
        ++_size;

        // inserting new element in current node only if it is not
        // completely filled
        if (tail->_queue->back != tail->_queue->_size)
        {
            tail->_queue->Push(a);
            return;
        }

        // if the tail node is filled
        // try to allocate memory for a new node
        secret::List<T> *temp;

        try
        {
            temp = new secret::List<T>();
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
            std::exit(2);
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
            std::exit(2);
        }

        // if the current node is the only node in the list
        if (head->right == nullptr)
        {
            // if the node has only 1 remaining element
            // delete this node to free memory
            if (head->_queue->front == head->_queue->_size - 1)
            {
                --_size;
                delete head;
                return;
            }

            // otherwise calling Box->Pop() method on current node queue
            head->_queue->Pop();

            // reducing the size of queue
            --_size;

            return;
        }

        // when list has more than 1 nodes
        // and current list only has 1 element left
        if (head->_queue->front == head->_queue->_size - 1)
        {
            // taking a temporary pointer
            secret::List<T> *temp = head->right;

            // detaching the head node (because recursive nature of destructor)
            head->right = nullptr;
            temp->left = nullptr;

            // free the memory
            delete head;

            // reducing size of queue
            head = temp;
            --_size;
            return;
        }

        // popping if none of the above conditions satisfy
        head->_queue->Pop();
        --_size;
    }

    // function to return front of queue
    T front()
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
            std::exit(2);
        }

        // returning from of queue
        return head->_queue->Front();
    }

    // tells whether queue is empty or not
    bool isEmpty()
    {
        return _size == 0;
    }

    int size()
    {
        return this->_size;
    }
};
