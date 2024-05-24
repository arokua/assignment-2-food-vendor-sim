#ifndef HELPER_H
#define HELPER_H

#include <vector>
#include <iostream>
#include <limits>
#include <algorithm>
#include <string>
#include <cctype>

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
    ~Helper(); //Default destructor

    vector<string> takeInput(int);
    template<typename T>
    void vectorPrint(const vector<T>& v) {
        for (const T& item : v) {
            cout << item << endl;
        }
    }

    //Compare if string A is lexographically smaller than string B
    //By default, if length of string A is smaler than B then
    // It is consider smaller, hence 
    //Butch might be insert to the begginning of a linked list 
    // Starting with Baklava despite the letter u comes after the letter a
    static bool strSmaller(string &AA, string& B);
    
    //Splits a string into a vector
    static void splitString(string s, vector<std::string>& tokens, string delimeter);

    //Checks if a string is completely numeric
    static bool isNumber(std::string number);

};

#endif //HELPER_H