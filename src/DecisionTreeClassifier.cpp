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

vector<vector<Generic*>>* DecisionTreeClassifier::sortMerge(vector<vector<Generic*>>* half1,
        vector<vector<Generic*>>* half2, int sortIndex) {
    vector<vector<Generic*>>* merged = new vector<vector<Generic*>>;
    int index1 = 0;
    int index2 = 0;
    while (index1 < half1->size() && index2 < half2->size()) {
        double value1 = ((Double*)(*half1)[index1][sortIndex])->data;
        double value2 = ((Double*)(*half2)[index2][sortIndex])->data;
        if (value1 < value2) {
            merged->push_back((*half1)[index1]);
            index1++;
        } else {
            merged->push_back((*half2)[index2]);
            index2++;
        }
    }
    while (index1 < half1->size()) {
        merged->push_back((*half1)[index1]);
        index1++;
    }
    while (index2 < half2->size()) {
        merged->push_back((*half2)[index2]);
        index2++;
    }

    return merged;
}

vector<vector<Generic*>>* DecisionTreeClassifier::sortSplit(vector<vector<Generic*>>* data, int sortIndex) {
    if (data->size() == 1) {
        return data;
    } else {
        vector<vector<Generic*>>* half1 = new vector<vector<Generic*>>;
        vector<vector<Generic*>>* half2 = new vector<vector<Generic*>>;
        for (int i = 0; i < data->size() / 2; i++) {
            half1->push_back((*data)[i]);
        }
        for (int i = data->size() / 2; i < data->size(); i++) {
            half2->push_back((*data)[i]);
        }
        half1 = sortSplit(half1, sortIndex);
        half2 = sortSplit(half2, sortIndex);
        return sortMerge(half1, half2, sortIndex);
    }
}

void DecisionTreeClassifier::fit(vector<vector<Generic*>>* testData) {
    /*vector<vector<Generic*>>* sorted = sortSplit(testData, 0);
    for (int row = 0; row < sorted->size(); row++) {
        Generic* item = (*sorted)[row][0];
        Generic* species = (*sorted)[row][(*sorted)[0].size() - 1];
        cout << ((Double*)item)->data << ", " << ((String*)species)->data << endl;
    }*/
    double lossOrSomething = 0.0;
    for (int col = 0; col < testData[0].size() - 1; col++) {
        if ((*testData)[0][col]->type() == STRING) {
            unordered_map<string, int> counts;
            for (int row = 0; row < testData->size(); row++) {
                counts[((String*)(*testData)[row][col])->data]++;
            }
            for (auto pair : counts) {
                //calculate the loss and replace if better
            }
        } else {
            //do a sort
            for (int row = 0; row < testData->size(); row++) {
                //calculate the loss and replace if better
            }
        }
    }
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