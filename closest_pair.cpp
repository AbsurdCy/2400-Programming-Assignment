#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <chrono>
#include <cmath>
using namespace std;


struct City{
    int id;
    double x;
    double y;
};

double efficient_closest_pair(vector<City>& cityX, vector<City>& cityY){
    int n = cityX.size();
    int mid = n/2;
    if (n <= 3){
        // Base case: use brute force, impliment later
    }
    else{
        double midX = cityX[n/2].x;

        // divide x and y vectors into left and right
        vector<City> leftX( cityX.begin(), cityX.begin() + mid);
        vector<City> rightX( cityX.begin() + mid, cityX.end());
        vector<City> leftY, rightY;

        for (int i=0 ; i < n; i++){
            if (cityY[i].x <= midX){
                leftY.push_back(cityY[i]);
            } else {
                rightY.push_back(cityY[i]);
            }
        }

        // conquer
        double distL = efficient_closest_pair(leftX, leftY);
        double distR = efficient_closest_pair(rightX, rightY);
        double shortestDistA = min(distL, distR);
        double midX = cityX[mid-1].x;

        vector<City> stp;
        for (int i=0; i < n; i++){
            if (abs(cityY[i].x - midX) < shortestDistA){
                stp.push_back(cityY[i]);
            }
        }

        double shortestTot = (pow(shortestDistA,2));
        int stpsiz = stp.size();
        for (int i=0; i < stpsiz; i++){
            int k = i + 1;
            while (k < stpsiz - 1 && (pow((stp[k].y - stp[i].y),2)) < shortestTot){
                shortestTot = min(pow(stp[k].x - stp[i].x,2) + pow((stp[k].y - stp[i].y),2), shortestTot);
                k++;
            }
        }
        
        return sqrt(shortestTot);
    }
}

