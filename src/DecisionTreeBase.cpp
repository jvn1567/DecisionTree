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

void DecisionTreeBase::findSplit(DataFrame* trainData, int& bestRow, int& bestCol,
        double minLoss) {
    for (int col = 0; col < trainData->cols() - 1; col++) {
        GenericType type = trainData->get(0, col)->type();
        //probably separate functions
        if (type == STRING) {
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
                    bestRow = pair.second; // i think??? this is the count for "this item"
                    bestCol = col;
                }
                delete left;
                delete right;
            }
        //ew
        } else {
            trainData->sort(col);
            for (int row = 1; row < trainData->rows(); row++) {
                //TODO the actual loss calculation
                DataFrame* left = trainData->slice(0, row);
                DataFrame* right = trainData->slice(row, trainData->rows());
                double lossLeft = computeLoss(getTruthVector(left));
                double lossRight = computeLoss(getTruthVector(right));
                int totalRows = left->rows() + right->rows();
                double weightedLoss = (lossLeft * left->rows() / totalRows) + 
                        (lossRight * right->rows() / totalRows);
                if (weightedLoss < minLoss) {
                    minLoss = weightedLoss;
                    bestRow = row;
                    bestCol = col;
                }
            }
        }
    }
}

void DecisionTreeBase::fit(DataFrame* trainData, DecisionNode*& node) {
    vector<double> truthVector = getTruthVector(trainData);
    double nodeLoss = computeLoss(truthVector);
    if (trainData->rows() >= minSamplesSplit) {
        //split data
        int bestSplitRow = 0;
        int splitColumn; // If splittable, this should be populated by findSplit()
        findSplit(trainData, bestSplitRow, splitColumn, nodeLoss);
        int rightCount = trainData->rows() - bestSplitRow;
        bool splitable = bestSplitRow > minSamplesLeaf && rightCount > minSamplesLeaf;
        //make branch node
        if (splitable) {
            trainData->sort(splitColumn);
            
            double left = ((Double*)trainData->get(bestSplitRow - 1, splitColumn))->data;
            double right = ((Double*)trainData->get(bestSplitRow, splitColumn))->data;

            DataFrame* half1 = trainData->slice(0, bestSplitRow);
            DataFrame* half2 = trainData->slice(bestSplitRow, trainData->rows());

            double splitValue = (left + right) / 2.0;
            
            node = new DecisionNode(nodeLoss, truthVector, splitColumn, 
                Generic::wrapPrimitive(to_string(splitValue)));
            fit(half1, node->left);
            fit(half2, node->right);
        //make leaf node
        } else {
            node = new DecisionNode(nodeLoss, truthVector);
        }
        // TODO: Causes free error
        // delete trainData;
        // trainData = nullptr;
    } else {
        node = new DecisionNode(nodeLoss, truthVector);
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
            cout << (node->splitValue)->getDouble() << endl;

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