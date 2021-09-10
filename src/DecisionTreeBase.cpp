#include <iostream>
#include "DecisionTreeBase.h"

using namespace std;

DecisionTreeBase::DecisionTreeBase(
    std::string lossCriterion,
    double maxFeatures,
    int minSamplesSplit,
    int maxDepth,
    int minSamplesLeaf,
    double minImpurityDecrease
) {
    root = nullptr;
    this->lossCriterion = lossCriterion;
    this->maxFeatures = maxFeatures;
    this->minSamplesSplit = minSamplesSplit;
    this->maxDepth = maxDepth;
    this->minSamplesLeaf = minSamplesLeaf;
    this->minImpurityDecrease = minImpurityDecrease;
}

void DecisionTreeBase::printTree(DecisionNode* node, int indents) {
    if (node->isLeaf()) {
        for (int i = 0; i < indents; i++) {
            cout << "    ";
        }
        cout << "TEMP PLACEHOLDER" << endl;
    } else {
        printTree(node->left, indents + 1);
        printTree(node->right, indents + 1);
    }
}

void DecisionTreeBase::printTree() {
    printTree(root, 0);
}