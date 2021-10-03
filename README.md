# DecisionTree in C++
Authors: John Nguyen, Joshua Goldberg

# Overview
Decision tree is a popular, yet simple, machine learning algorithm. This C++ implementationwas inspired by sklearn's [DecisionTreeClassifier](https://scikit-learn.org/stable/modules/generated/sklearn.tree.DecisionTreeClassifier.html).

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

```
MAKING PREDICTIONS...
PREDICTIONS PRINTED...
Index     predictions     
0         virginica       
1         virginica       
2         virginica       
3         virginica       
4         virginica       
5         virginica       
6         virginica       
7         versicolor      
8         virginica       
9         virginica       
10        virginica       
11        virginica       
12        virginica       
13        virginica       
14        virginica       
15        virginica       
16        virginica       
17        virginica       
18        virginica       
19        virginica       
20        virginica       
21        versicolor      
22        virginica       
23        virginica       
24        virginica       
25        virginica       
26        virginica       
27        virginica       
28        virginica       
29        virginica       
30        virginica       
31        virginica       
32        virginica       
33        virginica       
34        virginica       
35        virginica       
36        virginica       
37        virginica
```

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
