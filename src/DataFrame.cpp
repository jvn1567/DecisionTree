#include <sstream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include "DataFrame.h"
using namespace std;

DataFrame::DataFrame(string filename) {
    vector<vector<Generic*>>* dataset = new vector<vector<Generic*>>;
    vector<string> colNames;
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
    this->colNames = colNames;
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
    //merge until end of one half
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
    //push the rest of the unfinished half
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
            || (startIndex > endIndex)) {
        throw "INVALID START/END BOUNDARIES";
    }
    vector<vector<Generic*>>* vec = new vector<vector<Generic*>>;
    for (int row = startIndex; row < endIndex; row++) {
        vec->push_back((*data)[row]);
    }
    DataFrame* newDataFrame = new DataFrame(vec);
    newDataFrame->colNames = colNames;
    return newDataFrame;
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

Generic* DataFrame::parseFilterCondition(string condition) const {
    if (condition.length() == 0) {
        throw "NO CONDITION GIVEN";
    }
    //remove spaces
    int i = 0;
    while (i < condition.size()) {
        if (condition[i] != ' ') {
            condition.erase(condition.begin() + i);
        } else {
            i++;
        }
    }
    //find comparison operators
    int lessThan = condition.find('<');
    int greaterThan = condition.find('>');
    int equalTo = condition.find('=');
    bool noneFound = lessThan == string::npos && greaterThan == string::npos &&
            equalTo == string::npos;
    bool conflicting = greaterThan != string::npos && lessThan != string::npos;
    if (noneFound || conflicting) {
        throw "INVALID COMPARISON CONDITIONS";
    }
    //segment condition and grab
    if (equalTo != string::npos) {
        if (lessThan != string::npos) {
            /* have to find min/max since there's two chars, have to make sure
            they're next to each other, then for each of these six cases have to
            check the column name and throw an error and make sure the right side
            is a valid type, then throw another error if not. And then finally send
            back to be actually filtered.*/
        } else if (greaterThan != string::npos) {

        } else {

        }
    } else {
        if (lessThan != string::npos) {
            
        } else if (greaterThan != string::npos) {

        } else {

        }
    }
    /* return the type AND modify an integer so we know which column to compare
    AND return or modify some indicator of what kind of comparison we have to
    make*/
    return new String("TEMP"); //TEMP
}

//helper for filtering
DataFrame* DataFrame::filterMin(int col, Generic* min, bool inclusive) const {
    vector<vector<Generic*>>* vec = new vector<vector<Generic*>>;
    for (int row = 0; row < rows(); row++) {
        bool greaterMin = get(row, col) > min;
        bool equalMin = get(row, col) == min;
        if ((inclusive && (greaterMin || equalMin)) || (!inclusive && greaterMin)) {
            vec->push_back(get(row));
        }
    }
    return new DataFrame(vec);
}

//helper for filtering
DataFrame* DataFrame::filterMax(int col, Generic* max, bool inclusive) const {
    vector<vector<Generic*>>* vec = new vector<vector<Generic*>>;
    for (int row = 0; row < rows(); row++) {
        bool lessMax = get(row, col) < max;
        bool equalMax = get(row, col) == max;
        if ((inclusive && (lessMax || equalMax)) || (!inclusive && lessMax)) {
            vec->push_back(get(row));
        }
    }
    return new DataFrame(vec);
}

DataFrame* DataFrame::filter(int col, string comparator, string value) const {
    if (rows() == 0 || cols() == 0) {
        throw "EMPTY DATAFRAME, NOTHING TO FILTER";
    }
    Generic* generic = Generic::wrapPrimitive(value);
    if (generic->type() != get(0, col)->type()) {
        throw "THE PASSED VALUE MUST BE THE SAME TYPE AS THE COLUMN TO FILTER";
    }
    if (comparator == ">") {
        return filterMin(col, generic, false);
    } else if (comparator == "<") {
        return filterMax(col, generic, false);
    } else if (comparator == "==" || comparator == "=") {
        //mega cheater temp version
        DataFrame* partial = filterMin(col, generic, true);
        DataFrame* equalOnly = filterMax(col, generic, true);
        delete partial;
        return equalOnly;
    } else if (comparator == ">=" || comparator == "=>") {
        return filterMin(col, generic, true);
    } else if (comparator == "<=" || comparator == "=<") {
        return filterMax(col, generic, true);
    } else {
        throw "INVALID COMPARISON OPERATOR";
    }
}

/*DataFrame* filter(string condition) const {
    vector<vector<Generic*>>* vec = new vector<vector<Generic*>>;
    for (int row = 0; row < rows; row++) {
        Generic* currentValue = (data->get(row, colIndex));
        if (condition == "==") {
            if (currentValue->data == value) {
                vec->push_back((*data)[row]);
            }
        } else if (condition == ">=") {
            if (currentValue->data >= value) {
                vec->push_back((*data)[row]);
            }
        } else if (condition == "<=") {
            if (currentValue->data <= value) {
                vec->push_back((*data)[row]);
            }
        } else if (condition == "<") {
            if (currentValue->data < value) {
                vec->push_back((*data)[row]);
            }
        } else if (condition == ">") {
            if (currentValue->data > value) {
                vec->push_back((*data)[row]);
            }
        } else if (condition == "<") {
            if (currentValue->data < value) {
                vec->push_back((*data)[row]);
            }
        } else {
            throw "CONDITION " + condition + "NOT RECOGNIZED. TRY ==, >=, <=, >, <.";
        }
    }
    return new DataFrame(vec);
}*/

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

vector<string> DataFrame::getColNames() const {
    return colNames;
}

std::vector<GenericType> DataFrame::getColTypes() const {
    if (rows() == 0) {
        throw "DATAFRAM IS EMPTY";
    }
    vector<GenericType> colTypes;
    for (int col = 0; col < cols(); col++) {
        colTypes.push_back(get(0, col)->type());
    }
    return colTypes;
}

GenericType DataFrame::getColType(int colIndex) const {
    return getColTypes()[colIndex];
}

ostream& operator <<(ostream& out, const DataFrame& dataFrame) {
    vector<string> colNames = dataFrame.getColNames();
    vector<int> maxWidth;
    for (int i = 0; i < colNames.size(); i++) {
        maxWidth.push_back(colNames[i].length());
    }
    for (int col = 0; col < dataFrame.cols(); col++) {
        for (int row = 0; row < dataFrame.rows(); row++) {
            Generic* currentValue = dataFrame.get(row, col);
            int currentValueLength;
            if (currentValue->type() == DOUBLE) {
                currentValueLength = to_string(((Double*)currentValue)->data).length();
            } else {
                currentValueLength = (((String*)currentValue)->data).length();
            }
            if (currentValueLength > maxWidth[col]) {
                maxWidth[col] = currentValueLength;
            }
        }
    }
    for (int i = 0; i < maxWidth.size(); i++) {
        maxWidth[i] += 5;
    }

    for (int i = 0; i < colNames.size(); i++) {
        out << left << setw(maxWidth[i]) << colNames[i];
    }
    out << endl;

    for (int row = 0; row < dataFrame.rows(); row++) {
        for (int col = 0; col < dataFrame.cols(); col++) {
            Generic* generic = dataFrame.get(row, col);
            out << left << setw(maxWidth[col]);
            if (generic->type() == DOUBLE) {
                out << ((Double*)generic)->data;
            } else {
                out << ((String*)generic)->data;
            }
        }
        out << endl;
    }
    return out;
}

