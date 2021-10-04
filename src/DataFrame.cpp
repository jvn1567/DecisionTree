/**
 * @file DataFrame.cpp
 * @author John Nguyen (jvn1567@gmail.com)
 * @author Joshua Goldberg (joshgoldbergcode@gmail.com)
 * @brief This file implements the functions of DataFrame.h.
 * @version 0.1
 * @date 2021-10-01
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <sstream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <stdexcept>
#include <random>
#include "DataFrame.h"
using namespace std;

DataFrame::DataFrame() {
   data = new vector<vector<Generic*>>;
}

DataFrame::DataFrame(vector<string> colNames) {
   data = new vector<vector<Generic*>>;
   this->colNames = colNames;
}

DataFrame::DataFrame(string filename) {
    data = new vector<vector<Generic*>>;
    vector<string> colNames;
    ifstream input;
    input.open(filename);
    if (!input.good()) {
        throw invalid_argument("INVALID FILE");
    }
    string line;
    getline(input, line);
    // grab variables line
    istringstream inputstring(line);
    string variable;
    while (getline(inputstring, variable, ',')) {
        colNames.push_back(variable);
    }
    // grab remaining dataset
    while (getline(input, line)) {
        string value;
        vector<Generic*> row;
        istringstream inputstring(line);
        while (getline(inputstring, value, ',')) {
            Generic* genericData = Generic::wrapPrimitive(value);
            row.push_back(genericData);
        }
        data->push_back(row);
    }
    this->colNames = colNames;
}

DataFrame::DataFrame(vector<vector<Generic*>>* data) {
    if (data == nullptr) {
        throw invalid_argument("DATA MATRIX IS NULLPTR");
    }
    this->data = data;
}

vector<vector<Generic*>>* DataFrame::sortMerge(vector<vector<Generic*>>* half1,
        vector<vector<Generic*>>* half2, int sortIndex) {
    vector<vector<Generic*>>* merged = new vector<vector<Generic*>>;
    // merge until end of one half
    int index1 = 0;
    int index2 = 0;
    while (index1 < half1->size() && index2 < half2->size()) {
        double value1 = (*half1)[index1][sortIndex]->getDouble();
        double value2 = (*half2)[index2][sortIndex]->getDouble();
        if (value1 <= value2) {
            merged->push_back((*half1)[index1]);
            index1++;
        } else {
            merged->push_back((*half2)[index2]);
            index2++;
        }
    }
    // push the rest of the unfinished half
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
        throw out_of_range("INDEX TO SORT OUT OF BOUNDS");
    }
    data = sortSplit(data, sortIndex);
}

DataFrame* DataFrame::slice(int startIndex, int endIndex) const {
    if (startIndex < 0 || endIndex < 0 || startIndex > rows() || endIndex > rows()
            || (startIndex > endIndex)) {
        throw out_of_range("INVALID START/END BOUNDARIES");
    }
    DataFrame* newDataFrame = new DataFrame();
    for (int row = startIndex; row < endIndex; row++) {
        newDataFrame->appendRow(getRow(row));
    }
    newDataFrame->colNames = colNames;
    return newDataFrame;
}

void DataFrame::appendRow(vector<Generic*> row) {
    if (row.size() != cols() && rows() != 0 && cols() != 0) {
        throw invalid_argument("ROW DOES NOT HAVE THE CORRECT COLUMN COUNT");
    }
    data->push_back(row);
}

void DataFrame::appendRows(DataFrame* other) {
    if (other == nullptr) {
        throw invalid_argument("DATAFRAME TO APPEND DOES NOT EXIST");
    } else if (other->cols() != cols()) {
        throw invalid_argument("DATAFRAMES DO NOT HAVE MATCHING COLUMN COUNTS");
    }
    for (int row = 0; row < other->rows(); row++) {
        data->push_back(other->getRow(row));
    }
}

void DataFrame::set(Generic* generic, int row, int col) {
    if (row >= rows() || row < 0 || col >= cols() || col < 0) {
        throw out_of_range("SET LOCATION OUT OF BOUNDS");
    }
    (*data)[row][col] = generic;
}

Generic* DataFrame::get(int row, int col) const {
    if (row >= rows() || row < 0 || col >= cols() || col < 0) {
        throw out_of_range("GET LOCATION OUT OF BOUNDS");
    }
    return (*data)[row][col];
}

vector<Generic*> DataFrame::getRow(int row) const {
    if (row >= rows() || row < 0) {
        throw out_of_range("ROW GET LOCATION OUT OF BOUNDS");
    }
    return (*data)[row];
}

vector<string> DataFrame::getColNames() const {
    return colNames;
}

string DataFrame::getColName(int colIndex) const {
    if (colNames.size() == 0) {
        throw domain_error("NO COLUMN NAMES STORED");
    } else if (colIndex < 0 || colIndex >= colNames.size()) {
        throw out_of_range("COLUMN NAME LOCATION OUT OF BOUNDS");
    }
    return getColNames()[colIndex];
}

vector<GenericType> DataFrame::getColTypes() const {
    if (rows() == 0) {
        throw range_error("DATAFRAME IS EMPTY");
    }
    vector<GenericType> colTypes;
    for (int col = 0; col < cols(); col++) {
        colTypes.push_back(get(0, col)->type());
    }
    return colTypes;
}

GenericType DataFrame::getColType(int colIndex) const {
    vector<GenericType> types = getColTypes();
    if (types.size() <= colIndex || colIndex < 0) {
        throw out_of_range("COLUMN TYPE INDEX OUT OF BOUNDS");
    }
    return types[colIndex];
}

int DataFrame::rows() const {
    return data->size();
}

int DataFrame::cols() const {
    return colNames.size();
}

DataFrame::~DataFrame() {
    delete data;
}

DataFrame* DataFrame::filter(string condition) const {
    if (rows() == 0 || cols() == 0) {
        throw domain_error("EMPTY DATAFRAME, NOTHING TO FILTER");
    } else if (condition.length() == 0) {
        throw invalid_argument("NO CONDITION GIVEN");
    }
    // remove spaces
    int i = 0;
    while (i < condition.length()) {
        if (condition[i] == ' ') {
            condition.erase(condition.begin() + i);
        } else {
            i++;
        }
    }
    // condition index
    vector<string> comparators = {"<=", ">=", "<", ">", "==", "!="};
    string comparator;
    int comparatorIndex = string::npos;
    int loopIndex = -1;
    int size = comparators.size();
    while (loopIndex < size && comparatorIndex == string::npos) {
        loopIndex++;
        comparatorIndex = condition.find(comparators[loopIndex]);
    }
    if (comparatorIndex == string::npos) {
        throw invalid_argument("INVALID COMPARISON CONDITIONS");
    } else {
        comparator = comparators[loopIndex];
    }
    int colIndex = -1;
    string dataToCheck;
    // filter calls by operator
    if (comparator == "<") {
        Generic* genericData = parseCondition(colIndex, dataToCheck, 
                comparatorIndex, condition, false);
        return filterLessthan(colIndex, genericData, false);
    } else if (comparator == ">") {
        Generic* genericData = parseCondition(colIndex, dataToCheck, 
                comparatorIndex, condition, false);
        return filterGreaterThan(colIndex, genericData, false);
    } else if (comparator == ">=") {
        Generic* genericData = parseCondition(colIndex, dataToCheck, 
                comparatorIndex, condition, true);
        return filterGreaterThan(colIndex, genericData, true);
    } else if (comparator == "<=") {
        Generic* genericData = parseCondition(colIndex, dataToCheck, 
                comparatorIndex, condition, true);
        return filterLessthan(colIndex, genericData, true);
    } else if (comparator == "==") {
        Generic* genericData = parseCondition(colIndex, dataToCheck, 
                comparatorIndex, condition, true);
        return filterEquals(colIndex, genericData, true);
    } else { // comparator == "!=" is the only condition left
        Generic* genericData = parseCondition(colIndex, dataToCheck, 
                comparatorIndex, condition, true);
        return filterEquals(colIndex, genericData, false);
    }
}

Generic* DataFrame::parseCondition(
    int& colIndex, 
    std::string dataToCheck, 
    int operatorIndex,
    std::string condition,
    bool inclusive
) const {
    string colNameToCheck = condition.substr(0, operatorIndex);
    for (int i = 0; i < colNames.size(); i++) {
        if (colNames[i] == colNameToCheck) {
            colIndex = i;
        }
    }
    if (colIndex == -1) {
        throw invalid_argument("COLUMN NAME DOES NOT EXIST");
    }
    if (inclusive) {
        operatorIndex++;
    }
    // TODO: make this not scuffed
    if (operatorIndex + 1 >= condition.length()) {
        throw invalid_argument("COMPARISON VALUE NOT VALID");
    }
    dataToCheck = condition.substr(operatorIndex + 1, condition.length());
    Generic* genericData = Generic::wrapPrimitive(dataToCheck);
    if (genericData->type() != get(0, colIndex)->type()) {
        cout << genericData->type() << endl;
        cout << get(0, colIndex)->type() << endl;
        throw invalid_argument(
            "THE PASSED VALUE MUST BE THE SAME TYPE AS THE COLUMN TO FILTER"
        );
    }
    return genericData;
}

// Helper for filtering
DataFrame* DataFrame::filterGreaterThan(int col, Generic* min, bool inclusive) const {
    DataFrame* newDataFrame = new DataFrame();
    for (int row = 0; row < rows(); row++) {
        bool greaterMin = *get(row, col) > *min;
        bool equalMin = *get(row, col) == *min;
        if ((inclusive && (greaterMin || equalMin)) || (!inclusive && greaterMin)) {
            newDataFrame->appendRow(getRow(row));
        }
    }
    newDataFrame->colNames = colNames;
    return newDataFrame;
}

// Helper for filter
DataFrame* DataFrame::filterLessthan(int col, Generic* max, bool inclusive) const {
    DataFrame* newDataFrame = new DataFrame();
    for (int row = 0; row < rows(); row++) {
        bool lessMax = *get(row, col) < *max;
        bool equalMax = *get(row, col) == *max;
        if ((inclusive && (lessMax || equalMax)) || (!inclusive && lessMax)) {
            newDataFrame->appendRow(getRow(row));
        }
    }
    newDataFrame->colNames = colNames;
    return newDataFrame;
}

// Helper for filter
DataFrame* DataFrame::filterEquals(int col, Generic* value, bool equals) const {
    DataFrame* newDataFrame = new DataFrame();
    for (int row = 0; row < rows(); row++) {
        bool equal = *get(row, col) == *value;
        if ((equals && equal) || (!equals && !equal)) {
            newDataFrame->appendRow(getRow(row));
        }
    }
    newDataFrame->colNames = colNames;
    return newDataFrame;
}

void DataFrame::shuffle() {
    random_device random_dev;
    mt19937 generator(random_dev());
    std::shuffle(data->begin(), data->end(), generator);
}

// DataFrame* sampleN(int n) {
//     vector<int> indices = generateRandomIndices(n);
// }

// DataFrame* sampleFrac(double fraction) {

// }

double DataFrame::average(int col) const {
    if (rows() == 0 || cols() == 0) {
        throw domain_error("DATAFRAME IS EMPTY");
    } else if (col < 0 || col >= cols()) {
        throw out_of_range("COLUMN IS OUT OF BOUNDS");
    } else if (get(0, col)->type() != DOUBLE) {
        throw domain_error("SPECIFIED COLUMN DOES NOT CONTAIN DOUBLE VALUES");
    }
    double total = 0.0;
    for (int row = 0; row < rows(); row++) {
        total += ((Double*)get(row, col))->data;
    }
    return total / rows();
}

ostream& operator <<(ostream& out, const DataFrame& dataFrame) {
    // feature labels row
    vector<string> colNames = dataFrame.getColNames();
    colNames.insert(colNames.begin(), "Index");
    vector<int> maxWidth;
    for (int i = 0; i < colNames.size(); i++) {
        maxWidth.push_back(colNames[i].length());
    }
    for (int col = 0; col < dataFrame.cols(); col++) {
        for (int row = 0; row < dataFrame.rows(); row++) {
            Generic* currentValue = dataFrame.get(row, col);
            int currentValueLength;
            if (currentValue->type() == DOUBLE) {
                currentValueLength = to_string(currentValue->getDouble()).length();
            } else {
                currentValueLength = (currentValue->getString()).length();
            }
            if (currentValueLength > maxWidth[col + 1]) {
                maxWidth[col + 1] = currentValueLength;
            }
        }
    }
    // print spacing
    for (int i = 0; i < maxWidth.size(); i++) {
        maxWidth[i] += 5;
    }
    for (int i = 0; i < colNames.size(); i++) {
        out << left << setw(maxWidth[i]) << colNames[i];
    }
    out << endl;
    // data matrix print
    for (int row = 0; row < dataFrame.rows(); row++) {
        out << left << setw(maxWidth[0]) << row;
        for (int col = 0; col < dataFrame.cols(); col++) {
            Generic* generic = dataFrame.get(row, col);
            out << left << setw(maxWidth[col + 1]) << *generic;
        }
        out << endl;
    }
    return out;
}

ostream& operator <<(ostream& out, const DataFrame* dataFrame) {
    out << *dataFrame;
    return out;
}

