/**
 * @file DecisionTreeBase.h
 * @author John Nguyen (jvn1567@gmail.com)
 * @author Joshua Goldberg (joshgoldbergcode@gmail.com)
 * @brief This file implements the functions of DecisionTreeBase.h.
 * @version 0.1
 * @date 2021-10-01
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <iostream>
#include <unordered_map>
#include "DecisionTreeBase.h"

using namespace std;

DecisionTreeBase::DecisionTreeBase(
    std::string lossCriterion,
    double maxFeatures,
    int minSamplesSplit,
    int maxDepth,
    int minSamplesLeaf,
    double minImpurityDecrease
) {
    root = nullptr;
    this->lossCriterion = lossCriterion;
    this->maxFeatures = maxFeatures;
    this->minSamplesSplit = minSamplesSplit;
    this->maxDepth = maxDepth;
    this->minSamplesLeaf = minSamplesLeaf;
    this->minImpurityDecrease = minImpurityDecrease;
}

void DecisionTreeBase::fit(DataFrame* trainData, DecisionNode*& node) {
    vector<double> truthVector = getTruthVector(trainData);
    double nodeLoss = computeLoss(truthVector);
    if (trainData->rows() >= minSamplesSplit) {
        // split data
        int splitColumn; // If splittable, this should be populated by findSplit()
        int rightCount = 0;
        int leftCount = 0;
        Generic* splitValue = nullptr;
        findSplit(trainData, splitColumn, nodeLoss, leftCount, rightCount, splitValue);
        bool splitable = leftCount > minSamplesLeaf && rightCount > minSamplesLeaf;
        // make branch node
        if (splitable) {
            string splitValueString;
            string colName = trainData->getColName(splitColumn);
            string operator1;
            string operator2;
            if (trainData->getColType(splitColumn) == DOUBLE) {
                splitValueString = to_string(splitValue->getDouble());
                operator1 = "<=";
                operator2 = ">";
            } else if (trainData->getColType(splitColumn) == STRING) {
                splitValueString = splitValue->getString();
                operator1 = "==";
                operator2 = "!=";                
            } else {
                throw invalid_argument("DATA TYPE NOT SUPPORTED");
            }
            DataFrame* half1 = trainData->filter(colName + operator1 + splitValueString);
            DataFrame* half2 = trainData->filter(colName + operator2 + splitValueString);
            node = new DecisionNode(nodeLoss, truthVector, splitColumn, splitValue);
            fit(half1, node->left);
            fit(half2, node->right);
            // clear memory on the way back up since half1/half2 are not needed
            // outside of fitting
            delete half1;
            half1 = nullptr;
            delete half2;
            half2 = nullptr;                    
        } else { // make leaf node
            node = new DecisionNode(nodeLoss, truthVector);
        }
    } else {
        node = new DecisionNode(nodeLoss, truthVector);
    }
}

void DecisionTreeBase::findSplit(
    DataFrame* trainData,
    int& bestCol,
    double minLoss,
    int& leftCount, 
    int& rightCount, 
    Generic*& splitValue
    ) {
    for (int col = 0; col < trainData->cols() - 1; col++) {
        GenericType type = trainData->get(0, col)->type();
        if (type == STRING) {
            findRowSplitString(
                col, trainData, bestCol, 
                minLoss, leftCount, rightCount, splitValue
            );
        } else if (type == DOUBLE || type == INTEGER) {
            findRowSplitDouble(
                col, trainData, bestCol, 
                minLoss, leftCount, rightCount, splitValue
            );            
        } else {
            throw invalid_argument("DATA TYPE NOT SUPPORTED");
        }
    }
}

void DecisionTreeBase::findRowSplitString(
    int col,
    DataFrame*& trainData,
    int& bestCol,
    double& minLoss,
    int& leftCount, 
    int& rightCount, 
    Generic*& splitValue
) {
    unordered_map<string, int> counts;
    for (int row = 0; row < trainData->rows(); row++) {
        counts[trainData->get(row, col)->getString()]++;
    }
    for (auto pair : counts) {
        string colName = trainData->getColName(col);
        DataFrame* left = trainData->filter(colName + "==" + pair.first);
        DataFrame* right = trainData->filter(colName + "!=" + pair.first);
        double lossLeft = computeLoss(getTruthVector(left));
        double lossRight = computeLoss(getTruthVector(right));
        int totalRows = left->rows() + right->rows();
        double weightedLoss = (lossLeft * left->rows() / totalRows) +
                (lossRight * right->rows() / totalRows);
        if (weightedLoss < minLoss) {
            minLoss = weightedLoss;
            bestCol = col;
            splitValue = Generic::wrapPrimitive(pair.first);
            leftCount = left->rows();
            rightCount = right->rows();
        }
    }        
}

void DecisionTreeBase::findRowSplitDouble(
    int col,
    DataFrame*& trainData,
    int& bestCol,
    double& minLoss,
    int& leftCount, 
    int& rightCount, 
    Generic*& splitValue
) {
    trainData->sort(col);
    for (int row = 1; row < trainData->rows(); row++) {
        DataFrame* left = trainData->slice(0, row);
        DataFrame* right = trainData->slice(row, trainData->rows());
        double lossLeft = computeLoss(getTruthVector(left));
        double lossRight = computeLoss(getTruthVector(right));
        int totalRows = left->rows() + right->rows();
        double weightedLoss = (lossLeft * left->rows() / totalRows) + 
                (lossRight * right->rows() / totalRows);
        if (weightedLoss < minLoss) {
            minLoss = weightedLoss;
            bestCol = col;
            double leftValue = ((Double*)trainData->get(row - 1, bestCol))->data;
            double rightValue = ((Double*)trainData->get(row, bestCol))->data;
            double value = (leftValue + rightValue) / 2.0;
            splitValue = Generic::wrapPrimitive(to_string(value));
            leftCount = left->rows();
            rightCount = right->rows();
        }
    }  
}

void DecisionTreeBase::fit(DataFrame* trainData) {
    fit(trainData, root);
}

string DecisionTreeBase::getLossCriterion() const {
    return lossCriterion;
}

void DecisionTreeBase::printSpaces(int indents) {
    for (int i = 0; i < indents; i++) {
        cout << "            ";
    }
}

void DecisionTreeBase::printTree(DecisionNode* node, int indents) {
    if (node != nullptr) {
        printTree(node->right, indents + 1);
        
        if (node->splitValue != nullptr) {
            printSpaces(indents);
            string splitValue;
            if (node->splitValue->type() == DOUBLE) {
                splitValue = (node->splitValue)->getDouble();
            } else if (node->splitValue->type() == STRING) {
                splitValue = (node->splitValue)->getString();
            } else {
                throw invalid_argument("DATA TYPE NOT SUPPORTED");
            }
            cout << splitValue << endl;

            printSpaces(indents);
            cout << node->splitColumn << endl;
        }

        printSpaces(indents);
        printTruthVector(node->values);
        cout << endl;

        printSpaces(indents);
        cout << "splitLoss: " << node->splitLoss << endl;

        printSpaces(indents);
        cout << "sampleSize: " << node->sampleSize << endl << endl;
        
        printTree(node->left, indents + 1);
    }
}

void DecisionTreeBase::printTree() {
    printTree(root, 0);
}