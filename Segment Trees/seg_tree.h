#include <iostream>
#include <vector>

// Segment tree
class SegTree
{
    // User provided linear structure
    int *base;
    std::vector<int> *vec;

    // Removes need to make another function
    int base_type;

    // Array to store the segement tree
    int *tree;

    // Size of user array
    int n;

    // Size of segement tree
    int size;

    // Type of segement tree
    int type;

    // For minor performance improvement
    // these variables act as place holders
    // for variables that do not change value
    // during recursion, removing
    // need of passing them in recursive calls
    int q_start, q_end, u_start, u_end;

    // Builds the segement tree
    // start, end -> indices of user array copy (base)
    // index -> of segment tree array (tree)
    void buildTree(int start, int end, int index)
    {
        // Return at single point
        if (start == end)
        {
            // For vector base / array base
            switch (base_type)
            {
            case 0:
                tree[index] = base[start];
                return;
            case 1:
                tree[index] = (*vec)[start];
                return;
            }
        }

        int mid = start + ((end - start) / 2);

        // Get answers from left and right sub trees
        buildTree(start, mid, (2 * index) + 1);
        buildTree(mid + 1, end, (2 * index) + 2);

        // To switch different types of segement trees
        switch (type)
        {
        case 0:
            tree[index] = tree[2 * index + 1] + tree[2 * index + 2];
            return;
        case 1:
            tree[index] = std::max(tree[2 * index + 1], tree[2 * index + 2]);
            return;
        case 2:
            tree[index] = std::min(tree[2 * index + 1], tree[2 * index + 2]);
            return;
        case 3:
            tree[index] = (tree[2 * index + 1] ^ tree[2 * index + 2]);
            return;
        }
    }

    // query utility function
    // accepts range and index (segment tree index) as input
    int _query(int b_start, int b_end, int index)
    {
        // Complete overlap
        if (q_start <= b_start and q_end >= b_end)
            return tree[index];

        // Partial overlap
        int mid = b_start + ((b_end - b_start) / 2);

        // Default initialization for XOR and Sum Tree
        int left = 0, right = 0;

        switch (type)
        {
        case 1:
            left = right = INT32_MIN;
            break;
        case 2:
            left = right = INT32_MAX;
            break;
        }

        // Only making call if query ranges will lie in left or right sub-array
        // this covers No overlap case, and improves performance
        // as useless recursive call are not made

        // Get left sub tree answer
        if (mid >= q_start)
            left = _query(b_start, mid, 2 * index + 1);

        // Get right sub tree answer
        if (mid  < q_end)
            right = _query(mid + 1, b_end, 2 * index + 2);

        // Returning answer based on type of segement tree
        switch (type)
        {
        case 0:
            return left + right;
        case 1:
            return left > right ? left : right;
        case 2:
            return left < right ? left : right;
        }

        // To remove warning
        // Answer for XOR tree
        return (left ^ right);
    }

    // point_update utility function
    void _update(int b_start, int b_end, int index)
    {
        // Found the update point
        if (b_start == q_start and q_start == b_end)
        {
            tree[index] = q_end;
            return;
        }

        // Partial overlap
        int mid = b_start + ((b_end - b_start) / 2);

        // Search in the left sub-tree
        if (mid >= q_start)
            _update(b_start, mid, 2 * index + 1);

        // Search in the left right-tree
        if (mid < q_start)
            _update(mid + 1, b_end, 2 * index + 2);

        // To switch different types of segement trees
        switch (type)
        {
        case 0:
            tree[index] = tree[2 * index + 1] + tree[2 * index + 2];
            return;
        case 1:
            tree[index] = std::max(tree[2 * index + 1], tree[2 * index + 2]);
            return;
        case 2:
            tree[index] = std::min(tree[2 * index + 1], tree[2 * index + 2]);
            return;
        case 3:
            tree[index] = (tree[2 * index + 1] ^ tree[2 * index + 2]);
            return;
        }
    }

    // Utility function for range_update
    void _range_update(int start, int end, int index = 0)
    {
        // Update a point within range
        if (start == end)
        {
            // For vector base / array base
            switch (base_type)
            {
            case 0:
                tree[index] = base[start - u_start]; // to get real index
                return;
            case 1:
                tree[index] = (*vec)[start - u_start]; // to get real index
                return;
            }
        }
        // Partial overlap
        int mid = start + ((end - start) / 2);

        // Search in the left sub-tree
        if (mid >= u_start)
            _range_update(start, mid, 2 * index + 1);

        // Search in the left right-tree
        if (mid < u_end)
            _range_update(mid + 1, end, 2 * index + 2);

        // To switch different types of segement trees
        switch (type)
        {
        case 0:
            tree[index] = tree[2 * index + 1] + tree[2 * index + 2];
            return;
        case 1:
            tree[index] = std::max(tree[2 * index + 1], tree[2 * index + 2]);
            return;
        case 2:
            tree[index] = std::min(tree[2 * index + 1], tree[2 * index + 2]);
            return;
        case 3:
            tree[index] = (tree[2 * index + 1] ^ tree[2 * index + 2]);
            return;
        }
    }

public:
    /*
    type defines type of Segement Tree avaliable options:
    0 - Sum Segement Tree
    1 - Max Segement Tree
    2 - Min Segement Tree
    3 - XOR Segement Tree
    */
    SegTree(int *start, int *last, int type = 0)
    {
        // Saving the type of segement tree
        this->type = type;
        base_type = 0;

        n = last - start;
        size = 4 * (n);

        // saving pointer to start of array
        base = start;

        // Trying to allocate memory for segement tree
        try
        {
            tree = new int[++size];
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
            return;
        }

        int init = 0;
        switch (type)
        {
        case 1:
            init = INT32_MIN;
            break;
        case 2:
            init = INT32_MAX;
            break;
        }

        // Initialization of segement tree array
        // and copying data from user provided array
        int i = 0;
        for (; i < n; ++i)
            base[i] = start[i], tree[i] = init;

        for (; i < size; ++i)
            tree[i] = init;

        // After initialization building tree
        buildTree(0, n - 1, 0);

        // clearing pointer to user provided array
        base = nullptr;
    }

