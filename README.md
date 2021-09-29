# DecisionTree in C++
Authors: John Nguyen, Joshua Goldberg

# Overview
Decision tree is a popular, yet simple, machine learning algorithm. This was inspired by sklearn's [DecisionTreeClassifier](https://scikit-learn.org/stable/modules/generated/sklearn.tree.DecisionTreeClassifier.html).

# Usage
```cpp

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
            even->append(testFrame.get(row));
        } else {
            odd->append(testFrame.get(row));
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
```

# Dependencies
This implementation relies heavily on the DataFrame class included in this repository.
