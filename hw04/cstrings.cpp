/* 
 * cstrings.cpp
 * Purpose: Determine if any word in an input file
 * is a substring of another word in the same line
 * using cstrings 
 * Author: Zach Meyers | zmeyer02 | started 02/22/23
 */
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <cctype> //Lets us use the isalpha function

using namespace std;

const int SIZE = 50;
int read_line(ifstream &infile, char words[SIZE][SIZE]);
bool is_equal(char *word1, char *word2);
bool is_prefix(char *word1, char *word2);
char *find_substring(char *haystack, char *needle);

int main(int argc, char *argv[])
{
    if (argc < 2) {
        cerr << "ERROR: A filename must be specified as the first argument.\n";
        exit(EXIT_FAILURE);
    }

    /* Open the file */
    ifstream infile;
    infile.open(argv[1]);

    /* Error check */
    if (infile.fail()) {
        cerr << "ERROR: Error opening file - ";
        cerr << "please check that you specified the correct file name\n";
        exit(EXIT_FAILURE);
    }

    int total_words = 0;
    char words[SIZE][SIZE];
    total_words = read_line(infile, words); //Read the first line from the file
    while (!infile.eof()) {
        //Loop through each line, taking one word at a time
        //and substring-checking it against all other words
        for(int i=0; i<total_words; i++)
        {
            for(int j=0; j<total_words; j++)
            {
                if(find_substring(words[i],words[j]) != nullptr)
                {
                    cout << words[j] << " is a substring of " << words[i] << endl;
                }
            }
        }


        //Read the next line from the file
	    total_words = read_line(infile, words);
    }
    /* Close the file */
    infile.close();
}

/* is_equal
 * Arguments: two pointers to C-style strings
 * Description: determines if two C-style strings are equivalent
 * Return value: true if strings are equivalent, false otherwise
 */
bool is_equal(char *word1, char *word2)
{
    //Declare a variable the length of word1,
    //and loop through word1 to determine its length
    int length_1 = 0;
    while(word1[length_1] != '\0'){length_1 += 1;}
    for(int i = 0; i < length_1; i++)
    {
        //Check each character in word1 against word2
        if (word1[i] != word2[i])
        {
            return false;
        }

    }
    return true;
}

/* is_prefix
 * Arguments: two pointers to C-style strings
 * Description: determines if string word2 is a prefix of string word1
 * Return value: true if word2 is a prefix of word1, false otherwise
 */
bool is_prefix(char *word1, char *word2)
{
    //Declare variables to hold the length of word1 and word2,
    //and loop through the words to find their length
    int length_1 = 0;
    int length_2 = 0;
    while(word1[length_1] != '\0'){length_1 += 1;}
    while(word2[length_2] != '\0'){length_2 += 1;}
    //Create a temp cstring to hold a substring of word1,
    //and loop through it so temp holds the same size as word2
    char temp[length_2 + 1];
    for (int i = 0; i < (length_2); i++)
    {
        temp[i] = word1[i];
    }
    temp[length_2] = '\0';
    //Pass temp and word2 to is_equal()
    return is_equal(temp,word2);
}

/* find_substring
 * Arguments: two pointers to C-style strings
 * Description: determines whether string 'needle' is a proper substring of
 *              string 'haystack'.
 * Return value: if 'needle' isn't a proper substring of 'haystack', return
 *               nullptr. Otherwise, return a pointer to the beginning of the
 *               first occurrence of 'needle' within 'haystack'.
 */
char *find_substring(char *haystack, char *needle)
{
    //Loop through haystack and needle to determine their lengths
   int length_haystack = 0;
   int length_needle = 0;
   while(haystack[length_haystack] != '\0')
   {
    length_haystack++;
   }
   while(needle[length_needle] != '\0')
   {
    length_needle++;
   }
   //If needle is too long, return nullptr
   if(length_haystack <= length_needle)
   {
    return nullptr;
   }
    //Loop through haystack one character at a time
   for(int i = 0; i<(length_haystack - length_needle + 1); i++)
   {
    //Create a temp cstring to hold different substrings of haystack
        char temp[length_haystack - i + 1];
        
        for (int j = 0; j < (length_haystack - i); j++)
        {
            //Fill temp with a haystack substring
            temp[j] = haystack[j+i];
        }
        temp[length_haystack-i] = '\0';
        //If is_prefix() returns true, return the pointer
        if(is_prefix(temp, needle))
        {
            return (haystack + i);
        }
        else
        {
            continue;
        }
   }
   //If no substring is found, return nullptr
    return nullptr;
}

/* Retrieve a line of input from a file, parse it into individual words, and
 * store those words in the "words_in_sentence" 2D-array. Each "row" of
 * words_in_sentence is another word. Return the total number of words read in.
 *
 * For example, if we read in the sentence "Here I am!", then the
 * first 3 rows (R) and first 5 columns (C) of the words_in_sentence array
 * will look like the picture belwo (the empty cells hold garbage values):
 *
 *        C0   C1   C2   C3   C4
 * R0:  | H  | e  | r  | e  | \0 |
 * R1:  | I  | \0 |    |    |    |
 * R2:  | a  | m  | \0 |    |    |
 *
 * NOTE: We have to write "ifstream &infile" as a parameter to pass an input
 * file stream correctly to a function (without needing even more pointers). If
 * you need to write a function that takes a file stream as an argument, always
 * put the '&' in front of the name of your file stream parameter.
 */
int read_line(ifstream &infile, char words_in_sentence[SIZE][SIZE])
{
    int spot = 0;
    int word_index = 0;
    char *next_word;
    char next_char;

    infile.get(next_char);
    while (!infile.eof() && next_char != '\n') {
        next_word = words_in_sentence[word_index];
        //Written question 1 asks about this loop
        while (!infile.eof() && isalpha(next_char)) {
            //Written question 2 asks about the line below
	        next_word[spot] = next_char;
            ++spot;
            infile.get(next_char);
        }
        if (spot > 0) {
            next_word[spot] = '\0';
            ++word_index;
            spot = 0;
        } else {
            infile.get(next_char);
        }
    }
    return word_index;
}
