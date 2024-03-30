#include <algorithm>
#include <iostream>
#include <stdio.h>
#include <time.h>
#include <fstream>
#include <sstream>
#include <vector>


using namespace std;

pair <vector<int>, int> BruteForce(vector<vector<int> >&graph){
    vector<int>path, res;
    int minCost = INT_MAX, i;
    

    for (i = 0; i < graph.size(); i++){
        path.push_back(i);
    }

    do {
        int cost = 0;

        // calculate the distance of the current permutation
        for (i = 0; i < path.size()-1; i++){
            cost += graph[path[i]][path[i+1]];
        }

        // must consider mapping back to starting node
        cost+= graph[path[path.size()-1]][path[0]];

        // if we found a lower cost, then update minCost and res
        if (cost < minCost){
            minCost = cost;
            res = path;
        }
        

    } while(next_permutation(path.begin(), path.end()));


    return{res, minCost};
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
    cout << "reading file..." << endl;
    vector<vector<int> >graph = openFile("Size10.graph");
    cout << "done." << endl;
    cout << "---------------------------------------------------------------------" << endl;

    // initialize variables
    clock_t start, end;

    start = clock();
    auto res = BruteForce(graph);
    cout << res.second << endl;
    end = clock();
    

    double time = (double) (end-start) / CLOCKS_PER_SEC;

    cout << "Brute force took this long: " << time << " seconds"<<endl;

    for (int x : res.first){
        cout << x << " ";
    } cout << end;
    


    return 0;
}
