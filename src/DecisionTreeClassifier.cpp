#include <cmath>
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

double DecisionTreeClassifier::calculateLoss(vector<int> labelCounts) {
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