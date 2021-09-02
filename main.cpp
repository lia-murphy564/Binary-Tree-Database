#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;

struct Person
{
    int ssn, dob, zip;
    string fname, lname;
};

struct Node
{
    Person data;
    Node* left, *right;
    
    Node(Person p)
    {
        data = p;
        left = NULL;
        right = NULL;
    }
};

class Tree
{
protected:
    Node* root;
    
public:
    // CONSTRUCTOR
    Tree()
    {
        root = NULL;
    }
    
    void Insert(Node*& n, Person p)
    {
        if (n == NULL)
        {
            n = new Node(p);
            return;
        }
        
        if (p.lname < n->data.lname)
        {
            Insert(n->left, p);
        }
        
        else if (p.lname == n->data.lname)
        {
            if (p.fname < n->data.fname)
                Insert(n->left, p);
            else
                Insert(n->right, p);
        }
        
        else
        {
            Insert(n->right, p);
        }
    }
    
    void Insert(Person p)
    {
        Insert(root, p);
    }
    
    void Find(string fname, string lname)
    {
        Node* curr = root;
        bool bFound = false;
        while (curr != NULL)
        {
            if (curr->data.fname == fname && curr->data.lname == lname)
            {
                cout << "Found person: " << curr->data.fname << " " << curr->data.lname << "\n" << "DoB: " << curr->data.dob << "\n" << "Zip: " << curr->data.zip << "\n" << "SSN: " << curr->data.ssn << "\n";
                bFound = true;
            }
            else if (curr->data.lname > lname)
            {
                curr = curr->left;
            }
            else if (curr->data.lname == lname)
            {
                if (curr->data.fname > fname)
                    curr = curr->left;
                else
                    curr = curr->right;
            }
            else
                curr = curr->right;
        }
        if (bFound == false)
        {
            cout << "Could not find person " << fname << " " << lname << "\n";
        }
    }
};

string ReadFile(istream &stream)
{
    string out;
    string line;
    
    while (getline(stream, line))
    {
        if (!stream.eof())
        {
            line += "\n";
            out += line;
        }
    }
    return out;
}

Tree ParseData(string data) //parses data into People structs as a binary tree
{
    Tree tree;
    int size = 100000;
    Person p[size];
    string line;
    istringstream stream(line);
    
    for (int i = 0; i < size; i++)
    {
        stream >> p[i].ssn >> p[i].dob >> p[i].fname >> p[i].lname >> p[i].zip ;
    }
    
    return tree;
}

int main()
{
    ifstream f;
    string path = "/Users/liammurphy/Desktop/ECE 318 - Algorithms/database.txt";
    
    f.open(path);
    
    if (f.fail())
    {
        cout << "Error: Could not open file" << "\n";
        exit(1);
    }
    cout << "Reading in file at path " << path << "\n";
    
    string data = ReadFile(f);
    
    
}
