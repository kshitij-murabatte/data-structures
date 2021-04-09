#include "../deque_base/deque_base.h"

template <typename T>
class Deque
{
private:
    // keep count of number of elements in deque
    int _size;

    // max size of a container
    int max_size;

    // pointers to maintain linked list
    secret::List<T> *head, *tail;

    // utility function to allocate memory
    secret::List<T> *make_new_node(int type = 1)
    {
        // trying to allocate memory
        // if failed, an exception is thrown
        secret::List<T> *temp;
        try
        {
            temp = new secret::List<T>(type);
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
            std::exit(2);
        }

        // return pointer to newly allocated memory
        return temp;
    }

    // initial initilization of deque
    void init()
    {
        head = tail = make_new_node();

        // initilizating back and front at middle of container
        head->container->back = max_size / 2 - 1;
        head->container->front = max_size / 2;
    }

    // garbage collector funtion
    // to delocate container if it is empty
    void delete_empty()
    {
        // remove empty head
        if (head->container->front == max_size)
        {
            secret::List<T> *temp = head;
            head = head->next;

            temp->next = nullptr;

            if (!head)
            {
                tail = nullptr;
                delete temp;
                return;
            }

            head->prev = nullptr;
            delete temp;
        }

        // remove empty tail
        if (tail->container->back == -1)
        {
            secret::List<T> *temp = tail;
            tail = tail->prev;

            temp->prev = nullptr;

            if (!tail)
            {
                head = nullptr;
                delete temp;
                return;
            }

            tail->next = nullptr;
            delete temp;
        }
    }

    // deque empty error
    void empty_error()
    {
        std::cerr << "\nDeque is empty!";
        std::exit(2);
    }

public:
    Deque()
    {
        max_size = secret::container_size;
        _size = 0;
        head = tail = nullptr;
    }
    ~Deque()
    {
        delete head;
    }

    // Pushes element to the front of the deque
    void push_front(T data)
    {
        if (!head)
        {
            // if the size of queue is 0, trying to make a new node
            // otherwise informing the programmer of failed operation
            init();
        }

        ++_size;

        // getting the front pointer from in the current node
        int fr = head->container->front;

        // checking if it is possible to insert new
        // element in the current container
        if (fr > 0 and fr < max_size)
        {
            // insert if possible
            head->container->PushFront(data);
            return;
        }

        // if no space is there in current list node make a new one
        secret::List<T> *temp = make_new_node(0);

        // reassigning new head
        temp->next = head;
        head->prev = temp;
        head = temp;

        // push new element in newly created container
        head->container->PushFront(data);

        // as back was initialized as max_size
        // so after a successful insertion
        // setting back as max_size - 1 (0 based indexing)
        (head->container->back)--;
    }

    // Pushes element at the end of the deque
    void push_back(T data)
    {
        if (!head)
        {
            // if the size of queue is 0, trying to make a new node
            // otherwise informing the programmer of failed operation
            init();
        }

        ++_size;

        // getting the front pointer from in the current node
        int bk = tail->container->back;

        // checking if it is possible to insert new
        // element in the current container
        if (bk < max_size - 1 and bk > -1)
        {
            // insert if possible
            tail->container->PushBack(data);
            return;
        }

        // if no space is there in current list node make a new one
        secret::List<T> *temp = make_new_node();

        // reassigning new tail
        tail->next = temp;
        temp->prev = tail;
        tail = temp;

        // push new element in newly created container
        tail->container->PushBack(data);

        // as front was initialized as -1
        // so after a successful insertion
        // setting front as 0
        (tail->container->front)++;
    }

    // Remove element from the front of the deque
    void pop_front()
    {
        // if deque is empty throw error
        if (!_size)
            empty_error();

        --_size;

        head->container->PopFront();

        // check if any memory can be delocated
        // after a pop operation
        delete_empty();
    }

    // Remove element from the back of the deque
    void pop_back()
    {
        // if deque is empty throw error
        if (!_size)
            empty_error();

        --_size;

        tail->container->PopBack();

        // check if any memory can be delocated
        // after a pop operation
        delete_empty();
    }

    // Return element at the back of the deque
    T front()
    {
        // if deque is empty throw error
        if (!_size)
            empty_error();

        // return element otherwise
        return head->container->Front();
    }

    // Returns element at the back of the deque
    T back()
    {
        // if deque is empty throw error
        if (!_size)
            empty_error();

        // return element otherwise
        return tail->container->Back();
    }

    // Returns size of deque
    int size()
    {
        return _size;
    }

    void clear()
    {
        delete head;

        max_size = secret::container_size;
        _size = 0;
        head = tail = nullptr;
    }
};