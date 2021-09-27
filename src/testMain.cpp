#include <iostream>
#include <string>
#include <vector>
#include "DecisionTreeClassifier.h"
// #include "magictest.h"

using namespace std;

int main() {
    DataFrame testFrame("iris.csv");
    cout << "DATAFRAME READ" << endl;

    DecisionTreeClassifier treeModel("GINI");
    treeModel.fit(&testFrame);
    treeModel.printTree();
    cout << endl;
    DataFrame* newData = testFrame.slice(20, 50);
    cout << "NEW DATA..." << endl;
    cout << *newData << endl;
    cout << "MAKING PREDICTIONS..." << endl;
    DataFrame* predictions = treeModel.predict(newData);
    cout << "PREDICTIONS PRINTED..." << endl;
    cout << *predictions << endl;
}