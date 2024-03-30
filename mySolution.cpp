#include <vector>
#include <stdio.h>
#include <unordered_map>
#include <iostream>
#include <queue>
#include <limits>
#include <time.h>
#include <fstream>
#include <sstream>

/*
 @file - mySolution.cpp

 @author - Jacob Santos
*/

using namespace std;

pair<vector<int>, int> NN(vector<vector<int> >&graph, int s, int prev, vector<int>&prevpath){
    int n = graph.size();
    int cost = 0;
    unordered_map<int, bool> visited;
    vector<int>path;

    // start at 0th node
    int currentNode = s;
    visited[s] = true;
    path.push_back(currentNode);

    // iterate through adjacent nodees (all of them)
    for (int i = 1; i < n; i++){
        
        int minDist = INT_MAX;
        int closestNode;

        // find closest node
        for (int j = 0; j < n; j++){

            // continuously find a closer node that we haven't visited until there's no more to visit
            if ((graph[currentNode][j] < minDist)&&(visited.find(j) == visited.end())){

                closestNode = j;
                minDist = graph[currentNode][j];

            }

        }

        // calculate the cost
        cost+=minDist;

        // return past cost and previous path if current cost exceeds the previous one
        if (cost > prev){
            return {prevpath, prev};
        }

        // update current node and visited map
        currentNode = closestNode;
        visited[currentNode] = true;
        // append node to resulting vector
        path.push_back(currentNode);
       
    }

    // map back to the starting node (0)
    path.push_back(s);
    cost += graph[currentNode][s];

    return {path, cost};
}

// function to open the file and read a diagonal graph as a symmetric graph
vector<vector<int> > openFile(string filename){
    vector<vector<int> > graph;

    ifstream inputFile(filename);

    string line;

    // read in diagonal graph
    while (getline(inputFile, line)){
        vector <int> row;
        istringstream inputstream(line);
        int val = 0;
        while(inputstream >> val ){
            row.push_back(val);
        }
        graph.push_back(row);
    }

    // close the file
    inputFile.close();

    // Make the diagonal graph symmetric
    for (int i = 0; i < graph.size(); ++i) {
        for (int j = i + 1; j < graph.size(); ++j) {
            graph[i].push_back(graph[j][i]);
        }
    }

    return graph;
}

// this is the function that performs the optimization, flips the two nodes
void doOpt(vector<int>&path, int i, int j){
    reverse(path.begin() + i + 1, path.begin() + j + 1);
}

void dosOpt(vector<int>&path, int &minCost, vector<vector<int> >&graph){
            int n = path.size();
            bool improved = true;

            while(improved){
                improved = false;
                // started loops at 1 and ended loops earlier so the trips back to starting node don't get swapped
                for (int i = 1; i < n-3; i++){
                    for (int j = i + 1; j < n-1; j++){

                        // calculates the change if we were to swap the two nodes in O(1) time
                        int deltaChange = -graph[path[i]][path[(i+1)%n]] - graph[path[j]][path[(j+1)%n]] + graph[path[i]][path[j]] + graph[path[(i+1)%n]][path[(j+1)%n]];

                        // if this is negative, then that means we found a valid optimization
                        if (deltaChange < 0){
                            doOpt(path, i, j);
                            minCost += deltaChange;
                            improved = true;
                        }

                    }
                }
            }
}

int main(){

    // open file
    cout << "reading file..." << endl;
    vector<vector<int> >graph = openFile("g5000_2.graph");
    cout << "done." << endl;

    // initialize needed variables
    clock_t start; clock_t end;

    cout << "---------------------------------------------------------------------" << endl;

    // start algorithm
    int pastMin = INT_MAX;
    int min = INT_MAX;
    vector<int>path;
    start = clock();
    for (int i = 0; i < graph.size(); i++){
        auto res = NN(graph, i, pastMin, path);

        // check if we found a better min from last nearest neighbor
        if (res.second < pastMin){

            pastMin = res.second;

            // then run optimization of the path found
            dosOpt(res.first, res.second, graph);

            // if optimized cost is less than previously optimized cost, then update accordingly
            if (res.second < min){
                min = res.second;

                path = res.first;
            }
                
        }

        // print out progress 
        cout<< "\r"<<(float(i)/graph.size())*100.0 << "% done...";
        cout.flush();

    }
    //dosOpt(path, min, graph);
    end = clock();
    //double time = (double) (end-start) / CLOCKS_PER_SEC * 1000.0;
    double time = (double) (end-start) / CLOCKS_PER_SEC ;

    cout << "your solution took this long: " << time << " seconds"<<endl;
    cout << "---------------------------------------------------------------------" << endl;

    // create solution file
    string fileName = "s" + to_string(min) + "_jasantos1.sol";
    ofstream solFile(fileName);

    for (auto x : path){
        solFile << x << " ";
    } 
    solFile.close();

    int count = 0;
    for (int i = 0; i < path.size()-1; i++){
        count += graph[path[i]][path[i+1]];
    }

    if (count == min){
        cout << "min cost of " << min << " is verified!" << endl;
    } else {
        cout << "min cost of: " << min << "doesn't match verified: " << count << endl;
    }
    return 0;
}