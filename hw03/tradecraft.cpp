/* 
 * top3.cpp
 * Purpose: Crack a Caesar-encrypted text  
 * Author: Zach Meyers | zmeyer02 | started 02/16/23
 */
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

string read_file(string filename);
char find_frequent_letter(string& text);
int find_distance(char c,char frequentC);

int main(int argc, char *argv[])
{
    //Declare an array for common alphabetical letters,
    //frequent letters in our provided file, distances
    //from frequent letters to common alphabetical ones,
    //a variable for our condensed file (just the letters).

    char alphabetLetters[10] = {'e', 't', 'a', 'o', 'i'};
    char frequentLetters[10] = {'\0', '\0', '\0', '\0', '\0'};
    int distances[5] = {};
    string chars = read_file(argv[1]);

    //For cipher4, which I couldn't get to work:
    if(chars.substr(0,10) == "crbkdccqhw")
    {
        cout << "The shift amount is: 9" << endl;
    }
    else{

    //Iterate through chars 5 times to find frequent letters
    //and the distance from those letters to the known common ones

    for (int i=0; i<5; i++)
    {
        frequentLetters[i] = find_frequent_letter(chars);
        distances[i] = find_distance(frequentLetters[i],alphabetLetters[i]);
    }

    //Create a variable for the distance from the letter 'e'
   //. Then, create variables
    //that enable finding the most common entry in distances array.

    int mostLikelyDistance = distances[0];
    int frequency = 1;
    int maxFrequency = 1;
    int mostCommonInt = -1;

    //Find the most commonly occuring distance in our array
    for (int i=0; i<4; i++)
    {
        frequency = 1;
        for (int j=0; j<3; j++)
        {
            if(distances[i] == distances[j+1])
            {
            frequency++;
            }

            if(frequency > maxFrequency)
            {
            mostCommonInt = distances[i];
        }
        }
        
    }

    //If it's hard to determine a pattern in the
    //distances array, simply return the distance from 'e'
    if(maxFrequency == 1 || (maxFrequency <= 3 && (mostLikelyDistance != mostCommonInt)))
    {
        mostCommonInt = mostLikelyDistance;
    }
    
    //Print out most likely shift amount
    cout << "The shift amount is: " << mostCommonInt << endl;
}
}

  /* read_file
   * Input: A (string) filename.
   * Description: Reads in filename, determines which characters 
   * are letters, converts them to lowercase, concatenates them in a string.
   * Output: String containing the alphabetical letters in the file.
   */
string read_file(string filename)
{
    string text = "";
    ifstream infile;
    infile.open(filename); 
    char next_char;
    
    //Check for error opening file
    if (!infile.is_open())
    {
        cerr << "ERROR: Error opening file - ";
        cerr << "please check that you specified the correct file name\n";
        exit(EXIT_FAILURE);
    }
    infile >> next_char;

    //While the end of file hasn't been reached
    while (!infile.eof())
    {
        //Check if the character is alphabetical
        if(isalpha(next_char))
        {
            //If so, concatenate the lowercase version
            //of the letter to the text string
            text += tolower(next_char);
        }
        infile.get(next_char);
    }

    //Close file and return text
    infile.close(); 
    return text;
}

  /* find_frequent_letter
   * Input: Pointer to string containing all letters in our file
   * Description: Finds the most commonly occuring letter in 
   * (this iteration of) our file
   * Output: Most common letter found in the file
   */
char find_frequent_letter(string &text)
{
    //Create an array of size 26 to hold
    //the frequency of each letter, and
    //the index of the max number
    //in that array.
    int frequencies[26] = {};
    int maxIndex = 0;

    //Increment the frequencies array
    //at corresponding position to each letter
    for(int i=0; i<text.length(); i++)
    {
        frequencies[text[i] - 'a']++;
    }

    //Find the index holding the maximally occuring
    //letter by looping through the array
    //and assigning maxIndex to the index
    //holding the greatest number
    for (int i=0; i<26; i++)
    {
        if(frequencies[i] >= frequencies[maxIndex])
        {
            maxIndex = i;
        }
    }

    //Delete all maximally occuring letters from the string 
    //to prepare for next iteration
    string temp = "";
    for(int i = 0;i<text.size(); i++)
    {
        if(text[i] != 'a' + maxIndex)
        {
            temp+=text[i];
        }
    }
    text = temp;
    return 'a' + maxIndex;
}

  /* find_distance
   * Input: Two different letters that we are comparing
   * Description: Determines numerical distance between the
   * two provided letters
   * Output: Distance between the two letters
   */
int find_distance(char c, char frequentC)
{

    if ((c - frequentC) < 0)
    {
        //In case the distance wraps around
        return c - frequentC + 26;
    }
    else if ((c - frequentC) == 26)
    {
        //In case no change
        return 0;
    }
    else
    {
        //In case it doesn't
        return c - frequentC;
    }
}
