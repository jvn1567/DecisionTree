#include <cmath>
#include <unordered_map>
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

vector<vector<double>> DecisionTreeClassifier::predict(
        vector<vector<Generic*>>* validationData) {
    vector<vector<double>> temp;
    return temp;
}

string DecisionTreeClassifier::predictClass() {
    return "TEMP";
}

//we need a vector of classes
vector<int> DecisionTreeClassifier::countClasses(DataFrame* testData) {
    unordered_map<string, int> classes; //TEMP PLACEHOLDER
    vector<int> counts;
    for (int i = 0; i < classes.size(); i++) {
        counts.push_back(0);
    }
    for (int row = 0; row < testData->rows(); row++) {
        //assumes class is the last column
        string classname = ((String*)testData->get(row, testData->cols()))->data;
        counts[classes[classname]]++;
    }
    return counts;
}

vector<double> DecisionTreeClassifier::getTruthVector(DataFrame*) {
    vector<double> temp;
    return temp;
}