/**
 * @file DecisionNode.h
 * @author John Nguyen (jvn1567@gmail.com)
 * @author Joshua Goldberg (joshgoldbergcode@gmail.com)
 * @brief DataFrame is a data class containing a vector of observations 
 * (one per row) and their characteristics (in each column). The DataFrame also 
 * contains an additional vector for the names of each characteristic/column.
 * @version 0.1
 * @date 2021-10-01
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef _DataFrame_H
#define _DataFrame_H

#include <vector>
#include <iostream>
#include <unordered_set>
#include "GenericTypeWrapper.h"

/**
 * @brief The DataFrame is a matrix where each row corresponds to a data entry
 * and each column of that row representing a characteristic of that data entry.
 * 
 */
class DataFrame {
private:
    std::vector<std::vector<Generic*>>* data;
    std::vector<std::string> colNames;
    /**
     * Merges two 2D vectors into a sorted vector containing all the values
     * in the original two vectors. Used for merge sorting.
     */
    std::vector<std::vector<Generic*>>* sortMerge(
        std::vector<std::vector<Generic*>>* half1,
        std::vector<std::vector<Generic*>>* half2,
        int sortIndex);

    /**
     * Performs a merge sort on the passed in 2D vector.
     */
    std::vector<std::vector<Generic*>>* sortSplit(
        std::vector<std::vector<Generic*>>* data,
        int sortIndex);

    /**
     * Deletes a pointer to a 2D vector and assigns nullptr to it.
     */
    void deleteFrame(std::vector<std::vector<Generic*>>*& data);

    /**
     * Returns a new DataFrame* containing all rows where the stored Generic*
     * at the specified column is greater than the passed-in Generic*. Passing in
     * true for inclusive will store all rows with a greater than or equal value
     * in the returned DataFrame*.
     */
    DataFrame* filterGreaterThan(int col, Generic* min, bool inclusive) const;

    /**
     * Returns a new DataFrame* containing all rows where the stored Generic*
     * at the specified column is less than the passed-in Generic*. Passing in
     * true for inclusive will store all rows with a less than or equal value
     * in the returned DataFrame*.
     */
    DataFrame* filterLessthan(int col, Generic* max, bool inclusive) const;

    /**
     * Returns a new DataFrame* containing all rows where the stored Generic*
     * at the specified column is equal to the passed-in Generic*. Passing false
     * will filter Generic* values not equal into the returned DataFrame*.
     */
    DataFrame* filterEquals(int col, Generic* value, bool equals = true) const;

    /**
     * Helper for the public filter method. Finds the index of the column
     * specified by name in the original condition and assigns it to colIndex.
     */
    Generic* parseCondition(
        int& colIndex, 
        std::string dataToCheck, 
        int operatorIndex,
        std::string condition,
        bool inclusive
    ) const;

public:
    /**
     * @brief Constructs and empty DataFrame with no column names.
     * 
     */
    DataFrame();

    /**
     * @brief Constructs an empty DataFrame with the specified column names.
     * 
     * @param colNames a vector containing the names of the DataFrame's columns
     */
    DataFrame(std::vector<std::string> colNames);

    /**
     * @brief Constructs a DataFrame from a file. The format must be a comma
     * separated list, with each row corresponding to a data entry, or DataFrame
     * row. The first row contains the column names.
     * 
     * @param filename the name of the file to read
     * @pre assumes proper file format
     */
    DataFrame(std::string filename);

    /**
     * @brief Constructs a DataFrame with no column names containing the passed-in
     * data in a 2D vector.
     * 
     * @param data the DataFrame data
     * @throw invalid_argument if passed a nullptr
     */
    DataFrame(std::vector<std::vector<Generic*>>* data);

    /**
     * @brief Sorts this DataFrame on the specified column index.
     * 
     * @param sortindex the column index to sort on
     * @throw out_of_range if the passed-in column is negative or greater
     * than the maximum column index
     */
    void sort(int sortindex);

    /**
     * @brief Returns a new DataFrame* containing all rows of this DataFrame,
     * from the start index to end index, exclusive.
     * 
     * @param startIndex the starting row index
     * @param endIndex the ending row index, exclusive
     * @return DataFrame* containing the specified rows of this DataFrame
     * @throw out_of_range if start index is greater than end index, or
     * either index is negative or greater than maximum row index
     */
    DataFrame* slice(int startIndex, int endIndex) const;

