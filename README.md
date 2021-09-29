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

```
MAKING PREDICTIONS...
PREDICTIONS PRINTED...
Index     predictions     
0         setosa          
1         setosa          
2         setosa          
3         setosa          
4         setosa          
5         setosa          
6         setosa          
7         setosa          
8         setosa          
9         setosa          
10        setosa
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
