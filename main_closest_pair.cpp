#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <chrono>
#include <cmath>


// CREDIT STATEMENT: We only worked within our group, did not recieve help from anyone else
// Used the textbook and lecture notes as references for pseudocode

using namespace std;

double bf_closest_pair(const vector<city>& cities);
double efficient_closest_pair(const vector<city>& cityX, const vector<city>& cityY);

struct city {
    string id;
    double x;
    double y;
};

int main() {
    vector<city> cities;
    ifstream infile("cities.txt");
    while (infile) {
        city c;
        infile >> c.id >> c.x >> c.y;
        if (infile) {
            cities.push_back(c);
        }
    }
    infile.close();

    ofstream outfileBF("BF-closest.txt");
    ofstream outfileDC("DC-closest.txt");
    ofstream outfileTime("runtimes.txt");
    for (int i = 50 ; i <= 100; ++i) {

        vector<city> citiesSubset(cities.begin(), cities.begin() + i);

        auto start = chrono::high_resolution_clock::now();
        double minDist = bf_closest_pair(citiesSubset);
        auto end = chrono::high_resolution_clock::now();
        outfileBF << setprecision(10) << minDist << endl;
        long long runtime1 = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        
        
        vector<city> cityX = citiesSubset;
        vector<city> cityY = citiesSubset;

        for (int j = 0; j < cityX.size(); ++j) {
            for (int k = j + 1; k < cityX.size(); ++k) {
                if (cityX[j].x > cityX[k].x) {
                    city temp = cityX[j];
                    cityX[j] = cityX[k];
                    cityX[k] = temp;
                }
                if (cityY[j].y > cityY[k].y) {
                    city temp = cityY[j];
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

        outfileTime <<runtime1 <<" "<< runtime2 << endl;

    }
}
