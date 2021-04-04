#include <vector>

class realDisjointSet
{
private:
    std::vector<int> parent;

public:
    realDisjointSet()
    {
        parent.clear();
        parent.push_back(-1);
    }
    int _find(int a)
    {
        if (a != parent[a])
            parent[a] = find(parent[a]);
        return parent[a];
    }
    int find(int a)
    {
        try
        {
            parent.at(a);
        }
        catch (const std::exception &e)
        {
            //std::cerr << '\n' << a << " does not exist in the set!";
            return -1;
        }
        return _find(a);
    }
    void Union(int a, int b)
    {
        int x = find(a);
        int y = find(b);
        try
        {
            if (x == -1)
            {
                throw 'a';
            }
            else if (y == -1)
            {
                int *q;
                throw q;
            }
        }
        catch (char q)
        {
            //std::cerr << "\ndSet::_union: operation failed => " << a << " was not found";
            return;
        }
        catch (int *q)
        {
            //std::cerr << "\ndSet::_union: operation failed => " << b << " was not found";
            return;
        }
        parent[x] = y;
    }
    void resize(int a)
    {
        if (find(a) == -1)
        {
            for (int i = parent.size(); i <= a; ++i)
            {
                parent.push_back(0);
            }
            parent[a] = a;
        }
        return;
    }
    void make(int size)
    {
        parent.resize(size + 1);
    }
    int sets()
    {
        int unique = 0;
        for (int i = 1; i < parent.size(); i++)
        {
            if (parent[i] == i)
                unique++;
        }
        return unique;
    }
};

class dSet
{
private:
    realDisjointSet _set;

public:
    void _union(int a, int b)
    {
        _set.Union(a, b);
    }
    int findParent(int a)
    {
        return _set.find(a);
    }
    void insert(int a)
    {
        _set.resize(a);
    }
    dSet()
    {
    }
    dSet(int size)
    {
        _set.make(size);
    }
    int numberOfSets()
    {
        return _set.sets();
    }
};