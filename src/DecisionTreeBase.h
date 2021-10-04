/**
 * @file DecisionTreeBase.h
 * @author John Nguyen (jvn1567@gmail.com)
 * @author Joshua Goldberg (joshgoldbergcode@gmail.com)
 * @brief DecisionTreeBase is a semi-virtual parent class that contains methods
 * used in both DecisionTreeClassifier and DecisionTreeRegressor.
 * @version 0.1
 * @date 2021-10-01
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef _DECISIONTREEBASE_H
#define _DECISIONTREEBASE_H

#include <string>
#include <vector>
#include "DataFrame.h"
#include "DecisionNode.h"
#include "GenericTypeWrapper.h"

/**
 * @brief DecisionTreeBase is a semi-virtual parent class that contains methods
 * used in both DecisionTreeClassifier and DecisionTreeRegressor.
 * 
 */
class DecisionTreeBase {
protected:
    DecisionNode* root;
    
private:
    std::string lossCriterion;
    int maxDepth;
    int minSamplesSplit;
    int minSamplesLeaf;
    double maxFeatures;
    double minImpurityDecrease;
    int* featureImportance;
    void fit(DataFrame* trainData, DecisionNode*& node);    
    int findSplit(
        DataFrame* trainData,
        int& bestCol, 
        double minLoss,
        Generic*& splitValue
    );
    int findRowSplitString(
        int col,
        DataFrame*& trainData,
        int& bestCol,
        double& minLoss,
        Generic*& splitValue
    );
    int findRowSplitDouble(
        int col,
        DataFrame*& trainData,
        int& bestCol,
        double& minLoss,
        Generic*& splitValue
    );
    void printTree(DecisionNode* node, int indents);
    virtual double computeLoss(std::vector<double>) = 0;
    virtual std::vector<double> getTruthVector(DataFrame*) = 0;
    virtual void printTruthVector(std::vector<double> truthVector) = 0;
    void printSpaces(int indents);
public:
    /**
     * @brief Construct a new DecisionTreeBase object.
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
    DecisionTreeBase(
        std::string lossCriterion,
        double maxFeatures,
        int minSamplesSplit,
        int maxDepth,
        int minSamplesLeaf,
        double minImpurityDecrease
    );

    /**
     * @brief This method creates the decision tree, which can be used later for 
     * prediction.
     * 
     * @pre fit() assumes computeLoss() private method is implemented by the 
     * child class. Otherwise, the user can implement their own fit() if they 
     * have a different algorithm for constructing a decision tree.
     * 
     * @param trainData 
     */
    virtual void fit(DataFrame* trainData);
    virtual DataFrame* predict(DataFrame* testData) = 0;
    std::string getLossCriterion() const;
    void printTree();
};

#endif