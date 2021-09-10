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
    
void DecisionTreeClassifier::fit(vector<vector<Generic*>>* testData) {
    double lossOrSomething = 0.0;
    for (int label = 0; label < labels.size(); label++) {
        if ((*testData)[0][label]->type == STRING) {
            unordered_map<string, int> counts;
            for (int row = 0; row < testData->size(); row++) {
                counts[((String*)(*testData)[row][label])->data]++;
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