    /**
     * @brief Returns a new DataFrame* containing all rows where the specified
     * condition is met. The format is "COLUMN_NAME < VALUE", where < can be
     * any comparator operator (<, <=, >, >=, ==, !=).
     * 
     * @param condition the condition to filter
     * @return DataFrame* a new DataFrame containing the filtered rows
     * @pre assumes the passed in condition has a valid operator, valid column
     * name, and valid condition of the same type (double, string, etc) as the
     * Generic* values stored in the DataFrame's column
     * @throw domain_error if the DataFrame is empty
     * @throw invalid_argument if an invalid condition is given
     */
    DataFrame* filter(std::string condition) const;

    /**
     * @brief Appends a row to the DataFrame.
     * 
     * @param row a vector to append as a row to the DataFrame data.
     * @pre assumes the passed-in row contains the same columns as this
     * DataFrame, and contains valid data
     * @throw invalid_argument if the column count for this DataFrame and the
     * the row to append are not the same
     */
    void appendRow(std::vector<Generic*> row);

    /**
     * @brief Appends all rows of the passed-in DataFrame* to the end of this
     * DataFrame.
     * 
     * @param other the DataFrame to append to this one
     * @throw invalid_argument if passed a nullptr or the DataFrames do not
     * contain the same number of columns.
     */
    void appendRows(DataFrame* other);

    /**
     * @brief Sets the value at the passed-in row and column.
     * 
     * @param generic the value to set
     * @param row the row to set the value
     * @param col the column to set the value
     * @pre assumes the passed-in value is the same type as all other values
     * in the DataFrame's column
     * @throw out_of_range if the row or column is out of bounds
     */
    void set(Generic* generic, int row, int col);

    /**
     * @brief Returns the value at the passed-in row and column.
     * 
     * @param row the row
     * @param col the column
     * @return Generic* the value at the passed-in row and column
     * @throw out_of_range if the row or column is out of bounds
     */
    Generic* get(int row, int col) const;

    /**
     * @brief Returns row at the specified index.
     * 
     * @param row the index of the row
     * @return std::vector<Generic*> the row
     * @throw out_of_range if the row is out of bounds
     */
    std::vector<Generic*> getRow(int row) const;
    
    /**
     * @brief Shuffles dataframe with a C++ std uniform distribution random 
     * number generator.
     * 
     * @return DataFrame* 
     */
    void shuffle();
    DataFrame* sampleN(int n);
    DataFrame* sampleFrac(double fraction);

    // Most efficient way to do this is to create and indices member variable
    // And check for indices
    DataFrame* notIN(DataFrame* dataFrame2);

    /**
     * @brief Returns the column name at the specified column index.
     * 
     * @param colIndex the index of the column
     * @return std::string the column's name
     * @throw domain_error if no column names are stored for this DataFrame
     * @throw out_of_range if the column index is out of bounds
     */
    std::string getColName(int colIndex) const;

    /**
     * @brief Returns a vector containing all column names.
     * 
     * @return std::vector<std::string> the column names
     */
    std::vector<std::string> getColNames() const;

    /**
     * @brief Returns the GenericType of data on the specified column.
     * 
     * @param colIndex the column index
     * @return GenericType the type stored at the column
     * @pre assumes the entire column stores the same data type
     * @throws range_error if DataFrame is empty
     * @throws out_of_range if column index is out of bounds
     */
    GenericType getColType(int colIndex) const;

    /**
     * @brief Returns a vector containing the GenericType of data in each column.
     * 
     * @return std::vector<GenericType> the column types
     * @pre assumes each column of the DataFrame contains data of a single type
     * @throws range_error if DataFrame is empty
     */
    std::vector<GenericType> getColTypes() const;

    /**
     * @brief Counts the number of rows of this DataFrame.
     * 
     * @return int the row count
     */
    int rows() const;

    /**
     * @brief Counts the number of columns of this DataFrame.
     * 
     * @return int the column count
     * @pre assumes every row contains the same number of columns
     */
    int cols() const;

    /**
     * @brief Returns the average of all values in the specified row.
     * 
     * @param col the index of the column
     * @return double the average
     * @pre the column must contain numeric data
     * @throw domain_error if DataFrame is empty
     * @throw out_of_range if column index is out of bounds
     * @throw domain_error if the column does not contain double values
     */
    double average(int col) const;

    /**
     * @brief Destructor, deletes the outer vector of DataFrame.
     * 
     */
    ~DataFrame();
};

/**
 * @brief Overloads the output operator. DataFrame output contains a table with
 * column name labels at the top and row count on the left.
 * 
 * @param out the output stream
 * @param data the DataFrame to output
 * @return std::ostream& the output stream with the output data
 */
std::ostream& operator <<(std::ostream& out, const DataFrame& data);
std::ostream& operator <<(std::ostream& out, const DataFrame* data);

#endif