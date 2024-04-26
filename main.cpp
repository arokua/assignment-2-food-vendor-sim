#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
#include "Node.h"
#include "LinkedList.h"
#include <string>

using namespace std;
#include <iostream>
#include <vector>
#include <limits>
#include <string>
#include <algorithm>

using namespace std;
int change_making(const std::vector<int>& coins, std::vector<int>& counts, int n) {
    //Modified function based on wikipedia.org/Change_making_problem
    //This function return the minimum number of coins used to make the amount n
    //If no solution exists, it returns -1
    //The additional part to the original algorithm is that the coins set is finite
    // Thus, additional comparision is made to see if the original optimal deno is suitable
    // Then, a tracking matrix is used to keep track of all possible solutions
    int numCoins = coins.size();
    
    std::vector<int> m(n + 1, std::numeric_limits<int>::max());
    // Use 2D vector of size (n+1) for tracking used coins 
    std::vector<std::vector<int>> used_coins(n + 1);

    // Initialize the zero amount case
    m[0] = 0;

    // Fill the DP table
    for (int amount = 1; amount <= n; ++amount) {
        for (int c = 0; c < numCoins; ++c) {
            int coin = coins[c];
            if (coin <= amount) {
                if (m[amount - coin] + 1 < m[amount] && counts[c] > 0) {
                    m[amount] = m[amount - coin] + 1;
                    used_coins[amount] = used_coins[amount - coin];
                    used_coins[amount].push_back(c);
                }
            }
        }
    }

    // Check if a solution exists
    if (m[n] == std::numeric_limits<int>::max() || m[n] == std::numeric_limits<int>::min()) {
        std::cout << "No solution exists" << std::endl;
        return -1;
    }   

    // Compute the count of each coin used
    std::vector<int> coinUsage(numCoins, 0);
    for (int idx : used_coins[n]) {
        coinUsage[idx]++;
    }

    // Update counts directly within the loop for efficiency
    std::cout << "Minimum coins used: " << m[n] << std::endl;
    std::cout << "Coins used:" << std::endl;
    for (int i = 0; i < numCoins; ++i) {
        if (coinUsage[i] > 0) {
            std::cout << coins[i] << " x " << coinUsage[i] << std::endl;
            counts[i] -= coinUsage[i];
        }
    }

    // // Print remaining counts conditionally to avoid unnecessary output
    // if (std::any_of(counts.begin(), counts.end(), [](int count) { return count > 0; })) {
    //     std::cout << "Remaining coin counts:" << std::endl;
    //     for (int i = 0; i < numCoins; ++i) {
    //         if (counts[i] > 0) {
    //             std::cout << coins[i] << ": " << counts[i] << std::endl;
    //         }
    //     }
    // }

    return 0;
}

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
            // delete nNodes; // Free memory
        }
    }else{
        //Incorrect number of file inputs
        cout << "Expect 2 file inputs!\n";
        cout << "Usage: ./main coin.dat food.dat\n";
    }
    //Initialize the coins denom
    vector<int> coinsExample={5,10,20};
    for (int i=0;i<7;i++){
        coinsExample.push_back(coinsExample[i]*10);
    }
    vector<int> coinCounts(coinsExample.size(),DEFAULT_COIN_COUNT);
    cout <<"current coins denominator:\t";vectorPrint(coinsExample);
    cout <<"current amounts:\t";vectorPrint(coinCounts);

    vector<int> changeTest={2,135,502,4750,5210};
    for (auto& n:changeTest){
        cout <<"For n = "<<n<<endl;
        int changes=change_making(coinsExample,coinCounts,n);
        if (changes > 0){
            cout <<"New count:\n\t";
            vectorPrint(coinCounts);
        }
    }
}