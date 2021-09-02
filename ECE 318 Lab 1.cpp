// ECE 318 Lab 1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

using namespace std;

struct node
{
    string data;
    node* left, * right;

    node(string s)
    {
        data = s; left = NULL; right = NULL;
    }
};


class tree
{
protected:
    node* root;
public:
    tree()
    {
        root = NULL;
    }

    void insert(node*& t, string s)
    {
        if (t == NULL)
        {
            t = new node(s);
            return;
        }
        if (s < t->data)
            insert(t->left, s);
        else
            insert(t->right, s);
    }

    void insert(string s)
    {
        insert(root, s);
    }

    void insert_loop(node*& t, string s)
    {
        if (t == NULL)
        {
            t = new node(s);
            return;
        }
        node* prev = NULL;
        while (t != NULL)
        {
            prev = t;
            if (s < t->data)
                t = t->left;
            else
                t = t->right;
        }
        if (s < prev->data)
            prev->left = new node(s);
        else
            prev->right = new node(s);
    }

    void print(node* t) //print everything reachable from this node
    {
        if (t == NULL)
        {
            //      cout << "error: tree has no data\n";
            return;
        }
        print(t->left);
        cout << t->data << "\n";
        print(t->right);
    }

    void print()
    {
        print(root);
    }
};



int main()
{
    std::cout << "Hello World!\n";
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
