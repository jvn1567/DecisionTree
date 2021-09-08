#ifndef _DecisionTreeBase_h
#define _DecisionTreeBase_h

#include <string>
#include "DecisionNode.h"
using namespace std;

class DecisionTreeBase {
private:
    DecisionNode* root;
    string lossCriteria;
    int maxDepth;
    int minSamplesSplit;
    int minSamplesLeaf;
    int maxFeatures;
    double minImpurityChange;
    int* featureImportance;
    void printTree(DecisionNode* node, int indents);
    void printTree();
public:
    DecisionTreeBase();
    virtual void fit();
    virtual int predict();
    virtual double computeLoss();
};

#endif