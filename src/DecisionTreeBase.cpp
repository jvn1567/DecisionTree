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

void DecisionTreeBase::findSplit(DataFrame* testData, int& bestRow, int& bestCol,
        double minLoss) {
    for (int col = 0; col < testData->cols() - 1; col++) {
        GenericType type = testData->get(0, col)->type();
        //probably separate functions
        if (type == STRING) {
            unordered_map<string, int> counts;
            for (int row = 0; row < testData->rows(); row++) {
                counts[((String*)(testData->get(row, col)))->data]++;
            }
            for (auto pair : counts) {
                //shoves all rows with current string to the front of all other rows
                DataFrame* left = new DataFrame(new vector<vector<Generic*>>);
                DataFrame* right = new DataFrame(new vector<vector<Generic*>>);
                for (int row = 0; row < testData->rows(); row++) {
                    string current = ((String*)testData->get(row, col))->data;
                    if (current == pair.first) {
                        left->append(testData->get(row));
                    } else {
                        right->append(testData->get(row));
                    }
                }
                double lossLeft = computeLoss(getTruthVector(left));
                double lossRight = computeLoss(getTruthVector(right));
                int totalRows = left->rows() + right->rows();
                double weightedLoss = (lossLeft * left->rows() / totalRows) / 
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
            testData->sort(col);
            for (int row = 0; row < testData->rows(); row++) {
                //TODO the actual loss calculation
                DataFrame* left = testData->slice(0, row);
                DataFrame* right = testData->slice(row, testData->rows());
                double lossLeft = computeLoss(getTruthVector(left));
                double lossRight = computeLoss(getTruthVector(right));
                int totalRows = left->rows() + right->rows();
                double weightedLoss = (lossLeft * left->rows() / totalRows) / 
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

void DecisionTreeBase::fit(DataFrame* testData, DecisionNode*& node) {
    if (testData->rows() >= minSamplesSplit) {
        //split data
        //TODO calculate loss for root/current node
        double nodeLoss = computeLoss(getTruthVector(testData));
        int bestSplitRow = 0;
        int splitColumn; // If splittable, this should be populated by findSplit()
        findSplit(testData, bestSplitRow, splitColumn, nodeLoss);
        int rightCount = testData->rows() - bestSplitRow;
        bool splitable = bestSplitRow > minSamplesLeaf && rightCount > minSamplesLeaf;
        //make branch node
        if (splitable) {
            DataFrame* half1 = testData->slice(0, bestSplitRow + 1);
            DataFrame* half2 = testData->slice(bestSplitRow + 1, testData->rows());
            double left = ((Double*)half1->get(half1->rows(), splitColumn))->data;
            double right = ((Double*)half2->get(half2->rows(), splitColumn))->data;
            double splitValue = (left + right) / 2.0;
            node = new DecisionNode(testData->rows(), nodeLoss, nullptr /*TODO function*/,
                splitColumn, Generic::wrapPrimitive(to_string(splitValue)));
            fit(half1, node->left);
            fit(half2, node->right);
        //make leaf node
        } else {
            node = new DecisionNode(testData->rows(), nodeLoss, nullptr /*TODO*/);
        }
        delete testData;
        testData = nullptr;
    }
}

void DecisionTreeBase::fit(DataFrame* testData) {
    fit(testData, root);
}

string DecisionTreeBase::getLossCriterion() const {
    return lossCriterion;
}

void DecisionTreeBase::printTree(DecisionNode* node, int indents) {
    if (node->isLeaf()) {
        for (int i = 0; i < indents; i++) {
            cout << "    ";
        }
        cout << "TEMP PLACEHOLDER" << endl;
    } else {
        printTree(node->left, indents + 1);
        printTree(node->right, indents + 1);
    }
}

void DecisionTreeBase::printTree() {
    printTree(root, 0);
}