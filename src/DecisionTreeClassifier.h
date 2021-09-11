#ifndef _DECISIONTREECLASSIFIER_H
#define _DECISIONTREECLASSIFIER_H

#include "DecisionTreeBase.h"

class DecisionTreeClassifier : public DecisionTreeBase {
private:
    std::vector<std::string> labels;
    std::vector<std::vector<Generic*>>* sortMerge(std::vector<std::vector<Generic*>>* half1,
        std::vector<std::vector<Generic*>>* half2, int sortIndex);
    std::vector<std::vector<Generic*>>* sortSplit(std::vector<std::vector<Generic*>>* data,
        int sortIndex);
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
    void fit(std::vector<std::vector<Generic*>>* testData);
    std::vector<std::vector<double>> predict(
        std::vector<std::vector<Generic*>>* validationData);
    std::string predictClass();
    double computeLoss();
};

#endif