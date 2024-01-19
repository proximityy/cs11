/*
 * midterm.cpp
 * purpose: lab 07
 * author: zach meyers
 * last modified: 03/15/23
 */

#include <iostream>
#include <fstream>

using namespace std;
int add(int input1, int input2);
int subtract(int input1, int input2);
int multiply(int input1, int input2);
int modulu(int input1, int input2);


int main()
{
    // Part I: Functions
    int result_1 = 5 * 6 - 10 % 4 * 3 + 2 - 10 + 9 % 5 + 5;
    cout << result_1 << endl;
    int p1 = subtract(multiply(5,6),multiply(modulu(10,4),3));
    int p2 = add(add(subtract(2,10),modulu(9,5)),5);
    cout << p1 + p2 << endl;


    int result_2 = ((2 + 5) * 6 - 10 % 4) * (3 + (6 - 4)) + 9 % 5 - 15;
    int q1 = subtract(multiply(add(2,5),6),modulu(10,4));
    int q2 = add(3,subtract(6,4));
    int q3 = multiply(q1, q2);
    int q4 = subtract(add(q3,modulu(9,5)),15);
    cout << q4 << endl;
    cout << result_2 << endl;

    // Part II: Pointers
    int trix[4][6];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 6; j++) {
            trix[i][j] = (i * 6) + j;
        }
    }

    int *x = &trix[1][1];
    int **y = &x;
    int ***z = &y;

    // DO NOT UNCOMMENT THESE UNTIL YOU HAVE COMPUTED THE ANSWER ON PAPER
    cout << trix[3][5] << endl;
    cout << *(x + 2) << endl;
    cout << x[6] << endl;
    cout << *((*y) - 1) << endl;
    cout << (*(*z))[1] << endl;
    cout << *((*(&x)) + 12) << endl;
    cout << z << endl;

    return 0;
}

int add(int input1, int input2)
{
    return input1 + input2;
}
int subtract(int input1, int input2)
{
    return input1 - input2;

}
int multiply(int input1, int input2)
{
    return input1 * input2;

}
int modulu(int input1, int input2)
{
    return input1 % input2;

}