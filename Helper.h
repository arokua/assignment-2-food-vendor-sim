#ifndef HELPER_H
#define HELPER_H
#include <vector>
#include <iostream>
#include <limits>
#include <algorithm>
#include <string>

using std::vector;
using std::numeric_limits;
using std::to_string;
using std::string;
using std::cin;
using std::cout;
using std::endl;


class Helper{
public:
    Helper();//Default constructor

    //Modified function based on wikipedia.org/Change_making_problem
    //This function return the minimum number of coins used to make the amount n
    //If no solution exists, it returns -1
    //The additional part to the original algorithm is that the coins set is finite
    // Thus, additional comparision is made to see if the original optimal deno is suitable
    // Then, a tracking matrix is used to keep track of all possible solutions
    // This function needs a vector that have the denomination of the coins in numerical values
    // And a vector that contain the current amount of each denomination
    int change_making(vector<int>&coins,vector<int>&counts,int n);
    vector<string> takeInput(int);
    template<typename T>
    void vectorPrint(const vector<T>& v) {
        for (const T& item : v) {
            cout << item << endl;
        }
    }
    bool strSmaller(string AA, string B);//Compare if string A is lexographically smaller than string B, not
    //counting the length
    
    //Splits a string into a vector
    static void splitString(std::string s, std::vector<std::string>& tokens, std::string delimeter);

    //Checks if a string is completely numeric
    static bool isNumber(std::string number);

};

#endif //HELPER_H