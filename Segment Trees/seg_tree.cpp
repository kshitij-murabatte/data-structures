#include <iostream>
#include <vector>

using namespace std;

// Segment tree
class SegTree
{
public:
    int *tree;
    int size;
    int type;

    void buildTree(int start, int end, int *arr, int index)
    {
        if (start == end)
        {
            tree[index] = arr[start];
            return;
        }

        int mid = start + ((end - start) / 2);

        buildTree(start, mid, arr, (2 * index) + 1);
        buildTree(mid + 1, end, arr, (2 * index) + 2);

        switch (type)
        {
            case 0:
                tree[index] = tree[2 * index + 1] + tree[2 * index + 2];
                break;
            case 1:
                tree[index] = max(tree[2 * index + 1], tree[2 * index + 2]);
                break;
            case 2:
                tree[index] = min(tree[2 * index + 1], tree[2 * index + 2]);
                break;
            case 3:
                tree[index] = (tree[2 * index + 1] ^ tree[2 * index + 2]);
                break;
        }
    }

    /*
    type
    0 - Sum Segement Tree
    1 - Max Segement Tree
    2 - Min Segement Tree
    3 - XOR Segement Tree
    */
    SegTree(int *start, int *last, int type = 0)
    {
        this->type = type;

        size = 4 * (last - start);
        tree = new int[++size];

        for (int i = 0; i < size; ++i)
            tree[i] = 0;

        // throw error if no space allocated
        buildTree(0, last - start - 1, start, 0);
    }
    /*
    SegTree(vector<int> &arr)
    {
        tree = new int[4 * (arr.size())];
        buildTree(arr);
    }*/

    int query(int start, int end)
    {
        return 0;
    }

    void update(int index)
    {
    }

    void range_update(int start, int end)
    {
    }
};

int main()
{
    int arr[] = {1, 2, 5, 9, -1, 2, 4, -7};
    int size = sizeof(arr) / sizeof(arr[0]);

    SegTree mine(arr, arr + size, 3);

    for (int i = 0; i < mine.size; ++i)
    {
        cout << mine.tree[i] << ' ';
    }
}