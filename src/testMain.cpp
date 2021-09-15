#include <iostream>
#include <string>
#include <vector>
#include "DecisionTreeClassifier.h"
using namespace std;

int main() {
    vector<string> colNames;
    DataFrame testFrame("iris.csv", colNames);
    cout << testFrame << endl;
    return 0;
}