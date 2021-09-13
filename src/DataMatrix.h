#ifndef _DATAMATRIX_H
#define _DATAMATRIX_H

#include <vector>
#include <iostream>
#include "GenericTypeWrapper.h"

class DataMatrix {
private:
    std::vector<std::vector<Generic*>>* data;
    std::vector<std::vector<Generic*>>* sortMerge(
        std::vector<std::vector<Generic*>>* half1,
        std::vector<std::vector<Generic*>>* half2,
        int sortIndex);
    std::vector<std::vector<Generic*>>* sortSplit(
        std::vector<std::vector<Generic*>>* data,
        int sortIndex);
    void deleteMatrix(std::vector<std::vector<Generic*>>*& data);
public:
    DataMatrix(std::vector<std::vector<Generic*>>* data);
    void sort(int sortindex);
    void set(Generic* generic, int row, int col);
    Generic* get(int row, int col) const;
    int rows() const;
    int cols() const;
};
std::ostream& operator <<(std::ostream& out, const DataMatrix& data);

#endif