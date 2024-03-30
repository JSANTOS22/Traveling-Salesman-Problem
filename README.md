# Traveling-Salesman-Problem

## Input Graph Structure
The structure of the graphs being read into all three algorithms consist of a diagonal matrix. An example of this can be seen below:

```
0
1 0
2 1 0
3 2 1 0
```

Note that 0's represent the distance from a city to itself. That's how the algorithms keep track of each city that's already been visited

Each algorithm has the function that reads in the diagonal matrix and makes it symmetrical to fit the complete graph representation like this below:

```
0 1 2 3
1 0 1 2
2 1 0 1
3 2 1 0
```

When making an input graph, make sure you label the file as a graph file: 
```example.graph```

## Brute Force Compiling
For this program it is very important that you do not compile it with graphs that have greater than `15` nodes because it has a `O(n!)` time complexity.

Once you have your input graph file, all you need to do is alter line `81` to ensure the algorithm uses the correct file: 
```vector<vector<int> >graph = openFile("example.graph");```

Finally, the program must be compiled with `C++11` because it uses functionality that earlier versions cannot support, use `./a.out` to execute: 
```
g++ -std=c++11 BruteForce.cpp
./a.out 
```

## Nearest Neighbor Compiling
For this program you can use much larger graphs of up to `10,000` to `20,000` nodes because it has a `O(n^2)` time complexity.

Once you have your input graph file, all you need to do is alter line `91` to ensure the algorithm uses the correct file:
```vector<vector<int> >graph = openFile("example.graph");```

Finally, the program must be compiled with `C++11` because it uses functionality that earlier versions cannot support, use `./a.out` to execute:
```
g++ -std=c++11 NearestNeighbor.cpp
./a.out
```

## mySolution Compiling
For this program you can use graphs up to `5000` nodes because it has a `O(n^3)` worst case time complexity. The program does skip to the next iteration if the current cost exceeds the minimum already found.

Once you have your input graph file, all you need to do is alter line `138` to ensure the algorithm uses the correct file:
```vector<vector<int> >graph = openFile("example.graph");```

Finally, the program must be compiled with `C++11` because it uses functionality that earlier versions cannot support, use `./a.out` to execute:
```
g++ -std=c++11 mySolution.cpp
./a.out
```

Lastly, this program will create `.sol` solution file consisting of the best path that it could find. Each of these files are labled with an `s` followed by the `solution` and my bama `username`. For example, a solution of `1000` would have a file labeled `s1000_jasantos1.sol` and inside the file would be the path of such cost.

