#include <iostream>
#include <string>
#include <vector>
#include "DecisionTreeClassifier.h"
// #include "magictest.h"

using namespace std;

int main() {
    vector<string> colNames;
    DataFrame testFrame("iris.csv", colNames);
    cout << testFrame << endl;
    // MagicParent* mp = new MagicChild();
    // cout << mp->method2() << endl;
    return 0;
}