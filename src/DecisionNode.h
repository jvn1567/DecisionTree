#ifndef _DECISIONNODE_H
#define _DECISIONNODE_H

#include "GenericTypeWrapper.h"

struct DecisionNode {
    DecisionNode* left;
    DecisionNode* right;
    int splitColumn;
    Generic* splitValue;
    double splitLoss;
    int sampleSize;
    double* values;
    
    DecisionNode(
        int sampleSize, 
        double splitLoss,
        double* values, 
        int splitColumn = 0, 
        Generic* splitValue = 0, 
        DecisionNode* left = nullptr,
        DecisionNode* right = nullptr
    );
    bool isLeaf();
};

#endif