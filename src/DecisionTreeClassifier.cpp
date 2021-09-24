#include <cmath>
#include "DecisionTreeClassifier.h"
#include <unordered_map>

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
) {
    labels = unordered_set<string>();
}

void DecisionTreeClassifier::fit(DataFrame* testData) {
    setLabels(testData);
    DecisionTreeBase::fit(testData);
}

void DecisionTreeClassifier::setLabels(DataFrame* testData) {
    for (int i = 0; i < testData->rows(); i++) {
        labels.insert(((String*)testData->get(i, testData->cols() - 1))->data);
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

DataFrame* DecisionTreeClassifier::predict(DataFrame* validationData) {
    return nullptr;
}

string DecisionTreeClassifier::predictClass() {
    return "TEMP";
}

vector<double> DecisionTreeClassifier::getTruthVector(DataFrame* testData) {
    vector<double> counts(labels.size(), 0);
    unordered_map<string, int> labelIndices;
    
    int i = 0;
    for (string label : labels) {
        labelIndices[label] = i;
        i++;
    }

    for (int row = 0; row < testData->rows(); row++) {
        string className = ((String*)testData->get(row, testData->cols() - 1))->data;
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