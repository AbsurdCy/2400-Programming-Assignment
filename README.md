# Travel Planner - Algorithm Analysis

A C++ program that solves three algorithmic problems involving city travel data: maximizing cities visited within a budget using dynamic programming, finding the closest pair of cities using brute force and divide and conquer, and sorting flight data by time and cost using bubble sort.

All algorithms and helper functions are contained within a single travel_planner.cpp file. This was a requirement of the course assignment for which this project was built.

## Setup

Compile travel_planner.cpp with a C++ compiler and ensure the input files are in the same directory as the executable.

Input files needed: flights.txt, cities.txt, roundtrip_costs.txt

## What It Does

### Max Cities (Knapsack / Dynamic Programming)
Reads roundtrip_costs.txt, which contains lists of cities and their roundtrip travel costs. For each city list, determines the maximum number of cities that can be visited within a $5000 budget. Uses a knapsack-style DP algorithm with O(nB) time and space complexity, where n is the number of cities and B is the budget. Results are written to trip_nums.txt.

### Closest Pair of Cities
Reads cities.txt, which contains city IDs and their x/y coordinates. Finds the closest pair of cities across subsets of size 50 to 100 using two approaches: brute force (O(n^2)) and divide and conquer (O(n log n)). Results from each approach are written to BF-closest.txt and DC-closest.txt respectively, with runtimes logged separately.

### Flight Sorting
Reads flights.txt, which contains lists of flights per city with destination ID, flight time, and cost. Sorts each city's flights by time and by cost separately using bubble sort, measuring the runtime of each sort in nanoseconds. Sorted results are written to FtimeBubSort.txt and FcostBubSort.txt, and runtimes are written to runtimes.txt.

## Output Files

- trip_nums.txt — max cities visitable per budget scenario
- BF-closest.txt — closest pair distances using brute force
- DC-closest.txt — closest pair distances using divide and conquer
- FtimeBubSort.txt — flights sorted by time
- FcostBubSort.txt — flights sorted by cost
- runtimes.txt — bubble sort runtimes in nanoseconds per city

## Notes

max_roundtrip.cpp is a standalone version of the max cities knapsack algorithm, written separately before being integrated into travel_planner.cpp.

AI was used to help with reading files in C++ and measuring runtimes with chrono. No code was directly copied; it was used as a reference only.
