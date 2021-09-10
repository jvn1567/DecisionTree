#ifndef _DECISIONTREEBASE_H
#define _DECISIONTREEBASE_H

#include <string>
#include <vector>
#include "DecisionNode.h"
#include "GenericTypeWrapper.h"

class DecisionTreeBase {
private:
    DecisionNode* root;
    std::string lossCriterion;
    int maxDepth;
    int minSamplesSplit;
    int minSamplesLeaf;
    double maxFeatures;
    double minImpurityDecrease;
    int* featureImportance;
    void printTree(DecisionNode* node, int indents);
    void printTree();
public:
    DecisionTreeBase(
        std::string lossCriterion,
        double maxFeatures,
        int minSamplesSplit,
        int maxDepth,
        int minSamplesLeaf,
        double minImpurityDecrease
    );
    virtual void fit() = 0;
    virtual std::vector<std::vector<double>> predict(std::vector<std::vector<Generic*>>*) = 0;
    virtual double computeLoss() = 0;
};

#endif