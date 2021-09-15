#include "DataFrame.h"
using namespace std;

DataFrame::DataFrame(vector<vector<Generic*>>* data) {
    if (data == nullptr) {
        throw "INVALID DATA MATRIX";
    }
    this->data = data;
}

vector<vector<Generic*>>* DataFrame::sortMerge(vector<vector<Generic*>>* half1,
        vector<vector<Generic*>>* half2, int sortIndex) {
    vector<vector<Generic*>>* merged = new vector<vector<Generic*>>;
    int index1 = 0;
    int index2 = 0;
    while (index1 < half1->size() && index2 < half2->size()) {
        double value1 = ((Double*)(*half1)[index1][sortIndex])->data;
        double value2 = ((Double*)(*half2)[index2][sortIndex])->data;
        if (value1 < value2) {
            merged->push_back((*half1)[index1]);
            index1++;
        } else {
            merged->push_back((*half2)[index2]);
            index2++;
        }
    }
    while (index1 < half1->size()) {
        merged->push_back((*half1)[index1]);
        index1++;
    }
    while (index2 < half2->size()) {
        merged->push_back((*half2)[index2]);
        index2++;
    }
    delete half1;
    delete half2;
    return merged;
}

vector<vector<Generic*>>* DataFrame::sortSplit(vector<vector<Generic*>>* data, int sortIndex) {
    if (data->size() == 1) {
        return data;
    } else {
        vector<vector<Generic*>>* half1 = new vector<vector<Generic*>>;
        vector<vector<Generic*>>* half2 = new vector<vector<Generic*>>;
        for (int i = 0; i < data->size() / 2; i++) {
            half1->push_back((*data)[i]);
        }
        for (int i = data->size() / 2; i < data->size(); i++) {
            half2->push_back((*data)[i]);
        }
        half1 = sortSplit(half1, sortIndex);
        half2 = sortSplit(half2, sortIndex);
        return sortMerge(half1, half2, sortIndex);
    }
}

void DataFrame::sort(int sortIndex) {
    data = sortSplit(data, sortIndex);
}

DataFrame* DataFrame::slice(int startIndex, int endIndex) {
    vector<vector<Generic*>>* vec = new vector<vector<Generic*>>;
    for (int row = startIndex; row < endIndex; row++) {
        vec->push_back((*data)[row]);
    }
    return new DataFrame(vec);
}

void DataFrame::set(Generic* generic, int row, int col) {
    if (row >= rows() || row < 0 || col >= cols() || col < 0) {
        throw "LOCATION OUT OF BOUNDS";
    }
    (*data)[row][col] = generic;
}

Generic* DataFrame::get(int row, int col) const {
    if (row >= rows() || row < 0 || col >= cols() || col < 0) {
        throw "LOCATION OUT OF BOUNDS";
    }
    return (*data)[row][col];
}

int DataFrame::rows() const {
    return data->size();
}

int DataFrame::cols() const {
    if (data->size() == 0) {
        return 0;
    } else {
        return (*data)[0].size();
    }
}

ostream& operator <<(ostream& out, const DataFrame& DataFrame) {
    out << "{" << endl;
    for (int row = 0; row < DataFrame.rows(); row++) {
        for (int col = 0; col < DataFrame.cols(); col++) {
            Generic* generic = DataFrame.get(row, col);
            if (generic->type() == DOUBLE) {
                out << ((Double*)generic)->data;
            } else {
                out << ((String*)generic)->data;
            }
            out << " ";
        }
        out << endl;
    }
    out << "}" << endl;
    return out;
}