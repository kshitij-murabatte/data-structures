#include "Queue.h"
#include <queue>
#include <chrono>
#include <vector>

using namespace std;

int const times = 1e4;

class node
{
public:
    int a;
    float b;
    bool c;
    node() {}
    node(int q, float w, bool e)
    {
        a = q;
        b = w;
        c = e;
    }
    bool operator==(node &n)
    {
        return a == n.a and b == n.b and c == n.c;
    }
};

int main()
{
    cout << times << '\n';
    
    int x = 0;
    double STDmax = 0.0, MINEmin = 10.0, STDmin = 10.0, MINEmax = 0.0;
    double MINEavg = 0.0, STDavg = 0.0;
    
    while (x < 100000)
    {
        cout << x << '\n';
        vector<int> arr;
        for (int i = 0; i < times; ++i)
        {
            int a = rand(); /*
        int b = rand() + 1;
        float c = a / (1.0) * b;
        bool d = rand() % 2*/
            ;
            arr.push_back(a);
        }

        auto start = chrono::high_resolution_clock::now();

        queue<int> Q;

        for (int i = 0; i < times; ++i)
        {
            Q.push(arr[i]);
        }
        for (int i = 0; i < times; ++i)
        {
            Q.pop();
        }

        auto end = chrono::high_resolution_clock::now();

        double selection;
        selection = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        selection *= 1e-9;
        STDavg += selection;
        STDmax = max(STDmax, selection);
        STDmin = min(STDmin, selection);
        //cout << "std::queue : " << selection << '\n';

        start = chrono::high_resolution_clock::now();

        Queue<int> q;

        for (int i = 0; i < times; ++i)
        {
            q.push(arr[i]);
        }
        for (int i = 0; i < times; ++i)
        {
            q.pop();
        }

        end = chrono::high_resolution_clock::now();

        selection = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        selection *= 1e-9;
        //cout << "My lib : " << selection;
        MINEavg += selection;
        MINEmin = min(MINEmin, selection);
        MINEmax = max(MINEmax, selection);
        ++x;
    }
    cout << STDmin << '\t' << STDmax << '\t' << STDavg / x
    << '\n'
    << MINEmin << '\t' << MINEmax << '\t' << MINEavg / x;
}