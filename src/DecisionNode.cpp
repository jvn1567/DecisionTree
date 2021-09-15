#include "DecisionNode.h"

using namespace std;

DecisionNode::DecisionNode(
    int sampleSize,
    double splitLoss,
    double* values, 
    int splitIndex,
    double splitValue,
    DecisionNode* left,
    DecisionNode* right
) {
    this->sampleSize = sampleSize;
    this->splitIndex = splitIndex;
    this->splitValue = splitValue;
    this->splitLoss = splitLoss;
    this->values = values;
    this->left = left;
    this->right = right;
}

bool DecisionNode::isLeaf() {
    return left == nullptr && right == nullptr;
}