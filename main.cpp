#include <iostream>
#include <vector>
#include "Node.h"
#include "LinkedList.h"
#include <string>

using namespace std;
//Holds the numbers of original nodes from input

vector<string> takeInput(int * nNodes){
    // Get input from console
    // Split them by spaces and store to a vector
    string in;
    vector<string> pp;
    std::cout << "";
    getline (cin, in);
    //Check whether a string has been meet
    bool metOrder = false;
    int len = in.length(); //length of input
    string temp = ""; //tempoary string
    for (int i = 0; i < len; i++){
        char current = in.at(i);
        if (current != ' '){
            temp += current;
            if ( !isdigit(current) && !metOrder){
                *nNodes = pp.size() - 1;
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
    (*nNodes)++;
    return pp;
}



int main(int argc, char ** argv){
    
    // assume inputs are of correct format
    //Get number of queries
    if (argc ==1 || argc ==3){
        //ar
        int n=0;
        string numInp="";
        if (argc==3) cout << "File names:\t" << argv[1]<<", "<< argv[2]<<endl;
        while (n < 1){
            cout << "Enter number of queries:\t";
            getline(cin,numInp);
            n=stoi(numInp);
        }
        for (int i=0; i < n;i++){    //Get input
            int * nNodes=new int(0);
            vector<string> ins = takeInput( nNodes);
            
            //Take in the list of nodes value   
            vector<int> arr; //vector that holds the node values
            for (int i = 0; i < *nNodes; i++){
                arr.push_back(stoi(ins[i].c_str()));
            }
            //Make a linked list object using above values
            LinkedList ll(arr,*nNodes);
            //Operations to be performed
            string order = ins[*nNodes];
            if (order == "AF") ll.addFront(stoi(ins[*nNodes + 1].c_str()));
            else if (order == "AE") ll.addEnd(stoi(ins[*nNodes + 1].c_str()));
            else if (order == "AP") ll.addAtPosition(stoi(ins[*nNodes + 1].c_str()), stoi(ins[*nNodes + 2].c_str()));
            else if (order == "DF") ll.deleteFront();
            else if (order == "DE") ll.deleteEnd();
            else if (order == "DP") ll.deletePosition(stoi(ins[*nNodes + 1].c_str()));
            else if (order == "S") ll.search(stoi(ins[*nNodes + 1].c_str()));
            else if (order == "GI") ll.getItem(stoi(ins[*nNodes + 1].c_str()));
            else cout << "Invalid command\n";
            //Print out result
            ll.printItems();
            delete nNodes; // Free memory
        }
    }else{
        //Incorrect number of file inputs
        cout << "Expect 2 file inputs!\n";
        cout << "Usage: ./main coin.dat food.dat\n";
    }
}