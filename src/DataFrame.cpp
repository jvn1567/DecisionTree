#include <sstream>
#include <fstream>
#include "DataFrame.h"
using namespace std;

DataFrame::DataFrame(string filename, vector<string>& colNames) {
    vector<vector<Generic*>>* dataset = new vector<vector<Generic*>>;
    ifstream input;
    input.open(filename);
    if (!input.good()) {
        throw "INVALID FILE";
    }
    string line;
    getline(input, line);
    //grab variables line
    istringstream inputstring(line);
    string variable;
    while (getline(inputstring, variable, ',')) {
        colNames.push_back(variable);
    }
    //grab remaining dataset
    while (getline(input, line)) {
        string data;
        vector<Generic*> row;
        istringstream inputstring(line);
        while (getline(inputstring, data, ',')) {
            Generic* genericData = Generic::wrapPrimitive(data);
            row.push_back(genericData);
        }
        dataset->push_back(row);
    }
    this->data = dataset;
}

DataFrame::DataFrame(vector<vector<Generic*>>* data) {
    if (data == nullptr) {
        throw "DATA MATRIX IS NULLPTR";
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
    if (sortIndex < 0 || sortIndex >= cols()) {
        throw "INDEX TO SORT OUT OF BOUNDS";
    }
    data = sortSplit(data, sortIndex);
}

DataFrame* DataFrame::slice(int startIndex, int endIndex) const {
    if (startIndex < 0 || endIndex < 0 || startIndex >= rows() || endIndex >= rows()
            || (startIndex >= endIndex)) {
        throw "INVALID START/END BOUNDARIES";
    }
    vector<vector<Generic*>>* vec = new vector<vector<Generic*>>;
    for (int row = startIndex; row < endIndex; row++) {
        vec->push_back((*data)[row]);
    }
    return new DataFrame(vec);
}

void DataFrame::append(vector<Generic*> row) {
    if (row.size() != cols()) {
        throw "ROW DOES NOT HAVE THE CORRECT COLUMN COUNT";
    }
    data->push_back(row);
}

void DataFrame::append(DataFrame* other) {
    if (other == nullptr) {
        throw "DATAFRAME TO APPEND DOES NOT EXIST";
    } else if (other->cols() != cols()) {
        throw "DATAFRAMES DO NOT HAVE MATCHING COLUMN COUNTS";
    }
    for (int row = 0; row < other->rows(); row++) {
        data->push_back(other->get(row));
    }
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

vector<Generic*> DataFrame::get(int row) const {
    if (row >= rows() || row < 0) {
        throw "LOCATION OUT OF BOUNDS";
    }
    return (*data)[row];
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

DataFrame::~DataFrame() {
    delete data;
}

double DataFrame::average(int col) const {
    if (rows() == 0 || cols() == 0) {
        throw "DATAFRAME IS EMPTY";
    } else if (col < 0 || col >= cols()) {
        throw "COLUMN IS OUT OF BOUNDS";
    } else if (get(0, col)->type() != DOUBLE) {
        throw "SPECIFIED COLUMN DOES NOT CONTAIN DOUBLE VALUES";
    }
    double total = 0.0;
    for (int row = 0; row < rows(); row++) {
        total += ((Double*)get(row, col))->data;
    }
    return total / rows();
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

