#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include "DecisionTreeBase.h"
#include "GenericTypeWrapper.h"
using namespace std;

Generic* wrapPrimitive(string data) {
    Generic* genericData;
    try {
        genericData = new Double(stod(data));
    } catch (std::invalid_argument) {
        genericData = new String(data);
    }
    return genericData;
}

vector<vector<Generic*>>* parseFile(string filename, vector<string>& colNames) {
    vector<vector<Generic*>>* dataset = new vector<vector<Generic*>>;
    ifstream input;
    input.open(filename); //try-catch
    string line;
    getline(input, line);
    //grab variables line
    istringstream inputstring(line);
    string variable;
    while (getline(inputstring, variable, ',')) {
        colNames.push_back(variable);
    }
    //grab remaining dataset
    while (getline(input, line)) {
        string data;
        vector<Generic*> row;
        istringstream inputstring(line);
        while (getline(inputstring, data, ',')) {
            Generic* genericData = wrapPrimitive(data);
            row.push_back(genericData);
        }
        dataset->push_back(row);
    }
    return dataset;
}

int main() {
    vector<string> colNames;
    vector<vector<Generic*>>* dataset = parseFile("iris.csv", colNames);
    
    return 0;
}