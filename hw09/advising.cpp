// advising.cpp
// Author: Zach Meyers (zmeyer02)
// Date: 4/5/2023
// Purpose: Help identify trends in advising period data
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>

using namespace std;

struct Node {
    string name;
    Node *supervisee_1;
    Node *supervisee_2;
    int advisee_count;
};

const string PRINT = "p";
const string ADD_A = "a";
const string ADD_F = "f";
const string TOTAL = "t";
const string SLACKER = "s";
const string QUIT = "q";

Node *new_node(string name);
Node *read_file(string filename);
void print_advisees(Node *curr_node, string bureaucracy);
Node *find_node(Node *curr_node, string name);
void add_advisee(Node *curr_node, string name);
void add_supervisee(Node *curr_node, string faculty, string supervisee);
void total_advisee_helper(Node *curr_node, string faculty);
int total_advisees(Node *curr_node, string faculty);
void slacker(Node *curr_node);
void quit(Node *curr_node);

//STYLE NOTE: You do not have to worry about making main() fit in 30 lines for
//this assignment!
int main(int argc, char *argv[])
{
    if (argc < 2) {
        cerr << "ERROR: No filename provided as an argument" << endl;
        exit(EXIT_FAILURE);
    }
    Node *boss = read_file(argv[1]);

    //Loop to continually prompt for queries
    string c;
    cout << "Enter a query: ";
    while (cin >> c) {
        if (c == PRINT) {
            print_advisees(boss, "");
        } else if (c == TOTAL) {
            string name;
            cin >> name;
            total_advisee_helper(boss, name);
        } else if (c == SLACKER) {
            slacker(boss);
        }
          else if(c == QUIT) {
            quit(boss);
            break;
        }
         else {
            cout << c << " not recognized." << endl;
        }
        cout << endl << "Enter a query: ";
    }

    return 0;
}

//Print the tree path of every person who has advisees
void print_advisees(Node *curr_node, string bureaucracy)
{
    //Base Case: If we are at a person who has advisees, print the count
    if (curr_node->advisee_count > 0) {
        cout << bureaucracy;
        cout << curr_node->name + "->";
        cout << curr_node->advisee_count << endl;
    } else {
        //Recursive Cases: If we are at a person who doesn't have advisees,
        //recurse to their subtrees
        if (curr_node->supervisee_1 != nullptr) {
            string bureaucracy_left = bureaucracy + curr_node->name + "->";
            print_advisees(curr_node->supervisee_1, bureaucracy_left);
        }

        if (curr_node->supervisee_2 != nullptr) {
            string bureaucracy_right = bureaucracy + curr_node->name + "->";
            print_advisees(curr_node->supervisee_2, bureaucracy_right);
        }
    }
}

//Read file and build tree structure, returning root "boss" node.
//STYLE NOTE: You do not have to worry about paring down read_file() to a
//30-line limit for this assignment.
Node *read_file(string filename)
{
    //Open the given file
    ifstream infile(filename);
    if (infile.fail()) {
        cerr << "ERROR: Error opening file, please check file name: "
             << filename << endl;
        exit(EXIT_FAILURE);
    }

    //Read the first line of the file
    string supervisor;
    string supervisee;

    infile >> supervisor;
    infile >> supervisee;
    Node *boss = new_node(supervisor);
    bool first_line = true;

    //Process each line of the file
    while (!infile.eof()) {
        Node *supervisor_node;

        //Initialize the root node if we're on the first line of the file
        if (first_line) {
            supervisor_node = boss;
            first_line = false;
        } else {
            supervisor_node = find_node(boss, supervisor);
        }

        //Check if we're dealing with an advisor or a supervisor
        if (supervisee == "Advisee") {
            supervisor_node->advisee_count++;
        } else {
            //Determine if the supervisee should be the first or second supervisee
            if (supervisor > supervisee) {
                supervisor_node->supervisee_1 = new_node(supervisee);
            } else {
                supervisor_node->supervisee_2 = new_node(supervisee);
            }
        }

        //Read the next line
        infile >> supervisor;
        infile >> supervisee;
    }

    infile.close();

    return boss;
}

//Finds and returns the node with the given name
Node *find_node(Node *curr_node, string name)
{
    //Base Case: If curr_node is the person we're looking for, return it
    if (curr_node->name == name) {
        return curr_node;
        //Recursive Cases: Search either the left or right subtree for the name
    } else if (curr_node->name > name) {
        if (curr_node->supervisee_1 == nullptr) {
            return nullptr;
        }
        return find_node(curr_node->supervisee_1, name);
    } else {
        if (curr_node->supervisee_2 == nullptr) {
            return nullptr;
        }
        return find_node(curr_node->supervisee_2, name);
    }

    return nullptr;
}