    /*
    type defines type of Segement Tree avaliable options:
    0 - Sum Segement Tree
    1 - Max Segement Tree
    2 - Min Segement Tree
    3 - XOR Segement Tree
    */
    SegTree(std::vector<int> &arr, int type = 0)
    {
        // Saving the type of segement tree
        this->type = type;
        base_type = 1;

        n = arr.size();
        size = 4 * (n);

        // storing a pointer to vector
        // avoids making class object bulky
        vec = &arr;

        // Trying to allocate memory for segement tree
        try
        {
            tree = new int[++size];
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
            return;
        }

        int init = 0;
        switch (type)
        {
        case 1:
            init = INT32_MIN;
            break;
        case 2:
            init = INT32_MAX;
            break;
        }

        // Initialization of segement tree array
        // and copying data from user provided array
        for (int i = 0; i < size; ++i)
            tree[i] = init;

        // After initialization building tree
        buildTree(0, n - 1, 0);

        // clearing pointer to user provided vector
        vec = nullptr;
    }

    /*
    type defines type of Segement Tree avaliable options:
    0 - Sum Segement Tree
    1 - Max Segement Tree
    2 - Min Segement Tree
    3 - XOR Segement Tree
    */
    SegTree(std::vector<int> arr, int type = 0)
    {
        // Saving the type of segement tree
        this->type = type;
        base_type = 1;

        n = arr.size();
        size = 4 * (n);

        // storing a pointer to vector
        // avoids making class object bulky
        vec = &arr;

        // Trying to allocate memory for segement tree
        try
        {
            tree = new int[++size];
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
            return;
        }

        int init = 0;
        switch (type)
        {
        case 1:
            init = INT32_MIN;
            break;
        case 2:
            init = INT32_MAX;
            break;
        }

        // Initialization of segement tree array
        // and copying data from user provided array
        for (int i = 0; i < size; ++i)
            tree[i] = init;

        // After initialization building tree
        buildTree(0, n - 1, 0);

        // clearing pointer to user provided vector
        vec = nullptr;
    }

    // Answers a query of valid range (O (log n)), returns -1 otherwise O(1)
    int query(int start, int end)
    {
        // Invalid range
        if (start > end or start < 0 or end >= n)
            return -1;

        // q_start and q_end to avoid
        // passing them as function argument
        // again and again will improve performance
        q_start = start;
        q_end = end;

        // private query calculator
        return _query(0, n - 1, 0);
    }

    // Update a single index
    void point_update(int index, int update)
    {
        if (index < 0 or index >= n)
            return;

        // this is to reduce number of paramaters in
        // utility function call
        q_start = index;
        q_end = update;

        _update(0, n - 1, 0);
    }

    /* 
    range_update has three types of overloads 
    */
    
    /*
    start, end => (inclusive)indices of the base/provided array
    update => vector of update values 
    */
    void range_update(int start, int end, std::vector<int> &update)
    {
        if (end - start + 1 != update.size())
            return;

        base_type = 1;
        u_start = start, u_end = end;
        vec = &update;

        q_start = start, q_end = end;
        _range_update(0, n - 1, 0);

        vec = nullptr;
    }

    /*
    start, end => (inclusive)indices of the base/provided array
    update => vector of update values 
    */
    void range_update(int start, int end, std::vector<int> arr)
    {
        if (end - start + 1 != arr.size())
            return;

        base_type = 1;
        u_start = start, u_end = end;
        vec = &arr;

        q_start = start, q_end = end;
        _range_update(0, n - 1, 0);

        vec = nullptr;
    }

    /*
    start, end => (inclusive)indices of the base/provided array
    array range - [first, last)
    */
    void range_update(int start, int end, int *first, int *last)
    {
        if (end - start + 1 != last - first)
            return;

        base_type = 0;
        u_start = start, u_end = end;
        base = first;

        q_start = start, q_end = end;
        _range_update(0, n - 1, 0);

        base = nullptr;
    }
};