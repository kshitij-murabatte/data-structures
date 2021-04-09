/*

    * Author - Kshitij Murabatte

*/

#include <iostream>

// a namespace to keep internal structure hidden

namespace secret
{
    const int container_size = 64;
    // class that stores queue elements in a segmented form
    // to provide similar performance with better space efficency
    template <typename T>
    class Box
    {
        /*
        * front -> index of front of the current container
        * back -> index of back of container
        * *arr -> the container
        */
    public:
        int front, back;
        T *arr;

        // constructor allocates memory to container
        Box(int type = 1)
        {
            arr = new T[container_size];

            // type 1 to get a new container
            // for pushing at back 
            if (type)
                front = back = -1;

            // type 0 to get a new container
            // for pushing in front
            else
                front = back = container_size;
        }

        // deleting dynamically allocated container
        ~Box()
        {
            delete[] arr;
        }

        // returning front element of the container
        T Front()
        {
            return arr[front];
        }

        // returning back element of the container
        T Back()
        {
            return arr[back];
        }

        // pushing element at back of the conatiner
        void PushBack(const T &a)
        {
            arr[++back] = a;
        }

        // pushing element in front of the conatiner
        void PushFront(const T &a)
        {
            arr[--front] = a;
        }

        // popping from front of the container
        void PopFront()
        {
            ++front;
        }

        // popping from back of the container
        void PopBack()
        {
            --back;
        }
    };

    /*
    * Blueprint of a linked list node
    * Refer the architecture for better understanding
    */
    template <typename T>
    class List
    {
    public:
        // stores a pointer to box
        // it is like small arrays in
        // a linked list node
        // this reduces frequent memory
        // allocations and deallocations 
        Box<T> *container;
        List<T> *next, *prev;

        List(int type = 1)
        {
            container = new Box<T>(type);
            next = prev = nullptr;
        }
        ~List()
        {
            // recursively deleting list and queue that it contains
            delete container;
            delete next;
        }
    };
}