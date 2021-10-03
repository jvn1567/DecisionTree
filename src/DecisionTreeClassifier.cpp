/**
 * @file DecisionTreeClassifier.cpp
 * @author John Nguyen (jvn1567@gmail.com)
 * @author Joshua Goldberg (joshgoldbergcode@gmail.com)
 * @brief Implementation of DecisionTreeClassifier.h.
 * @version 0.1
 * @date 2021-10-01
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <cmath>
#include <set>
#include <map>
#include "DecisionTreeClassifier.h"

using namespace std;

DecisionTreeClassifier::DecisionTreeClassifier(
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
) {}

void DecisionTreeClassifier::fit(DataFrame* trainData) {
    setLabels(trainData);
    DecisionTreeBase::fit(trainData);
}

void DecisionTreeClassifier::setLabels(DataFrame* trainData) {
    set<string> labelSet;
    for (int i = 0; i < trainData->rows(); i++) {
        labelSet.insert(trainData->get(i, trainData->cols() - 1)->getString());
    }
    for (string label : labelSet) {
        labels.push_back(label);
    }
}

double DecisionTreeClassifier::computeLoss(vector<double> labelCounts) {
    if (getLossCriterion() == "GINI") {
        int total = 0; 
        for (int i = 0; i < labelCounts.size(); i++) {
            total += labelCounts[i];
        }
        double probabilityRaw = 0.0;
        for (int i = 0; i < labelCounts.size(); i++) {
            probabilityRaw += pow((1.0 * labelCounts[i] / total), 2);
        }
        return 1 - probabilityRaw;
    //placeholder
    } else {
        return 0.0;
    }
}

Generic* DecisionTreeClassifier::predict(const vector<Generic*>& row, DecisionNode* node) {
    if (node->isLeaf()) {
        double max = 0;
        int maxIndex = 0;
        vector<double> labelCounts = node->values;
        for (int i = 0; i < labelCounts.size(); i++) {
            if (labelCounts[i] > max) {
                maxIndex = i;
            }
        }
        return Generic::wrapPrimitive(labels[maxIndex]);
    } else {
        if (*row[node->splitColumn] < *node->splitValue) {
            return predict(row, node->left);
        } else {
            return predict(row, node->right);
        }
    }
}

DataFrame* DecisionTreeClassifier::predict(DataFrame* validationData) {
    vector<string> colNames {"predictions"};
    DataFrame* predictions = new DataFrame(colNames);
    for (int row = 0; row < validationData->rows(); row++) {
        vector<Generic*> prediction;
        prediction.push_back(predict(validationData->getRow(row), root));
        predictions->appendRow(prediction);
    }
    return predictions;
}

vector<double> DecisionTreeClassifier::getTruthVector(DataFrame* data) {
    vector<double> counts(labels.size(), 0);
    map<string, int> labelIndices;
    int i = 0;
    for (string label : labels) {
        labelIndices[label] = i;
        i++;
    }
    for (int row = 0; row < data->rows(); row++) {
        string className = data->get(row, data->cols() - 1)->getString();
        counts[labelIndices[className]]++;
    }
    return counts;
}

void DecisionTreeClassifier::printTruthVector(std::vector<double> truthVector) {
    cout << "[";
    int i;
    for (i = 0; i < truthVector.size() - 1; i++) {
        cout << truthVector[i] << ", ";
    }
    cout << truthVector[i] << "]";
}