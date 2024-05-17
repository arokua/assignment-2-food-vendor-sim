#include "Helper.h"

#include <memory>

Helper::Helper(){}


vector<string> Helper::takeInput(int nNodes=0){
    // Get input from console
    // Split them by spaces and store to a vector
    string in;
    vector<string> pp;
    cout << "Please enter input: ";
    getline (cin, in);
    //Check whether a string has been meet
    bool metOrder = false;
    int len = in.length(); //length of input
    if (in[-1]=='\n'){
        cout << "Has newline char\n";
    }
    string temp = ""; //tempoary string
    for (int i = 0; i < len; i++){
        char current = in.at(i);
        if (current != ' '){
            temp += current;
            if ( !isdigit(current) && !metOrder){
                nNodes = pp.size() - 1;
                metOrder = true;
            }
        }
        else{
            pp.push_back(temp);
            temp ="";
        }
        if (i == len - 1){
            pp.push_back(temp);
        }
    }
    nNodes++;
    //Store nNodes value as final element of the input array
    pp.push_back(to_string(nNodes));
    return pp;
}

void Helper::splitString(string s, vector<string>& tokens, string delimiter)
{
    tokens.clear();

    // pos = current delimiter position
    // prev = previous delimiter position
    std::string::size_type pos = 0, prev = 0;

    while ((pos = s.find(delimiter, prev)) != std::string::npos) {
        if (pos != prev) {
            // take specific substring and add to the vector
            tokens.push_back(s.substr(prev, pos - prev));
        }
        
        prev = pos + delimiter.length();
    }
    if (prev < s.length()) {
        tokens.push_back(s.substr(prev));
    }
}