#ifndef _DECISIONNODE_H
#define _DECISIONNODE_H

#include "GenericTypeWrapper.h"
#include <vector>

struct DecisionNode {
    DecisionNode* left;
    DecisionNode* right;
    int splitColumn;
    Generic* splitValue;
    double splitLoss;
    int sampleSize;
    std::vector<double> values;
    
    DecisionNode(
        int sampleSize, 
        double splitLoss,
        std::vector<double> values, 
        int splitColumn = 0, 
        Generic* splitValue = nullptr, 
        DecisionNode* left = nullptr,
        DecisionNode* right = nullptr
    );
    bool isLeaf();
};

#endif