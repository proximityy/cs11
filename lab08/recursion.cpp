// recursion.cpp
// Purpose: Get practice solving problems recursively!
// Starter Code Written by: Richard Townsend (rtowns01)

#include <iostream>
#include <string>

using namespace std;

void print_menu();
void call_power();
void call_reverse();
void call_subseq();

//Recursive functions to try and implement
int power(int n, int k);
void print_reverse(string s);
bool subseq(string s, string t); //Extra challenge!

int main()
{
    int choice;

    //Display the menu and get a user's choice
    cout << "Welcome to the recursion program!" << endl;
    print_menu();
    cin >> choice;

    //Perform an execute-and-prompt cycle
    while (choice != 0) {
        //Error checking -- make sure they give me an integer I can handle
        if (choice > 3 || choice < 0) {
            cout << "Please provide an integer between 0 and 3 as an option: ";
        }
        //Run the function the user requested
        else if (choice == 1) {
            call_power();
        } else if (choice == 2) {
            call_reverse();
        } else {
            call_subseq();
        }
        //Print the menu again and get the user's next choice
        print_menu();
        cin >> choice;
    }
    return 0;
}

/* Print out a menu of options for the user */
void print_menu()
{
    cout << "Here are the recursive functions you can run:" << endl;
    cout << "1. power" << endl;
    cout << "2. print_reverse" << endl;
    cout << "3. subseq" << endl;
    cout << "Please provide the number of a function in the list to execute";
    cout << " (0 to quit): ";
}

/* Pass two user-provided arguments to the power function. Print the result. */
void call_power()
{
    int n, k;
    cout << "Please provide the n to pass to power: ";
    cin >> n;
    cout << "Please provide the k to pass to power: ";
    cin >> k;
    cout << power(n, k) << endl;
}

/* Pass a user-provided argument to the print_reverse function. */
void call_reverse()
{
    string s;
    cout << "Please provide the string to reverse: ";
    cin >> s;
    print_reverse(s);
    cout << endl;
}

/* Pass two user-provided arguments to the subseq function. Print the result. */
void call_subseq()
{
    string s, t;
    cout << "Please provide the s to pass to subseq: ";
    cin >> s;
    cout << "Please provide the t to pass to subseq: ";
    cin >> t;
    cout << subseq(s, t) << endl;
}

/* Compute and return the result of n raised to the power of k.
 * You can assume that k is a non-negative integer. */
int power(int n, int k)
{
    if(k == 0)
    {
        return 1;
    }
    return n * power(n,k-1);
}

/* Print out the string s backwards. */
void print_reverse(string s)
{
    if(s.length() == 1)
    {
        cout << s;
    }
    else
    {
        cout << s.substr((s.length() - 1));
        print_reverse(s.substr(0, s.length() - 1));
    }
}

/* Return true if string s is a subsequence of string t, false otherwise. */
bool subseq(string s, string t)
{
    if(s.length() == 0)
    {
        return true;
    }
    else if((t.length() == 0) && (s.length() > 0))
    {
        return false;
    }
    else if(s.substr(0,1) == t.substr(0,1))
    {
        return subseq(s.substr(1,s.length()), t.substr(1,t.length()));
    }
    else{
        return subseq(s, t.substr(1,t.length()));
    }
}
