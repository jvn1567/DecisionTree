#ifndef _DECISIONNODE_H
#define _DECISIONNODE_H

struct DecisionNode {
    DecisionNode* left;
    DecisionNode* right;
    int splitIndex;
    double splitValue;
    double splitLoss;
    int sampleSize;
    double* values;
    
    DecisionNode(
        int sampleSize, 
        double splitLoss,
        double* values, 
        int splitIndex = 0, 
        double splitValue = 0, 
        DecisionNode* left = nullptr,
        DecisionNode* right = nullptr
    );
    bool isLeaf();
};

#endif