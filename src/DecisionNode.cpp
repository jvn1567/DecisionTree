#include "DecisionNode.h"

using namespace std;

DecisionNode::DecisionNode(
    int splitIndex, 
    double splitValue, 
    double splitLoss,
    int sampleSize, 
    int* values, 
    DecisionNode* left,
    DecisionNode* right
) {
    this->splitIndex = splitIndex;
    this->splitValue = splitValue;
    this->splitLoss = splitLoss;
    this->sampleSize = sampleSize;
    this->values = values;
    this->left = left;
    this->right = right;
}

bool DecisionNode::isLeaf() {
    return left == nullptr && right == nullptr;
}