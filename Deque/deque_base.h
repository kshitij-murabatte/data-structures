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

            if (type)
                front = back = -1;
            else
                front = back = container_size;
        }

        // deleting dynamically allocated container
        ~Box()
        {
            delete[] arr;
        }

        // returning front element of container
        T Front()
        {
            return arr[front];
        }
        T Back()
        {
            return arr[back];
        }

        // pushing element at back of the conatiner
        void PushBack(const T &a)
        {
            arr[++back] = a;
        }
        void PushFront(const T &a)
        {
            arr[--front] = a;
        }

        // popping from front of the container
        void PopFront()
        {
            ++front;
        }
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