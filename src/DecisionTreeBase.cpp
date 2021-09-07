#include <iostream>
#include "DecisionTreeBase.h"

DecisionTreeBase::DecisionTreeBase() {

}

void DecisionTreeBase::fit() {

}

int DecisionTreeBase::predict() {
    return 0;
}

double DecisionTreeBase::computeLoss() {
    return 0;
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