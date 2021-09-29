/**
 * @file DecisionNode.h
 * @author John Nguyen (jvn1567@gmail.com)
 * @author Joshua Goldberg (joshgoldbergcode@gmail.com)
 * @brief DecisionNode is a node object that makes up a decision tree, which is a
 * algorithm used to predict categorical and continuous data. 
 * @version 0.1
 * @date 2021-09-28
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef _DECISIONNODE_H
#define _DECISIONNODE_H

#include "GenericTypeWrapper.h"
#include <vector>

/**
 * @brief DecisionNodes can either be branches or leafs. Branch nodes store
 * data used to instruct the traversal of the decision tree. The data used for
 * traversal are a column index of a DataFrame and a row value. Both of these
 * are used for comparison with new data to go left (true) or right (false).
 * Leaf nodes contain data used for prediction.
 * 
 */
struct DecisionNode {
    DecisionNode* left;
    DecisionNode* right;
    int splitColumn;
    Generic* splitValue;
    double splitLoss;
    int sampleSize;
    std::vector<double> values;
    
    /**
     * @brief Construct a new DecisionNode object.
     * 
     * @param splitLoss Used for optimizing the fit of a decision tree.
     * @param values An array containing the expected value (mean) or the counts 
     * of each class for DecisionTreeRegressor and DecisionTreeClassifier, 
     * respectively.
     * @param splitColumn The column index used for splitting the node.
     * @param splitValue The row value used for splitting the node.
     * @param left The node that represents true for comparison.
     * @param right The node that represents false for comparison.
     */
    DecisionNode(
        double splitLoss,
        std::vector<double> values, 
        int splitColumn = 0, 
        Generic* splitValue = nullptr, 
        DecisionNode* left = nullptr,
        DecisionNode* right = nullptr
    );

    /**
     * @brief Determines whethers node is a leaf node. 
     * 
     * @return true a leaf node.
     * @return false not a leaf node.
     */
    bool isLeaf();
};

#endif