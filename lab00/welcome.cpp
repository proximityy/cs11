// welcome.cpp
// Purpose: Welcome the squad to their new favorite class.
// Written by: Megan Monroe (mmonroe)
// Edited by: Richard Townsend (rtowns01)
// Date Edited: 8/1/2022

#include <iostream>
#include <string>

using namespace std;

int main() {
  string name;
  
  // Get the user's name
  cout << endl;
  cout << "Hello!";
  cout << endl;
  cout << "Please enter your name: ";
  cin >> name;
  
  // Print the welcome message
  cout << endl;
  cout << "Hi " << name << "!" << endl;
  cout << "I love turtles!" << endl;
  cout << endl;
  
  return 0;
} 
