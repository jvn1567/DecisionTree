#ifndef _DECISIONTREECLASSIFIER_H
#define _DECISIONTREECLASSIFIER_H

#include "DecisionTreeBase.h"
#include <unordered_set>

class DecisionTreeClassifier : public DecisionTreeBase {
private:
    std::unordered_set<std::string> labels;
    void setLabels(DataFrame* testData);
    double computeLoss(std::vector<double> labelCounts);
    std::vector<double> getTruthVector(DataFrame* testData);
    void printTruthVector(std::vector<double> truthVector);
    Generic* predict(vector<Generic*>, DecisionNode* node);
public:
    DecisionTreeClassifier(
        std::string lossCriterion,
        double maxFeatures = 1.0,
        int minSamplesSplit = 2,
        int maxDepth = -1,
        int minSamplesLeaf = 0,
        double minImpurityDecrease = 0.0
    );
    void fit(DataFrame* testData);
    DataFrame* predict(DataFrame* validationData);
};

#endif