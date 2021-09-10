#ifndef _DECISIONNODE_H
#define _DECISIONNODE_H

struct DecisionNode {
    DecisionNode* left;
    DecisionNode* right;
    int splitIndex;
    double splitValue;
    double splitLoss;
    int sampleSize;
    int* values;
    DecisionNode(
        int splitIndex, 
        double splitValue, 
        double splitLoss,
        int sampleSize, 
        int* values, 
        DecisionNode* left = nullptr,
        DecisionNode* right = nullptr
    );
    bool isLeaf();
};

#endif