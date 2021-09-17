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

//we need a vector of classes
vector<int> DecisionTreeBase::countClasses(DataFrame* testData) {
    unordered_map<string, int> classes; //TEMP PLACEHOLDER
    vector<int> counts;
    for (int i = 0; i < classes.size(); i++) {
        counts.push_back(0);
    }
    for (int row = 0; row < testData->rows(); row++) {
        //assumes class is the last column
        string classname = ((String*)testData->get(row, testData->cols()))->data;
        counts[classes[classname]]++;
    }
    return counts;
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
                DataFrame* thisItemFirst = new DataFrame(new vector<vector<Generic*>>);
                DataFrame* allOthers = new DataFrame(new vector<vector<Generic*>>);
                for (int row = 0; row < testData->rows(); row++) {
                    string current = ((String*)testData->get(row, col))->data;
                    if (current == pair.first) {
                        thisItemFirst->append(testData->get(row));
                    } else {
                        allOthers->append(testData->get(row));
                    }
                    thisItemFirst->append(allOthers);
                    double loss = calculateLoss();
                    if (loss < minLoss) {
                        minLoss = loss;
                        bestRow = pair.second; // i think??? this is the count for "this item"
                        bestCol = col;
                    }
                }
                delete thisItemFirst;
                delete allOthers;
            }
        //ew
        } else {
            testData->sort(col);
            for (int row = 0; row < testData->rows(); row++) {
                //TODO the actual loss calculation
                double loss = calculateLoss();
                if (loss < minLoss) {
                    minLoss = loss;
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
        double nodeLoss = calculateLoss();
        int bestSplitRow = 0;
        int bestFeatureCol = 0;
        findSplit(testData, bestSplitRow, bestFeatureCol, nodeLoss);
        int rightCount = testData->rows() - bestSplitRow;
        bool splitable = bestSplitRow < minSamplesLeaf || rightCount < minSamplesLeaf;
        //make branch node
        if (splitable) {
            DataFrame* half1 = testData->slice(0, bestSplitRow + 1);
            DataFrame* half2 = testData->slice(bestSplitRow + 1, testData->rows());
            double left = ((Double*)half1->get(half1->rows(), bestFeatureCol))->data;
            double right = ((Double*)half2->get(half2->rows(), bestFeatureCol))->data;
            double average = (left + right) / 2.0;
            node = new DecisionNode(testData->rows(), nodeLoss, nullptr /*TODO function*/,
                bestFeatureCol, average);
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

void DecisionTreeBase::fit(vector<vector<Generic*>>* testData) {
    fit(new DataFrame(testData));
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