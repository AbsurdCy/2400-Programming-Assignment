#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <chrono>
#include <cmath>
using namespace std;

// CREDIT STATEMENT: We only worked within our group, did not recieve help from anyone else
// Used the textbook and lecture notes as references for pseudocode



struct City{
    int id;
    double x;
    double y;
};



double bf_closest_pair(const vector<City>& cities){

// Add derek's implimentation here

}

// divide and conquer approach
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
}
