#include <iostream>
#include <string>
#include <vector>
#include "DecisionTreeClassifier.h"
// #include "magictest.h"

using namespace std;

int main() {
    cout << "INITIAL DATAFRAME" << endl;
    DataFrame testFrame("iris.csv");
    cout << testFrame << endl;
    cout << "FILTERED DATAFRAME" << endl;
    DataFrame* filteredFrame = testFrame.filter("Sepal.Length <       5.0");
    cout << "FILTER SUCCESSFUL" << endl;
    cout << *filteredFrame << endl;
}