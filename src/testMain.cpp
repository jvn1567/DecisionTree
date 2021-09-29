
#include <iostream>
#include <string>
#include <vector>
#include "DecisionTreeClassifier.h"

using namespace std;

int main() {
    DataFrame testFrame("iris.csv");
    
    DataFrame* even = testFrame.slice(0, 0);
    DataFrame* odd = testFrame.slice(0, 0);

    for (int row = 0; row < testFrame.rows(); row++) {
        if (row % 2 == 0) {
            even->appendRow(testFrame.getRow(row));
        } else {
            odd->appendRow(testFrame.getRow(row));
        }
    }

    cout << "FRAMES MADE" << endl;

    DecisionTreeClassifier treeModel("GINI");
    treeModel.fit(even);
    treeModel.printTree();
    cout << endl;

    cout << "NEW DATA..." << endl;
    cout << *odd << endl;

    cout << "MAKING PREDICTIONS..." << endl;
    DataFrame* predictions = treeModel.predict(odd);

    cout << "PREDICTIONS PRINTED..." << endl;
    cout << *predictions << endl;
}