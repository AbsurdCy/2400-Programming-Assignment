
/* CREDIT STATEMENT:
    Our group only worked with the members of our group,
    no outside help or aid from other groups or a TA was used
    on this programming assignment. */

    
/*  The author(s) acknowledge the utilization of ChatGPT-5,
    a language model developed by OpenAI, in the preparation of this assignment. 
    ChatGPT was employed in the following manner(s) within this assignment: 

    - help check how to read files in c++
    - help measuring runtimes for each sorting algorithm
        - note: code was not directly pasted from AI, it was used as a reference,
        and only used in those sections. */

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <chrono>

using namespace std;

struct flight {
    int dest_id;
    double time;
    double cost;
};

// sorts connected cities by time using bubble sort
void bubbleSortTime(vector<flight>& flights, int& runtime) {
    // starts chrono runtime measurement
    auto start = chrono::high_resolution_clock::now();

    int n = flights.size();

    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            // swap if needed
            if (flights[j].time > flights[j + 1].time) {
                flight temp = flights[j];
                flights[j] = flights[j + 1];
                flights[j + 1] = temp;
            }
        }

    }
    // ends chrono runtime measurement
    auto end = chrono::high_resolution_clock::now();
    runtime = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
}


// sorts connected cities by cost using bubble sort
void bubbleSortCost(vector<flight>& flights, int& runtime) {
    auto start = chrono::high_resolution_clock::now();

    int n = flights.size();

    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (flights[j].cost > flights[j + 1].cost) {
                flight temp = flights[j];
                flights[j] = flights[j + 1];
                flights[j + 1] = temp;
            }
        }
    }
    auto end = chrono::high_resolution_clock::now();
    runtime = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
}
// retrieves flight data from file
vector<vector<flight>> retrieveAllFlights(){

    vector<vector<flight>> allFlights;
    ifstream inFile("flights.txt");

    if (!inFile) {
        cout << "Err opening flights.txt" << endl;
        return allFlights;
    }

    string line;

    // loop thru each line of the file
    while (getline(inFile, line)) {

        vector<flight> flightList;
        string cleanData = line;
        cleanData = cleanData.substr(1, cleanData.length() - 2);
        stringstream ss(cleanData);
        string flightStr;
        

        while(getline(ss, flightStr, '(')) {
            if (flightStr.length() == 0 || flightStr == ",") {
                continue;
            }

            flight flightEntry;
            stringstream flightStream(flightStr);
            char delimiter;
            // reads info from file into flight attributes
            flightStream >> flightEntry.dest_id >> delimiter >> flightEntry.time >> delimiter >> flightEntry.cost;
            flightList.push_back(flightEntry);
        }
        allFlights.push_back(flightList);
    }
    inFile.close();
    return allFlights;

}

// outputs the sorted flight data to a file
void writeFlights(ofstream& outFile, const vector<flight>& flights){
    outFile << "[";
    for (int i = 0; i < flights.size(); ++i) {
        outFile << "(" << flights[i].dest_id << ", " << fixed << setprecision(2) << flights[i].time << ", " << fixed << setprecision(2) << flights[i].cost << ")";
        if (i != flights.size() - 1) {
            outFile << ", ";
         }
    }
    outFile << "]" << endl;
}


int main() {
    
    vector<vector<flight>> allFlights = retrieveAllFlights();

    ofstream timeBubFile("FtimeBubSort.txt");
    ofstream costBubFile("FcostBubSort.txt");
    ofstream runtimeFile("runtimes.txt");

    // loop thru each city flight list and sort by time and cost and print to file
    for(int i=0; i < allFlights.size(); i++){
    

        int bubTimeRuntime = 0;
        int bubCostRuntime = 0;

        vector<flight> flightsByTime = allFlights[i];
        vector<flight> flightsByCost = allFlights[i];

        bubbleSortTime(flightsByTime, bubTimeRuntime);
        writeFlights(timeBubFile, flightsByTime);
        
        bubbleSortCost(flightsByCost, bubCostRuntime);
        writeFlights(costBubFile, flightsByCost);

        runtimeFile << "(" << i << ", " << bubTimeRuntime << " ns" << ", " << bubCostRuntime << " ns" << ")" << endl;

    }


    timeBubFile.close();
    costBubFile.close();
    runtimeFile.close();

    cout << "Sorting Completed, output files generated" << endl;
    return 0;
}
