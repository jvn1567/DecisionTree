#ifndef _DataFrame_H
#define _DataFrame_H

#include <vector>
#include <iostream>
#include <unordered_set>
#include "GenericTypeWrapper.h"

class DataFrame {
private:
    std::vector<std::vector<Generic*>>* data;
    std::vector<std::string> colNames;
    std::vector<std::vector<Generic*>>* sortMerge(
        std::vector<std::vector<Generic*>>* half1,
        std::vector<std::vector<Generic*>>* half2,
        int sortIndex);
    std::vector<std::vector<Generic*>>* sortSplit(
        std::vector<std::vector<Generic*>>* data,
        int sortIndex);
    void deleteMatrix(std::vector<std::vector<Generic*>>*& data);
    DataFrame* filterGreaterThan(int col, Generic* min, bool inclusive) const;
    DataFrame* filterLessthan(int col, Generic* max, bool inclusive) const;
    DataFrame* filterEquals(int col, Generic* value, bool equals) const;
    Generic* parseCondition(
        int& colIndex, 
        std::string dataToCheck, 
        int operatorIndex,
        std::string condition,
        bool inclusive
    ) const;
public:
    DataFrame(std::string filename);
    DataFrame(std::vector<std::vector<Generic*>>* data);
    void sort(int sortindex);
    DataFrame* slice(int startIndex, int endIndex) const;
    DataFrame* filter(std::string condition) const;
    void append(std::vector<Generic*> row);
    void append(DataFrame* other);
    void set(Generic* generic, int row, int col);
    Generic* get(int row, int col) const;
    std::vector<std::string> getColNames() const;
    std::vector<GenericType> getColTypes() const;
    GenericType getColType(int colIndex) const;
    std::vector<Generic*> get(int row) const;
    int rows() const;
    int cols() const;
    double average(int col) const;
    ~DataFrame();
};
std::ostream& operator <<(std::ostream& out, const DataFrame& data);

#endif