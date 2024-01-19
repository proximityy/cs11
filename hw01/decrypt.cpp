//decrypt.cpp
// Purpose: This program decrypts a provided word encrypted 
//with a Caesar cipher by a given shift amount.
// Written by: Zach Meyers | zmeyer02 | 02/02/23
#include <iostream>
#include <string>

using namespace std;

int main()
{
    //Declare variables for the inputted word and shift amount
    string word;
    int shift_amount;
    //Request user to input encrypted word
    cout << "Enter the word that you would like to decrypt (in lowercase characters)";
    cout << endl;
    cout << "Word to decrypt: ";
    //Assign encrypted word to word
    cin >> word;
    //Request user to input shift amount
    cout << "Enter the shift amount: ";
    //Assign shift amount to shift_amount
    cin >> shift_amount;
    cout << "Decrypted word: ";
    //Declare variables for the length of the word and 
    //the character being modified at a given point, and the decrypted word
    int length_of_word = word.length();
    int pos = 0;
    string new_word = "";
    while (pos < length_of_word)
    {
        //While the letter we are analyzing is included in the word
        if (word[pos] >= ('a' + shift_amount)) 
        {
        //If the letter does not need to wrap
        new_word += word[pos] - shift_amount;
        } 
        else 
        {
        //If the letter will wrap
        new_word += word[pos] + 26 - shift_amount;
        }

    // Move to the next character
    pos++;
    }
    // Print out decrypted word
    cout << new_word << endl;
}