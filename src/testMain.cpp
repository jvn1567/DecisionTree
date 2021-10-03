
#include <iostream>
#include <string>
#include <vector>
#include "DecisionTreeClassifier.h"

using namespace std;

int main() {
    DataFrame dataFrame("iris.csv"); // testing using numeric columns
    // DataFrame dataFrame("mushrooms.csv"); // testing using string columns
    double trainingSetProportion = .75;
    int trainSetLength = dataFrame.rows() * trainingSetProportion;
    
    // Split train and test data
    DataFrame* train = dataFrame.slice(0, trainSetLength);
    DataFrame* test = dataFrame.slice(trainSetLength, dataFrame.rows());

    cout << "Train/test datasets created." << endl;

    DecisionTreeClassifier treeModel("GINI");
    treeModel.fit(train);
    treeModel.printTree();
    cout << endl;

    cout << "Test data:" << endl;
    cout << test << endl;

    cout << "Making predictions..." << endl;
    DataFrame* predictions = treeModel.predict(test);

    cout << predictions << endl;
}

// int main() {
//     DataFrame dataFrame("iris.csv"); // testing using numeric columns
//     DataFrame* firstTenRows = dataFrame.slice(0, 10);
//     cout << firstTenRows << endl;

//     cout << "NOW SHUFFLE..." << endl;
//     cout << firstTenRows->shuffle() << endl;
//     cout << "SHUFFLED!" << endl;
// }