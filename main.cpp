#include <limits>
#include <algorithm>
#include "Node.h"
#include "LinkedList.h"
#include "Helper.h"
#include <map>

using std::map;
using std::vector;
using std::string;
using std::cin;
using std::cout;
using std::endl;
using std::stoi;
using std::to_string;

template<typename T>
void vectorPrint(vector<T>& v) {
  for (auto& element : v) {
    std::cout << element << " ";
  }
  std::cout << "\n";
}

int main(int argc, char ** argv){
    
    // assume inputs are of correct format
    //Get number of queries
    if (argc ==1 || argc ==3 || argc==4){
        //argc is 4 when testing with text file input, 3 when take 2 files and run in terminal
    //     int n=0;
    //     string numInp="";
    //     if (argc==3) cout << "File names:\t" << argv[1]<<", "<< argv[2]<<endl;
    //     cout << "Enter number of queries:\t";
    //     getline(cin,numInp);
    //     n=stoi(numInp);
    //     for (int i=0; i < n;i++){    //Get input
    //         int nNodes=0;
    //         vector<string> ins = takeInput( nNodes);
    //         nNodes=stoi(ins.back());
            
            
    //         //Take in the list of nodes value   
    //         vector<int> arr; //vector that holds the node values
    //         cout << "Total number of nodes:\t"<< nNodes<<"\n";
    //         for (int i = 0; i < nNodes; i++){
    //             arr.push_back(stoi(ins[i].c_str()));
    //         }
    //         //Make a linked list object using above values
    //         LinkedList ll(arr,nNodes);
    //         //Operations to be performed
    //         string order = ins[nNodes];
    //         if (order == "AF") ll.addFront(stoi(ins[nNodes + 1].c_str()));
    //         else if (order == "AE") ll.addEnd(stoi(ins[nNodes + 1].c_str()));
    //         // else if (order == "AP") ll.addAtPosition(stoi(ins[nNodes + 1].c_str()), stoi(ins[nNodes + 2].c_str()));
    //         else if (order == "DF") ll.deleteFront();
    //         else if (order == "DE") ll.deleteEnd();
    //         else if (order == "DP") ll.deletePosition(stoi(ins[nNodes + 1].c_str()));
    //         else if (order == "S") ll.search(stoi(ins[nNodes + 1].c_str()));
    //         else if (order == "GI") ll.getItem(stoi(ins[nNodes + 1].c_str()));
    //         else cout << "Invalid command\n";
    //         //Print out result
    //         ll.printItems();
    //     }
    // }else{
    //     //Incorrect number of file inputs
    //     cout << "Expect 2 file inputs!\n";
    //     cout << "Usage: ./main coin.dat food.dat\n";
    // }
        cout <<"The following is for demonstration purposes, to be removed.\n";
        cout << "No input is required.\n";
        Helper helperObject; // Create an instance of Helper
        //Initialize the coins denom
        vector<int> coinsExample={1,4, 7,9};
        for (int i=0;i<7;i++){
            coinsExample.push_back(coinsExample[i]*10);
        }
        vector<int> coinCounts(coinsExample.size(),DEFAULT_COIN_COUNT);
        cout <<"current coins denominator:\t";vectorPrint(coinsExample);
        cout <<"current amounts:\t";vectorPrint(coinCounts);

        vector<int> changeTest={2,135,502,4750,5210};
        for (auto& n:changeTest){
            cout <<"For n = "<<n<<endl;
            int changes=helperObject.change_making(coinsExample,coinCounts,n);
            if (changes > 0){
                cout <<"New count:\n\t";
                vectorPrint(coinCounts);
            }
        }
        cout << "Dummy food item map:\n";
        //Inplace of reading input from file:
        map<string, vector<string>> foods;
        foods["F0001"]={"F0001","Name1","Desc1","8.50"};
        foods["F0003"]={"F0003","Name3","Desc3","28.50"};
        foods["F0002"]={"F0002","Name2","Desc2","18.50"};
        // Map to keep references to the food items
        map<int, shared_ptr<Node>> refMap;
        LinkedList foodList;
        //Only do this once is sure the input is valid!
        //Put in try catch to handle missed invalid input that cause access problems
        for (auto& k:foods){
            cout <<k.first <<" ";
            vectorPrint(k.second);
            // Creating a shared_ptr FoodItem
                auto newFoodItem = make_shared<FoodItem>(k.second[0], k.second[1], k.second[2], stod(k.second[3])*100);

            // Add to LinkedList and store in map for reference
            refMap[stoi(k.second[0].substr(k.second[0].length()-3,3))]=foodList.addEnd(newFoodItem);
        }
        string userInput="";
        bool keepGoing = true;
        while (keepGoing) {
            cout << "Enter a food item key , or 'X' to stop): ";
            std::getline(std::cin, userInput);
            keepGoing = ! ((userInput=="X") || (userInput=="x")) ;
            // Validate input
            if (keepGoing){
                int key = 0;
                try {
                    key = stoi(userInput);
                    if (key <= 0) {
                    throw std::invalid_argument("Invalid key: Must be a positive integer.");
                    }
                } catch (const std::invalid_argument& e) {
                    std::cerr << "Error: " << e.what() << endl;
                
                } catch (const std::out_of_range& e) {
                    std::cerr << "Error: Input value out of range." << std::endl;
                }

                // Check if key exists in refMap
                if (refMap.count(key) == 0) {
                    std::cerr << "Error: Key " << key << " not found in reference map." << endl;
                    continue; // Skip to next iteration if key doesn't exist
                }

                // Access the corresponding FoodItem using the key
                shared_ptr<Node> nodePtr = refMap[key];
                if (nodePtr)  nodePtr->dataFood->printInfo();
                else std::cerr << "Error: Unexpected error retrieving FoodItem." << std::endl;
            }
        }

    }
    else{
        //Incorrect number of file inputs
        cout << "Expect 2 file inputs!\n";
        cout << "Usage: ./main coin.dat food.dat\n";
    }
}