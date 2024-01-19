/*
 * baby_g.cpp
 * purpose:
 * author:
 * last modified:
 */

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main(int argc, char *argv[])
{
    if (argc < 2) {
        cerr << "ERROR: A filename must be specified as the first argument.\n";
        exit(EXIT_FAILURE);
    }

    bool valid_braces = true;

    /* DO NOT MODIFY THE CODE ABOVE OR BELOW THIS COMMENT BLOCK */
    /*                  YOUR CODE GOES HERE                     */
    ifstream infile;
    infile.open(argv[1]); 
    /* Error check */
    if (!infile.is_open())
    {
        cerr << "ERROR: Error opening file - ";
        cerr << "please check that you specified the correct file name\n";
        exit(EXIT_FAILURE);
    }
    char next_char;
    int open_braces = 0;
    int closed_braces = 0;
    infile >> next_char;
    while (!infile.eof())
    {
        if(next_char == '{')
        {
            open_braces++;
        }
        else if(next_char == '}')
        {
            closed_braces++;
            if(closed_braces > open_braces)
            {
                valid_braces = false;
                break;
            }
        }
        infile >> next_char;
    }
    if(open_braces != closed_braces)
    {
        valid_braces = false;
    }
    infile.close();

    /* DO NOT MODIFY THE CODE ABOVE OR BELOW THIS COMMENT BLOCK */

    if (valid_braces) {
        cout << "Baby G approves!" << endl;
    } else {
        cout << "Baby G does NOT approve!" << endl;
    }

    return 0;
}
