// my_ing.cpp
// Purpose: This program decides whether a user-provided
//          word ends in the suffix "ing"
// Written by: Zach Meyers | zmeyer02

#include <iostream>
#include <string>

using namespace std;

int main()
{
    string word;
    cout << "Greetings! I am the \"ing\" decider!" << endl;
    cout << "Please enter a word: ";
    cin >> word;
    if (word.length() >= 3 && word[word.length()-1] == 'g' && word[word.length()-2] == 'n' && word[word.length()-3] == 'i')
    {
        cout << "Your word ends in \"ing\"! Fantastic!" << endl;
    }
    else
    {
        cout << "Oh no! I think you meant " << word << "-ing!" << endl;
    }

    return 0;
}
