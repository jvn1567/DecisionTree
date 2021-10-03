/**
 * @file DecisionTreeClassifier.h
 * @author John Nguyen (jvn1567@gmail.com)
 * @author Joshua Goldberg (joshgoldbergcode@gmail.com)
 * @brief DecisionTreeClassifier is an algorithm used to predict discrete 
 * outcomes. This implementation was inspired by sklearn's 
 * DecisionTreeClassifier, as many of the same parameters and methods are 
 * included.
 * @version 0.1
 * @date 2021-10-01
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef _DECISIONTREECLASSIFIER_H
#define _DECISIONTREECLASSIFIER_H

#include "DecisionTreeBase.h"

/**
 * @brief The DecisionTreeClassifier extends DecisionTreeBase for [classification
 * problems in machine learning](https://en.wikipedia.org/wiki/Decision_tree_learning). 
 * 
 */
class DecisionTreeClassifier : public DecisionTreeBase {
private:
    std::vector<std::string> labels;
    
    /**
     * Populates the labels member variable, which is a unique string value
     * of each label from the target column.
     * 
     */
    void setLabels(DataFrame* testData);
    double computeLoss(std::vector<double> labelCounts);
    
    /**
     * Returns a vector of the class counts, such as [50, 50, 50]. This example
     * has three classes and 150 samples total.
     */
    std::vector<double> getTruthVector(DataFrame*);

    /**
     * Prints the truth vector returned from getTruthVector().
     * 
     */
    void printTruthVector(std::vector<double> truthVector);
    Generic* predict(const std::vector<Generic*>& row, DecisionNode* node);
public:
    /**
     * @brief Construct a new DecisionTreeClassifier object.
     * 
     * @param lossCriterion type of loss calculation used
     * @param maxFeatures number of features used for splitting a node
     * @param minSamplesSplit minimun number of samples at root to consider 
     * splitting
     * @param maxDepth maxiumum depth of the decision tree
     * @param minSamplesLeaf minimum number of samples in child leafs to consider
     * the split
     * @param minImpurityDecrease minimum improvement in loss calculation to
     * consider the split
     */
    DecisionTreeClassifier(
        std::string lossCriterion,          // TODO: Add entropy
        double maxFeatures = 1.0,           // TODO: need to implement
        int minSamplesSplit = 2,
        int maxDepth = -1,                  // TODO: need to implement
        int minSamplesLeaf = 1,             // TODO: this can't be zero, otherwise segfault
        double minImpurityDecrease = 0.0    // TODO: need to implement
    );

    /**
     * @brief fit consumes training data to construct a decision tree that
     * later can be used for prediction.
     * 
     * @pre Currently, the last column is assumed to be the response variable.
     * 
     * @param trainData a data frame with all the features used for fitting a
     * decision tree.
     */
    void fit(DataFrame* trainData);

    /**
     * @brief Predicts the class of the observations provided to the fitted
     * decision tree. This method expects a DataFrame* and will output a 
     * DataFrame* for the same number of rows as testData.
     * 
     * @param testData 
     * @return DataFrame* 
     */
    DataFrame* predict(DataFrame* testData);
};

#endif