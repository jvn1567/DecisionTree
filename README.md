# DecisionTree in C++
Authors: John Nguyen, Joshua Goldberg
<br>
View documentation [here](https://jvn1567.github.io/DecisionTree/).

# Overview
Decision tree is a popular, yet simple, machine learning algorithm. This C++ implementationwas inspired by sklearn's [DecisionTreeClassifier](https://scikit-learn.org/stable/modules/generated/sklearn.tree.DecisionTreeClassifier.html). The dataFrame class is mostly inspired by R's [dplyr](https://dplyr.tidyverse.org) and in some cases, python's [pandas](https://pandas.pydata.org).

# Usage
```cpp

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
```
![tree](https://user-images.githubusercontent.com/56368354/208554878-f1be3702-3239-46c7-85ef-42db33ac92f7.png)

# Dependencies
This implementation relies heavily on the DataFrame class included in this repository.

# License
MIT License

Copyright (c) 2021 John Nguyen, Joshua Goldberg

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
