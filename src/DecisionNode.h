#ifndef _DecisionNode_h
#define _DecisionNode_h

struct DecisionNode {
    DecisionNode* left;
    DecisionNode* right;
    int splitIndex;
    double splitValue;
    double splitLoss;
    int sampleSize;
    int* values;
    DecisionNode(int splitIndex, double splitValue, double splitLoss,
        int sampleSize, int* values, DecisionNode* left, DecisionNode* right);
    bool isLeaf();
};

#endif