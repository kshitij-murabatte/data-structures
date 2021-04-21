#include <iostream>

namespace secret
{
    template <typename T>
    class default_t
    {
    public:
        operator T() const { return T(); }
    };
}

template <typename T>
class Array
{
public:
    // _size -> maintian total size of array
    // back -> maintain last occupied index of array

    int _size, back;

    // pointer to memory loocation
    T *array;

    // pointer for memory reallocation
    T *new_array;

    // default initializer
    T _default;

    // copy contents from array to new_array
    void copy(int size)
    {
        int i;
        for (i = 0; i <= back; ++i)
            new_array[i] = array[i];

        // initialize empty solts with default value
        for (; i < size; ++i)
            new_array[i] = _default;
    }

    // allocate new memory and delete old
    void allocator(int size)
    {
        // allocate new memory
        new_array = new T[size];

        // copy contents of array to newly allocated memory
        copy(size);

        // delete old memory
        delete[] array;

        // save memory location of new_array in array
        array = new_array;

        new_array = nullptr;
    }

    // inilializer
    void init()
    {
        _size = 0;
        back = -1;
        array = new_array = nullptr;

        // sets container element to it's default value
        _default = secret::default_t<T>();
    }

public:
    T operator [] (int i)
    {
        return *(array + i);
    }

    Array()
    {
        init();
    }

    Array(int size)
    {
        init();

        allocator(size);
    }

    Array(int size, T fill_with)
    {
        init();

        // override deafult value which provided value
        _default = fill_with;

        allocator(size);
    }
};