#include <unordered_map>
#include <iostream>
#include "DecisionTreeClassifier.h"
using namespace std;

DecisionTreeClassifier::DecisionTreeClassifier(
    vector<string> labels,
    string lossCriterion,
    double maxFeatures,
    int minSamplesSplit,
    int maxDepth,
    int minSamplesLeaf,
    double minImpurityDecrease
) : DecisionTreeBase(
    lossCriterion,
    maxFeatures,
    minSamplesSplit,
    maxDepth,
    minSamplesLeaf,
    minImpurityDecrease
), labels(labels) {}

void DecisionTreeClassifier::fit(vector<vector<Generic*>>* testData) {
    fit(new DataMatrix(testData));
}

void DecisionTreeClassifier::fit(DataMatrix* testData) {
    //find best split location
    double minLoss = 0.0; //TEMP
    int bestFeatureCol = 0; //TEMP
    int bestSplitRow = 0; //TEMP
    for (int col = 0; col < testData->cols() - 1; col++) {
        if (testData->get(0, col)->type() == STRING) {
            //probably separate functions
            unordered_map<string, int> counts;
            for (int row = 0; row < testData->rows(); row++) {
                counts[((String*)(testData->get(row, col)))->data]++;
            }
            for (auto pair : counts) {
                //calculate the loss and replace if better
            }
        } else {
            //probably separate functions
            testData->sort(col);
            for (int row = 0; row < testData->rows(); row++) {
                double loss = 0.0; //TEMP, send to calculation
                if (loss < minLoss) {
                    minLoss = loss;
                    bestFeatureCol = col;
                    bestSplitRow = row;
                }
            }
        }
    }
    //perform split
}

vector<vector<double>> DecisionTreeClassifier::predict(
        vector<vector<Generic*>>* validationData) {
    vector<vector<double>> temp;
    return temp;
}

string DecisionTreeClassifier::predictClass() {
    return "TEMP";
}

double DecisionTreeClassifier::computeLoss() {
    return 0.0;
}