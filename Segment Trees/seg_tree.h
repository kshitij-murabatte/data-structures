#include <iostream>
#include <vector>

// Segment tree
class SegTree
{
    // Copy of user provided linear structure
    int *base;

    // Array to store the segement tree
    int *tree;

    // Size of user array
    int n;

    // Size of segement tree
    int size;

    // Type of segement tree
    int type;

    // For performance improvement
    int q_start, q_end;

    // Builds the segement tree
    // start, end -> indices of user array copy (base)
    // index -> of segment tree array (tree)
    void buildTree(int start, int end, int index)
    {
        // Return at single point
        if (start == end)
        {
            tree[index] = base[start];
            return;
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
            break;
        case 1:
            tree[index] = std::max(tree[2 * index + 1], tree[2 * index + 2]);
            break;
        case 2:
            tree[index] = std::min(tree[2 * index + 1], tree[2 * index + 2]);
            break;
        case 3:
            tree[index] = (tree[2 * index + 1] ^ tree[2 * index + 2]);
            break;
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
        if (mid + 1 <= q_end)
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

public:
    /*
    type defines type of Segement Tree avaliable options:
    0 - Sum Segement Tree
    1 - Max Segement Tree
    2 - Min Segement Tree
    3 - XOR Segement Tree
    */
    SegTree(const int *start, const int *last, int type = 0)
    {
        // Saving the type of segement tree
        this->type = type;

        n = last - start;
        size = 4 * (n);

        // Trying to allocate memory for segement tree
        try
        {
            tree = new int[++size];
            base = new int[n];
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
            return;
        }

        // Initialization of segement tree array
        // and copying data from user provided array
        int i = 0;
        for (; i < n; ++i)
            base[i] = start[i], tree[i] = 0;

        for (; i < size; ++i)
            tree[i] = 0;

        // After initialization building tree
        buildTree(0, n - 1, 0);
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

        n = arr.size();
        size = 4 * (n);

        // Trying to allocate memory for segement tree
        try
        {
            tree = new int[++size];
            base = new int[n];
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
            return;
        }

        // Initialization of segement tree array
        // and copying data from user provided array
        int i = 0;
        for (; i < n; ++i)
            base[i] = arr[i], tree[i] = 0;

        for (; i < size; ++i)
            tree[i] = 0;

        // After initialization building tree
        buildTree(0, n - 1, 0);
    }

    // Answers a query of valid range, returns -1 otherwise
    int query(int start, int end)
    {
        // No need to call function for just 1 index
        if (start == end)
            return base[start];

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

    void point_update(int index, int update)
    {
    }

    void range_update(int start, int end, const int *first, const int *last)
    {
    }
};