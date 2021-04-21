#include <iostream>
#include <vector>
#include "Array.h"
using namespace std;

template <typename T>
class default_t
{
public:
    operator T() const { return T(); }
};

struct f
{
    int a, b;
    bool c;
    float d;
    f(int q, int w, bool e, float r)
    {
        a = q;
        b = w;
        c = e;
        d = r;
    }
    f()
    {
        a = 0;
        b = 0;
        c = 0;
        d = 0;
    }
};



int main()
{
    int arr[10];
    arr[0] = default_t<int>();
    string s[2];

    string a = default_t<string>();

    s[0] = default_t<string>();

    float ar[10];
    ar[2] = default_t<float>();

    f qqq = default_t<f>();

    f S[2];
    S[0] = f(2, 3, 0, 0);

    Array<int> myArray(100, 320);
    cout << myArray[10];
    myArray[10];
}