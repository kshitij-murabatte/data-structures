#include <vector>

class Heap
{
    // do you really need _size?
    bool heap_type;

    // 0 based heap indexing
    std::vector<int> heap;

    int empty_slot;

    // utility functions
    void swap(int a, int b)
    {
        int temp = heap[a];
        heap[a] = heap[b];
        heap[b] = temp;
    }

    inline int getParent(int index)
    {
        // handle index = 0
        return (index - 1) / 2;
    }

    inline int leftChild(int index)
    {
        return index * 2 + 1;
    }

    inline int rightChild(int index)
    {
        return index * 2 + 2;
    }

    // min heap config

    // max heap config

    void shiftDown(int _new, int last)
    {
        while (_new <= last)
        {
            if (heap[_new] >= heap[leftChild(_new)] and heap[_new] >= heap[rightChild(_new)])
            {
                return;
            }
            else if (heap[leftChild(_new)] >= heap[rightChild(_new)])
            {
                this->swap(_new, leftChild(_new));
                _new = leftChild(_new);
            }
            else
            {
                this->swap(_new, rightChild(_new));
                _new = rightChild(_new);
            }
        }
    }

    void shiftUp(int i)
    {
        while (i > 0)
        {
            if (heap[getParent(i)] >= heap[i])
            {
                return;
            }
            else
            {
                this->swap(heap[getParent(i)], heap[i]);
            }
            i = getParent(i);
        }
    }

    // Remove element
    void remove(int last)
    {
        int j = extractTop(last);
    }

    void insert(int &last, int element, int size)
    {
        heap[last++] = element;

        int i = last - 1;
        shiftUp(i);
    }

    int extractTop(int &last)
    {
        int _max = heap[0];

        // Put leftmost leaf at root

        heap[0] = heap[last];
        // And now we need to select a drirection to go
        shiftDown(0, last);
        return _max;
    }

    // iterative heapify for better performance

    void itrBuildHeap(int index, int size)
    {
        int L, R;

        L = leftChild(index);
        R = rightChild(index);

        if (L > size)
        {
            // Node has no children
            return;
        }

        else if (R > size && L <= size)
        {
            // Node has only left child
            if (heap[L] < heap[index])
            {
                this->swap(L, index);
            }
            return;
        }

        // Node has both children
        while (index <= size)
        {
            L = leftChild(index);
            R = rightChild(index);

            if (L > size)
            {
                // Node has no children
                return;
            }

            else if (R > size && L <= size)
            {
                // Node has only left child
                if (heap[L] < heap[index])
                {
                    this->swap(L, index);
                }
                return;
            }

            if (heap[L] <= heap[R])
            {
                if (heap[L] < heap[index])
                {
                    this->swap(L, index);
                    index = L;
                }
                else
                {
                    return;
                }
            }
            else if (heap[R] < heap[L])
            {
                if (heap[R] < heap[index])
                {
                    this->swap(R, index);
                    index = R;
                }
                else
                {
                    return;
                }
            }
        }
    }

    void buildHeap()
    {
        // loop from first node from last
        // that has a child -> i = getParent(last)
        // for i >= 0; i-- : itrBuildHeap(i);
    }

public:
    // constructor
    // vector to heap

    // Initilize heap with vector, heap_type -> true means max heap,
    // false means min heap (default)
    Heap(std::vector<int> &convert, bool heap_type = false)
    {
        heap = convert;
        this->heap_type = heap_type;

        empty_slot = 0;
        buildHeap();
    }

    // heap_type -> true means max heap,
    // false means min heap (default)
    Heap(bool heap_type = false)
    {
        this->heap_type = heap_type;
        empty_slot = 0;
    }
    // push

    // pop

    // top

    // size

    // = operator overload
};