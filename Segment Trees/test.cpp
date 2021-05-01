#include "seg_tree.h"

using namespace std;

int main()
{
  /*  int arr[] = {1, 2, 5, 9, -1, 2, 4, -7};
    int size = sizeof(arr) / sizeof(arr[0]);

    SegTree mine(arr, arr + size, 0);

    cout << mine.query(2, 2);
*/
    SegTree vec(vector<int>{1, 2, 5, 9, -1, 2, 4, -7});

    cout << vec.query(0, 7);
}