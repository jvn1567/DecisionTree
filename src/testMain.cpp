#include "DecisionTreeBase.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
using namespace std;

char* convertString(string basicString) {
    char* cstring = new char[basicString.length()];
    for (int i = 0; i < basicString.length(); i++) {
        cstring[i] = basicString[i];
    }
    return cstring;
}

//template <typename T>
vector<vector<int>>* parseFile(string filename, vector<string>& attributes) {
    vector<vector<int>>* dataset = new vector<vector<int>>;
    ifstream input;
    input.open(filename); //try-catch
    string line;
    getline(input, line);
    //grab attributes line
    char* attribute = strtok(convertString(line), ",");
    while (attribute != NULL) {
        cout << attribute << endl;
        attributes.push_back(string(attribute));
        attribute = strtok(NULL, ",");
    }
    //grab remaining dataset
    while (getline(input, line)) {
        //different data types????
    }
    return dataset;
}

int main() {
    vector<string> attributes;
    vector<vector<int>>* dataset = parseFile("iris.csv", attributes);
    return 0;
}