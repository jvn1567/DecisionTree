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

double DecisionTreeClassifier::calculateLoss() {
    if (getLossCriterion() == "GINI") {
        return 0.0;
    } else {
        return 0.0;
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