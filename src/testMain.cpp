
#include <iostream>
#include <string>
#include <vector>
#include "DecisionTreeClassifier.h"

using namespace std;

int main() {
    // DataFrame dataFrame("iris.csv"); // testing using numeric columns
    DataFrame dataFrame("mushrooms.csv"); // testing using string columns
    int totalRows = dataFrame.rows();
    double trainingSetProportion = .75;

    int trainSetLength = dataFrame.rows() * trainingSetProportion;
    
    // Split train and test data (non-random currently)
    DataFrame* train = dataFrame.slice(0, trainSetLength);
    DataFrame* test = dataFrame.slice(trainSetLength, totalRows);

    cout << "FRAMES MADE" << endl;

    DecisionTreeClassifier treeModel("GINI");
    treeModel.fit(train);
    treeModel.printTree();
    cout << endl;

    cout << "NEW DATA..." << endl;
    cout << *test << endl;

    cout << "MAKING PREDICTIONS..." << endl;
    DataFrame* predictions = treeModel.predict(test);

    cout << "PREDICTIONS PRINTED..." << endl;
    cout << *predictions << endl;
}