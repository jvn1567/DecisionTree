#include <iostream>
#include <string>
#include <vector>
#include "DecisionTreeClassifier.h"
// #include "magictest.h"

using namespace std;

int main() {
    DataFrame testFrame("iris.csv");
    cout << "DATAFRAME READ" << endl;
    cout << testFrame << endl;

    DecisionTreeClassifier treeModel("GINI");
    treeModel.fit(&testFrame);
    treeModel.printTree();
    cout << endl;
}