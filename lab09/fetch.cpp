// fetch.cpp
// Purpose: Interact with a binary tree storing numbers and colors
// Written by: Megan Monroe (mmonroe)

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

//Node struct contains a number, a color,
//and pointers to the left and right sub-trees
struct Node {
    int number;
    string color;
    Node *less_than;
    Node *greater_than;
};

const string INSERT = "i";
const string FETCH = "f";
const string RAINBOW = "r";
const string REVERSE = "rr";
const string QUIT = "q";

Node *new_node(int number, string color);
void insert_node(Node *curr_node, int number, string color);
string fetch_node(Node *curr_node, int num);

int main(int argc, char *argv[])
{
    //Initialize a root node and point to it
    Node *root = new_node(50, "black");

    //Loop to continually prompt for queries
    int number;
    string c, color;
    cout << "Enter your command: ";
    cin >> c;
    while (c != QUIT) {
        if (c == INSERT) {
            cin >> number >> color;
            insert_node(root, number, color);
        } else if (c == FETCH) {
            cin >> number;
            cout << fetch_node(root, number) << endl;
        } else if (c == RAINBOW) {
            cin >> number;

            /* YOUR (TOTALLY OPTIONAL CHALLENGE) CODE HERE */
        } else if (c == REVERSE) {
            cin >> number;

            /* YOUR (TOTALLY OPTIONAL CHALLENGE) CODE HERE */
        } else {
            cout << c << " not recognized." << endl;
        }
        cout << endl << "Enter your command: ";
        cin >> c;
    }

    return 0;
}

//Starting from the current node, find where a node with the given number should
//be stored. If such a node already exists, update its color. Otherwise, create
//a new node in the proper location with the given number and color.
void insert_node(Node *curr_node, int number, string color)
{
    //Base Case 1: If that number is already stored, update the color
    if (curr_node->number == number) {
        curr_node->color = color;
    } else if (curr_node->number > number) {
        if (curr_node->less_than == nullptr) {
            //Base Case 2: We found the correct spot; add the new node
            curr_node->less_than = new_node(number, color);
        } else {
            //Recursive Case 1: Move to the left ("less_than") subtree
            insert_node(curr_node->less_than, number, color);
        }
    } else {
        if (curr_node->greater_than == nullptr) {
            //Base Case 3: We found the correct spot, add the new node
            curr_node->greater_than = new_node(number, color);
        } else {
            //Recursive Case 2: Move to the right ("greater_than") subtree
            insert_node(curr_node->greater_than, number, color);
        }
    }
}

//Returns a pointer to a new node with the provided number and color. Note that
//a new node always has it's less_than and greater_than fields set to nullptr.
Node *new_node(int number, string color)
{
    Node *new_node = new Node; //Allocating a single struct (not an array)!

    new_node->number = number;
    new_node->color = color;
    new_node->less_than = nullptr;
    new_node->greater_than = nullptr;

    return new_node;
}

string fetch_node(Node *curr_node, int num)
{
    if(curr_node->number == num)
    {
        return curr_node->color;
    }
    else if((curr_node->less_than == nullptr) && (curr_node->greater_than == nullptr))
    {
        return "Node not found!";
    }
    else if(curr_node->less_than == nullptr)
    {
        return fetch_node(curr_node->greater_than,num);
    }
    else if(curr_node->greater_than == nullptr)
    {
        return fetch_node(curr_node->less_than,num);
    }
    else if(curr_node->number > num)
    {
        return fetch_node(curr_node->less_than,num);
    }
    else
    {
        return fetch_node(curr_node->greater_than,num);
    }
}
