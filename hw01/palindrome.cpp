//palindrome.cpp
// Purpose: This program determines if a given word is a palindrome,
//a partial palindrome, or not a palindrome.
// Written by: Zach Meyers | zmeyer02 | 02/02/23
#include <iostream>
#include <string>

using namespace std;
string next_word()
{
    string word;
    cout << "Please enter a word: ";
     //Assign user input to word
    cin >> word;
    return word;
}
int typeOfPalindrome(string word)
{
    //Define len for the for loop, and a counter of the number 
    //of letters shared by the front and back of the word
    int len = word.length() / 2;
    int shared_letters = 0;
    //Tracks if there is no longer a palindrome match
    bool broke = false;
    for (int i=0; i<len; i++)       
    {
        //Loop through the front and back of the word until reaching the middle
        if(word[i] == word[word.length() - i - 1])
        {
            //Match
            shared_letters++;
        }
        else
        {
            //No match
            broke = true;
            break;
        }
    }
    if (!broke)
    {
        //Palindrome
        return 2;
    }
    else if (broke && shared_letters >= 3)
    {
        //Partial palindrome
        return 1;
    }
    else
    {
        //Not a palindrome
        return 0;
    }
}

int main()
{
    //Initialize word variable and request user to input a word
    string word;
    bool first_run = true;
    int palindromeType = 0;
    cout << "Greetings! I am the palindrome decider!" << endl;
    while (first_run || palindromeType > 0)
    {
        //If it is the user's first time running the program, 
        //or if the previous word was (partially or fully) a palindrome
        first_run = false;
        //Take user input from next_word() function and assign it to word variable
        word = next_word();
        //Call the typeOfPalindrome function
        palindromeType = typeOfPalindrome(word);
        if(palindromeType == 1)
        {
            //Partially a palindrome
            cout << "Not quite a palindrome, but close enough." << endl;
        }
        else if(palindromeType == 2)
        {
            //Palindrome
            cout << "Your word is a palindrome! Fantastic!" << endl;
        }
    }
    //When the word is no longer a palindrome
    cout << "Your word is NOT a palindrome. Thanks anyway!" << endl;
    return 0;
    
}
