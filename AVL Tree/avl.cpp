#include <iostream>
#include <queue>

using namespace std;

class tree
{
public:
    tree *left, *right;
    int data, height;

    tree()
    {
        this->left = this->right = nullptr;
        this->height = 1;
    }
    tree(int val)
    {
        this->left = this->right = nullptr;
        this->data = val;
        this->height = 1;
    }
    ~tree()
    {
        delete this->left;
        delete this->right;
    }
};

class Set
{
    tree *root;

    int getHeight(tree *node)
    {
        if (!node)
            return 0;
        return node->height;
    }

    int balance_factor(tree *node)
    {
        return getHeight(node->left) - getHeight(node->right);
    }

    tree *rightRotation(tree *node)
    {
        tree *LeftTree = node->left;
        tree *LeftRightTree = LeftTree->right;

        LeftTree->right = node;
        node->left = LeftRightTree;

        // After rotation we need to update heights
        // only 2 nodes may have changed their heights
        // as we changed only 2 pointers

        node->height = max(getHeight(node->left), getHeight(node->right)) + 1;

        LeftTree->height = max(getHeight(LeftTree->left), getHeight(LeftTree->right)) + 1;

        // LeftTree is the new root now
        return LeftTree;
    }

    tree *leftRotation(tree *node)
    {
        tree *RightTree = node->right;
        tree *RightLeftTree = RightTree->left;

        RightTree->left = node;
        node->right = RightLeftTree;

        node->height = max(getHeight(node->left), getHeight(node->right)) + 1;

        RightTree->height = max(getHeight(RightTree->left), getHeight(RightTree->right)) + 1;

        return RightTree;
    }

    tree *insert(tree *node, int key)
    {
        if (node == nullptr)
            return (new tree(key));

        if (key < node->data)
            node->left = insert(node->left, key);
        else if (key > node->data)
            node->right = insert(node->right, key);
        else
            return node;

        // Coming back from recursion

        // Firstly update height of current ansestor
        node->height = max(getHeight(node->left), getHeight(node->right)) + 1;

        // After height updation get the balance factor
        int factor = balance_factor(node);

        // Now if tree has became unbalanced check for case

        // Left left case
        if (factor > 1 and key < node->left->data)
        {
            return rightRotation(node);
        }

        // Right right case
        if (factor < -1 and key > node->right->data)
        {
            return leftRotation(node);
        }

        // Left right case
        if (factor > 1 and key > node->left->data)
        {
            node->left = leftRotation(node->left);
            return rightRotation(node);
        }

        // Right left case
        if (factor < -1 and key < node->right->data)
        {
            node->right = rightRotation(node->right);
            return leftRotation(node);
        }

        return node;
    }

public:
    Set() { root = nullptr; }
    ~Set() { delete root; }

    void insert(int key)
    {
        this->root = insert(this->root, key);
    }

    int Height()
    {
        return getHeight(root);
    }

    // remove
    // size
    // lower_bound
    // upper_bound

/*
    void print()
    {
        queue<tree *> Q;

        Q.push(root);
        Q.push(nullptr);

        while (Q.size() != 1)
        {
            tree *temp = Q.front();
            Q.pop();

            if (temp == nullptr)
            {
                Q.push(temp);
                cout << "\n";
                continue;
            }
            cout << temp->data << '\t';
            if (temp->left)
            {
                cout << "L: " << temp->left->data << '\t';
                Q.push(temp->left);
            }
            if (temp->right)
            {
                cout << "R: " << temp->right->data;
                Q.push(temp->right);
            }
            cout << "\n";
        }

        cout << "\n\n\n\n\n";
    }*/
};

int main()
{
    Set s;
    for (int i = 1; i <= 3000; ++i)
    {
        s.insert(i);
        cout << s.Height() << " ";
    }
}
