#include <vector>
#include <stdio.h>
#include <unordered_map>
#include <iostream>
#include <queue>
#include <limits>
#include <time.h>
#include <fstream>
#include <sstream>

using namespace std;

pair<vector<int>, int> NN(vector<vector<int> >&graph){
    int n = graph.size();
    int cost = 0;
    unordered_map<int, bool> visited;
    vector<int>path;

    // start at 0th node
    int currentNode = 0;
    visited[0] = true;
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

        // update current node and visited map
        currentNode = closestNode;
        visited[currentNode] = true;
        // append node to resulting vector
        path.push_back(currentNode);
        cost+=minDist;  
    }

    // map back to the starting node (0)
    path.push_back(0);
    cost += graph[currentNode][0];

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

int main(){

    // open file
    vector<vector<int> >graph = openFile("Size10000.graph");

    // initialize needed variables
    clock_t start; clock_t end;

    cout << "---------------------------------------------------------------------" << endl;

    // start algorithm
    start = clock();
    auto res = NN(graph);
    end = clock();
    double time = (double) (end-start) / CLOCKS_PER_SEC * 1000.0;

    cout << "Nearest neighbor solution took this long: " << time << " ms"<<endl;
    cout << "---------------------------------------------------------------------" << endl;

    // create solution file
    string fileName = "TSP/s" + to_string(res.second) + "_jasantos1.sol";
    ofstream solFile(fileName);

    for (auto x : res.first){
        solFile << x << " ";
    } 
    solFile.close();

    return 0;
}
