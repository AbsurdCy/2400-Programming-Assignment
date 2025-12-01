
/*  The author(s) acknowledge the utilization of ChatGPT-5,
    a language model developed by OpenAI, in the preparation of this assignment. 
    ChatGPT was employed in the following manner(s) within this assignment: 

    - help check how to read files in c++ and stripping characters */

    /* CREDIT STATEMENT:
    Our group only worked with the members of our group,
    no outside help or aid from other groups or a TA was used
    on this programming assignment. */

#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <cmath>

using namespace std;

// retrueve costs from line in file
vector<double> retrieveCosts(string line) {

    vector<double> costs;
    string cleanData =line.substr(1, line.length()-2); 
    stringstream ss(cleanData);

    char delimiter;
    int cityID;
    double cost;


    while (ss >> delimiter) {
        if (delimiter =='('){
            ss >> cityID >> delimiter >> cost >> delimiter;
            costs.push_back(cost);

        }
    }

    return costs;
}

int max_cities(double B, vector<double>& costs){


    int n= costs.size();

    // convert to cents
    int BCents = int(B*100); 
    vector<int> cCents;
    for (int i=0 ;i<n; i++){
    cCents.push_back(int(costs[i]*100));
    }


    vector<vector<int>> D(n+1, vector<int>(BCents +1,0));
    
    for (int i=1; i<=n; i++){
        for (int c=1; c<=BCents; c++){
            
            // cost > budget then skip
            if (cCents[i-1] > c){ 
                D[i][c] = D[i-1][c]; 

            }
            

            // max of skip or visit
            else{
                D[i][c] = max(D[i-1][c],D[i-1][c -(cCents[i-1])]+1); 
            }
        }

    }
    return D[n][BCents];
}

int main(){

    ifstream inFile("roundtrip_costs.txt");
    ofstream outFile("trip_nums.txt");

    double budget =5000.00;
    string line;
    int lineCount=1;
    while (getline(inFile, line)) {

            // cout for debug
            cout<< "Processing line: " << lineCount << endl;
            lineCount++;
            // cout << "Line data: " << line << endl; (debug)
            vector<double> costs = retrieveCosts(line);
            int maxCities = max_cities(budget,costs);
            cout << "Max cities: "<< maxCities << endl;
            outFile << maxCities << endl;
        
    }

    inFile.close();
    outFile.close();

    return 0;
}