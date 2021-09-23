#ifndef _DECISIONTREEBASE_H
#define _DECISIONTREEBASE_H

#include <string>
#include <vector>
#include "DataFrame.h"
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
    void findSplit(DataFrame* testData, int& bestRow, int& bestCol, double minLoss);
    void fit(DataFrame* testData, DecisionNode*& node);
    void printTree(DecisionNode* node, int indents);
    virtual double computeLoss(std::vector<double>) = 0;
    virtual std::vector<double> getTruthVector(DataFrame*) = 0;
public:
    DecisionTreeBase(
        std::string lossCriterion,
        double maxFeatures,
        int minSamplesSplit,
        int maxDepth,
        int minSamplesLeaf,
        double minImpurityDecrease
    );
    virtual void fit(DataFrame* testData);
    virtual DataFrame* predict(DataFrame*) = 0;
    std::string getLossCriterion() const;
    void printTree();
};

#endif