//Returns a new node that is blank except for the provided name
Node *new_node(string name)
{
    Node *new_node = new Node;

    new_node->name = name;
    new_node->supervisee_1 = nullptr;
    new_node->supervisee_2 = nullptr;
    new_node->advisee_count = 0;

    return new_node;
}

  /* total_advisee_helper
   * Input: A node of the advising tree, and the name of a faculty member.
   * Description: Call total_advisees() and cout 
   * statements based on the result.
   * Output: None (void).
   */
void total_advisee_helper(Node *curr_node, string faculty)
{
    int advisees = total_advisees(curr_node, faculty);
    //If faculty member can't be found
    if(advisees == -1)
    {
        cout << faculty << " doesn't work here!" << endl;
    }
    //Print out advisee statement
    else
    {
        cout << faculty << " is responsible for ";
        cout << advisees << " advisee(s)." << endl;
    }
}

  /* total_advisees
   * Input: A node of the advising tree, and the name of a faculty member.
   * Description: Return the total number of advisees under a specified
   * faculty member (using a recursive call).
   * Output: Number of advisees (int).
   */
int total_advisees(Node *curr_node, string faculty)
{
    //Find node with faculty's name
    Node *faculty_node = find_node(curr_node, faculty);
    //Return -1 if the faculty can't be found
    if(faculty_node == nullptr){
        return -1;
    }//Reached a node with no supervisees
    if(faculty_node->supervisee_1 == nullptr 
    && faculty_node->supervisee_2 == nullptr){
        return faculty_node->advisee_count;
    }else{
         //If the first supervisee is null, make a recursive call to second
        if(faculty_node->supervisee_1 == nullptr){
            return faculty_node->advisee_count + 
            total_advisees(curr_node,faculty_node->supervisee_2->name);
        }//If the second supervisee is null, make a recursive call to first
        else if(faculty_node->supervisee_2 == nullptr){
            return faculty_node->advisee_count + 
            total_advisees(curr_node,faculty_node->supervisee_1->name);
        }//If neither supervisee is null, make recursive call to both
        else
        { 
            return faculty_node->advisee_count + 
            total_advisees(curr_node,faculty_node->supervisee_1->name) +
            total_advisees(curr_node,faculty_node->supervisee_2->name);
        }
    }
}

  /* slacker
   * Input: A node of the advising tree.
   * Description: Print out all faculty members who neither
   * supervise other faculty or advise students.
   * Output: None (void).
   */
void slacker(Node *curr_node)
{
    //If both supervisees of current node are null
    if(curr_node->supervisee_1 == nullptr
    && curr_node->supervisee_2 == nullptr)
    {
        //If the current node also has zero advisees, it's a slacker
        if(curr_node->advisee_count == 0)
        {
            cout << "Slacker: " << curr_node->name << endl;
        }
    }
    //If the first supervisee is null, make a recursive call to second
    else if(curr_node->supervisee_1 == nullptr)
    {
        slacker(curr_node->supervisee_2);
    }
    //If the second supervisee is null, make a recursive call to first
    else if(curr_node->supervisee_2 == nullptr)
    {
        slacker(curr_node->supervisee_1);
    }
    //Otherwise, make a recursive call to both
    else
    {
        slacker(curr_node->supervisee_1);
        slacker(curr_node->supervisee_2);
    }
}

  /* quit
   * Input: A node of the advising tree.
   * Description: Free all memory from the heap and exit the program.
   * Output: None (void).
   */
void quit(Node *curr_node)
{
    //Create variables to hold next nodes to delete
    Node *next_node_1, *next_node_2;
    //If both supervisees of current node are null
    if(curr_node->supervisee_1 == nullptr
    && curr_node->supervisee_2 == nullptr){
        delete curr_node;
    }//If the first supervisee is null, make a recursive call to second
    else if(curr_node->supervisee_1 == nullptr){ 
        //Initialize the next node and delete the current one
        next_node_2 = curr_node->supervisee_2;
        delete curr_node;
        quit(next_node_2);
    }//If the second supervisee is null, make a recursive call to first
    else if(curr_node->supervisee_2 == nullptr){
        //Initialize the next node and delete the current one
        next_node_1 = curr_node->supervisee_1;
        delete curr_node;
        quit(next_node_1);
    }//Otherwise, make a recursive call to both
    else{
        //Initialize the next nodes and delete the current one
        next_node_1 = curr_node->supervisee_1;
        next_node_2 = curr_node->supervisee_2;
        delete curr_node;
        quit(next_node_1);
        quit(next_node_2);
    }
}