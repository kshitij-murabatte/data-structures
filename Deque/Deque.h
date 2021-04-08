#include "deque_base.h"

template <typename T>
class Deque
{
private:
    int _size;
    int max_size;
    secret::List<T> *head, *tail;

    secret::List<T> *make_new_node(int type = 1)
    {
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
        return temp;
    }

    void empty_error()
    {
        std::cerr << "\nQueue is empty!";
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

    // push_front
    void push_front(T data)
    {
        if (!head)
        {
            // if the size of queue is 0, trying to make a new node
            // otherwise informing the programmer of failed operation
            head = tail = make_new_node();
        }

        ++_size;

        if (head->container->front != 0)
        {
            // insert
            head->container->PushFront(data);
            return;
        }

        // if no space is there in current list node make a new one
        secret::List<T> *temp = make_new_node(0);

        temp->next = head;
        head->prev = temp;
        head = temp;

        head->container->PushFront(data);
    }

    // push_back
    void push_back(T data)
    {
        if (!head)
        {
            // if the size of queue is 0, trying to make a new node
            // otherwise informing the programmer of failed operation
            head = tail = make_new_node();
        }

        ++_size;

        if (head->container->back != max_size - 1)
        {
            // insert
            head->container->PushBack(data);
            return;
        }

        // if no space is there in current list node make a new one
        secret::List<T> *temp = make_new_node();

        tail->next = temp;
        temp->prev = tail;
        tail = temp;

        tail->container->PushBack(data);
    }

    // pop_front
    void pop_front()
    {
        if (!_size)
            empty_error();

        --_size;
        head->container->PopFront();

        if (head->container->front == max_size)
        {
            secret::List<T> *temp = head;
            head = head->next;
            
            temp->next = nullptr;
            
            head->prev = nullptr;
            delete temp;

            if (!head)
                tail = nullptr;
        }
    }

    // pop_back
    void pop_back()
    {
        if (!_size)
            empty_error();

        --_size;
        tail->container->PopBack();
   
        if (tail->container->back == -1)
        {
            secret::List<T> *temp = tail;
            tail = tail->prev;
            
            tail->next = nullptr;
            
            temp->prev = nullptr;
            delete temp;

            if (!tail)
                head = nullptr;
        }
    }

    // front
    T front()
    {
        if (!_size)
            empty_error();

        return head->container->Front();
    }

    // back
    T back()
    {
        if (!_size)
            empty_error();

        return tail->container->Back();
    }
    
    // size
    int size()
    {
        return _size;
    }
};