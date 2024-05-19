#include "Helper.h"

Helper::Helper(){

}
int Helper::change_making(vector<int>& coins, vector<int>& counts, int n) {
    
    int numCoins = coins.size();
    
    vector<int> m(n + 1, numeric_limits<int>::max());
    // Use 2D vector of size (n+1) for tracking used coins 
    vector<vector<int>> used_coins(n + 1);

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
    if (m[n] == numeric_limits<int>::max() || m[n] == numeric_limits<int>::min()) {
        cout << "Not possible to do transaction" << endl;
        return 0;
    }   

    // Compute the count of each coin used
    vector<int> coinUsage(numCoins, 0);
    for (int idx : used_coins[n]) {
        coinUsage[idx]++;
    }

    // Update counts directly within the loop for efficiency
    cout << "Minimum coins used: " << m[n] << endl;
    cout << "Coins used:" << endl;
    for (int i = 0; i < numCoins; ++i) {
        if (coinUsage[i] > 0) {
            cout << coins[i] << " x " << coinUsage[i] << ", ";
            counts[i] -= coinUsage[i];
        }
    }
    cout<<endl;

    // // Print remaining counts conditionally to avoid unnecessary output
    if (any_of(counts.begin(), counts.end(), [](int count) { return count > 0; })) {
        cout << "Remaining coin counts:" << endl;
        for (int i = 0; i < numCoins; ++i) {
            if (counts[i] > 0) {
                cout << coins[i] << ": " << counts[i] << endl;
            }
        }
    }
    
    return 1;
}

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

bool Helper::isNumber(string number) {
    bool checkingNumber = true;
    bool isNumber = true;

    while (checkingNumber) {
        for (long unsigned int i = 0;i < number.size();i++) {
            if (isdigit(number[i])) {
                isNumber = true;   
            }
            else {
                isNumber = false;
                checkingNumber = false;
            }
        }
        checkingNumber = false;
    }
    return isNumber;
}

bool Helper::strSmaller(string& AA, string& B) {
    size_t lenA = AA.length();
    size_t lenB = B.length();
    size_t minLength = std::min(lenA, lenB);
    bool smaller=true;
    for (size_t i = 0; i < minLength; ++i) {
        if (AA[i] >= B[i] && smaller) {
            smaller=false;
        }
    }
    return smaller;
}