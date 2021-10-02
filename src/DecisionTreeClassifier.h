#ifndef _DECISIONTREECLASSIFIER_H
#define _DECISIONTREECLASSIFIER_H

#include "DecisionTreeBase.h"

class DecisionTreeClassifier : public DecisionTreeBase {
private:
    std::vector<std::string> labels;
    void setLabels(DataFrame* testData);
    double computeLoss(std::vector<double> labelCounts);
    std::vector<double> getTruthVector(DataFrame*);
    void printTruthVector(std::vector<double> truthVector);
    Generic* predict(const std::vector<Generic*>& row, DecisionNode* node);
public:
    DecisionTreeClassifier(
        std::string lossCriterion,
        double maxFeatures = 1.0,
        int minSamplesSplit = 2,
        int maxDepth = -1,
        int minSamplesLeaf = 0,
        double minImpurityDecrease = 0.0
    );
    void fit(DataFrame* trainData);
    DataFrame* predict(DataFrame* testData);
};

#endif