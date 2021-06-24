#include "Trie.h"

using namespace std;

int main()
{
    Trie root;

    root.insert("cars");
    root.insert("car");

    root.clear();

    root.insert("cart");
    root.insert("carts");
    root.insert("carts");

    root.showAll();

    root.remove("carts");

    root.showAll();
}