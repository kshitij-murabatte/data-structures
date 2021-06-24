#include <iostream>

#define characters 26

namespace trieBase
{
    // bluprint of a trie node
    class trieDev
    {
    public:
        bool isString; // does the string end here?
        trieDev *nextChar[characters]; // array of pointers
        int commonPrefix; // tells for how many strings, the current string is a prefix to
        // the root is empty and hence prefix to all string

        // destructor
        ~trieDev()
        {
            // delete all children then delete itself
            for (int i = 0; i < characters; ++i)
            {    
                delete this->nextChar[i];
            }
        }

        // constructor
        trieDev()
        {
            isString = false;
            commonPrefix = 0;

            // basic initilization
            for (int i = 0; i < characters; ++i)
                nextChar[i] = nullptr;
        }
    };
} // namespace tt

class Trie
{
    // the root
    trieBase::trieDev *root;
    
    // useful for remove function
    bool wasDeleted;

    // private remove function to remove a string
    trieBase::trieDev *_remove(const std::string &Remove, trieBase::trieDev *temp, int index = 0)
    {
        // if all characters have been traversed then
        if (index == Remove.size())
        {
            // check if string ends at current character
            if (temp->isString)
            {
                // if it does end then set is as false
                temp->isString = false;

                // the commonPrefix alsp helps in 
                // finding out children in constant time
                // ABC is a prefix of ABC 
                // so if any node has prefix as 1 ten it has no children
                // and can be deleted
                if (temp->commonPrefix == 1)
                {
                    // setting flag as true
                    // this will help decrement
                    // commonPrefix while 
                    // returning from recursion
                    wasDeleted = true;
                    delete temp;
                    return nullptr;
                }
            }

            // just return if none of above conditons satisfy
            return temp;
        }

        // get the relative index of current character
        int i = Remove[index] - 'a';

        // check if the character exists along the current path 
        // and continue in bottom up recurion if it does exist
        // and attach the update pointer
        if (temp->nextChar[i])
            temp->nextChar[i] = _remove(Remove, temp->nextChar[i], index + 1);

        // while returning in recursion if a node is encountered
        // that does not have any children and no string ends there
        // then it can be deleted
        if (temp->isString == false and temp->commonPrefix == 1)
        {
            delete temp;
            return nullptr;
        }

        // otherwise update commonPrefix across the 
        // return path
        else if (wasDeleted)
            --(temp->commonPrefix);

        return temp;
    }

    // private utility for printing all string in trie
    void _showAll(trieBase::trieDev *temp, std::string str)
    {
        // str acts as a prefix and is passed by value
        // this could end up using lot of memory
        // but no way around when it comes to printing
        for (int i = 0; i < characters; ++i)
        {
            if (temp->nextChar[i])
            {
                // attach new characters to end of prefix
                _showAll(temp->nextChar[i], str + char('a' + i));
            }
        }

        // and print the string if end of string is encountered
        if (temp->isString)
            std::cout << str << '\n';
    }

public:

    // Constructor
    Trie()
    {
        root = new trieBase::trieDev();
        wasDeleted = false;
    }

    // Destructor
    ~Trie()
    {
        delete this->root;
    }

    // Resets the data structure
    void clear()
    {
        this->~Trie();
        root = new trieBase::trieDev();
    }

    // Prints all the strings present in Trie
    void showAll()
    {
        _showAll(this->root, "");
    }

    // Inserts a string into Trie
    void insert(const std::string &Put)
    {
        // return on empty string
        if (Put.empty())
            return;

        // duplicate check
        if (this->search(Put))
            return;

        trieBase::trieDev *temp = this->root;

        // iterate the string
        for (int i = 0; i < Put.size(); ++i)
        {
            // get the relative index 
            int index = Put[i] - 'a';
            
            // if no nodes exists for current character
            // create one
            if (temp->nextChar[index] == nullptr)
            {
                temp->nextChar[index] = new trieBase::trieDev();
            }

            // traverse down the Trie
            temp = temp->nextChar[index];

            // mainting the commonPrefix
            ++(temp->commonPrefix);
        }

        // to maintain size
        ++(this->root->commonPrefix);

        // set the last node as end of string
        temp->isString = true;
    }

    // Returns number of unique string present in Trie
    int size()
    {
        return this->root->commonPrefix;
    }

    // Checks whether a string is present in Trie or not
    bool search(const std::string &Find)
    {
        if (Find.empty())
            return false;

        trieBase::trieDev *temp = root;

        // iterate over the string
        for (int i = 0; i < Find.size(); ++i)
        {
            // get the relative character index
            int index = Find[i] - 'a';

            // if there is no node for current
            // it is sure that input string 
            // is not present in the Trie
            if (temp->nextChar[index] == nullptr)
            {
                return false;
            }

            // traverse down the Trie
            temp = temp->nextChar[index];
        }

        // is the last node really an end of string
        return temp->isString;
    }

    // Delete a string from Trie
    void remove(const std::string &Remove)
    {
        // calls bottom up revursive utility function
        this->root = _remove(Remove, this->root);

        // resetting the variable
        wasDeleted = false;
    }
};
