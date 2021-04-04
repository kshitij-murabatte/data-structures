#include <iostream>
#include <queue>

using namespace std;

namespace secret
{
    class tree
    {
    public:
        tree *left, *right;
        int data, Height;

        tree()
        {
            this->left = this->right = nullptr;
            this->Height = 1;
        }
        tree(int val)
        {
            this->left = this->right = nullptr;
            this->data = val;
            this->Height = 1;
        }
        ~tree()
        {
            delete this->left;
            delete this->right;
        }
    };
}

class Set
{
    int _size;
    secret::tree *root;
    bool reallyDeleted;

    int getHeight(secret::tree *node)
    {
        if (!node)
            return 0;
        return node->Height;
    }

    int balance_factor(secret::tree *node)
    {
        return getHeight(node->left) - getHeight(node->right);
    }

    secret::tree *rightRotation(secret::tree *node)
    {
        secret::tree *LeftTree = node->left;
        secret::tree *LeftRightTree = LeftTree->right;

        LeftTree->right = node;
        node->left = LeftRightTree;

        // After rotation we need to update heights
        // only 2 nodes may have changed their heights
        // as we changed only 2 pointers

        node->Height = max(getHeight(node->left), getHeight(node->right)) + 1;

        LeftTree->Height = max(getHeight(LeftTree->left), getHeight(LeftTree->right)) + 1;

        // LeftTree is the new root now
        return LeftTree;
    }

    secret::tree *leftRotation(secret::tree *node)
    {
        secret::tree *RightTree = node->right;
        secret::tree *RightLeftTree = RightTree->left;

        RightTree->left = node;
        node->right = RightLeftTree;

        node->Height = max(getHeight(node->left), getHeight(node->right)) + 1;

        RightTree->Height = max(getHeight(RightTree->left), getHeight(RightTree->right)) + 1;

        return RightTree;
    }

    secret::tree *insert(secret::tree *node, int key)
    {
        if (node == nullptr)
        {
            ++_size;
            return (new secret::tree(key));
        }
        if (key < node->data)
            node->left = insert(node->left, key);
        else if (key > node->data)
            node->right = insert(node->right, key);
        else
            return node;

        // Coming back from recursion

        // Firstly update height of current ansestor
        node->Height = max(getHeight(node->left), getHeight(node->right)) + 1;

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

    secret::tree *minVal(secret::tree *node)
    {
        while (node->left)
            node = node->left;

        return node;
    }

    secret::tree *remove(secret::tree *node, int key)
    {
        if (!node)
            return root;

        if (key < node->data)
            node->left = remove(node->left, key);

        else if (key > node->data)
            node->right = remove(node->right, key);

        else
        {
            if (node->left == nullptr or node->right == nullptr)
            {
                secret::tree *temp = nullptr;

                if (node->left)
                    temp = node->left;

                if (node->right)
                    temp = node->right;

                if (temp == nullptr)
                {
                    temp = node;
                    node = nullptr;
                }
                else
                    *node = *temp;

                temp->left = temp->right = nullptr;
                
                delete temp;
            }
            else
            {
                secret::tree *temp = minVal(node->right);

                node->data = temp->data;

                node->right = remove(node->right, temp->data);
            }
            reallyDeleted = true;
        }

        // Check for imbalance
        if (!node)
            return node;

        node->Height = 1 + max(getHeight(node->left), getHeight(node->right));

        int factor = balance_factor(node);

        // Left left case
        if (factor > 1 and balance_factor(node->left) >= 0)
            return rightRotation(node);

        // Right right case
        if (factor < -1 and balance_factor(node->right) <= 0)
            return leftRotation(node);

        // Left right case
        if (factor > 1 and balance_factor(node->left) < 0)
        {
            node->left = leftRotation(node->left);
            return rightRotation(node);
        }

        // Right left case
        if (factor < -1 and balance_factor(node->right) > 0)
        {
            node->right = rightRotation(node->right);
            return leftRotation(node);
        }

        return node;
    }

public:
    Set()
    {
        _size = 0;
        root = nullptr;
    }
    ~Set() { delete root; }

    void insert(int key)
    {
        this->root = insert(this->root, key);
    }
    void remove(int key)
    {
        this->root = remove(this->root, key);

        if (reallyDeleted)
        {
            --_size;
            reallyDeleted = false;
        }
    }

    int height()
    {
        return getHeight(root);
    }
    int size()
    {
        return _size;
    }
    // lower_bound
    // upper_bound

    void print()
    {
        queue<secret::tree *> Q;

        Q.push(root);
        Q.push(nullptr);

        while (Q.size() != 1)
        {
            secret::tree *temp = Q.front();
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
    }
};

int main()
{
    Set s;
    for (int i = 1; i <= 15; ++i)
    {
        s.insert(i);
    }
}
