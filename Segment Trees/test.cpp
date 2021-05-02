#include "seg_tree.h"

using namespace std;

int main()
{
	/*  int arr[] = {1, 2, 5, 9, -1, 2, 4, -7};
    int size = sizeof(arr) / sizeof(arr[0]);

    SegTree mine(arr, arr + size, 0);

    cout << mine.query(2, 2);
*/
	SegTree vec(vector<int>{1, 2, 5, 9, -1, 2, 4, -7}, 1);

	cout << vec.query(0, 7) << '\n';
/*
	for (int i = 0; i < vec.size; ++i)
		cout << vec.tree[i] << ' ';
*/
	cout << "\n\n";/*
	int arr[] = {5, 7, 3, 1};
	vec.range_update(4, 7, arr, arr + 4);
	*/
	vec.point_update(5, 100);
	/*for (int i = 0; i < vec.size; ++i)
		cout << vec.tree[i] << ' ';

	cout << "\n\n";
	cout << '\n';*/
	cout << vec.query(0, 7);
}