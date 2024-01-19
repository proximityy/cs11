/* phone_tree.cpp
 *
 * Author: Zachary Meyers
 * Date: 3/1/23
 *
 * Purpose: Determine if a call plan will work 
 *
 */

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Parent
{
    string name;
    int time;
    string parent_name;
    Parent *recipient;
    bool is_dialed;
};

Parent *read_parents(string filename, int *num_parents);
int find_parent(Parent *parent_list, int num_parents);
void print_solution(Parent *parent_list, int num_parents, int result);

int main(int argc, char *argv[]) {
    //Make sure a filename is provided
    if (argc < 2) {
        cerr << "ERROR: Please check file name" << endl;
        exit(EXIT_FAILURE);
    }
    //Call helper functions using filename and num_parents
    int num_parents;
    Parent *parent_list = read_parents(argv[1], &num_parents);
    int where_is_parent = find_parent(parent_list, num_parents);
    print_solution(parent_list, num_parents, where_is_parent);
    //Clear allocated memory
    delete [] parent_list;

return 0;
} 

  /* read_parents
   * Input: A filename and a pointer to the total number of parents.
   * Description: Creates a dynamically sized array and fills
   * it with Parents structs using the inputted file.
   * Output: The filled array of Parents.
   */
Parent *read_parents(string filename, int *num_parents)
{
    ifstream infile(filename);
    //If the file doesn't open properly
    if(infile.fail())
    {
        cout << "error";
        exit(EXIT_FAILURE);
    }
    infile >> *num_parents;

    //Create an array of parents and fill it from the file
    Parent *parent_list = new Parent[*num_parents];
    for(int i = 0; i < *num_parents; i++)
    {
        infile >> parent_list[i].name >> 
        parent_list[i].time >> parent_list[i].parent_name;
        parent_list[i].recipient = nullptr;
        parent_list[i].is_dialed = false;
    }
    infile.close();

    //Loop through all students to assign proper pointers
    //for each parent's recipient
    for(int i = 0; i < *num_parents; i++)
    {
        for(int j = 0; j < *num_parents; j++)
        {
            //If a parent's recipient matches the name of
            //another parent, assign that parent as a pointer
            //to the first parent's recipient
            if(parent_list[i].parent_name == parent_list[j].name)
            {
                parent_list[i].recipient = &parent_list[j];
            }
        }
    }
    return parent_list;
}

  /* find_parent
   * Input: Pointer to an array filled with Parents
   * and the total number of parents in the array.
   * Description: Determine which parent, if any, can 
   * successfully initiate an unbroken chain of calls.
   * Output: An int of the row holding the 'successful' parent.
   */
int find_parent(Parent *parent_list, int num_parents)
{
    //Loop through the parents one by one
    for(int i = 0; i < num_parents; i++)
    {
        //Create this_iteration to determine if a parent can
        //make an unbroken chain of callers, temp_parent to point
        //to the next parent in the chain
        bool this_iteration = true;
        Parent *temp_parent;
        parent_list[i].is_dialed = true;
        temp_parent = parent_list[i].recipient;
        //Follow the path of callers for each parent,
        //updating the is_dialed variable to determine
        //if each parent makes an unbroken chain of callers
        for(int j = 0; j < num_parents; j++)
        {
            temp_parent->is_dialed = true;
            temp_parent = temp_parent->recipient;
        }
        //Loop through the list of parents again
        for(int k = 0; k < num_parents; k++)
        {
            //If one parent in the list has not been reached,
            //set this_iteration to false
            if(parent_list[k].is_dialed == false)
            {
                this_iteration = false;
                break;
            }
        }
        //If all parents have been successfully reached, 
        //return the line holding the successful parent
        if(this_iteration)
        {
            return i;
        }
        else
        {
            //Reset parent_list is_dialed values to false
            for(int j = 0; j < num_parents; j++)
            {
                parent_list[j].is_dialed = false;
            }
        }
    }
    //If unable to find an unbroken chain with any parent
    return -1;
}

  /* print_solution
   * Input: Pointer to an array filled with Parents,
   * the total number of parents in the array, and the result
   * from find_parent()
   * Description: Print out whether an unbroken chain of calls
   * is possible, and if so, how long it would take
   * Output: None (void)
   */
void print_solution(Parent *parent_list, int num_parents, int result)
{
    //If find_parent() was unable to find an unbroken chain
    if(result == -1)
    {
        cout << "Curse you, Harold Hacker!" << endl;
    }
    else
    {
        //Loop through parents, setting is_dialed values
        //to false
        for(int j = 0; j < num_parents; j++)
        {
            parent_list[j].is_dialed = false;
        }
        //Create total_time to hold the total time the chain
        //of calls will take, a temp_parent to hold the next
        //parent in the chain, and update total_time with the 
        //first parent's call time
        int total_time = 0;
        Parent *temp_parent = parent_list[result].recipient;
        total_time += parent_list[result].time;
        parent_list[result].is_dialed = true;
        for(int i = 0; i < num_parents; i++)
        {
            //If the current caller's recipient has been dialed,
            //do not add the caller's time to total_time
            if(temp_parent->recipient->is_dialed == true)
            {
                continue;
            }
            //Otherwise add the current caller's time to
            //total_time and set the caller's is_dialed
            //variable to true
            else if(temp_parent->is_dialed == false)
            {
                 total_time += temp_parent->time;
                 temp_parent->is_dialed = true;
            }
            //Get the next parent in the chain
            temp_parent = temp_parent->recipient;
        }
        cout << "Starting with " << parent_list[result].name << 
        " the phone tree will succeed in " 
        << total_time << " seconds!" << endl;
    }
}


