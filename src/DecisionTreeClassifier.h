#ifndef _DECISIONTREECLASSIFIER_H
#define _DECISIONTREECLASSIFIER_H

#include "DecisionTreeBase.h"

class DecisionTreeClassifier : public DecisionTreeBase {
private:
    std::vector<std::string> labels;
    double calculateLoss();
public:
    DecisionTreeClassifier(
        std::vector<std::string> labels,
        std::string lossCriterion,
        double maxFeatures = 1.0,
        int minSamplesSplit = 2,
        int maxDepth = -1,
        int minSamplesLeaf = 1,
        double minImpurityDecrease = 0.0
    );
    std::vector<std::vector<double>> predict(
        std::vector<std::vector<Generic*>>* validationData);
    std::string predictClass();
    double computeLoss();
};

#endif