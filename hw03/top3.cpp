/* 
 * top3.cpp
 * Purpose: Return the top 3 numbers in a provided file  
 * Author: Zach Meyers | zmeyer02 | started 02/15/23
 */
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
const int MAX_NUMS = 25;
int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        //If user did not specify a filename
        cerr << "ERROR: Not enough arguments specified\n";
        exit(EXIT_FAILURE);
    } 
    ifstream infile;
    //Open file
    infile.open(argv[1]); 
    //Initialize array
    int nums[MAX_NUMS];
    for(int i = 0; i < MAX_NUMS; i++)
    {
        //Fill array with values of -1
        nums[i] = -1;
    }

    if (!infile.is_open())
    {
        //If infile opening error
        cerr << "ERROR: Error opening file - ";
        cerr << "Please check that you specified the correct file name\n";
        exit(EXIT_FAILURE);
    }
    //Counter represents how many numbers are in the file
    int counter = 0;
    //Next_num is a full number
    string next_num = "";
    //Char is the next digit or whitespace character from infile
    char next_char;
    infile >> next_char;
    while (!infile.eof())
    {
        if(next_char == '\n') //If whitespace character (new line)
        {
        nums[counter] = stoi(next_num);
        //Turns next_num into int and passes it to nums
        next_num = "";
        //Reset next_num and increment counter
        counter++;
        }
        else{
            //Concatenate next digit onto next_num
            next_num += next_char;
        }
        infile.get(next_char);
    }
    //Alternative code I was experimenting with:

    /* while (getline(infile, next_num))
    {
        nums[counter] = stoi(next_num);
        counter++;
    } */
    int top1 = -1;
    int index;
    for(int i = 0; (i < counter); i++)
    //Loop through array
    {
        //If the current entry is greater than the previous top,
        //Replace top1 with the current entry
        if (nums[i] > top1)
        {
            top1 = nums[i];
            index = i;
        }
    }
    //Erase the top number from nums
    nums[index] = -1;

    //Repeat the same process for 2nd and 3rd top number
    int top2 = -1;
    for(int i = 0; (i < counter); i++)
    {
        if (nums[i] > top2)
        {
            top2 = nums[i];
            index = i;
            //cout << "new highest number found of " << top2 << " with index " << index << endl;
        }
    }
    nums[index] = -1;
    int top3 = -1;
    for(int i = 0; (i < counter); i++)
    {
        if (nums[i] > top3)
        {
            top3 = nums[i];
            index = i;
            //cout << "new highest number found of " << top3 << " with index " << index << endl;
        }
    }
    cout << top1 << endl;
    cout << top2 << endl;
    cout << top3 << endl;


    infile.close(); 
    return 0;
}
