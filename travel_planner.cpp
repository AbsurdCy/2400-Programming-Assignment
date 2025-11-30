
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
#include <cmath>

using namespace std;

struct flight {
    int dest_id;
    double time;
    double cost;
};

struct City{
    int id;
    double x;
    double y;
};

// struct to store result of closest pair
struct ClosestPairResult {
    double distance;
    City cityA;
    City cityB;
};

// function to calculate distance between two cities
double dist(const City& a, const City& b) {
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

// brute force approach for closest pair of points
double bf_closest_pair(const vector<City>& cities){
    int n = (int)cities.size();
    double best = numeric_limits<double>::infinity();
    // to store the closest pair
    City bestA, bestB;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            double d = dist(cities[i], cities[j]);
            if (d < best) {
                best = d;
                bestA = cities[i];
                bestB = cities[j];
            }
        }
    }
    ClosestPairResult result;
    result.distance = best;
    result.cityA = bestA;
    result.cityB = bestB;
    return result.distance;
}

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

//approach for divide and conquer approach
double efficient_closest_pair(vector<City>& cityX, vector<City>& cityY){

    int n = cityX.size();
    int mid = n/2;


    if (n <= 3){
        return bf_closest_pair(cityX);
    }


    else{
        double midX = cityX[mid].x;

        // divide x and y vectors into left and right
        vector<City> leftX( cityX.begin(), cityX.begin() + mid);
        vector<City> rightX( cityX.begin() + mid, cityX.end());
        vector<City> leftY, rightY;

        for (int i=0 ; i < n; i++){
            City currCity = cityY[i];
            bool inLeftX = false;
            for (int j=0; j < leftX.size(); j++){
                if (currCity.id == leftX[j].id){
                    inLeftX = true;
                    break;
                }
            }
            if (inLeftX== true){
                leftY.push_back(cityY[i]);
            } else {
                rightY.push_back(cityY[i]);
            }
        }

        // recurse to find min dist
        double distL = efficient_closest_pair(leftX, leftY);
        double distR = efficient_closest_pair(rightX, rightY);
        double shortestDistA = min(distL, distR);

        // find cities in the strip
        vector<City> stp;
        for (int i=0; i < n; i++){
            if (abs(cityY[i].x - midX) < shortestDistA){
                stp.push_back(cityY[i]);
            }
        }
        // compare distances in stp to the shortestTot
        double shortestTot = (pow(shortestDistA,2));
        int stpsiz = stp.size();
        for (int i=0; i < stpsiz; i++){
            int k = i + 1;
            while (k < stpsiz && (stp[k].y - stp[i].y) < shortestTot){
                shortestTot = min(pow(stp[k].x - stp[i].x,2) + pow((stp[k].y - stp[i].y),2), shortestTot);
                k++;
            }
        }
        
        return sqrt(shortestTot);

    }
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
    // read city input
    vector<City> cities;

    ifstream infile("cities.txt");
    while (infile) {
        City c;
        infile >> c.id >> c.x >> c.y;
        if (infile) {
            cities.push_back(c);
        }
    }
    infile.close();

    ofstream outfileBF("BF-closest.txt");
    ofstream outfileDC("DC-closest.txt");
    ofstream outfileTime("runtimes.txt");

    // loop thru each subset and find min dist
    for (int i = 50 ; i <= 100; ++i) {

        vector<City> citiesSubset(cities.begin(), cities.begin() + i);

        auto start = chrono::high_resolution_clock::now();
        double minDist = bf_closest_pair(citiesSubset);
        auto end = chrono::high_resolution_clock::now();
        outfileBF << setprecision(10) << minDist << endl;
        long long runtime1 = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        
        
        vector<City> cityX = citiesSubset;
        vector<City> cityY = citiesSubset;
        
        // sorting for dc approach
        for (int j = 0; j < cityX.size(); ++j) {
            for (int k = j + 1; k < cityX.size(); ++k) {
                if (cityX[j].x > cityX[k].x) {
                    City temp = cityX[j];
                    cityX[j] = cityX[k];
                    cityX[k] = temp;
                }
                if (cityY[j].y > cityY[k].y) {
                    City temp = cityY[j];
                    cityY[j] = cityY[k];
                    cityY[k] = temp;
                }
            }
        }
        auto start2 = chrono::high_resolution_clock::now();
        double effMinDist = efficient_closest_pair(cityX, cityY);
        auto end2 = chrono::high_resolution_clock::now();
        outfileDC << setprecision(10) << effMinDist << endl;
        long long runtime2 = chrono::duration_cast<chrono::nanoseconds>(end2 - start2).count();

        outfileTime << "Brute Force Runtime:" <<runtime1<< "ns" <<" Divide and Conquer Runtime:" << runtime2 << "ns" << endl;
    }

    outfileBF.close();
    outfileDC.close();
    outfileTime.close();
    
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
