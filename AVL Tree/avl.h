#include <iostream>

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
    // saves the size of the set
    int _size;

    // root of the tree
    secret::tree *root;

    // variable to tell if a key was deleted (used to update size)
    bool reallyDeleted;

    // utility pointers for upper bound, lower bound and find function
    const int *lowerPointer, *upperPointer, *findPointer;

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

        node->Height = std::max(getHeight(node->left), getHeight(node->right)) + 1;

        LeftTree->Height = std::max(getHeight(LeftTree->left), getHeight(LeftTree->right)) + 1;

        // LeftTree is the new root now
        return LeftTree;
    }

    secret::tree *leftRotation(secret::tree *node)
    {
        secret::tree *RightTree = node->right;
        secret::tree *RightLeftTree = RightTree->left;

        RightTree->left = node;
        node->right = RightLeftTree;

        node->Height = std::max(getHeight(node->left), getHeight(node->right)) + 1;

        RightTree->Height = std::max(getHeight(RightTree->left), getHeight(RightTree->right)) + 1;

        return RightTree;
    }

    // Private insertion function
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
        node->Height = std::max(getHeight(node->left), getHeight(node->right)) + 1;

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

    // Private utility function to get the mininum value
    secret::tree *minVal(secret::tree *node)
    {
        while (node->left)
            node = node->left;

        return node;
    }

    // Private function to remove the key
    secret::tree *remove(secret::tree *node, int key)
    {

        if (!node)
            return node;

        if (key < node->data)
            node->left = remove(node->left, key);

        else if (key > node->data)
            node->right = remove(node->right, key);

        else
        {
            if (node->left == nullptr or node->right == nullptr)
            {
                secret::tree *temp = node->left ? node->left : node->right;

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

        node->Height = 1 + std::max(getHeight(node->left), getHeight(node->right));

        int factor = balance_factor(node);

        // Left left case
        if (factor > 1 and balance_factor(node->left) >= 0)
            return rightRotation(node);

        // Left right case
        if (factor > 1 and balance_factor(node->left) < 0)
        {
            node->left = leftRotation(node->left);
            return rightRotation(node);
        }

        // Right right case
        if (factor < -1 and balance_factor(node->right) <= 0)
            return leftRotation(node);

        // Right left case
        if (factor < -1 and balance_factor(node->right) > 0)
        {
            node->right = rightRotation(node->right);
            return leftRotation(node);
        }

        return node;
    }

    // Private function to find the lowerbound
    void lowerBound(secret::tree *node, int key)
    {
        if (!node)
            return;

        if (node->data >= key)
        {
            lowerPointer = &node->data;
            lowerBound(node->left, key);
        }
        else
        {
            lowerBound(node->right, key);
        }
    }

    // Private function to find the upperbound
    void upperBound(secret::tree *node, int key)
    {
        if (!node)
            return;

        if (node->data > key)
        {
            upperPointer = &node->data;
            upperBound(node->left, key);
        }
        else
        {
            upperBound(node->right, key);
        }
    }

    // Private function to find the key
    void find(secret::tree *node, int key)
    {
        while (node)
        {
            if (node->data == key)
            {
                findPointer = &node->data;
                return;
            }
            else if (node->data < key)
                node = node->right;
            else
                node = node->left;
        }
    }

public:

    Set()
    {
        _size = 0;
        root = nullptr;
        lowerPointer = upperPointer = findPointer = nullptr;
    }

    ~Set() 
    { 
        delete this; 
    }

    // Insert a key into the set
    void insert(int key)
    {
        this->root = insert(this->root, key);
    }

    // Removes the given key from set if present
    void remove(int key)
    {
        this->root = remove(this->root, key);

        if (reallyDeleted)
        {
            --_size;
            reallyDeleted = false;
        }
    }

    int height(secret::tree *node)
    {
        return getHeight(node);
    }
    int size()
    {
        return _size;
    }

    // Returns NULL pointer if no lower found, a const integer pointer to the lower bound otherwise
    const int *lowerBound(int key)
    {
        lowerBound(this->root, key);

        const int *temp = lowerPointer;
        lowerPointer = nullptr;

        return temp;
    }

    // Returns NULL pointer if no upper found, a const integer pointer to the upper bound otherwise
    const int *upperBound(int key)
    {
        upperBound(this->root, key);

        const int *temp = upperPointer;
        upperPointer = nullptr;

        return temp;
    }

    // Returns NULL pointer if given key was not found, a const integer pointer to the key otherwise
    const int *find(int key)
    {
        find(this->root, key);

        const int *temp = findPointer;
        findPointer = nullptr;

        return temp;
    }
};