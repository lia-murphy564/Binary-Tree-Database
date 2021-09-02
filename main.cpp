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
    Node* left, * right;

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

    void Insert(Node*& n, Person p) // Inserts person into the tree
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

    void Find(string fname, string lname) // Finds person by fname and lname and prints all data
    {
        Node* curr = root;
        bool bFound = false;
        while (curr != NULL)
        {
            if (curr->data.fname == fname && curr->data.lname == lname)
            {
                cout << "Found person: " << curr->data.fname << " " << curr->data.lname << "\n" << "DoB: " << curr->data.dob << "\n" << "Zip: " << curr->data.zip << "\n" << "SSN: " << curr->data.ssn << "\n";
                bFound = true;
                break;
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

    void Print(Node* n) // prints all data in the tree
    {
        if (n == NULL)
            return;
        Print(n->left);
        cout << n->data.ssn << " " << n->data.dob << " " << n->data.fname << " " << n->data.lname << " " << n->data.zip << "\n";
        Print(n->right);
    }

    void Zip(Node* n, int zip) // prints all names of people living in a certain zipcode
    {
        if (n == NULL)
        {
            return;
        }
        Zip(n->left, zip);
        if (n->data.zip == zip)
            cout << n->data.fname << " " << n->data.lname << " lives in zipcode " << zip << "\n";
        Zip(n->right, zip);

        // cout << "Could not find person with zipcode " << zip << "\n";
    }

    void Oldest(Node* n) // prints the name of the oldest person with their date of birth
    {
        Person oldest = n->data;
        Node* curr = n;
        while (curr != NULL)
        {
            if (oldest.lname < curr->data.lname)
            {
                if (oldest.dob < curr->data.dob)
                    oldest = n->data;
                curr = curr->left;
            }
            else if (oldest.lname > curr->data.lname)
            {
                if (oldest.dob < curr->data.dob)
                    oldest = n->data;
                curr = curr->right;
            }
            else
            {
                if (oldest.fname < curr->data.fname)
                {
                    if (oldest.dob < n->data.dob)
                        oldest = n->data;
                    curr = curr->left;
                }
                else
                {
                    if (oldest.dob < n->data.dob)
                        oldest = n->data;
                    curr = curr->right;
                }
            }
        }
        cout << "The oldest person is " << oldest.fname << " " << oldest.lname << " born on " << oldest.dob << "\n";
    }

    void Remove(Node* n, string fname, string lname)
    {
        if (n == NULL)
            return;
        if (n->left == NULL && n->right == NULL)
        {

        }
    }

    void Insert(Person p)
    {
        Insert(root, p);
    }
    
    void Print()
    {
        Print(root);
    }

    void Zip(int zip)
    {
        Zip(root, zip);
    }

    void Oldest()
    {
        Oldest(root);
    }

    void Remove(string fname, string lname)
    {
        Remove(root, fname, lname);
    }
};

string ReadFile(istream& stream)
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

int main()
{
    ifstream f;

    // Mac Path
    //string path = "/Users/liammurphy/Desktop/ECE 318 - Algorithms/database.txt";

    // Windows Path
    string path = "C:/Users/Amelia/Documents/database.txt";

    f.open(path);

    if (f.fail())
    {
        cout << "Error: Could not open file" << "\n";
        exit(1);
    }
    cout << "Reading in file at path " << path << "\n";

    // Parse the data and place into Binary Tree
    Person p[10000];
    Tree t;

    for (int i = 0; i < 10000; i++)
    {
        f >> p[i].ssn >> p[i].dob >> p[i].fname >> p[i].lname >> p[i].zip;
        t.Insert(p[i]);
        if (f.fail())
            break;
    }

    while (true)
    {
        string command;
        Person x;
        cout << "Available commands: find, zip, print, oldest, remove, exit \n";
        cin >> command;
        if (command == "find" || command == "Find")
        {
            cin >> x.fname >> x.lname;
            t.Find(x.fname, x.lname);
        }
        else if (command == "zip" || command == "Zip")
        {
            cin >> x.zip;
            t.Zip(x.zip);
        }
        else if (command == "print" || command == "Print")
        {
            t.Print();
        }
        else if (command == "oldest" || command == "Oldest")
        {
            t.Oldest();
        }
        else if (command == "all" || command == "All")
        {

        }
        else if (command == "remove" || command == "Remove")
        {

        }
        else if (command == "help" || command == "Help")
        {
            // cout function help notes
        }
        else if (command == "exit" || command == "Exit")
        {
            cout << "Shutting down program...";
            exit(1);
        }
        else
        {
            cout << "Invalid command \n";
        }
    }
}
