#include "Deque.h"
#include <deque>
#include <assert.h>
#include <chrono>
#include <vector>

using namespace std;

int const times = 1e6;

class node
{
public:
    int a;
    float b;
    bool c;
    node() {}
    node(int q)
    {
        a = q;
        b = 10.0;
        c = false;
    }
    bool operator==(node &n)
    {
        return a == n.a and b == n.b and c == n.c;
    }
};

int main()
{
    /*    
    bool check()
    {
        return D.front() == d.front() and D.back() == d.back();
    }

    D.push_back({10});
    d.push_back({10});

    check();

    srand(time(0));

    bool flag = false;

    for (long long i = 0; i < 1000000000; ++i)
    {
        if (i % 10000 == 0)
            cout << (i / (1.0 * 1000000000)) * 100 << '\n';

        if (flag)
            break;

        int p = rand();
        int per = p % 4;

        switch (per)
        {
        case 0:
            D.push_back({p}), d.push_back({p});

            if (d.size() and !check())
            {
                flag = true;
            }
            break;

        case 1:
            D.push_front({p}), d.push_front({p});

            if (d.size() and !check())
            {
                flag = true;
            }
            break;

        case 2:
            if (!d.size())
                break;

            D.pop_front(), d.pop_front();

            if (d.size() and !check())
            {
                flag = true;
            }
            break;

        case 3:
            if (!d.size())
                break;

            D.pop_back(), d.pop_back();

            if (d.size() and !check())
            {
                flag = true;
            }
            break;
        }
    }
    cout << "Success!";

    */
    cout << times << '\n';

    int x = 0;
    double STDmax = 0.0, MINEmin = 100.0, STDmin = 100.0, MINEmax = 0.0;
    double MINEavg = 0.0, STDavg = 0.0;

    while (x < 100)
    {
        if (x % 10 == 0)
            cout << (x / 1000.0) * 100 << '\n';

        Deque<int> D;
        deque<int> d;
        vector<int> arr;

        for (int i = 0; i < times; ++i)
        {
            int a = rand();

            int b = rand() + 1;
            float c = a / (1.0) * b;
            bool d = rand() % 2;

            arr.push_back(a);
        }

        auto start = chrono::high_resolution_clock::now();

        for (int i = 0; i < times; ++i)
        {
            int a = arr[times] % 4;
            int p = arr[times];

            switch (a)
            {
            case 0:
                d.push_back(p);
                break;

            case 1:
                d.push_front(p);
                break;

            case 2:
                if (d.size())
                    d.pop_front();
                break;

            case 3:
                if (d.size())
                    d.pop_back();
                break;
            }
        }

        auto end = chrono::high_resolution_clock::now();
        d.clear();
        double selection;
        selection = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        selection *= 1e-9;
        STDavg += selection;
        STDmax = max(STDmax, selection);
        STDmin = min(STDmin, selection);

        //cout << "std::queue : " << selection << '\n';
        //cout << "Does not work!";

        start = chrono::high_resolution_clock::now();

        for (int i = 0; i < times; ++i)
        {
            int a = arr[times] % 4;
            int p = arr[times];
            switch (a)
            {
            case 0:
                D.push_back(p);
                break;

            case 1:
                D.push_front(p);
                break;

            case 2:
                if (D.size())
                    D.pop_front();
                break;

            case 3:
                if (D.size())
                    D.pop_back();
                break;
            }
        }

        end = chrono::high_resolution_clock::now();
        //cout << D.size() << '\t' << secret::count << '\n';
        //D.clear();
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